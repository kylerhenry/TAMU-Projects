#include "common.h"
#include "BoundedBuffer.h"
#include "Histogram.h"
#include "common.h"
#include "HistogramCollection.h"
#include "FIFOreqchannel.h"
using namespace std;


class patient_thread_args{
public:
   /*put all the arguments for the patient threads */
	//FIFORequestChannel* patientChan;
	int numReq;
	int patientNum;
	BoundedBuffer* bb;
	bool fMode;
	string fName;
	__int64_t size;

	patient_thread_args(int n, int p, BoundedBuffer* _bb, bool _fMode, string _fName, __int64_t length) {
		this->numReq = n;
		this->patientNum = p;
		this->bb = _bb;
		this->fMode = _fMode;
		this->fName = _fName;
		this->size = length;
	}
};

class worker_thread_args{
public:
   /*put all the arguments for the wroker threads */
	FIFORequestChannel* workerChan;
	BoundedBuffer* bb;
	vector<Histogram*>* hists;
	int threadNum;	//used for debugging only

	worker_thread_args(FIFORequestChannel* chan, BoundedBuffer* _bb, vector<Histogram*>* _hists, int num) {
		this->workerChan = chan;
		this->bb = _bb;
		this->hists = _hists;
		this->threadNum = num;
	}
};

void *patient_thread_function(void *arg)
{
	/* What will the patient threads do? */
	patient_thread_args* patientArgs = (patient_thread_args*)arg;
	
	//datapoint mode
	if (!patientArgs->fMode) {
		for (int i = 0; i < patientArgs->numReq; i++) {
			//cout << "inserting request for patient " << patientArgs->patientNum << endl;
			datamsg* rawmsg = new datamsg(patientArgs->patientNum, i*.004, 1);
			char* msg = reinterpret_cast<char*>(rawmsg);

			//write message to buffer
			patientArgs->bb->push(msg);
			//delete rawmsg;
		}
	}
	//file mode
	else {
		
	}
}

void *worker_thread_function(void *arg)
{
    /*
		Functionality of the worker threads	
    */
	worker_thread_args* workerArgs = (worker_thread_args*)arg;
	//cout << "Thread number " << workerArgs->threadNum << " successfully created." << endl;
	while (true) {
		//get top message from buffer
		char* FIFOmsg = workerArgs->bb->pop();
		MESSAGE_TYPE m = *(MESSAGE_TYPE *)FIFOmsg;
		//cout << "Thread " << workerArgs->threadNum << " successfully popped a " << m << endl;
		

		if (m == DATA_MSG) {
			//get person the data is for so we can update the histogram later
			datamsg* msgData = (datamsg*)FIFOmsg;
			int person = msgData->person;
			//cout << "popped data for person " << person << endl;

			//send message to server and get data back
			int len = workerArgs->workerChan->cwrite(FIFOmsg, sizeof(datamsg));
			char* reply = workerArgs->workerChan->cread(&len);
			double ecgData = *(double*)reply;
			//cout << "Recieved data from server: " << ecgData << " for person " << person << endl;

			//update histogram
			workerArgs->hists->at(person - 1)->update(ecgData);
		}
		else if (m == QUIT_MSG) {
			//cout << "---------->quit message recieved" << endl;

			//must send quit message to close the channel
			workerArgs->workerChan->cwrite(FIFOmsg, sizeof(quitmsg));
			break;
		}
	}
	//cout << "Worker thread loop stopping" << endl;
}



int main(int argc, char *argv[])
{
	int opt;
	int n = 250;			//default number of requests per "patient"
	int p = 10;				//number of patients [1,15]
	int w = 100;			//default number of worker threads
	int b = 50; 			//default capacity of the request buffer, you should change this default
	int m = MAX_MESSAGE; 	//default capacity of the file buffer
	bool f = false;			//mode specifier
	string fName = "OutFile.bin";		//file name for file mode
	while ((opt = getopt(argc, argv, "n:p:w:b:f:m:")) != -1) {
		switch (opt) {
		case 'n':
			n = atoi(optarg);
			break;
		case 'p':
			if(atoi(optarg) > 0 && atoi(optarg) <= 15)
				p = atoi(optarg);
			else {
				fprintf(stderr, "Specified p is too large, or less than zero.\n");
			}
			break;
		case 'w':
			w = atoi(optarg);
			break;
		case 'b':
			b = atoi(optarg);
			break;
		case 'f':
			f = true;
			fName = optarg;
			p = 1;
			break;
		case 'm':
			if (atoi(optarg) <= MAX_MESSAGE) {
				m = atoi(optarg);
				b = m;
			}
			else {
				fprintf(stderr, "Specified m is too large, or less than zero.\n");
			}
			break;
		case '?':
			if (optopt == 'n' || optopt == 'p' || optopt == 'w' || optopt == 'b' || optopt == 'f' || optopt == 'm') {
				fprintf(stderr, "Option %c needs an argument\n", optopt);
			}
			else {
				fprintf(stderr, "Unknown option %c. \n", optopt);
			}
			break;
		default:
			break;
		}
	}
    srand(time_t(NULL));
    
    int pid = fork();
	if (pid == -1) {
		//error
		cout << "Couldnt create fork." << endl;
		exit(EXIT_FAILURE);
	}
    else if (pid == 0){
		// modify this to pass along m
		char* args[] = { "dataserver", (char*)to_string(m).c_str() , (char*)NULL };
        execvp ("./dataserver", args);
    }

    
	FIFORequestChannel* chan = new FIFORequestChannel("control", FIFORequestChannel::CLIENT_SIDE);
    BoundedBuffer request_buffer(b);
	HistogramCollection hc;
	
    struct timeval start, end;
    gettimeofday (&start, 0);




    /* Start all threads here */
	
	//make patient threads and histograms
	cout << "Beginning patient thread and histogram creation..." << endl;
	vector<Histogram*> hists;
	pthread_t pthreads[p];
	if (!f) {
		for (int i = 0; i < p; i++) {
			//threads
			Histogram* hist = new Histogram(75, -3, 3);
			hists.push_back(hist);
			patient_thread_args* pa = new patient_thread_args(n, i + 1, &request_buffer, f, fName, 0);
			pthread_create(&pthreads[i], 0, patient_thread_function, pa);
		}
	}
	else {
		//construct the file size request
		filemsg* rawFileSizeMsg = new filemsg(0, 0);
		char* fileSizeMsg = reinterpret_cast<char*>(rawFileSizeMsg);
		char fileName[] = "largefile.csv";
		char* sizeBuff = new char[sizeof(fileName) + sizeof(filemsg) + 1];
		sizeBuff[0] = *fileSizeMsg;
		for (int i = 0; i < sizeof(fileName); i++) {
			sizeBuff[sizeof(filemsg) + i] = fileName[i];
		}
		delete(rawFileSizeMsg);
		//get the size of the file from server
		int len = chan->cwrite(sizeBuff, sizeof(filemsg) + sizeof(fileName) + 1);
		char* sizeReply = chan->cread(&len);
		__int64_t length = *(__int64_t*)sizeReply;
	}
	cout << "Patient threads created successfully." << endl << endl;

	//create worker threads and make their channels
	cout << "Beginning worker thread creation..." << endl;
	pthread_t wthreads[w];
	//vector<FIFORequestChannel*> workerChannels;
	for (int i = 0; i < w; i++) {
		//channels
		channelmsg* msg = new channelmsg();
		char* chanRequest = reinterpret_cast<char*>(msg);
		int u = chan->cwrite(chanRequest, sizeof(NEWCHANNEL_MSG));
		char* channelVal = chan->cread(&u);
		string channelName(channelVal);
		FIFORequestChannel *newWorkerChannel = new FIFORequestChannel(channelName, FIFORequestChannel::CLIENT_SIDE);
		//workerChannels.push_back(newWorkerChannel);
		//threads
		worker_thread_args* wa = new worker_thread_args(newWorkerChannel, &request_buffer, &hists, i);
		pthread_create(&wthreads[i], 0, worker_thread_function, wa);
	}
	cout << "Worker threads created successfully." << endl << endl;





	/* Join all threads here */

	/*clean the patient threads and their channels
	has to be done defore the workers as this will signal when every patient is done*/
	cout << "Beginning removal of patient threads..." << endl;
	//pthread_join waits for all threads to finish
	for (int i = 0; i < p; i++) {
		pthread_join(pthreads[i], 0);
	}
	cout << "Finished patient thread deletion successfully." << endl << endl;
	
	//push w quit messages to buffer to end worker thread loops and channels
	//cout << "Number of worker threads: " << w << endl;
	for (int q = 0; q < w; q++) {
		//cout << "pushing quit msg " << q + 1 << endl;
		quitmsg* quit = new quitmsg();
		char* quitRequest = reinterpret_cast<char*>(quit);
		request_buffer.push(quitRequest);
	}

	//clean worker threads and their channels
	cout << "Beginning removal of worker threads and worker channels..." << endl;
	//pthread_join waits for all threads to finish
	for (int i = 0; i < w; i++) {
		//cout << "joining thread " << i << endl;
		int err = pthread_join(wthreads[i], 0);
		if (err) {
			cout << "join failed on thread " << i << endl;
			return 1;
		}
		//delete workerChannels.at(0);
		//workerChannels.erase(workerChannels.begin());
	}
	cout << "Finished worker thread deletion successfully." << endl << endl;

	//now we can add all the aquired data to the histogram collection
	for (int i = 0; i < hists.size(); i++) {
		hc.add(hists.at(i));
	}
	
	

    gettimeofday (&end, 0);
	hc.print ();
    int secs = (end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)/(int) 1e6;
    int usecs = (int)(end.tv_sec * 1e6 + end.tv_usec - start.tv_sec * 1e6 - start.tv_usec)%((int) 1e6);
    cout << "Took " << secs << " seconds and " << usecs << " micor seconds" << endl;

    MESSAGE_TYPE q = QUIT_MSG;
    chan->cwrite ((char *) &q, sizeof (MESSAGE_TYPE));
    cout << "All Done!!!" << endl;
    delete chan;
    
}

/*
    Tanzir Ahmed
    Department of Computer Science & Engineering
    Texas A&M University
    Date  : 2/8/19
 */
#include "common.h"
#include "FIFOreqchannel.h"

using namespace std;


int main(int argc, char *argv[]){
    int n = 100;    // default number of requests per "patient"
	int p = 15;		// number of patients
    srand(time_t(NULL));
    FIFORequestChannel chan ("control", FIFORequestChannel::CLIENT_SIDE);
	
	/////////////////	Requesting data points (pt. 1)	///////////////////
	//ofstream dataPointFile;
	//dataPointFile.open("received/x1.csv");
	//double ecg1temp;
	//double ecg2temp;
	//
	//cout << "Beginning data point copy...this will take a while..." << endl;
	//struct timeval begin1, end1;
	//gettimeofday(&begin1, NULL);

	//for (double time = 0.00; time <= 59.996; time += .004) {//one loop per time stamp
	//	for (int ecg = 1; ecg <= 2; ecg++) {				//one loop per ecg
	//		datamsg* rawmsg = new datamsg(1, time, ecg);
	//		char* msg = reinterpret_cast<char*>(rawmsg);

	//		int len = chan.cwrite(msg, sizeof(datamsg));	//write to channel to request information
	//		char* reply = chan.cread(&len);					//read from channel to get the information
	//		if (ecg == 1) {									//assign replies to appropriate temp value
	//			ecg1temp = *(double*)reply;
	//		}
	//		else {
	//			ecg2temp = *(double*)reply;
	//		}
	//	}
	//	//write them to new file
	//	dataPointFile << time << "," << ecg1temp << "," << ecg2temp << "\n";
	//}
	//dataPointFile.close();
	//gettimeofday(&end1, NULL);
	//unsigned int sec1 = end1.tv_sec - begin1.tv_sec;
	//cout << "Done. Time taken for data point copy: " << sec1 << "sec, " << end1.tv_usec << "usec" << endl;

	/////////////////	Requesting text file (pt. 2)	///////////////////
	
	//cout << "Beginning file copy..." << endl;
	//struct timeval begin2, end2;
	//gettimeofday(&begin2, NULL);

	////construct the file size request
	//filemsg* rawFileSizeMsg = new filemsg(0, 0);
	//char* fileSizeMsg = reinterpret_cast<char*>(rawFileSizeMsg);
	//char fileName[] = "1.csv";
	//char* sizeBuff = new char[sizeof(fileName) + sizeof(filemsg) + 1];
	//sizeBuff[0] = *fileSizeMsg;
	//for (int i = 0; i < sizeof(fileName); i++) {
	//	sizeBuff[sizeof(filemsg) + i] = fileName[i];
	//}

	////get the size of the file from server
	//int len = chan.cwrite(sizeBuff, sizeof(filemsg) + sizeof(fileName) + 1);
	//char* sizeReply = chan.cread(&len);
	//__int64_t length = *(__int64_t*)sizeReply;
	////cout << length << endl;

	////now send the actual requests and write to new file
	//ofstream fileCopy;
	//fileCopy.open("received/y1.csv");

	//int numRequests = (length / MAX_MESSAGE);	//number of requests needed to get whole file (minus the added bit at the end that doesnt evenly round)
	//int remainingBytes = length % MAX_MESSAGE;

	//for (int i = 0; i <= numRequests; i ++) {
	//	filemsg* rawFileRequest;
	//	if (i*MAX_MESSAGE + remainingBytes >= length) {
	//		rawFileRequest = new filemsg(length-remainingBytes, remainingBytes);
	//	}
	//	else {
	//		rawFileRequest = new filemsg(i*MAX_MESSAGE, MAX_MESSAGE);
	//	}
	//	char* fileRequest = reinterpret_cast<char*>(rawFileRequest);

	//	int len = chan.cwrite(fileRequest, sizeof(datamsg));
	//	char* reply = chan.cread(&len);
	//	fileCopy.write(reply, len);
	//}
	//fileCopy.close();
	//gettimeofday(&end2, NULL);
	//unsigned int sec2 = end2.tv_sec - begin2.tv_sec;
	//cout << "Done. Time taken for data point copy: " << sec2 << "sec, " << end2.tv_usec << "usec" << endl;

	/////////////////	Requesting binary file (pt. 3)	///////////////////

	//cout << "Beginning binary file copy..." << endl;
	//struct timeval begin3, end3;
	//gettimeofday(&begin3, NULL);

	////construct the file size request
	//filemsg* rawFileSizeMsg = new filemsg(0, 0);
	//char* fileSizeMsg = reinterpret_cast<char*>(rawFileSizeMsg);
	//char fileName[] = "largefile.csv";
	//char* sizeBuff = new char[sizeof(fileName) + sizeof(filemsg) + 1];
	//sizeBuff[0] = *fileSizeMsg;
	//for (int i = 0; i < sizeof(fileName); i++) {
	//	sizeBuff[sizeof(filemsg) + i] = fileName[i];
	//}
	//delete(rawFileSizeMsg);
	////get the size of the file from server
	//int len = chan.cwrite(sizeBuff, sizeof(filemsg) + sizeof(fileName) + 1);
	//char* sizeReply = chan.cread(&len);
	//__int64_t length = *(__int64_t*)sizeReply;
	////cout << length << endl;

	////now send the actual requests and write to new file
	//ofstream fileCopy;
	//string file = "received/large.csv";
	//fileCopy.open(file);
	//FILE* fp = fopen(file.c_str(), "ab");	//open a binary stream to write to

	//int numRequests = (length / MAX_MESSAGE);	//number of requests needed to get whole file (minus the added bit at the end that doesnt evenly round)
	//int remainingBytes = length % MAX_MESSAGE;
	//if (remainingBytes == 0)
	//	numRequests--;

	//for (int i = 0; i <= numRequests; i ++) {
	//	filemsg* rawFileRequest;
	//	int objSize;
	//	if (i*MAX_MESSAGE + remainingBytes >= length) {
	//		//we cant use MAX_MESSAGE for the next offset because it would go out of bounds
	//		rawFileRequest = new filemsg(length - remainingBytes, remainingBytes);
	//		objSize = remainingBytes;
	//	}
	//	else {
	//		//we havnt reached the "small bit" at the end, so we can still use MAX_MESSAGE
	//		//cout << i * MAX_MESSAGE << endl;
	//		rawFileRequest = new filemsg(i*MAX_MESSAGE, MAX_MESSAGE);
	//		objSize = MAX_MESSAGE;
	//	}
	//	char* fileRequest = reinterpret_cast<char*>(rawFileRequest);

	//	int len = chan.cwrite(fileRequest, sizeof(datamsg));
	//	char* reply = chan.cread(&len);

	//	fwrite(reply, objSize, 1,fp);			//write in binary

	//	delete(rawFileRequest);
	//}
	//fclose(fp);
	//fileCopy.close();


	//gettimeofday(&end3, NULL);
	//unsigned int sec3 = end3.tv_sec - begin3.tv_sec;
	//cout << "Done. Time taken for binary file copy: " << sec3 << "sec, " << end3.tv_usec << "usec" << endl;

	/////////////////	Requesting new channel (pt. 4)	///////////////////
	
	//create the channel request
	//channelmsg* m = new channelmsg();
	//char* chanRequest = reinterpret_cast<char*>(m);
	//int u = chan.cwrite(chanRequest, sizeof(NEWCHANNEL_MSG));
	//char* channelVal = chan.cread(&u);
	//string channelName(channelVal);
	//FIFORequestChannel mychan(channelName, FIFORequestChannel::CLIENT_SIDE);
	//
	////test the new channel
	//double ecg1temp;
	//double ecg2temp;
	//
	//cout << "Beginning data point copy on new channel..." << endl;

	//for (double time = 0.00; time <= 5; time += .004) {//one loop per time stamp
	//	for (int ecg = 1; ecg <= 2; ecg++) {				//one loop per ecg
	//		datamsg* rawmsg = new datamsg(1, time, ecg);
	//		char* msg = reinterpret_cast<char*>(rawmsg);

	//		int len = mychan.cwrite(msg, sizeof(datamsg));	//write to channel to request information
	//		char* reply = mychan.cread(&len);					//read from channel to get the information
	//		if (ecg == 1) {									//assign replies to appropriate temp value
	//			ecg1temp = *(double*)reply;
	//		}
	//		else {
	//			ecg2temp = *(double*)reply;
	//		}
	//	}
	//	cout << "Time: " << time << " ECG1: " << ecg1temp << " ECG2: " << ecg2temp << endl;
	//}
	
	/////////////////	Running server as child process (pt. 5) (test separate)	///////////////////
	
	//pid_t pid;
	//pid = fork();
	//if (pid == -1) {
	//	//error
	//	cout << "Couldnt create fork." << endl;
	//	exit(EXIT_FAILURE);
	//}
	//else if (pid == 0) {
	//	//we are in the child process, so we want to start the data server
	//	char *args[1];
	//	args[0] = "./dataserver";
	//	args[1] = NULL;
	//	execvp(args[0], args);
	//}
	//else {
	//	//we are in the parent process, test some stuff
	//	FIFORequestChannel chan("control", FIFORequestChannel::CLIENT_SIDE);
	//	double ecg1temp;
	//	double ecg2temp;

	//	for (double time = 0.00; time <= .2; time += .004) {//one loop per time stamp
	//		for (int ecg = 1; ecg <= 2; ecg++) {				//one loop per ecg
	//			datamsg* rawmsg = new datamsg(1, time, ecg);
	//			char* msg = reinterpret_cast<char*>(rawmsg);

	//			int len = chan.cwrite(msg, sizeof(datamsg));	//write to channel to request information
	//			char* reply = chan.cread(&len);					//read from channel to get the information
	//			if (ecg == 1) {									//assign replies to appropriate temp value
	//				ecg1temp = *(double*)reply;
	//			}
	//			else {
	//				ecg2temp = *(double*)reply;
	//			}
	//		}
	//		cout << "Time: " << time << " ECG1: " << ecg1temp << " ECG2: " << ecg2temp << endl;
	//	}

	//	//now close the server
	//	quitmsg* quit = new quitmsg();
	//	char* quitRequest = reinterpret_cast<char*>(quit);
	//	int u = chan.cwrite(quitRequest, sizeof(QUIT_MSG));
	//	pid_t wait(int *wstatus);
	//}

	return 0;
}

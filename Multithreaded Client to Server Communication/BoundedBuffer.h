#ifndef BoundedBuffer_h
#define BoundedBuffer_h

#include <stdio.h>
#include <queue>
#include <string>
#include <pthread.h>

using namespace std;

class BoundedBuffer
{
private:
	int cap;
	vector<char*> requests;	//implements FIFO buffer
	pthread_mutex_t lock;		//push and pop cannot occur at the same time
	pthread_cond_t count_zero;
	pthread_cond_t count_max;

public:
	BoundedBuffer(int _cap){
		this->cap = _cap;
		//initialize thread mutex and conditions
		pthread_mutex_init(&lock, NULL);
		pthread_cond_init(&count_zero, NULL);
		pthread_cond_init(&count_max, NULL);
	}
	~BoundedBuffer(){
		pthread_mutex_destroy(&lock);
		pthread_cond_destroy(&count_zero);
		pthread_cond_destroy(&count_max);
	}

	//push requests to buffer
	void push(char* data /*, int len*/){
		pthread_mutex_lock(&lock);

		while (requests.size() == cap) {
			//if size is max, we can't add any more data until the consumers have processed some requests
			pthread_cond_wait(&count_max, &lock);
		}

		/////DEBUGGING/////
		/*MESSAGE_TYPE m = *(MESSAGE_TYPE *)data;
		if (m != QUIT_MSG) {
			datamsg* msgData = (datamsg*)data;
			cout << "Pushing data " << msgData->seconds << " for person " << msgData->person << endl;
		}
		else {
			cout << "pushing quit msg" << endl;
		}*/
		///////////////////
		requests.push_back(data);
		
		//send signal to unlock the consumers as we added a data point
		pthread_cond_signal(&count_zero);
		pthread_mutex_unlock(&lock);
		return;
	}

	//get requests from buffer in FIFO order
	char* pop(){
		pthread_mutex_lock(&lock);

		while (requests.size() == 0) {
			//block the thread from removing items as the size if zero
			pthread_cond_wait(&count_zero, &lock);
		}
		char* request = requests.at(0);
		requests.erase(requests.begin());

		//////DEBUGGING/////
		/*MESSAGE_TYPE m = *(MESSAGE_TYPE *)request;
		if (m != QUIT_MSG) {
			datamsg* msgData = (datamsg*)request;
			cout << "popping data " << msgData->seconds << " for person " << msgData->person << " at ecg " << msgData->ecgno << endl;
		}
		else {
			cout << "popping quit msg" << endl;
		}
		cout << "Current buff requests: " << endl;
		for (int i = 0; i < requests.size(); i++) {
			MESSAGE_TYPE m = *(MESSAGE_TYPE *)requests.at(i);
			cout << m << endl;
		}*/
		////////////////////

		//wake up the the patient threads and allow them to add an element as we jsut removed one
		pthread_cond_signal(&count_max);
		pthread_mutex_unlock(&lock);
		return request;
	}
};

#endif /* BoundedBuffer_ */

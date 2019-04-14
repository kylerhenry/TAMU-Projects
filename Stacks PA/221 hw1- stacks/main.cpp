#include "StopWatch.h"
#include "ArrayStack.h"
#include "DoublingArrayStack.h"
#include "LinkedListStack.h"
#include "Node.h"
#include <stdio.h>


void main(void)
{
	DoublingArrayStack<int> DSA(50);	//double array stack
	ArrayStack<int> AS(50);				//ArrayStack
	LinkedListStack<int> LLS;			//link list stack
	StopWatch t;


	t.start();
	
	int i = 0;
	int j = 0;
	for (i; i < 1000000; ++i) {
		LLS.push(i);				//change object to run different tests (AS, DSA, or LLS)
		++j;
			if (j == 50000) {
			printf("%f\n", t.ms());	//prints time at steps of 50000 iterations
			j = 0;
		}
	}
	t.stop();
	system("pause");
}
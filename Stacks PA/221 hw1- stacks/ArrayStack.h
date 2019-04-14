#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

template <class Type>
class ArrayStack
{
private:
	int top;
	int maxSize;	//max size of stack before overflow
	Type *stackElements;

public:
	//constuctor
	ArrayStack(int stackSize) {
		stackElements = new Type[stackSize];	//allocated new memory of stackSize for stack, pointed to by stackElements
		maxSize = stackSize;
		top = -1;	//-1 because stack is still empty
	}
	//destuctor
	~ArrayStack(void) {
		delete[] stackElements;
		stackElements = NULL;	//set to null pointer so it isnt pointing to old array
	}
	//checks if stack is empty
	bool isEmpty(void) const{
		return top < 0;
	}
	//checks if stack is full -- not required by assignment but I wanted for ease of use
	bool isFull(void) const{
		return (top == maxSize - 1);	//top = stackSize - 1 so if top = maxSize - 1 then full
	}
	//finds current size of stack (number of elements)
	int size(void) {
		return(++top);
	}
	//sets new max size after changing array size
	void setMax(int stackSize) {
		this->maxSize = stackSize + 500;
	}
	//gets current stack values
	void getStack() {
		return stackElements;
	}
	//pops element off stack
	Type pop() {
		if (isEmpty()) {
			cout << "Nothing to pop; stack empty." << endl;
			exit(1);
		}
		else {								//sets a temp value equal to top element, decrements top, returns temp value
			Type temp = stackElements[top];
			--top;
			return(temp);
		}
	}
	//pushes element onto stack
	void push(Type e) {
		if (isFull()) {	//checks to ensure you arent going out of scope
			int stackSize = size();
			Type *temp = new Type[stackSize + 500];	//creates new temp array to copy all data to with an +50 incremented size
			for (int i = 0; i <= stackSize; ++i) {
				temp[i] = stackElements[i];			//assigns all values from stack to new temp array
			}
			delete stackElements;					//call destructor for old array (old stack)
			stackElements = temp;					//sets pointer to new array (new stack)
			setMax(stackSize);						//updates maxSize to new value
		}
		//updates top, pushes on new element at location top
		stackElements[++top] = e;
	}
};

#endif
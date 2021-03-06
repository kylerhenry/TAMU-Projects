// TicTacToe_Gui2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
using namespace std; 
extern "C"             //No name mangling
__declspec(dllexport)  //Tells the compiler to export the function
int                    //Function return type     
__cdecl                //Specifies calling convention, cdelc is default, 
					   //so this can be omitted

	
	//EXAMPLE FUNCTION 

	test(int number) {
	return number + 1;
}

/*

extern "C"             //No name mangling
__declspec(dllexport)  //Tells the compiler to export the function
void                   //Function return type     
__cdecl                //Specifies calling convention, cdelc is default, 
					   //so this can be omitted 

	readScores(string* initials, int size, int* scores, int size2) {

		for (int i = 0; i < size; i++) {

			cout << *(initials + i);
			*(initials + i) = "hello"; 
			cout << *(initials + i);
		}

	}
*/
extern "C" __declspec(dllexport) void getArray(long* len, double **data)
{
	string in[100];
	double n[100]; 

	ifstream inputFile("C:\\Users\\Sakshi\\Documents\\2018\\csce315\\TTT_GUI2\\t1\\GUI1\\TicTacToeGUI\\TicTacToeGUI\\scores.txt", std::ifstream::ate | std::ifstream::binary);
	string line;


	//read file
	int i = 0; 
	while (std::getline(inputFile, line))
	{
		istringstream iss(line);
		int score;
		string initial;
		if (!(iss >> initial >> score)) { break; } // error
		
		n[i] = score; 
		cout << "score" << score << n[i];

		in[i] = initial; 
		cout << "initial" << initial << in[i];
		
		i++;

	}

	inputFile.close();

	*len = 100;
	auto size = (*len) * sizeof(double);
	*data = static_cast<double*>(malloc(size));
	memcpy(*data, n, size);
	//memcpy(*data2, in, size);

}

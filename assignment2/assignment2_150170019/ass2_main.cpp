/* @Author
 * Student Name: Alp Eren Gençoğlu
 * Student ID : 150170019
 * Date: 01.11.2018
 */

#include <iostream>
#include "ass2_lan_model.h"

using namespace std;

int main(int argc, char* argv[])
{
	language_model* model = new language_model;

	// if there is only one command line argument, print the whole language model.
	if(argc==2)
	{

		model->readData(argv[1]);
		model->vocabularylist->print();
	}

	else if(argc==4)
	{
		model->readData(argv[1]);
		char char1 = argv[2][0];
		char char2 = argv[3][0];
		
		
		cout << model->calculateProbability(char1,char2) << endl;
	}

	return 0;
}



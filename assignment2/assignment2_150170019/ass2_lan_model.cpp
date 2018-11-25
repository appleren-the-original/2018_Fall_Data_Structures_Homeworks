#include <iostream>
#include <fstream>
#include <ctype.h>
#include "ass2_lan_model.h"

using namespace std;

void language_model::readData (const char * inputtxt){
	vocab_list* newlist = new vocab_list;
	vocabularylist = newlist;

	vocabularylist->create();
	
	FILE * inputptr;
	char input_line[200];
	inputptr = fopen(inputtxt, "r");
	

	while(!feof(inputptr))
	{

		fgets(input_line, 200, inputptr);

		
		for(int i=0, j=1; input_line[j]!='\n'; i++,j++)
		{
			if(input_line[j]=='\0' || input_line[j]=='\n' || input_line[i]=='\0' || input_line[i]=='\n')
				break;
			if(isalpha(input_line[i]))
				input_line[i] = tolower(input_line[i]);
			if(isalpha(input_line[j]))
				input_line[j] = tolower(input_line[j]);
			vocabularylist->add_char(input_line[i]);
			vocabularylist->add_occurence(input_line[i],input_line[j]);

		}
	}

	return;
}


double language_model::calculateProbability (char ch_first, char ch_second){
	double union_occurence = vocabularylist->get_union_occurence(ch_first,ch_second);
	double total_occurence = vocabularylist->get_occurence(ch_first);
	return  union_occurence / total_occurence;
}



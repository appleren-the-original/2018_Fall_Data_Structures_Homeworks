#ifndef LIST_H
#define LIST_H

#include "ass2_node.h"

struct vocab_list
{
	vocab_node *head;
	void create();
	void print();
	void add_char(char );
	void add_occurence(char , char );
	int get_occurence(char );
	int get_union_occurence (char , char );
};

#endif
#include <iostream>
#include <ctype.h>
#include "ass2_list.h"

using namespace std;

void vocab_list::create(){
	head = NULL;
	return;
}

void vocab_list::add_char(char ch_to_add){
	vocab_node *p, *p_behind;
	p = head;

	// check if the character to be added is already in the list.
	// if so, do not do anything and return
	while(p)
	{
		if(p->character == ch_to_add)
		{
			return;
		}
		p = p->next;
	}

	vocab_node* vocab_to_add = new vocab_node;
	vocab_to_add->character = ch_to_add;
	vocab_to_add->next = NULL;
	vocab_to_add->list = NULL;

	if(!isalpha(ch_to_add))
	{
		p = head;
		while(p)
		{
			p_behind = p;
			p = p->next;
		}
		p_behind->next = vocab_to_add;
		vocab_to_add->next = p;
		
		return;
	}

	// adding to an empty list
	if (head == NULL)
	{
		head = vocab_to_add;
		
		return;
	}


	// adding to the head of the list 
	if(vocab_to_add->character < head->character)
	{ 
		vocab_to_add->next = head;
		head = vocab_to_add;
		
		return;
	}

	// adding to the middle or end of the list
	p = head;
	while(p && (p->character < vocab_to_add->character) && isalpha(p->character) )
	{
		p_behind = p;
		p = p->next;
	}
	p_behind->next = vocab_to_add;
	vocab_to_add->next = p;


	return;
}

void vocab_list::add_occurence(char ch_first, char ch_second){
	vocab_node *p = head;
	occur_node *op, *op_behind; 
	while(p)
	{
		if (p->character == ch_first)
			break;
		p = p->next;
	}

	op = p->list;
	// check if the character to be added is already in the list.
	// if so, just increase the occurence and return
	while(op)
	{
		if(op->character == ch_second)
		{
			op->occurence++;
			
			return;
		}
		op_behind = op;
		op = op->next;
	}

	occur_node* occur_to_add = new occur_node;
	occur_to_add->character = ch_second;
	occur_to_add->occurence = 1;
	occur_to_add->next = NULL;

	
	// adding to an empty list
	if (p->list == NULL)
	{
		p->list = occur_to_add;

		return;
	}

	
	op_behind->next = occur_to_add;

	return;
}

int vocab_list::get_occurence(char ch)
{
	int total = 0;
	vocab_node *p = head;
	occur_node *op;
	while(p)
	{
		if (p->character == ch)
			break;
		p = p->next;
	}

	op = p->list;
	while(op)
	{
		total += op->occurence;
		op = op->next;
	}

	return total;
}

int vocab_list::get_union_occurence(char ch_first, char ch_second)
{
	vocab_node *p = head;
	occur_node *op;
	while(p)
	{
		if (p->character == ch_first)
			break;
		p = p->next;
	}

	op = p->list;
	while(op)
	{
		if (op->character == ch_second)
			break;
		op = op->next;
	}

	return op->occurence;
}

void vocab_list::print(){
	vocab_node *p = head;
	occur_node *op;

	while(p)
	{
		if(p->character == ' ')
			cout << "<SP>:" << endl;
		else
			cout << p->character << ":" << endl;

		op = p->list;	
		
		while(op)
		{
			if(op->character == ' ')
				cout << "<<SP>," << op->occurence << ">" << endl;
			else
				cout << "<" << op->character << "," << op->occurence << ">" << endl;
			
			op = op->next;
		}
		p = p->next;
		
		cout << endl;
	}

	return;
}

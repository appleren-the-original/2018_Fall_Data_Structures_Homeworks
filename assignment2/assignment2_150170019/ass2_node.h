#ifndef NODE_H
#define NODE_H

struct occur_node
{
	char character;
	occur_node *next;
	int occurence;
};

struct vocab_node
{
	char character;
	vocab_node *next;
	occur_node *list;
};

#endif
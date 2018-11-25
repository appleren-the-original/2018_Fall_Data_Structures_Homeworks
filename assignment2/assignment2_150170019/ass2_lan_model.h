#ifndef LAN_MOD_H
#define LAN_MOD_H

#include "ass2_list.h"

struct language_model {
	vocab_list *vocabularylist;
	void readData (const char *);
	double calculateProbability (char, char);
};

#endif
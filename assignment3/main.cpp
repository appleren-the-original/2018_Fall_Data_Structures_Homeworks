#include <iostream>
#include <ctype.h>

using namespace std;

struct Card
{
	int value;
	Card * next;
};

struct Deck
{
	Card * top;

	void create();
	void close();
	
	int pop();
	void push(int);
	bool isEmpty();
};

void Deck::create(){
	top = NULL;
}
void Deck::close(){
	Card * p;
	while(top){
		p = top;
		top = top->next;
		delete p;
	}
}
bool Deck::isEmpty(){
	return top == NULL;
}
int Deck::pop(){
	Card * p = top;
	int val = p->value;
	top = top->next;
	delete p;
	return val;
}
void Deck::push(int val){
	Card * card_to_add = new Card;
	card_to_add->value = val;
	card_to_add->next = top;
	top = card_to_add;
}



int main(int arg_num, char* args[]){
	int table_deck_size, player_deck_size; // number of the cards a deck contains in the beginning
	int card_value; // the calue of a card
	int turn_count = 0; // which round it is
	int bin_card_num = 0; // number of cards inside bin


	//
	// Creating a table deck, a bin, and decks for two players
	//
	Deck* p1 = new Deck;
	Deck* p2 = new Deck;
	Deck* table = new Deck;
	Deck* bin = new Deck;
	p1->create(); p2->create(); table->create(); bin->create();

	if(arg_num!=2)
		return 0;

	FILE* inputptr = fopen(args[1],"r");
	


	//
	// Determining deck sizes
	//	
	fscanf(inputptr, "%d %d", &table_deck_size, &player_deck_size);



	//
	// Dealing the cards
	//
	for(int i=0; i<table_deck_size; i++)
	{
		fscanf(inputptr, "%d", &card_value);
		table->push(card_value);
	}
	for(int i=0; i<player_deck_size; i++)
	{
		fscanf(inputptr, "%d", &card_value);
		p1->push(card_value);
	}
	for(int i=0; i<player_deck_size; i++)
	{
		fscanf(inputptr, "%d", &card_value);
		p2->push(card_value);
	}



	//
	// playing until one of the decks is empty
	//
	while( !(table->isEmpty()) && !(p1->isEmpty()) && !(p2->isEmpty()) ){
		turn_count++;
		card_value = table->pop();
		if(card_value > 0) // if the card value is positive:
		{
			if(turn_count%2==1) // if it is Player 1's turn
				for (int i=0; i<card_value; i++)
				{
					if(p1->top->value < p2->top->value)
						p1->push(p2->pop());
					else
					{
						bin->push(p2->pop());
						bin_card_num++;
					}
				}
			else // if it is Player 2's turn
				for (int i=0; i<card_value; i++)
				{
					if(p2->top->value < p1->top->value)
						p2->push(p1->pop());
					else
					{
						bin->push(p1->pop());
						bin_card_num++;
					}
				}
		}
		else // if the card value is negative:
		{
			if(turn_count%2==1) // if it is Player 1's turn
				for (int i=0; i<-card_value; i++)
				{
					if(p2->top->value < p1->top->value)
						p2->push(p1->pop());
					else
					{
						bin->push(p1->pop());
						bin_card_num++;
					}
				}
			else // if it is Player 2's turn
				for (int i=0; i<-card_value; i++)
				{
					if(p1->top->value < p2->top->value)
						p1->push(p2->pop());
					else
					{
						bin->push(p2->pop());
						bin_card_num++;
					}
				}
		}

	}


	// END OF THE GAME
	cout << bin_card_num;
	return 0;
}
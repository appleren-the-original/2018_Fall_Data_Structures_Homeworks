/** 
 * @Author
 * Student Name: Alp Eren Gençoğlu
 * Student ID : 150170019
 * Date: 05.12.18
 */

#include <iostream>
#include <cstdio>

using namespace std;

struct Ant
{
	int name;
	Ant* next;
};

struct stackAnt
{
	Ant * top;

	void create();
	void close();
	
	int pop();
	void push(int);
	bool isEmpty();
};
void stackAnt::create(){
	top = NULL;
}
void stackAnt::close(){
	Ant * p;
	while(top){
		p = top;
		top = top->next;
		delete p;
	}
}
bool stackAnt::isEmpty(){
	return top == NULL;
}
int stackAnt::pop(){
	Ant * p = top;
	int name = p->name;
	top = top->next;
	delete p;
	return name;
}
void stackAnt::push(int name){
	Ant * ant_to_add = new Ant;
	ant_to_add->name = name;
	ant_to_add->next = top;
	top = ant_to_add;
}



struct queueAnt
{
	Ant * front;
	Ant * back;

	void create();
	void close();

	void enqueue(int);
	int dequeue();
	bool isEmpty();
};
void queueAnt::create(){
	front = NULL;
	back = NULL;
}
void queueAnt::close(){
	Ant * p = front;
	while(front){
		p = front;
		front = front->next;
		delete p;
	}
}
void queueAnt::enqueue(int name){
	Ant * ant_to_add = new Ant;
	ant_to_add->name = name;
	ant_to_add->next = NULL;
	if(isEmpty()){
		back = ant_to_add;
		front = back;
	}
	else{
		back->next = ant_to_add;
		back = ant_to_add;
	}
}
int queueAnt::dequeue(){
	Ant* p = front;
	int name = p->name;
	front = front->next;
	delete p;
	return name;
}
bool queueAnt::isEmpty(){
	return front == NULL;
}



struct Ants {
	queueAnt ants ;
	queueAnt holeDepths ;
	stackAnt hole ;
	void ReadFile ( char *);
	void ShowContents ( bool );
	void CrossRoad ();
};
void Ants::ReadFile(char* filename){
	FILE * fptr = fopen(filename,"r");
	
	ants.create(); holeDepths.create(); hole.create();
	int number_of_ants, hole_depth;
	
	
	fscanf(fptr, "%d", &number_of_ants);
	for (int i = 0; i < number_of_ants ; i++)
	{
		ants.enqueue(i+1);
	}
	
	
	while( !feof(fptr) ){
		fscanf(fptr, "%d ", &hole_depth);
		holeDepths.enqueue(hole_depth);
	}

}
void Ants::ShowContents(bool holes_or_ants){
	queueAnt queue;
	if (holes_or_ants){
		queue = ants;
	}
	else{
		queue = holeDepths;
	}
	
	Ant* p = queue.front;
	while(p){
		cout << p->name << " ";
		p = p->next;
	}

	cout << endl;
}
void Ants::CrossRoad(){

	while( !(holeDepths.isEmpty()) ){
		for (int i = 0; i < holeDepths.front->name; i++)
		{
			hole.push(ants.dequeue());
		}
		for (int i = 0; i < holeDepths.front->name; ++i)
		{
			ants.enqueue(hole.pop());
		}
		holeDepths.dequeue();
		
	}

}




int main (int argc, char ** argv ){
	Ants a ;

	if (argc != 2)
	{
		return 1;
	}


	a.ReadFile ( argv [1] ); // store the number of ants and depths of holes
	
	cout << "The initial Ant sequence is: " ;
	a.ShowContents (1); // list ant sequence ( initially : 1 , 2 , ... , N )
	
	cout << "The depth of holes are: " ;
	a.ShowContents (0); // list depth of holes
	
	a.CrossRoad();
	
	cout << "The final Ant sequence is: " ;
	a.ShowContents (1);
	

	a.ants.close(); a.holeDepths.close(); a.hole.close();

	return 0;
}
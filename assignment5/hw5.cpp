/** 
 * @Author
 * Student Name: Alp Eren Gençoğlu
 * Student ID : 150170019
 * Date: 18.12.18
 */


#include <iostream>
#include <cstdio>

using namespace std;

struct ListNode
{
	int value;
	ListNode* next;
};
struct List
{
	ListNode* head = NULL;
	ListNode* tail = NULL;
	void insert(int);
	void close();
};
void List::insert(int val){
	ListNode* p = head;
	ListNode* behind = p;
	
	ListNode* node_to_add = new ListNode;
	node_to_add->value = val;
	node_to_add->next = NULL;
	
	if (head==NULL)
	{
		head = node_to_add;
		tail = head;
		return;
	}
	else
	{
		while (p!=NULL){
			behind = p;
			p = p->next;
		}
	
		p = node_to_add;
		behind->next = p;
		tail = p;
	}
}
void List::close(){
	ListNode* p;
	while (head){
		p = head;
		head = head->next;
		delete p;
	}
}




struct TreeNode
{
	int value;
	TreeNode* left;
	TreeNode* right;
};

struct StackNode
{
	TreeNode* treenode;
	StackNode* next;
};
struct Stack
{
	StackNode* top = NULL;

	void close();
	TreeNode* pop();
	void push(TreeNode*);
	bool isEmpty();
	void printStack();
};
void Stack::close(){
	StackNode* p;
	while(top){
		p = top;
		top = top->next;
		delete p;
	}
}
TreeNode* Stack::pop(){
	StackNode* p = top;
	TreeNode* treenode = p->treenode;
	top = top->next;
	delete p;
	return treenode;
}
void Stack::push(TreeNode* treenode ){
	StackNode* node_to_add = new StackNode;
	node_to_add->treenode = treenode;
	node_to_add->next = top;
	top = node_to_add;
}
bool Stack::isEmpty(){
	return top == NULL;
}
void Stack::printStack(){
	StackNode* p = top;
	while(p){
		cout << " " << p->treenode->value;
		p = p->next;
	}
}






struct Tree
{
	TreeNode* root = NULL;
	int item_count; // number of nodes in the tree
};
bool sum_reached = false;
void findRouteToSum(TreeNode* treenode, int target_sum, int total, bool &sum_reached, Stack* path){
	
	if (treenode && !sum_reached)
	{
		total += treenode->value;
		path->push(treenode);

		if (total == target_sum)
			sum_reached = true;

		//cout << treenode->value << " ";
		findRouteToSum(treenode->left, target_sum, total, sum_reached, path);
		findRouteToSum(treenode->right, target_sum, total, sum_reached, path);
		
		if(!sum_reached)
			path->pop();
	}
}





struct QueNode
{
	TreeNode* parent;
	QueNode* next;
};
struct Queue
{
	QueNode* front = NULL;
	QueNode* back = NULL;

	void enqueue(TreeNode*);
	TreeNode* dequeue();
	void close();
	bool isEmpty();
	void printQ();
};
void Queue::close(){
	QueNode * p = front;
	while(front){
		p = front;
		front = front->next;
		delete p;
	}
}
void Queue::enqueue(TreeNode* par){
	QueNode * node_to_add = new QueNode;
	node_to_add->parent = par;
	node_to_add->next = NULL;

	if(isEmpty()){
		back = node_to_add;
		front = back;
	}
	else{
		back->next = node_to_add;
		back = node_to_add;
	}
}
TreeNode* Queue::dequeue(){
	QueNode* p = front;
	TreeNode* par = p->parent;
	front = front->next;
	delete p;
	return par;
}
bool Queue::isEmpty(){
	return front == NULL;
}






TreeNode* createTreeNode(int val){
	TreeNode* t_node = new TreeNode;
	t_node->value = val;
	t_node->left = NULL;
	t_node->right = NULL;

	return t_node;
}


void inorderTraversal(TreeNode* root) 
{ 
    if (root) 
    { 
        inorderTraversal( root->left ); 
        cout << root->value << " "; 
        inorderTraversal( root->right ); 
    }
} 

int main(int argc, char const *argv[])
{
	if(argc!=2){
		return 1;
	}
	



	//
	// Declare starter variables and data structures
	//
	List list;
	Queue que;
	Tree tree;
	
	int val;
	int ctr = 0;
	int target_sum;
	
	bool found_path_on_left = false;
	bool found_path_on_right = false;











	//
	// read the node values from file and write them to a list
	//
	FILE * fptr = fopen(argv[1],"r");
	while( !feof(fptr) ){
		fscanf(fptr, "%d ", &val);
		list.insert(val);
		ctr++;
	}
	tree.item_count = ctr-1;
	target_sum = list.tail->value; // the last value read from the
                                   // file is target sum.











	//
	// Create Binary Tree from the values in the list
	//
	
	ListNode* traverser = list.head;
	
	// First, set the root of the tree
	TreeNode* t_node = createTreeNode(traverser->value);
	tree.root = t_node;
	que.enqueue(t_node);

	// Then, traverse through the list and add nodes to the tree
	traverser = traverser->next;
	while(traverser != list.tail){
		TreeNode* parent = que.dequeue();

		TreeNode* child_left = createTreeNode(traverser->value);
		que.enqueue(child_left);
		parent->left = child_left;
		traverser = traverser->next;
		if (traverser != list.tail)
		{
			TreeNode* child_right = createTreeNode(traverser->value);
			que.enqueue(child_right);
			traverser = traverser->next;
			parent->right = child_right;
		}
		else{
			parent->right = NULL;
		}

	}
	que.close();
	list.close();
	
	









	//
	// Find the routes to the target sum
	//
	TreeNode* root = tree.root;

	if (root->value == target_sum)
	{
		cout << "Path Found: " << root->value << endl;
		cout << "Path Found: " << root->value << endl;
	}
	else{
		// Find the route in left subtree
		Stack* reversed_path_left = new Stack; // the stack to be sent to findRouteToSum function.
		                                       // result is going to be reversed because of stack implementation

		Stack* path_left = new Stack; // the real path which is reversed version of the reversed_path stack.

		findRouteToSum(root->left, target_sum - root->value, 0, sum_reached, reversed_path_left);

		if( !reversed_path_left->isEmpty() ){
			found_path_on_left = true;
		}
		while(!reversed_path_left->isEmpty())
			path_left->push(reversed_path_left->pop());
		path_left->push(root);



		//Find the route in right subtree
		sum_reached = false;
		Stack* reversed_path_right = new Stack; // the stack to be sent to findRouteToSum function.
		                                        // result is going to be reversed because of stack implementation

		Stack* path_right = new Stack; // the real path which is reversed version of the reversed_path stack.

		findRouteToSum(root->right, target_sum - root->value, 0, sum_reached, reversed_path_right);

		if( !reversed_path_right->isEmpty() ) {
			found_path_on_right = true;
		}
		while(!reversed_path_right->isEmpty())
			path_right->push(reversed_path_right->pop());
		path_right->push(root);
		


		if(found_path_on_left){
			cout << "Path Found:";
			path_left->printStack();
			cout << endl;
		}
		else{
			cout << "No Path Found" << endl;
		}

		if(found_path_on_right){
			cout << "Path Found:";
			path_right->printStack();
			cout << endl; 
		}
		else{
			cout << "No Path Found" << endl;	
		}





		//
		// Final operations
		//
		reversed_path_left->close();
		reversed_path_right->close();
		path_left->close();
		path_right->close();
	}







	return 0;
}
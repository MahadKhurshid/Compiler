#include "stack.h"

stack::stack()
{
	top = NULL;
}

void stack::push(int val)
{
	struct Node* newnode = (struct Node*) malloc(sizeof(struct Node));
	newnode->data = val;
	newnode->next = top;
	top = newnode;
}

int stack::pop()
{
	if (top == NULL)
		return -999; // Stact is empty!
	else {
		Node *ptr = top;
		top = top->next;
		int data = ptr->data;
		delete ptr;
		return data;
	}
}

bool stack::isEmpty()
{
	if (top == NULL) return true;
	return false;
}

void stack::display()
{
	struct Node* ptr;
	if (top == NULL)
		cout << "stack is empty";
	else {
		ptr = top;
		cout << "Stack elements are: ";
		while (ptr != NULL) {
			cout << ptr->data << " ";
			ptr = ptr->next;
		}
	}
	cout << endl;
}

stack::~stack()
{
	Node *ptr = nullptr;
	while (top != NULL)
	{
		ptr = top;
		top = top->next;
		delete ptr;
		ptr = nullptr;
	}
	last = nullptr;
}

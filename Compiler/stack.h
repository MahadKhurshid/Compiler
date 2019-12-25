#pragma once
#include <iostream>
using namespace std;
struct Node {
public:
	int data;
	struct Node *next;
};

class stack
{
public:
	struct Node* top;
	struct Node* last;
	stack();
	void push(int val);
	int pop();
	bool isEmpty();
	void display();
	~stack();
};


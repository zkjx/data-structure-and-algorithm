#ifndef _LINKSTACK_H_
#define _LINKSTACK_H_

#include "Stack.h" 

template <class T>
class linkStack : public Stack<T> 
{
private:
	struct Node
	{
		T data;
		Node* next;
		Node(){ next = NULL; }
		Node(const T &value, Node *p = NULL){ data = value; next = p;}
	};
	Node* top;
public:
	linkStack(){ top = NULL; }
	~linkStack(){ clear(); }
	void clear();
	bool empty()const{ return top == NULL; }
	int size()const;
	void push(const T &value);
	T  pop();
	T getTop()const;
};

template <class T>
void linkStack<T>::clear() {
	Node *p;
	while (top != NULL) {
		p = top;
		top = top->next;
		delete p;
	}
}

template <class T>
int linkStack<T>::size()const {
	Node *p=top;
	int count=0;
	while (p) {
		count++;
		p = p->next;
	}
	return count;
}
template <class T>
void linkStack<T>::push(const T &value) {
	Node *p = new Node(value, top);
	top = p;
}
template <class T>
T linkStack<T>::pop() {
	if (empty())throw outOfRange();
	Node *p = top;
	T value = p->data;
	top = top->next;
	delete p;
	return value;
}
template <class T>
T linkStack<T>::getTop() const { 
	if (empty())throw outOfRange();
	return top->data; 
}
#endif


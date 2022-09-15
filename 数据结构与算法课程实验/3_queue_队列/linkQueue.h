#ifndef _LINKQUEUE_H_
#define _LINKQUEUE_H_
#include "queue.h"

template <class T>
class linkQueue: public Queue<T>
{
private:
	struct node {
		T  data;
		node *next;
		node(const T &x, node *N = NULL){ data = x; next = N; }
		node():next(NULL) {}
		~node() {}
	};
	node *front, *rear;  
public:
	linkQueue(){ front = rear = NULL; }	   
	~linkQueue();
	void clear();	
	bool empty()const{ return front == NULL;}
	int size()const;
	void enQueue(const T &x);
	T deQueue();
	T getHead()const;
}; 
template <class T>
linkQueue<T>::~linkQueue() {
	node *p;
	while (front != NULL) {
		p = front; 
		front = front->next;
		delete p;
	}
} 
template <class T>
void linkQueue<T>:: clear(){
	node *p;
	while (front != NULL) {
		p = front; 
		front = front->next;
		delete p;
	}
	rear=NULL;
}
template <class T>
int linkQueue<T>::size()const {
	node *p = front;
	int count=0;
	while(p){
		count++;
		p=p->next;
	}
	return count;
}
template <class T>
void linkQueue<T>::enQueue(const T &x) {
	if (rear == NULL)				//原空队列，入队元素即是队首又是队尾
		front = rear = new node(x);
	else {
		rear->next = new node(x);
		rear = rear->next;
	}
} 
template <class T>
T linkQueue<T>::deQueue() {
	if(empty())throw outOfRange();
	node *p = front;
	T value = front->data;
	front = front->next;		
	if (front == NULL) rear = NULL;//原队列只有一个元素，出队后要注意修改队尾指针
	delete p;
	return value;
}
template <class T>
T linkQueue<T>::getHead()const {
	if(empty())throw outOfRange();
	return front->data;
}

#endif


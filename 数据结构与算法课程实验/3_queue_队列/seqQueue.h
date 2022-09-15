#ifndef _SEQQUEUE_H_
#define _SEQQUEUE_H_
#include "queue.h"

template <class T>
class seqQueue : public Queue<T>
{
private:
	T *data;
	int maxSize;
	int front, rear;
	void resize();
public:
	seqQueue(int initsize = 100);
	~seqQueue(){ delete [] data; }
	void clear(){ front = rear = -1; }
	bool empty()const { return front == rear; }
	bool full()const { return (rear + 1) % maxSize == front; }
	int size()const{ return (rear-front+maxSize)%maxSize; } 
	void enQueue(const T &x);
	T deQueue();
	T getHead()const;
};

template <class T>
seqQueue<T>::seqQueue(int initsize){
    if(initsize<=0)throw badSize();
    data = new T[initsize];
    maxSize = initsize; 
    front = rear = -1;
}

template <class T>
void seqQueue<T>::enQueue(const T &x){
    if ((rear + 1) % maxSize == front) resize();	// 若队列满，扩大队列
    rear = (rear + 1) % maxSize; 					// 移动队尾指针
    data[rear] = x;		 						// x入队
}

template <class T>
T seqQueue<T>::deQueue(){
    if (empty())throw outOfRange();			// 若队列空，抛出异常
    front = (front + 1) % maxSize; 			// 移动队首指针
    return  data[front]; 			// 返回队首元素
}	

template <class T>
T seqQueue<T>::getHead()const{
    if (empty())throw outOfRange();
    return  data[(front + 1) % maxSize]; 			// 返回队首元素，不移动队首指针
}

template <class T>
void seqQueue<T>::resize(){
    T *p = data;
    data = new T[2 * maxSize];
    for (int i = 1; i < maxSize; ++i)
        data[i] = p[(front + i) % maxSize]; 		// 复制元素
    front = 0; rear = maxSize - 1; 				// 设置队首和队尾指针
    maxSize *= 2;
    delete p;
}

#endif

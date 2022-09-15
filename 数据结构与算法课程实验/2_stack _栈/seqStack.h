//  array-based stack: definition and implementation for some methods 
 
#ifndef _SEQSTACK_H_
#define _SEQSTACK_H_

#include "Stack.h" 
 
template <class T> 	 
class seqStack : public Stack<T> 
{       
private:
	T * data;
	int top;
	int maxSize;
	void resize();
public:
	seqStack(int initSize = 100) {
		if(initSize<=0) throw badSize();
		data = new T[initSize];
		maxSize = initSize ;    
		top = -1;  
	}	   
	~seqStack(){ delete [] data;}
	bool empty() const{ return top == -1;}      
	int size() const{ return top+1; } 
	void clear() { top = -1; } 				// 清空栈内容 
	void push(const T &value);   
	T  pop();   
	T  getTop() const;	  	  
}; 

template <class T>
void seqStack<T>::resize(){
	T *tmp = data;	
	data = new T[2 * maxSize];
	for (int i = 0; i < maxSize; ++i)
		data[i] = tmp[i];
	maxSize *= 2;
	delete [] tmp;
} 
template <class T>
void seqStack<T>::push(const T &value) {	
	if (top == maxSize - 1)   resize();
	data[++top] = value; 
}     
template <class T>
T seqStack<T>::pop(){ 	
	if(empty())throw outOfRange();
	return data[top--];  	
}    
template <class T>
T seqStack<T>::getTop() const{ 					// 若允许修改栈顶元素，考虑返回引用
	if(empty())throw outOfRange();
	return data[top];  	
}	
#endif


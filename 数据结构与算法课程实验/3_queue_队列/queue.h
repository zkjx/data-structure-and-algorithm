#ifndef _QUEUE_H_
#define _QUEUE_H_

class outOfRange:public exception {    	// 用于检查范围的有效性
public:    
   const char* what()const throw()    
   {    return "ERROR! OUT OF RANGE.\n";    } 
};  
class badSize:public exception {    		// 用于检查初始长度的有效性
public:    
   const char* what()const throw()    
   {    return "ERROR! BAD SIZE.\n";    }  
};


template <class T>
class Queue
{
public:
	virtual bool empty()const = 0;		//判队空
	virtual int size()const=0 ;
	virtual void clear()=0;				// 置空队列  
	virtual void enQueue(const T &x) = 0;	//入队
	virtual T  deQueue() = 0;				//出队
	virtual T  getHead()const = 0; 			//读队头元素[若取队首元素，且可以修改队首元素，考虑做成引用]
	virtual ~Queue() {}         			//虚析构函数
};

#endif

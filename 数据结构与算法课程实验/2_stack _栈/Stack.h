// abstract data type for stack 
#ifndef _STACK_H_
#define _STACK_H_
/*
class outOfRange:public exception {    	// 用于检查范围的有效性
public:    
outOfRange():exception("ERROR!OUT OF RANGE.\n")  
{}
};  
class badSize:public exception {    		// 用于检查长度的有效性
public:    
badSize():exception("ERROR!BAD SIZE.\n")  
{}
};
*/
class outOfRange:public exception {    	// 用于检查范围的有效性
public:    
   const char* what()const throw()    
   {    return "ERROR! OUT OF RANGE.\n";    } 
};  
class badSize:public exception {    		// 用于检查长度的有效性
public:    
   const char* what()const throw()    
   {    return "ERROR! BAD SIZE.\n";    }  
};

template <class T> 					// 栈的元素类型为 T 
class Stack 
{ public: 
	virtual bool empty() const = 0; 
	virtual int size() const = 0; 
	virtual void push(const T &x) = 0; 
	virtual T  pop() = 0;              
	virtual T getTop() const = 0;  
	virtual void clear() =0;
	virtual ~Stack() {}
};
#endif
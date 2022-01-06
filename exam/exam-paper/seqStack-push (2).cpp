/*********Begin**********  和  **********End**********不可删除
在*********Begin*********  和  ********End********之间作答
要求使用指定的类名、对象名、变量名、函数名等，少写漏写不得分

已知链栈的类型定义如下，
请实现进栈算法void push(const T &value);，将值为value的元素压入栈顶。
注意：请使用指针p指向值为value的新结点，然后让p成为新的栈顶。

template <class T>
class seqStack {       
private:
    T * data; 				// 存放栈中元素的数组
    int top; 				// 栈顶指针，指向栈顶元素
    int maxSize; 				// 栈的大小
    void resize();				// 扩大栈空间
public:
    seqStack(int initSize = 100); 
    ~seqStack(){ delete [] data;}
    void clear() { top = -1; } 			// 清空栈 
    bool empty() const{ return top == -1;}	// 判空
    int size() const{ return top+1; } 		// 求长度
    void push(const T &value);   		// 进栈
    T  pop();   				// 出栈
    T  getTop() const;	  	  	// 取栈顶元素
};

*/
/***************begin***************/
template <class T>
void linkStack<T>::push(const T &value)
{
	Node *p=new Node{value,top};
	top=p;
 } 
/****************end****************/






















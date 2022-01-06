/*********Begin**********  和  **********End**********不可删除
在*********Begin*********  和  ********End********之间作答
要求使用指定的类名、对象名、变量名、函数名等，少写漏写不得分

已知链栈的类型定义如下，请实现出栈算法T  pop()。若栈非空弹出栈顶元素，并返回栈顶元素的值。
请将工作指针请命名为p。
template <class T>
class linkStack {
private:
    struct Node{
        T data;
        Node* next;
        Node(){ next = NULL; }
        Node(const T &value, Node *p = NULL){ data = value; next = p;}
    }; 
    Node* top;				// 栈顶指针
public:
    linkStack(){ top = NULL; }		// 构造空栈
    ~linkStack(){ clear(); }
    void clear();				// 清空
    bool empty()const{ return top == NULL; }	// 判空
    int size()const;				// 求长度
    void push(const T &value);		// 压栈
    T  pop();				// 出栈
    T getTop()const;			// 取栈顶元素
};*/
/***************begin***************/


template<class T>
T linkStack<T>::pop(){
	if(!empty()){
		Node *p=top;
		T value = p->data;
		top=top->next;
		delete p;
		return value;
	}

}
/****************end****************/

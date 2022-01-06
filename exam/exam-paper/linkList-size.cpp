/*********Begin**********  和  **********End**********不可删除
在*********Begin*********  和  ********End********之间作答
要求使用指定的类名、对象名、变量名、函数名等，少写漏写不得分

已知单链表的类型定义如下，
请实现算法int size()const;求单链表的长度。注意：请将用于遍历链表的工作指针命名为p，计数器命名为count。

单链表的类型定义：
template <class elemType>						// elemType为单链表存储的元素类型
class linkList { 
private:  
    struct Node { 							// 结点类型
    public:  
        elemType  data;						// 结点的数据域 
        Node 	* next;						// 结点的指针域
        Node(const elemType value, Node* p = NULL){	// 两个参数的构造函数 
            data = value;    next = p; 
        } 
        Node(Node* p = NULL)  { 					// 一个参数的构造函数 
            next = p; 	
        } 
    };
    Node*  head;							// 单链表的头指针    
public:  
    linkList();							// 构造函数 
    ~linkList();							// 析构函数 
    int size()const;						// 返回单链表的当前实际长度  
……
}; 

*/
/***************begin***************/

template <class elemType>
int linkList<elemType>::size()const{ // 若没有curLength
    Node *p =head->next;		// 需要从头到尾遍历链
    int count=0;
    while(p){ count++; p=p->next;}
    return count;
}

/****************end****************/













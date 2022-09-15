#ifndef _LINKLIST_H_
#define _LINKLIST_H_
#include<stack>
#include "List.h" 

template <class elemType>								// elemType为单链表存储的元素类型
class linkList: public List<elemType>  { 
private:  
	struct Node { 
	public:  
   		elemType  data;									// 结点的数据域 
		Node 	* next;									// 结点的指针域，指向后继结点 
		Node(const elemType value, Node* p = NULL)  {	// 具有两个参数的Node构造函数 
			data = value; 
			next = p; 
		} 
		Node(Node* p = NULL)  { 						// 具有一个参数的Node构造函数 
			next = p; 
		}
	};
	Node*  head;								// 单链表的头指针 
    Node*  tail;    							// 单链表的尾指针 
	int curLength;								// 单链表的当前长度
	Node*  getPosition(int i)const;				// 返回指向单链表中第i个元素的指针   

	void traverseRecursive(Node * p);
	void traverseNonRecursive1();
	void traverseNonRecursive2();
	void traverseNonRecursive3();
public:  
	linkList();								// 构造函数 
	~linkList();								// 析构函数 
    void clear(); 								// 将单链表清空，使之成为空表
	bool empty()const{return head->next==NULL;}// 判空
	int size()const{return curLength;};         // 返回单链表的当前实际长度 						 
	void insert(int i,const elemType &value);	// 在位置i上插入一个元素value，表的长度增1 
	void remove(int i);							// 删除位置i上的元素value，若删除位置合法，表的长度减1 
	int search(const elemType&value)const;		// 查找值为value的元素第一次出现的位序
	elemType visit(int i)const;					// 访问位序为i的元素值，“位序”0表示第一个元素，类似于数组下标
	void traverse()const;						// 遍历单链表	
	void headCreate();							// “头插法”创建单链表
	void tailCreate();							// “尾插法”创建单链表
	void inverse();								// 逆置单链表
	int prior(const elemType&value)const;		// 查找值为value的元素的前驱
	linkList* Union(linkList<elemType> * lb);
	void outPut();
}; 
 
template <class elemType>  
linkList<elemType>::linkList(){ 
	head = tail = new Node();				// 创建带有头结点的空表
	curLength=0;
} 
 
template <class elemType> 
linkList<elemType>::~linkList(){ 
	clear();
	delete head;								// 删除头结点
} 

template <class elemType>  
void linkList<elemType>::clear(){ 
	Node *p,*tmp; 
	p = head->next;								// p为工作指针(注意不要随意修改头指针)，指向首元结点
	while (p != NULL) {							// 等效while(p)
		tmp = p; 
		p= p->next;								// 指针后移
		delete tmp;										
	} 
	head->next=NULL;							// 头结点的指针域置空
	tail = head;								// 头尾指针均指向头结点
	curLength=0;
}
/*
template <class elemType>  
int linkList<elemType>::size()const{ 
	//return curLength;							// 若linkList类中没有数据成员curLength
	Node *p =head->next;						// 需要从头到尾遍历链表					
	int count=0;
	while(p){ count++; p=p->next;}
	return count;
} 
*/
template <class elemType>  						
typename linkList<elemType> :: Node* linkList<elemType> :: getPosition(int i)const { 
	Node *p =head;      
	int count = 0; 

	if (i < -1 || i > curLength-1)				// // getPosition可查找位置为[-1..n-1],若i为-1则定位到头结点,若i为0则定位到首元结点 
		return NULL;							// 当i非法时返回NULL

	while (count <= i) { 
		p = p-> next; 
		count++; 
	} 

	return p;									// 返回指向第 i 结点的指针 
} 
      
 
template  <class elemType>  			 		
void linkList<elemType> :: insert(int i,const elemType &value)  { 
	Node *p, *q; 
					 
	if (i < 0 || i > curLength)					// 合法的插入位置为[0..n]
		 throw outOfRange();					// 插入位置非法，抛出异常

	p = getPosition(i-1);						// p是位序为i的结点的前驱 
    q = new Node(value, p->next); 
    p->next = q; 

    if (p == tail)tail = q;						// 插入点在表尾，插入结点成为新的尾结点   

	curLength++;
} 
 
template  <class elemType>  							
void  linkList<elemType>::remove(int i){ 
	Node *pre, *p;  
	if (i < 0 || i > curLength-1) 				// 合法的删除位置为[0..n-1] 
		 throw outOfRange();					// 当待删结点不存在时，抛出异常

	pre = getPosition(i-1);
    p = pre->next;								// p是真正待删结点 
	if (p == tail) {							// 待删结点为尾结点，则修改尾指针 
		  tail = pre; 
		  pre->next=NULL;
		  delete p; 
    } 
    else {										// 删除结点p 并修改指针 
    	pre->next = p->next; 
	    delete p; 
     } 
	curLength--;
} 
  
template <class elemType>  						
void  linkList<elemType> ::traverse()const{ 
	Node *p = head->next; 
	cout << "traverse:" ; 
	while (p != NULL) {  
		cout << p->data <<"  "; 
		p = p->next; 
	} 
	cout << endl; 
} 

template <class elemType>  							
int linkList<elemType> ::search(const elemType&value)const{ 
	Node *p = head->next; 
	int count=0;								// 首元结点的位序为0
	while (p != NULL && p->data!=value) {   
		p = p->next; 
		count++;
	} 
	if(p == NULL)return -1;						// 查找失败返回-1，这里-1并非头节点
	else return count;
} 

template <class elemType>  						// 访问位序为i的元素返回其数据域
elemType linkList<elemType> ::visit(int i)const{ 
	Node *p = head->next; 
	int count=0;								// 首元结点位序为0

	if (i < 0 || i > curLength-1) 				// 合法的访问位置为[0..n-1] 
		throw outOfRange();						// 当结点不存在时，抛出异常

	while ( count<i ) {   
		p = p->next; 
		count++;
	} 
	return p->data;
} 

template <class elemType>  						// 头插法创建链表 
void linkList<elemType> :: headCreate(){ 
	Node *p; 
	elemType value,flag;
	cout<<"input elements,ended with:";
	cin>>flag;									// 输入结束标志

	while(cin>>value,value!=flag)
	{
		p=new Node(value,head->next);
		head->next=p;							// 结点p插入到头结点的后面
		if(head==tail)tail=p;					// 原链表为空，则结点p是尾结点
		curLength++;
	}
} 

template <class elemType>  						// 尾插法创建链表
void linkList<elemType> ::tailCreate(){ 
	Node *p; 
	elemType value,flag;
	cout<<"input elements,ended with:";
	cin>>flag;									// 输入结束标志

	while(cin>>value,value!=flag)
	{
		p=new Node(value,NULL);
		tail->next=p;							// 结点p插入到尾结点的后面
		tail=p;									// 结点p成为新的表尾
		curLength++;
	}
} 
template <class elemType>  						// 头插法逆置 
void linkList<elemType> :: inverse(){ 
	Node *p,*tmp;
	p=head->next;								// p为工作指针指向首元结点
	head->next=NULL;							// 构成只有一个头结点的空链表							
	if(p)tail=p;								// 原首元结点将变成表尾
	while(p)
	{
		tmp=p->next;							// 保存当前处理结点p的后继
		p->next=head->next;						
		head->next=p;							// 结点p插入到头结点的后面
		p=tmp;
	}
} 

template <class elemType>  
int linkList<elemType> ::prior(const elemType&value)const{
    Node *p=head->next; 					// p是工作指针指向首元结点
    Node *pre=NULL; 						// pre指向p的前驱结点
    int count=-1;							// -1表示首元结点无前驱
    while(p &&p->data!=value){
        pre=p; 								// 前驱指针后移
        p=p->next; 							// 指向下个待处理结点
        count++;
    }
    if(p == NULL)return -1;					// 查找失败返回-1，这里-1并非头结点
    else return count; 						// 查找成功，count为元素的位序
}        
template <class elemType> 
linkList<elemType> * linkList<elemType> ::Union(linkList<elemType> * lb){
    Node *pa,*pb,*pc;						// 分别是链表la、lb、lc的工作指针
    linkList<elemType>* lc = this;			// lc利用la空间，将lb合并进来
    pa=head->next;  head->next=NULL;			// la表头结点的指针域置为NULL，构成空链表
    pb=(lb->head)->next;  (lb->head)->next=NULL;// lb表头结点的指针域置为NULL，构成空链表
    pc=lc->head;							// 为节约空间lc表直接利用la表头结点
    while(pa && pb){						// la和lb均非空
        if(pa->data<=pb->data) {				// pa所指结点尾插法插入lc表
            pc->next=pa;  pc=pa;  pa=pa->next;    
        }
        else	{							// pb所指结点尾插法插入lc表
            pc->next=pb;  pc=pb;  pb=pb->next;   
        }
    }
    if(pa){ 								// 若pa未到尾，将pc指向pa
        pc->next=pa;						
        lc->tail=tail;						// 修改尾指针
    }
    else{
        pc->next=pb;						// 若pb未到尾，将pc指向pb
        lc->tail=lb->tail;					// 修改尾指针
    }
    lc->curLength = curLength+lb->curLength;
    delete lb;	
    return lc;
}

template <class elemType> 
void linkList<elemType> :: outPut() {        
	cout<<"递归:";
	traverseRecursive(head->next);	cout<<endl;
	cout<<"非递归1:";
	traverseNonRecursive1();	cout<<endl;
	cout<<"非递归2:";
	traverseNonRecursive2();	cout<<endl;
	cout<<"非递归3:";
	traverseNonRecursive3();	cout<<endl;
}
template <class elemType> 
void linkList<elemType> :: traverseRecursive(Node * p) {        
    if(p) {
        cout<<p->data<<"  ";				// 输出结点的值
        traverseRecursive(p->next);       			// 尾递归调用	
    }									
}
//顺序输出单链表结点数据的非递归算法一：	
template <class elemType> 		 
void linkList<elemType> :: traverseNonRecursive1()  {    
	Node *p=head->next;
    Lb1:                      				// 在第一个可执行语句前设标号
    if(p){
        cout<<p->data<<"  ";				// 输出结点的值
        p=p->next;    
        goto Lb1;               			// 转到第一个可执行语句
    }
}
//顺序输出单链表结点数据的非递归算法二：
template <class elemType> 			
void linkList<elemType> :: traverseNonRecursive2() { 
    Node *tmp = head->next; 	
    while (tmp != NULL) {  
        cout << tmp->data <<"  ";			// 输出结点的值
        tmp = tmp->next; 				// 向里一层修改变量值 
    } 
    cout <<endl; 
}
//顺序输出单链表结点数据的非递归算法三：
template <class elemType> 				
void linkList<elemType> :: traverseNonRecursive3() { 
    stack<Node*> S; 
	Node* tmp=head->next;
    while (tmp != NULL) {  
        S.push(tmp);			
        tmp = tmp->next; 				
    }
	while(!S.empty()){
		tmp=S.top();
		S.pop();
		cout << tmp->data <<"  ";	
	}
    cout <<endl; 
}          

#endif

#ifndef _DOUBLELINKLIST_H_
#define _DOUBLELINKLIST_H_
#include "List.h" 

template <class elemType>
class doubleLinkList: public List<elemType>
{
 private:
	struct Node {
		elemType  data;
		Node *prior, *next;
		Node(const elemType &value, Node *p = NULL, Node *n = NULL)
		{ 	data = value; next = n; prior = p;		}
		Node( ):next(NULL), prior(NULL) {}
		~Node() {}
	};
	Node  *head, *tail;
	int curLength;
	Node *getPosition(int i)const; 
public:
	doubleLinkList() ;
	~doubleLinkList();
	void clear() ;
	bool empty()const{ return head->next == tail; }
	int size() const{ return curLength; }
	void insert(int i, const elemType &value); 
	void remove(int i);  
	int search(const elemType &value) const  ;
	elemType visit(int i) const;
	void traverse() const ;  
	void inverse();
};
template <class elemType>
doubleLinkList<elemType>::doubleLinkList() 
{   
	head = new Node;					// 头指针指向头结点
	tail = new Node;
    head->next = tail;		// 尾指针指向尾结点，此处尾结点作用类似头结点
    tail->prior = head;
    curLength = 0;
} 

template <class elemType>
void doubleLinkList<elemType>::clear() 
{ 
	Node  *p = head->next, *tmp;
	head->next = tail;
	tail->prior = head;
	while (p != tail) { 
		tmp = p->next;
		delete p;   
		p=tmp; 	 
	}
	curLength = 0;
}
template <class elemType>
doubleLinkList<elemType>::~doubleLinkList(){
	clear(); 
	delete head; 
	delete tail;
}
template <class elemType>
typename doubleLinkList<elemType>::Node *doubleLinkList<elemType>::getPosition(int i) const
{ 
	Node *p =head;      
	int count = 0; 
	// getPosition可查找位置为[-1..n],若i为-1则定位到头结点,若i为n则定位到tail指向的尾结点
	if (i < -1 || i > curLength )return NULL;	// 当i非法时返回NULL 								
	while (count <= i) { 
		p = p-> next; 
		count++; 
	} 
	return p;									// 返回指向第 i 结点的指针 
} 

template <class elemType>
void doubleLinkList<elemType>::insert(int i,const elemType &value)
{
	Node *p, *tmp;
	if (i < 0 || i > curLength)					// 合法的插入位置为[0..n]
		 throw outOfRange();					// 插入位置非法，抛出异常
	p = getPosition(i);						// 若i==n则定位到tail指向的尾结点
	tmp = new Node(value, p->prior, p);		// tmp插入到p之前
	p->prior->next = tmp;
	p->prior = tmp;
	++curLength;
}
template <class elemType>
void doubleLinkList<elemType>::remove(int i)
{
	Node *p;
	if (i < 0 || i > curLength-1) 				// 合法的删除位置为[0..n-1] 
		 throw outOfRange();					// 当待删结点不存在时，抛出异常
	p = getPosition(i);
	p->prior->next = p->next;
	p->next->prior = p->prior;
	delete p;
	--curLength;
}
template <class elemType>
int doubleLinkList<elemType>::search(const elemType &value) const  
{ 
	Node *p = head->next;
	int i = 0;
	while (p != tail && p->data != value) { p = p->next; ++i; }
	if (p == tail) return -1; else return i;
} 
template <class elemType>
elemType doubleLinkList<elemType>::visit(int i) const
{ 
	if (i < 0 || i > curLength-1) 			// 合法的访问位置为[0..n-1] 
		throw outOfRange();					// 当结点不存在时，抛出异常
	Node *p = getPosition(i);				// getPosition定位范围[-1..n]，因此不能直接利用getPosition判断范围是否合法
	return p->data;
} 
template <class elemType>
void doubleLinkList<elemType>::traverse() const
{
	Node *p = head->next;
	cout << "traverse:" ; 
	while (p != tail) {
		cout << p->data << "  ";
		p=p->next;
	}
	cout << endl;
}
template <class elemType>
void doubleLinkList<elemType>::inverse()
{
	Node *tmp,*p = head->next;
	head->next = tail;
	tail->prior = head;
	while (p != tail) { 
		tmp= p->next;
		p->next=head->next;  p->prior=head;
		head->next->prior=p;	head->next=p;
		p=tmp; 	 
	}
}

#endif
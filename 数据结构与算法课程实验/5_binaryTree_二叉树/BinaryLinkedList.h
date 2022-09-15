#ifndef _BINARY_LINKLIST_H_
#define _BINARY_LINKLIST_H_
#include"BinaryTree.h"

template <class elemType> 
class BinaryLinkList:public binaryTree<elemType>{
private:
    struct Node {  
        Node  *left , *right ;							// 指向左、右孩子的指针
        elemType data;									// 结点的数据域
        Node() : left(NULL), right(NULL) { }				// 无参构造函数
        Node(elemType value, Node *l = NULL, Node * r =NULL ){
            data=value; left=l; right=r; 
        }
        ~Node() {} 
    };
    enum Tags{Left,Right};			
	struct StackElement		
	{			
		Node* pointer; 
		Tags tag; 
		StackElement() {
		}
	};	
    Node * root;										// 指向二叉树的根结点
    void clear( Node *t );							
    int size( Node *t ) const;
    int height( Node *t ) const;
    int leafNum(Node *t )const;
    void preOrder( Node *t ) const;						// 递归前序遍历
    void inOrder( Node *t ) const;						// 递归中序遍历
    void postOrder( Node *t ) const;						// 递归后序遍历
    void preOrderCreate(elemType flag,Node* & t);			// 注意t为引用 
public: 
    BinaryLinkList() : root( NULL) {}						// 构造空二叉树
    ~BinaryLinkList(){ clear(); }				
    bool empty () const{ return root == NULL; }				// 判空
    void clear() {if (root) clear(root); root = NULL;}// 清空
    int size() const { return size(root);}					// 二叉树的结点总数
    int height() const { return height(root); }				// 二叉树的高度
    int leafNum()const{ return leafNum(root); }				// 二叉树的叶子数
    void preOrderTraverse() const{ if(root) preOrder(root); }	// 前序遍历 
    void inOrderTraverse() const { if(root) inOrder(root); }	// 中序遍历
    void postOrderTraverse() const{ if(root) postOrder(root); }// 后序遍历
    void levelOrderTraverse() const;						// 层次遍历
    void preOrderWithStack()const;						// 非递归前序遍历
    void inOrderWithStack()const;							// 非递归中序遍历 
    void postOrderWithStack()const;						// 非递归后序遍历
    void levelOrderCreate(elemType flag);		// 利用带外部结点的层次序列创建二叉树
    void preOrderCreate(elemType flag){ 		// 利用带外部结点的前序序列创建二叉树
        preOrderCreate(flag,root);
    } 
	void makeTree(const elemType &value, BinaryLinkList &lt, BinaryLinkList &rt){  
		root = new Node( value, lt.root,  rt.root);
		lt.root = NULL; rt.root = NULL;	  
	}
	elemType getRoot() const {return root->data;}		// 取根结点的值
	elemType getLeft() const {return root->left->data;}// 取左孩子的值
	elemType getRight() const{return root->right->data;}// 取右孩子的值
};

template <class elemType> 
void BinaryLinkList<elemType>::clear(Node *t) 
{ 
	if (t->left) clear(t->left); 
	if (t->right) clear(t->right);
	delete t;
}

template <class elemType> 
int BinaryLinkList<elemType>::size(Node *t) const
{ 
	if (t == NULL) return 0;							// 递归出口：空树结点数为0
	return 1 + size(t->left) + size(t->right);			// 树的结点数为左右子树结点数+根节点
} 
template <class elemType> 
int BinaryLinkList<elemType>::height(Node *t) const
{ 
	if (t == NULL) return 0;							// 递归出口：空树高度为0	
	else {
		int lh = height(t->left), rh = height(t->right);
		return 1 + ( (lh > rh) ? lh : rh);				// 树的高度为左右子树高度大者+1z
	}
}
template <class elemType> 
int BinaryLinkList<elemType>::leafNum(Node* t)const
{
	if(t==NULL)return 0;								// 递归出口：空树叶子数为0
	else if((t->left==NULL)&&(t->right==NULL))return 1;	// 递归出口：叶子结点
	else return leafNum(t->left)+leafNum(t->right);		// 递归统计左、右子树叶子数总和
}
template <class elemType> 
void BinaryLinkList<elemType>:: preOrder(Node *t) const
{ 
	if (t){  
		cout <<t->data << ' ';			// 访问当前结点
		preOrder(t->left);				// 递归前序遍历左子树
		preOrder(t->right);				// 递归前序遍历右子树
	}
}
template <class elemType> 
void BinaryLinkList<elemType>:: inOrder(Node *t) const
{ 
	if (t){  
		inOrder(t->left);
		cout <<t->data << ' ';
		inOrder(t->right);	  
	}
}
template <class elemType> 
void BinaryLinkList<elemType>::postOrder(Node *t) const
{ 
	if (t){  
		postOrder(t->left);
		postOrder(t->right);
		cout <<t->data << ' ';
	}
}
template <class elemType> 
void BinaryLinkList<elemType>::levelOrderTraverse() const
{
	queue<Node*> que;							// 使用STL中的队列
	Node* p = root;
	if(p) que.push(p);							// 根结点入队列
	while (!que.empty()) {						// 队列非空
		p = que.front(); 	     				// 取队首元素
		que.pop();								// 出队
		cout << p->data << ' ';					// 访问当前结点	
		if (p->left != NULL)que.push(p->left);	// 左子树进队列
		if (p->right!= NULL)que.push(p->right);	// 右子树进队列
	}
}
template <class elemType> 
void BinaryLinkList<elemType>::preOrderCreate(elemType flag,Node * & t)  
{ //按带外部结点的前序序列构造二叉链表表示的二叉树
	elemType value;
	cin>>value;
	if(value!=flag)						// 递归出口value==flag
	{
		t= new Node(value);	
		preOrderCreate(flag,t->left);	// 递归创建左子树
		preOrderCreate(flag,t->right);	// 递归创建右子树
	}
}

template <class elemType>
void BinaryLinkList<elemType>::levelOrderCreate(elemType flag)
{ //按带外部结点的层次序列构造二叉链表表示的二叉树
	queue<Node *> que;							// 使用STL中的队列
	Node *p;							
	elemType value, ldata, rdata;
	cin >> value;
	if (value != flag) root = new Node(value);	// 创建根结点
	que.push(root);								// 入队
	while (!que.empty()) {						// 队列非空
		p = que.front();	que.pop();			// 取队首元素
		cin >> ldata >> rdata;					// 输入左右孩子
		if (ldata != flag)que.push(p->left = new Node(ldata));
		if (rdata != flag)que.push(p->right = new Node(rdata));
	}
} 

template <class elemType>
void BinaryLinkList<elemType>::preOrderWithStack()const
{	// 非递归前序遍历
    stack<Node* > s;				// 使用STL中的栈						
    Node* p = root;      			// 工作指针	
	while(!s.empty() || p)			// 栈非空或者p非空
	{
		if(p)
		{
			s.push(p);				// 指针入栈
			cout<< p->data<<' ';	// 访问当前结点
			p= p->left;				// 工作指针指向左子树
		}
		else						// 左子树访问完毕，转向访问右子树
		{
			p= s.top();				// 获取栈顶元素
			s.pop();				// 退栈  
			p= p->right;			// 工作指针指向右子树
		}
	}

}

template <class elemType>
void BinaryLinkList<elemType>::inOrderWithStack() const 
{	// 非递归中序遍历					
    stack<Node *> s;				// 使用STL中的栈			
    Node* p= root;      			// 工作指针	
    while(!s.empty() || p)  {		// 栈非空或者p非空
        if (p)  {
            s.push(p);				// 指针入栈
            p= p->left;				// 工作指针指向左子树
        }
        else  {						// 左子树访问完毕，转向访问右子树
            p= s.top();				// 获取栈顶元素
            s.pop();				// 退栈    
            cout<< p->data<<' ';	// 访问当前结点
            p= p->right; 			// 工作指针指向右子树             
        }
    }
}

template <class elemType>
void BinaryLinkList<elemType>::postOrderWithStack()const 
{	// 非递归后序遍历	
/*	enum Tags{Left,Right};			
	struct StackElement		
	{			
		Node* pointer; 
		Tags tag; 
		StackElement() {
		}
	};					*/
	StackElement element;			
	stack<StackElement> S;				// 使用STL中的栈 
	Node* p= root;						// 工作指针
	 while (!S.empty() || p) { 
		while (p != NULL) { 
			element.pointer = p; 
			element.tag = Left; 
			S.push(element); 
			p = p->left;				// 沿左子树方向向下周游 
		} 
 
		element = S.top(); 
		S.pop();						// 取栈顶元素 
		p = element.pointer; 
 
		if (element.tag == Left){		//从左子树回来 
			element.tag = Right; 
			S.push(element); 
			p = p->right; 
		} 
		else {							// 从右子树回来 
            cout<< p->data<<' ';		// 访问当前结点
			p = NULL; 
		} 
	} 
}

#endif

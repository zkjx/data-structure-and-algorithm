#pragma once
#include<queue>
#include<stack>
#include"BinaryTree.h"
using namespace std;
template <class elemType>
class BinaryLinkList :public binaryTree<elemType> {
private:
    struct Node {  			// 二叉链表结点
        Node* left, * right;// 指向左、右孩子的指针
        elemType data;		// 结点的数据域
        Node() : left(NULL), right(NULL) { }// 无参构造
        Node(elemType value, Node* l = NULL, Node* r = NULL)
        {
            data = value; left = l; right = r;
        }
        ~Node() {}
    };
    enum ChildType { Left, Right };
    struct StackElem
    {
        Node* pointer;
        ChildType flag;

    };
    Node* root;				        // 指向二叉树的根结点 
// 下列私有函数的形参类型为Node型指针
    void clear(Node* t);			// 私有，清空
    int size(Node* t) const; 		// 私有，二叉树的结点总数
    int height(Node* t) const; 		// 私有，二叉树的高度
    int leafNum(Node* t)const; 		// 私有，二叉树的叶子数
    void preOrder(Node* t) const;	// 私有，递归前序遍历
    void inOrder(Node* t) const;	// 私有，递归中序遍历
    void postOrder(Node* t) const;	// 私有，递归后序遍历
    void preOrderCreate(elemType flag, Node*& t);// 私有，创建二叉树 
public:
    BinaryLinkList() : root(NULL) {}	// 构造空二叉树
    ~BinaryLinkList() { clear(); }
    bool empty() const { return root == NULL; }	// 判空
    // 公有的清空、结点数、高度、叶结点数，调用私有清空、结点数、高度、叶结点数
    void clear() { if (root) clear(root); root = NULL; }// 公有，清空
    int size() const { return size(root); }	// 公有，求结点总数
    int height() const { return height(root); }	// 公有，二叉树的高度
    int leafNum()const { return leafNum(root); }// 公有，二叉树的叶子数
     // 公有，前序、中序、后序遍历，调用私有前序、中序、后序遍历
    void preOrderTraverse() const { if (root) preOrder(root); }
    void inOrderTraverse() const { if (root) inOrder(root); }
    void postOrderTraverse() const { if (root) postOrder(root); }
    void levelOrderTraverse() const;	// 层次遍历
    void preOrderWithStack()const;		// 非递归前序遍历
    void inOrderWithStack()const;		// 非递归中序遍历 
    void postOrderWithStack()const;		// 非递归后序遍历
    // 利用带外部结点的层次序列创建二叉树
    void levelOrderCreate(elemType flag);
    // 公有，利用带外部结点的前序序列创建二叉树	
    void preOrderCreate(elemType flag) {
        preOrderCreate(flag, root);
    }
};

//二叉树的递归前序遍历
template <class elemType>
void BinaryLinkList<elemType>::preOrder(Node* t) const {
    if (t) {
        cout << t->data << ' ';	// 访问当前结点
        preOrder(t->left);		// 前序遍历左子树
        preOrder(t->right);		// 前序遍历右子树
    }
}

//二叉树的中序递归遍历
template <class elemType>
void BinaryLinkList<elemType>::inOrder(Node* t) const {
    if (t) {
        inOrder(t->left); 		// 中序遍历左子树
        cout << t->data << ' '; // 访问当前结点
        inOrder(t->right);	  	// 中序遍历右子树
    }
}

//二叉树的递归后序遍历
template <class elemType>
void BinaryLinkList<elemType>::postOrder(Node* t) const {
    if (t) {
        postOrder(t->left); 		// 后序遍历左子树
        postOrder(t->right); 		// 后序遍历右子树
        cout << t->data << ' '; 	// 访问当前结点
    }
}

//二叉树的层次遍历。
template <class elemType>
void BinaryLinkList<elemType>::levelOrderTraverse() const {
    queue<Node*> que;		// STL中的队列
    Node* p = root;
    if (p) que.push(p);		// 根结点入队列
    while (!que.empty()) {	// 队列非空
        p = que.front(); 	// 取队首元素
        que.pop();			// 出队
        cout << p->data << ' ';	// 访问当前结点	
        if (p->left != NULL)que.push(p->left);	// 左子树进队列
        if (p->right != NULL)que.push(p->right);// 右子树进队列
    }
}

//前序序列建立二叉树
template <class elemType>
void BinaryLinkList<elemType>::preOrderCreate(elemType flag, Node*& t) {
    // 需注意，因为要修改t指针，所以t指针使用引用传递
    elemType value;
    cin >> value;
    if (value != flag) {	// 递归出口value==flag
        t = new Node(value);// 生成根结点
        preOrderCreate(flag, t->left);	// 递归创建左子树
        preOrderCreate(flag, t->right);	// 递归创建右子树
    }
}

//求结点总数
template <class elemType>
int BinaryLinkList<elemType>::size(Node* t) const {
    if (t == NULL) return 0;// 情况(1)：空子树
    return 1 + size(t->left) + size(t->right);// 情况(2)：子树非空
}

//二叉树的高度
template <class elemType>
int BinaryLinkList<elemType>::height(Node* t) const {
    if (t == NULL) return 0;	         // 情况(1)：空子树	
    else {				                 // 情况(2)：子树非空
        int lh = height(t->left), rh = height(t->right);
        return 1 + ((lh > rh) ? lh : rh);// 树的高度为左右子树高度大者+1
    }
}

//求叶子数
template <class elemType>
int BinaryLinkList<elemType>::leafNum(Node* t)const {
    if (t == NULL)return 0;	// 情况(1)：空子树	
    else if ((t->left == NULL) && (t->right == NULL))
        return 1;	        // 情况(2)：叶结点
    else 			        // 情况(3)：求左右子树叶子数之和
        return leafNum(t->left) + leafNum(t->right);
}

//清空二叉树
//删除其左右子树之后再删除根结点自身。
template <class elemType>
void BinaryLinkList<elemType>::clear(Node* t) {
    if (t->left) clear(t->left);
    if (t->right) clear(t->right);
    delete t;
}

//利用带外部结点的层次序列创建二叉树
template <class elemType>
void BinaryLinkList<elemType>::levelOrderCreate(elemType flag) {
    queue<Node*> que; // STL中的队列
    Node* p;
    elemType value, ldata, rdata;
    cin >> value;
    if (value != flag) root = new Node(value); //创建根结点
        que.push(root); //入队
    while (!que.empty()) {// 队列非空
        p = que.front(); que.pop(); // 取队首元素
        cin >> ldata >> rdata; // 输入左、右孩子
        if (ldata != flag) que.push(p->left = new Node(ldata));
        if (rdata != flag)que.push(p->right = new Node(rdata));
    }
}

//非递归前序遍历
template <class elemType>
void BinaryLinkList<elemType>::preOrderWithStack()const {
    stack<Node*> s; //STL中的栈
    Node* p = root; // 工作指针
    while (!s.empty() || p) {// 栈非空或者p非空
        if (p) {
            cout << p->data << " "; //访问当前结点
            s.push(p); // 指针入栈
            p = p->left; //工作指针指向左子树
        }
        else { //左子树访问完毕，转向访问右子树
            p = s.top(); // 获取栈顶元素
            s.pop(); // 退栈
            p = p->right; //工作指针指向右子树
        }
    }
}

//非递归中序遍历
template <class elemType>
void BinaryLinkList<elemType>::inOrderWithStack()const {
    stack<Node*> s; //STL中的栈
    Node* p = root; // 工作指针
    while (!s.empty() || p) {// 栈非空或者p非空
        if (p) {
            s.push(p); // 指针入栈
            p = p->left; //工作指针指向左子树
        }
        else { //左子树访问完毕，转向访问右子树
            p = s.top(); // 获取栈顶元素
            s.pop(); // 退栈
            cout << p->data << " "; //访问当前结点
            p = p->right; //工作指针指向右子树
        }
    }
}

//非递归后序遍历
template <class elemType>
void BinaryLinkList<elemType>::postOrderWithStack()const {
    
    StackElem elem;
    stack<StackElem> s;
    Node* p = root; // 工作指针
    while (!s.empty() || p) {// 栈非空或者p非空
        while (p != NULL) {
            elem.pointer = p;
            elem.flag = Left;
            s.push(elem);
            p = p->left;
        }
        elem = s.top();
        s.pop();
        p = elem.pointer;
        if (elem.flag == Left) {
            elem.flag = Right;
            s.push(elem);
            p = p->right;
        }
        else {
            cout << p->data << " ";
            p = NULL;
        }
    }
}



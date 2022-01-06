# 数据结构与算法C++语言代码实现

## 1. 线性表的抽象数据类型

```c++
template<class T>
class List{
public:
    // 清空线性表
    virtual void clear()=0;	 
    // 判空
    virtual bool empty()const=0;
    // 求线性表的长度
    virtual int size()const=0;	
    // 在位序为i[0..n]的位置插入元素value
    virtual void insert(int i,const T &value)=0;
	// 删除位序为i[0..n-1]的元素								
    virtual void remove(int i)=0;
    // 查找值为value的元素第一次出现的位序
    virtual int search(const T&value)const=0; 
	// 查找位序为i的元素并返回其值								
    virtual T visit(int i)const=0;	
    // 遍历线性表
    virtual void traverse()const=0;
    // 逆置线性表
    virtual void inverse()=0;				
	// 析构函数						
    virtual ~List(){};
};
```

### 1.1 顺序表的类型定义

```c++
template <class elemType>	// elemType为顺序表存储的元素类型
class seqList: public List<elemType>{ 
private:
    elemType *data;			// 利用动态数组存储数据元素 
    int curLength;			// 当前顺序表中存储的元素个数
    int maxSize;			// 顺序表的最大长度
    void resize();			// 表满时扩大表空间
public:
    seqList(int initSize = 10);		// 构造函数 
    seqList(seqList & sl) ;			// 拷贝构造函数
    ~seqList(){ delete [] data; }	// 析构函数 
    void clear(){ curLength = 0; }	// 清空表，只需置curLength为0
    bool empty()const{return curLength==0;}// 判空
    int size()const{ return curLength; }// 返回顺序表中当前存储元素的个数 
    void traverse()const ;		// 遍历顺序表
    void inverse();			// 逆置顺序表
    void insert(int i,const elemType &value);
					// 在位序i上插入值为value的元素
    void remove(int i);          	// 删除位序i上的元素
    int search(const elemType &value) const ;// 查找值为value的元素第一次出现的位序
    elemType visit(int i) const;	  
				// 访问位序为i的元素的值，“位序0”表示第一个元素
};
```

#### 1.1.1 构建一个空顺序表

```c++
template <class elemType>
seqList<elemType>::seqList(int initSize=100) { 
    if (initSize <= 0) throw badSize();
    maxSize = initSize;					
    data = new elemType[maxSize];		
    curLength = 0;					
}
```

#### 1.1.2 拷贝构造函数

在构造函数里动态分配了内存资源，这时需要用户自定义拷贝构造函数进行深拷贝。

```c++
template <class elemType>
seqList<elemType>::seqList(seqList & sl) { 
    maxSize = sl.maxSize;				
    curLength = sl. curLength;			
    data = new elemType[maxSize];	
    for (int i = 0; i < curLength; ++i)
        data[i] = sl.data[i];		
}
```

#### 1.1.3 遍历顺序表

```c++
template<class elemType>
void seqList<elemType>::traverse()const{
    if(empty())cout<<"is empty"<<endl;	// 空表
    else{
        cout<<"output element:\n";
        for (int i = 0; i < curLength; i++)	
				// 依次访问顺序表中所有元素
            cout<<data[i]<<"  ";  
        cout<<endl;  	 				
    }						
} 
```

#### 1.1.4 查找值为value的元素

算法思想：遍历线性表，将线性表中每一个元素依次与value进行比较。若value==data[i](0<=i<curLength)则查找成功，返回data[i]的位序i，否则查找失败返回-1

```c++
template<class elemType>
int seqList<elemType>::search(const elemType & value) const{
    for (int i = 0; i < curLength; i++)
        if (value == data[i]) return i;
    return -1;			// 查找失败返回-1
}
```

#### 1.1.5 求前驱和后继

算法思想：求顺序表中位序为i的元素的前驱和后继，若 i==0，则为第一个元素无前驱，否则其前驱是 data[i-1]；若 i==curLength-1，则为最后一个元素无后继，否则其后继是 data[i+1]。通过元素的下标可以直接定位其前驱和后继，算法的时间复杂度为O(1)。

#### 1.1.6 插入运算

```c++
template <class elemType>
void seqList<elemType>::insert(int i, const elemType &value){ 
    if (i < 0 || i > curLength) throw outOfRange();	
				// 合法的插入位置为[0.. curLength]
    if (curLength == maxSize) resize();	// 表满，扩大

    // 下标j-1在[curLength-1..i]范围的元素往后移动一步
    for (int j = curLength; j > i; j--)
        data[j] = data[j-1];		
	
    data[i] = value; 		// 将 value 置入位序为i的位置
    ++curLength;		// 表的实际长度增1
}
```

**本算法中要注意以下问题：**

(1) 检验插入位置的有效性，这里 i 的有效范围是：0≤i≤curLength，注意：在表尾元素 data[curLength-1] 的后面插入元素成为新的表尾是合法的。

(2) 检查表空间是否满了，在表满的情况下不能再做插入，否则产生溢出错误。此时有两种解决方法：一种是不执行插入，报错后退出；另一种是扩大数组的容量。本书采用第二种方法。

(3) 注意数据的移动方向，最先移动的是表尾元素。

#### 1.1.7 删除运算

```c++
template <class elemType>
void seqList<elemType>::remove(int i) { 
    // 合法的删除位置为[0.. curLength-1] 
    if (i < 0 || i > curLength-1) 
         throw outOfRange();	

    // [i+1.. curLength-1]范围的元素往前移动一步
    for (int j = i; j < curLength - 1; j++)			 data[j] = data[j+1] ;	
			
    --curLength; 		// 表的实际长度减1
}
```

**本算法中要注意以下问题：**

(1) 检查删除位置的有效性。i的取值范围为：0≤i≤n-1。

(2) 顺序表为空时不能做删除，当顺序表为空时curLength的值为0，代码2.6中的判别条件 (i<0||i>curLength-1)隐含了对表为空的检查。

(3) 删除〖a〗i  之后，该数据被覆盖，如果需要保留它的值，则先取出〖a〗i，再做删除。

#### 1.1.8 逆置

```c++
template<class elemType>
void seqList<elemType>::inverse() {
    elemType tmp;
    for (int i = 0; i < curLength/2; i++){			// 控制交换的次数
        tmp = data[i];
        data[i] = data[curLength-i-1];
        data[curLength-i-1] = tmp;
    }
}
```

#### 1.1.9 扩大表空间

```c++
template <class elemType>
void seqList<elemType>::resize(){ 
    elemType *p = data;	// p指向原顺序表空间
    maxSize *= 2;			// 表空间扩大2倍
    data = new elemType[maxSize];
					// data指向新的表空间
    for (int i = 0; i < curLength; ++i)		
        data[i] = p[i];		// 复制元素
    delete [] p;
}
```

#### 1.1.10 合并顺序表

顺序表A与B的结点关键字为整数，A表与B表的元素均非递减有序，试给出一种高效的算法，将B表中元素合并到A表中，使新的A表的元素仍保持非递减有序，高效指最大限度的避免移动元素。

```c++
template<class elemType>
bool seqList<elemType>::Union(seqList<elemType> &B){	
    int m, n, k, i, j;
    m = this->curLength; 	// 当前对象为线性表A
    n = B.curLength;		// m，n分别为线性表A和B的长度
    k = m+n-1;		// k为结果线性表的工作指针（下标）
    i = m-1, j = n-1;	          // i，j分别为线性表A和B的工作指针（下标）
    while(m+n > this->maxSize){// 判断A表空间是否足够大
        resize();			// 空间不够，扩大表空间
    }
    while (i>=0 && j>=0)	// 合并顺序表，直到一个表为空
        if (data[i] >= B.data[j])  data[k--] = data[i--];
        else  data[k--] = B.data[j--];	// 默认当前对象
    while(j>=0) 		// 将B表的剩余元素复制到A表
        data[k--] = B.data[j--];
    curLength = m+n; 	// 修改A表长度
    return true;
}
```

### 1.2 单链表定义

```c++
template <class elemType>	
struct Node { 
public: 
    elemType  data;		// 数据域 
    Node 	* next;	// 指针域  
    Node(const elemType value, Node* p = NULL)  {	
				// 两个参数的构造函数 
        data = value; 
        next = p; 
    } 
    Node(Node* p = NULL)  { // 一个参数的构造函数 
        next = p; 
    } 
};
template <class elemType>   // elemType为单链表存储的元素类型
class linkList: public List<elemType>  { 
private:  
    struct Node { 			// 结点类型
    public:  
        elemType  data;			// 结点的数据域 
        Node 	* next;			// 结点的指针域
        Node(const elemType value, Node* p = NULL){
					// 两个参构造函数 
            data = value;    next = p; 
        } 
        Node(Node* p = NULL)  { 	// 一个参构造函数 
            next = p; 
        } 
    };
    Node*  head;			// 单链表的头指针 
    Node*  tail;    			// 单链表的尾指针 
    int  curLength;			// 单链表的当前长度，牺牲空间换时间
    Node*  getPosition(int i)const;	// 返回指向位序为i的元素的指针      
public:  
    linkList();					// 构造函数 
    ~linkList();					// 析构函数 
    void clear(); 				// 将单链表清空
    bool empty()const{ return head->next==NULL;}// 判空
    int size()const{ return curLength; } 	// 返回单链表的当前实际长度  
    void insert(int i,const elemType &value); // 在位序i上插入一个元素value
    void remove(int i);			// 删除位序i上的元素
    int search(const elemType&value)const;	
				// 查找值为value的元素第一次出现的位序
    int prior(const elemType&value)const;	
				// 查找值为value的元素的前驱的位序
    elemType visit(int i)const; // 访问位序为i的元素值，0定位到首元结点
    void traverse()const;			// 遍历单链表	
    void headCreate();			// “头插法”创建单链表
    void tailCreate();				// “尾插法”创建单链表
    void inverse();				// 逆置单链表
}; 

```

#### 1.2.1 单链表的初始化

```c++
template <class elemType>  
linkList<elemType>::linkList(){ 
    head = tail = new Node(NULL);  // 创建带有头结点的空表
    curLength=0;
}
```

#### 1.2.2 析构函数

```c++
template <class elemType> 
linkList<elemType>::~linkList(){ 
    clear();				    // 清空单链表
    delete head;			    // 释放头结点
} 
```

#### 1.2.3 清空单链表

清空单链表的主要操作是将工作指针从头结点一直移动到链表尾，边移动指针边释放结点

```c++
template <class elemType>  
void linkList<elemType>::clear(){ 
    Node * p, * tmp; 		// p为工作指针，指向首元结点
    p = head->next;	// 引入工作指针是为了防止随意修改头指针
    while (p != NULL) {	// 等效while(p)
        tmp = p; 
        p = p->next;		// 指针后移
        delete tmp;			
    } 
    head->next=NULL;	// 头结点的指针域置空
    tail = head;		// 头尾指针均指向头结点
    curLength=0;	
}
```

#### 1.2.4 求表长

若单链表类型定义中没有设置变量curLength用于存储表长，那么，就需要从第一个结点开始，一个结点一个结点的计数，直至链表尾。

```c++
template <class elemType>  
int linkList<elemType>::size()const{  
    return  curLength;	// 直接返回curLength
}
```

若单链表类型定义中没有设置变量curLength用于存储表长，那么，就需要从第一个结点开始，一个结点一个结点的计数，直至链表尾。

```c++
template <class elemType>  
int linkList<elemType>::size()const{ // 若没有curLength
    Node *p =head->next;		// 需要从头到尾遍历链	
    int count=0;
    while(p){ count++; p=p->next;}
    return count;
}
```

#### 1.2.5 遍历链表

```c++
template <class elemType>  		
void  linkList<elemType> ::traverse()const{ 
    Node *p = head->next; // 工作指针p指向首元结点
    cout << "traverse:" ; 
    while (p != NULL) {  
        cout << p->data <<"  "; 
        p = p->next; 	    // 向后移动指
    } 
    cout << endl; 
}
```

#### 1.2.6 查找位序为i的元素

```c++
template <class elemType>  		
typename linkList<elemType> :: Node* linkList<elemType> :: getPosition(int i)const { 
    if(i < -1 || i > curLength-1)	// 合法查找位置为[-1..n-1]
        return NULL;		  	// 当i非法时返回NULL
    Node *p = head;      		// 工作指针p指向头结点
    int count = 0; 
    while(count <= i) { 
        p = p-> next; 
        count++; 
    } 
    return p;				// 返回指向位序为 i 的结点的指针 
}
```

#### 1.2.7 查找值为value的元素的位序

```c++
template <class elemType>  			
int linkList<elemType> ::search(const elemType&value)const{ 
    Node *p = head->next; 	// 工作指针p指向首元结点
    int count = 0;		// 首元结点的位序为0
    while(p != NULL && p->data != value) {   
        p = p->next; 
        count++;
    } 
    if(p == NULL)return -1;	// 查找失败返回-1，这里-1并非头结点
    else return count; 		// 查找成功，count为元素的位序
}  
```

#### 1.2.8 查找值为value的元素的前驱的位序

求值为value的元素的前驱，需要从链表的第一个结点开始遍历链表。我们设置两个指针p和pre，分别指向当前正在访问的结点和它的前驱结点，还需要一个计数器count。从链表的第一个结点开始遍历链表：
(1) 若p == NULL，则查找值为value的元素失败，返回-1；
(2) 若查找值为value的元素成功，且该元素是首元结点，则无前驱，返回-1；
(3) 若查找值为value的元素成功，且该元素不是首元结点，则返回其前驱的位序。

```c++
template <class elemType>  
int linkList<elemType> ::prior(const elemType&value)const{
    Node *p = head->next; 	// p是工作指针指向首元结点
    Node *pre = NULL; 	// pre指向p的前驱结点
    int count = -1;		// 注意：-1表示首元结点无前驱
    while(p &&p->data != value){
        pre = p; 		// 前驱指针后移
        p = p->next; 		// 指向下个待处理结点
        count++;
    }
    if(p == NULL) return -1;	// 查找失败返回-1，这里-1并非头结点
    else return count; 		// 查找成功，count为元素的位序
}

```

#### 1.2.9 插入元素

在位序为i的位置插入值为value的新结点q。需要先找到位序为i-1的结点p，让q的指针域指向p原来的后继，然后修改p的后继为q

```c++
template  <class elemType>  			 	
void linkList<elemType> :: insert(int i,const elemType &value)  { 
    Node *p, *q; 
    if (i < 0 || i > curLength)		// 合法的插入位置为[0..n]
        throw outOfRange();		// 插入位置非法，抛出异常
    p = getPosition(i-1);		// p是位序为i的结点的前驱 
    q = new Node(value, p->next); 	// 申请新结点q
    p->next = q; 			// q结点插入到p结点的后面
    if (p == tail)tail = q;		// 若插入点在表尾，q成为新的表尾
    curLength++;
}
```

#### 1.2.10 删除元素 

删除位序为i的结点

```c++
template  <class elemType>  				
void  linkList<elemType>::remove(int i){ 
    Node *pre, *p;  		// p是待删结点，pre是其前驱
    if (i < 0 || i > curLength-1) // 合法的删除位置为[0..n-1] 
        throw outOfRange();	// 当待删结点不存在时，抛出异常
    pre = getPosition(i-1);
    p = pre->next;		// p是真正待删结点 
    if (p == tail) {		// 待删结点为表尾结点，则修改尾指针 
        tail = pre;    pre->next=NULL;    
    } 
    else {  pre->next = p->next; }
    delete p; 
    curLength--;
}
```

#### 1.2.11 头插法创建单链表

```c++
template <class elemType>  		 
void linkList<elemType> :: headCreate(){// 头插法创建单链表
    Node *p; 
    elemType value,flag;
    cout<<"input elements,ended with:";
    cin>>flag;			  // 输入结束标志
    while(cin>>value,value != flag){
        // 创建新结点p->data = value, p->next = head->next
        p = new Node(value,head->next); 
        head->next = p;	  // 结点p插入到头结点的后面
        if(head == tail) tail = p;// 原链表为空，新结点p成为表尾结点
        curLength++;
    }
}
```

#### 1.2.12 尾插法创建单链表 

```c++
template <class elemType>  					
void linkList<elemType> ::tailCreate(){// 尾插法创建链表
    Node *p; 
    elemType value,flag;
    cout<<"input elements,ended with:";
    cin>>flag;				// 输入结束标志
    while(cin>>value,value!=flag){
        p=new Node(value,NULL);
        tail->next=p;			// 结点p插入到表尾结点的后面
        tail=p;				// 结点p成为新的表尾
        curLength++;
    }
}
```

#### 1.2.13 逆置单链表

用工作指针p依次访问链表中的每个结点，每访问一个结点，将它插入到头结点的后面（头插法）。

```c++
template <class elemType>  
void linkList<elemType> :: inverse(){// 头插法逆置
    Node *p,*tmp;
    p=head->next;		// p为工作指针指向首元结点
    head->next=NULL;	// 头结点的指针域置空，构成空链表
    if(p)tail=p;			// 逆置后，原首元结点将变成表尾结点
    while(p){
        tmp=p->next;		// 暂存p的后继
        p->next=head->next;		
        head->next=p;	// 结点p插入到头结点的后面
        p=tmp; 		// 继续处理下一个结点
    }
}
```

合并链表
将非递减有序的单链表la和lb合并成新的非递减有序单链表lc，要求利用原表空间。
算法思想：因为新创建的单链表lc仍然是非递减有序的，所以用尾插法创建lc表。
[代码2.24]本例用类的成员函数实现，la表为this指针所指向的当前链表

```c++
template <class elemType> 
typename linkList<elemType> * linkList<elemType> ::Union(linkList<elemType> * lb){
    Node *pa,*pb,*pc;		// 分别是链表la、lb、lc的工作指针
    linkList<elemType>* lc = this;	// lc表利用la表空间
    pa=head->next;  head->next=NULL;	// la表构成空链表
    pb=(lb->head)->next;  (lb->head)->next=NULL;// lb表构成空链表
    pc=lc->head;
    while(pa && pb){		// la和lb均非空
        if(pa->data<=pb->data) {	// pa所指结点尾插法插入lc表
            pc->next=pa;  pc=pa;  pa=pa->next;    
        }
        else{			// pb所指结点尾插法插入lc表
            pc->next=pb;  pc=pb;  pb=pb->next;   
        }
    }
    if(pa){ 			// 若pa未到尾，将pc指向pa
        pc->next=pa;						
        lc->tail=tail;		// 修改尾指针，因lc=la，这条语句可省略
    }
    else{
        pc->next=pb;		// 若pb未到尾，将pc指向pb
        lc->tail=lb->tail;	// 修改尾指针
    }
    lc->curLength = curLength+lb->curLength;
    delete lb;	 return lc;
}
```

## 2. 栈的抽象数据定义

```c++
template <class T> 			// 栈的元素类型为 T 
class Stack {
public: 
    virtual bool empty() const = 0;	// 判空
    virtual int size() const = 0; 	// 求栈中元素个数
    virtual void push(const T &x) = 0; // 压栈
    virtual T  pop() = 0;           // 弹栈
    virtual T getTop() const = 0;   // 取栈顶元素（不弹出） 
    virtual void clear() =0; 		// 清空栈
    virtual ~Stack() {}
};
```

### 2.1 顺序栈的定义

```c++
template <class T>
class seqStack : public Stack<T> {       
private:
    T * data; 				// 存放栈中元素的数组
    int top; 				// 栈顶指针，指向栈顶元素
    int maxSize; 			// 栈的大小
    void resize();			// 扩大栈空间
public:
    seqStack(int initSize = 100); 
    ~seqStack(){ delete [] data;}
    void clear() { top = -1; } 		// 清空栈 
    bool empty() const{ return top == -1;}// 判空
    int size() const{ return top+1; } 	// 求长度
    void push(const T &value);   		// 进栈
    T  pop();   					// 出栈
    T  getTop() const;	  	  		// 取栈顶元素
};
```

通常将数组的小下标端设为栈底，栈空时，栈顶指针top=-1； 入栈时，栈顶指针加1，即++top；出栈时，栈顶指针减1，即top- -。

#### 2.1.1 构造函数

初始化一个空的顺序栈，置栈顶指针top为-1

```c++
template <class T>
seqStack<T>::seqStack(int initSize = 100) {
    if(initSize <= 0) throw badSize();
    data = new T[initSize];
    maxSize = initSize ;    
    top = -1;  
}
```

#### 2.1.2 进栈

```c++
template <class T>
void seqStack<T>::push(const T &value) {
    // 检查顺序栈是否已满	
    if (top == maxSize - 1) resize();			
    data[++top] = value;// 修改栈顶指针，新元素入栈
}
```

#### 2.1.3 出栈

```c++
template <class T>
T seqStack<T>::pop(){ 	
    if(empty())throw outOfRange();	// 空栈无法弹栈
    return data[top--];  	// 修改栈顶指针，返回栈顶元素
} 
```

应该指出，“出栈”并不一定要带回元素，带回元素是“副产品”，出栈的主要目的是下移指针，是否要返回栈顶元素取决于题目要求。

#### 2.1.4 取栈顶元素

说明：若允许修改返回的栈顶元素，考虑使用引用作为函数的返回值。

```c++
template <class T>
T seqStack<T>::getTop() const{ 		
    if(empty())throw outOfRange();
    return data[top];  	
}
```

#### 2.1.5 扩大栈空间

```c++
template <class T>
void seqStack<T>::resize(){
    T *tmp = data;	
    data = new T[2 * maxSize];
    for (int i = 0; i < maxSize; ++i)
        data[i] = tmp[i];
    maxSize *= 2;
    delete [] tmp;
} 
```

### 2.2 链栈的类型定义

```
template <class T>
class linkStack : public Stack<T> {
private:
    struct Node{
        T data;
        Node* next;
        Node(){ next = NULL; }
        Node(const T &value, Node *p = NULL){ data = value; next = p;}
    }; 
    Node* top;			// 栈顶指针
public:
    linkStack(){ top = NULL; }	// 构造空栈
    ~linkStack(){ clear(); }
    void clear();					// 清空
    bool empty()const{ return top == NULL; }	// 判空
    int size()const;				// 求长度
    void push(const T &value);			// 压栈
    T  pop();					// 弹栈
    T getTop()const;				// 取栈顶元素
};
```

#### 2.2.1 清空栈

```c++
template <class T>
void linkStack<T>::clear() {
    Node *p;
    while (top != NULL) {
        p = top;								// p指向当前栈顶元素
        top = top->next; 						// top指针移向次栈顶元素
        delete p;								// 释放p指向的当前栈顶元素
    }
}
```

#### 2.2.2 求栈中元素个数

```c++
template <class T>
int linkStack<T>::size()const {
    Node *p=top;
    int count=0;								// 计数器
    while (p) {								// 遍历栈，统计元素总数
        count++;
        p = p->next;
    }
    return count;
}
```

#### 2.2.3 进栈

```c++
template <class T>
void linkStack<T>::push(const T &value) {
    // 在栈顶插入元素
    Node *p = new Node(value, top); 
    top = p;			// p成为新的栈顶元素 
}
```

#### 2.2.4 出栈

```c++
template <class T>
T linkStack<T>::pop() {
    if (empty())throw outOfRange();
    Node *p = top;
    T value = p->data;	// value保存栈顶元素的值
    top = top->next; 	// top指向向后移动
    delete p;			// 删除栈顶元素
    return  value;
}
```

#### 2.2.5 取栈顶元素

```c++
template <class T>
T linkStack<T>::getTop() const { 
    if (empty())throw outOfRange();
    return top->data; 
}
```

## 3. 队列的抽象数据类型定义

```c++
template <class T>		// 队列的元素类型为T 
class Queue{
public:
    virtual bool empty()const = 0;	// 判队空
    virtual void clear()=0;			// 清空队列
    virtual int size()const=0 ; 		// 求队列长度
    virtual void enQueue(const T &x) = 0;	// 入队
    virtual T deQueue() = 0;			// 出队
    virtual T getHead()const = 0; 	// 读队头元素
    virtual ~Queue() {}         		// 虚析构函数
};
```

### 3.1 循环队列

#### 3.1.1 初始化一个空队列

```c++
template <class T>
seqQueue<T>::seqQueue(int initsize){
    if(initsize <= 0)throw badSize();
    data = new T[initsize];
    maxSize = initsize; 
    front = rear = -1;
}
```

#### 3.1.2 入队

```c++
template <class T>
void seqQueue<T>::enQueue(const T &x){
    // 若队列满，扩大队列
    if ((rear + 1) % maxSize == front) resize();
    rear = (rear + 1) % maxSize; 	// 移动队尾指针
    data[rear] = x;		 	// x入队
}
```

#### 3.1.3 出队

```c++
template <class T>
T seqQueue<T>::deQueue(){
    // 若队列空，抛出异常
    if (empty())throw outOfRange(); 
    front = (front + 1) % maxSize; 	// 移动队首指针
    return  data[front]; 			// 返回队首元素
}	
```

#### 3.1.4 取队首元素

```c++
template <class T>
T seqQueue<T>::getHead()const{
    if (empty())throw outOfRange();
    // 返回队首元素，不移动队首指针
    return  data[(front + 1) % maxSize]; 		
}
```

#### 3.1.5 扩大队列空间

```c++
template <class T>
void seqQueue<T>::resize(){
    T *p = data;
    data = new T[2 * maxSize];
    for (int i = 1; i < maxSize; ++i)
        data[i] = p[(front + i) % maxSize]; // 复制元素
    front = -1; rear = maxSize - 2; // 设置队首和队尾指针
    maxSize *= 2;
    delete p;
}
```

### 3.2 链队列的类型定义

```c++
template <class T>
class linkQueue: public Queue<T>{
private:
    struct node {
        T  data;    node *next;
        node(const T &x, node *N = NULL){ data = x; next = N; }
        node():next(NULL) {}
        ~node() {}
    };
    node *front, *rear;  			// 队头指针、队尾指针
public:
    linkQueue(){ front = rear = NULL; }	   
    ~linkQueue(){ clear(); }
    void clear();				// 清空队列
    bool empty()const{ return front == NULL;} 	// 判空
    int size()const;				// 队列长度
    void enQueue(const T &x); 		// 入队
    T deQueue();				// 出队
    T getHead()const;				// 取队首元素
};
```

#### 3.2.1 入队

```c++
template <class T>
void linkQueue<T>::enQueue(const T &x) {
    if (rear == NULL)			// 原队列为空
        front = rear = new node(x);	// 入队元素既是队首又是队尾
    else {
        rear->next = new node(x);	// 在队尾入队
        rear = rear->next; 		// 修改队尾指针
    }
}
```

#### 3.2.2 出队

出队操作有一个特殊情况，即如果执行deQueue操作时队列中只有一个元素，经过deQueue操作，队列为空，此时必须将front和rear同时置成NULL

```c++
template <class T>
T linkQueue<T>::deQueue() {
    if(empty())throw outOfRange();	// 队列空，抛出异常
    node *p = front;
    T value = front->data;		// 保存队首元素
    front = front->next;			// 在队首出队
    // 原来只有一个元素，出队后队列为空
    if(front == NULL) 							  rear = NULL;			// 修改队尾指针
    delete  p;
    return value;
} 
```

#### 3.2.3 取队首元素

```c++
template <class T>
T linkQueue<T>::getHead()const {
    if(empty())throw outOfRange();	// 队列空，抛出异常
    return  front->data; 			// 返回队首元素
}
```

#### 3.2.4 清空队列

```c++
template <class T>
void linkQueue<T>:: clear(){
    node *p;
    while (front != NULL) {	// 释放队列中所有结点
        p = front; 
        front = front->next;
        delete p;
    }
    rear = NULL;			// 修改尾指针
}
```

#### 3.2.5 求队列长度

```c++
template <class T>
int linkQueue<T>::size()const {
    node *p = front;
    int count=0;
    while(p){
        count++;
        p=p->next;
    }
    return count;
}
```

## 4.树的抽象数据类型

```c++
template <class elemType> 	                    // 二叉树的元素类型为elemType
class binaryTree {			                    // 二叉树的抽象数据类型
public:
    virtual void clear() = 0;		            // 清空
    virtual bool empty() const = 0;             // 判空
    virtual int height() const = 0;	            // 二叉树的高度
    virtual int size() const = 0;	            // 二叉树的结点总数
    virtual void preOrderTraverse() const = 0;  // 前序遍历
    virtual void inOrderTraverse() const = 0;	// 中序遍历
    virtual void postOrderTraverse() const = 0;	// 后序遍历
    virtual void levelOrderTraverse() const = 0;// 层次遍历
    virtual ~binaryTree() {};
};
```

### 4.1 二叉链树

```c++
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
```

### 4.2 哈夫曼树

```c++
template <class T>
class huffmanTree {
private:
    struct  Node {
        T data;				            // 结点的数据域
        int weight;			            // 结点的权值		  
        int parent, left, right;		// 双亲及左右孩子的下标
        Node() {				        // 构造函数
            weight = parent = left = right = 0;
        };
    };
    struct huffmanCode {
        T data;
        string code;			        // 保存data的哈夫曼编码
        huffmanCode() { code = ""; }	// 构造函数，编码前code是空串
    };
    Node* hfTree;		                // 顺序结构，保存huffman树
    huffmanCode* hfCode;	            // 顺序结构，保存huffman编码
    int size;			                // 叶结点数
    void selectMin(int m, int& p);	    // 选出当前集合中的最小元素
public:
    huffmanTree(int initSize);  	    // 构造函数
    ~huffmanTree() { delete[] hfTree; delete[]hfCode; }
    void createHuffmanTree(const T* d, const double* w);
                                        // 创建哈夫曼树
    void huffmanEncoding();	            // 获取huffman编码
    void printHuffmanCode();	        // 输出huffman编码
};

//构造函数
template <class T>
huffmanTree<T>::huffmanTree(int initSize) {
    size = initSize;	            // size为初始集合中的结点数
    hfTree = new Node[2 * size];
    // 哈夫曼树采用顺序储存结构
    hfCode = new huffmanCode[size]; // 哈夫曼编码
}

//根据叶结点数据数组d及其权值数组w创建哈夫曼树。
template <class T>
void huffmanTree<T>::createHuffmanTree(const T* d, const double* w) {
    int i, min1, min2;		            // 最小树、次最小树的下标
    for (i = size; i < 2 * size; ++i) {	// size个叶结点赋值
        hfTree[i].data = d[i - size];
        hfTree[i].weight = w[i - size];
    }
    for (i = size - 1; i > 0; --i) {   // 合并产生n-1个新结点  
     // 选出parent 的值为0且权值最小的两棵子树min1、min2作为结点i的左右孩子
        selectMin(i + 1, min1);	hfTree[min1].parent = i;
        selectMin(i + 1, min2);	hfTree[min2].parent = i;
        hfTree[i].weight = hfTree[min1].weight + hfTree[min2].weight;
        hfTree[i].left = min1;
        hfTree[i].right = min2;
    }
}

//选出parent 的值为0且权值最小的子树的根结点的下标。
template<class T>
void huffmanTree<T>::selectMin(int m, int& p) {
    int j = m;
    while (hfTree[j].parent != 0) j++;	    // 跳过已有双亲的结点
    for (p = j, j += 1; j < 2 * size; j++)	// 向后扫描剩余元素
        if ((hfTree[j].weight < hfTree[p].weight)
            && 0 == hfTree[j].parent)
            p = j;			                // 发现更小的记录，记录它的位置
}

//根据哈夫曼树为每个叶结点生成哈夫曼编码。
template <class T>
void huffmanTree<T>::huffmanEncoding() {
    int f, p;		                   // p是当前正在处理的结点，f是p的双亲的下标
    for (int i = size; i < 2 * size; ++i) {
        hfCode[i - size].data = hfTree[i].data;
        p = i;
        f = hfTree[p].parent;
        while (f) {
            if (hfTree[f].left == p)   // p是其双亲f的左孩子，编码+‘0’
                hfCode[i - size].code = '0' + hfCode[i - size].code;
            else  		               // p是其双亲f的右孩子，编码+‘1’
                hfCode[i - size].code = '1' + hfCode[i - size].code;
            p = f;
            f = hfTree[p].parent;
        }
    }
}

//输出哈夫曼编码
template<class T>
void huffmanTree<T>::printHuffmanCode() {
    for (int i = 0; i < size; i++) {
        cout << hfCode[i].data << ':' << hfCode[i].code << endl;
    }

}
```


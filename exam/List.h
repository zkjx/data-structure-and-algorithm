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













































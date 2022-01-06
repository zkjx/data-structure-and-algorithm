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



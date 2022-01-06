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

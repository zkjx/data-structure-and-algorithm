/*********Begin**********  和  **********End**********不可删除
在*********Begin*********  和  ********End********之间作答
要求使用指定的类名、对象名、变量名、函数名等，少写漏写不得分

已知循环队列的类型定义如下，请实现出队算法T deQueue();若队列非空删除队首元素，并返回队首元素的值。
其中：队头指针front指向队头元素的前一位置，队尾指针rear指向队尾元素
template <class T>
class seqQueue{
private:
    T *data; 							// 指向存放元素的数组
    int maxSize;					 		// 队列的大小
    int front, rear; 						// 队头和队尾指针
    void resize();							// 扩大队列空间
public:
    seqQueue(int initsize = 100);
    ~seqQueue(){ delete [] data; }
    void clear(){ front = rear = 0; }					// 清空队列
    bool empty()const { return  front == rear; }			// 判空
    bool full()const { return (rear + 1) % MaxSize == front; }		// 判满
    int size()const{ return (rear-front+maxSize)%maxSize; } 		// 队列长度
    void enQueue(const T &x);					// 入队
    T deQueue();							// 出队
    T getHead()const;						// 取队首元素
};

*/
/***************begin***************/
template <class T>
T seqQueue<T>::deQueue()
{
	if(empty())throw outOfRange();
	front=(front+1)%maxSize;
	return data[front];
}
/****************end****************/







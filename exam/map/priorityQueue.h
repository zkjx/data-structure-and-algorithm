#pragma once
#include<iostream>
using namespace std;

template <class elemType>
class priorityQueue {
private:
    int curLength;  	                        // 队列中元素个数
    elemType* data;                             // 指向存放元素的数组
    int  maxSize; 	                            // 队列的大小
    void resize();		                        // 扩大队列空间
    void siftDown(int parent);					// 从parent位置向下调整优先级队列
    void siftUp(int position);					// 从position位置向上调整优先级队列
public:
    priorityQueue();
    priorityQueue(const elemType *data, int size);
    ~priorityQueue() { delete[] data; }
    bool empty()const { return curLength == 0; }// 判空
    int size()const { return curLength; }	    // 求长度
    void buildHeap();				            // 建堆
    void enQueue(const elemType& x);		    // 入队
    elemType deQueue();				            // 出队
    elemType getHead()const {			        // 取队首元素
        if (empty())  cout << "\n已溢出！操作错误！" << endl;
        return  data[1];
    }
};

//入队
template <class elemType>
void priorityQueue<elemType>::enQueue(const elemType& x) {
    if (curLength == maxSize - 1)  resize();
    data[++curLength] = x;	// 下标从1开始
    siftUp(curLength);		// 新入队元素需向上调整
}

//向上调整堆，为提高效率，当双亲的键值大时，采用向下移动双亲数据的策略，而不是交换数据。
template <class elemType>
void priorityQueue<elemType>::siftUp(int position) {					// 从position开始向上调整
    elemType temp = data[position];								        // 保存position位置元素
    for (; position > 1 && temp < data[position / 2]; position = 2)
        data[position] = data[position / 2];							// position位置元素比双亲小，双亲下移
    data[position] = temp;
}

//出队
template <class elemType>
elemType priorityQueue<elemType>::deQueue() {
    if (empty()) cout<<"范围错误！操作失败！";
    elemType min;
    min = data[1];	                                            // 保存最小元素
    data[1] = data[curLength--];								// 队尾元素存入下标1位置（堆顶）
    siftDown(1);		                                        // 从队首（堆顶）向下调整
    return  min; 		                                        // 返回队首元素
}

//为提高效率，采用向上移动数据的策略，而不是交换数据
template <class elemType>
void priorityQueue<elemType>::siftDown(int parent) {
    // 从parent开始向下调整
    int child;
    elemType tmp = data[parent];// 保存parent处结点
    for (; parent * 2 <= curLength; parent = child) {
        child = parent * 2;		// child用于记录较小的子结点
        if (child != curLength && data[child + 1] < data[child])
            child++;			// 右孩子更小
        if (data[child] < tmp)  data[parent] = data[child];
        else  break;
    }
    data[parent] = tmp;
}

//建堆方法二的实现。
template <class elemType>
void priorityQueue<elemType>::buildHeap() {
    for (int i = curLength / 2; i > 0; i--)
        siftDown(i);
    // [curLength/2..1]从下标最大的非终端结点开始调整
}

//构造无序堆，有初始大小和初始序列，调用buildHeap( )建堆。
template <class elemType>
priorityQueue<elemType>::priorityQueue(const elemType* items, int size) :
    maxSize(size + 10), curLength(size) {
    data = new elemType[maxSize];
    for (int i = 0; i < size; i++)
        data[i + 1] = items[i];	// 拷贝元素
}

//构造无序堆，只有初始大小，无初始序列，建堆时需要调用入队操作
template <class elemType>
priorityQueue<elemType>::priorityQueue(){
    int initSize = 100;
    if (initSize <= 0)
        cout << "初始化建堆范围错误！" << endl;
    data = new elemType[initSize];
    maxSize = initSize;
    curLength = 0;
}

//扩大堆空间
template <class elemType>
void priorityQueue<elemType>::resize() {
    elemType* tmp = data; // tmp 指向原堆空间
    maxSize *= 2; //堆空间扩大2倍
    data = new elemType[maxSize]; // data指向新的堆空间
    for (int i = 0; i < curLength; ++i)
        data[i] = tmp[i]; // 复制元素
        delete[]tmp;
}




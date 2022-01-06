#pragma once
#include<typeinfo>
using namespace std;
    //向下调整成堆,参数为待排序序列R，要调整的结点编号pos以及序列大小size。
    template <class Type>
    void siftDown(Type R[], int pos, int size) {
        int child;
        Type tmp = R[pos]; 		// 暂存“根”记录R[pos]
        for (; pos * 2 + 1 < size; pos = child) {
            child = pos * 2 + 1;
            if (child != size - 1 && R[child + 1] > R[child])
                child++;			// 选取两个孩子的大者		
            if (R[child] > tmp) 	// 较大的孩子比双亲大
                R[pos] = R[child];
            else  break;
        }
        R[pos] = tmp; 			// 被调整结点放入正确位置
    }

    //堆排序,参数为待排序序列S，以及序列大小size。
    template <class Type>
    void heapSort(Type R[], int size) {
        int  i;
        // 初始建堆，从最后一个非叶结点开始调堆
        for (i = size / 2 - 1; i >= 0; i--)
            siftDown(R, i, size);
        // 共n-1趟排序（删除堆顶元素后反复调整堆）			
        for (i = size - 1; i > 0; i--) {
            swap(R[0], R[i]);	// 交换堆顶元素与子序列中最后一个元素
            siftDown(R, 0, i);	// 将R[0..i]重新调整为大顶堆
        }
    }

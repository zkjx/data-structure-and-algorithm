#pragma once
using namespace std;
//若以Shell提出的分组方法，则Shell排序的算法如下
template <class Type>
void shellSort(Type R[], int size) {
    int gap, pos, j;	// gap为希尔增量，pos为待插入记录位置
    Type tmp;
    for (gap = size / 2; gap > 0; gap /= 2) {
        for (pos = gap; pos < size; pos++) {
            tmp = R[pos];
            for (j = pos - gap; j >= 0 && R[j] > tmp; j -= gap)
                R[j + gap] = R[j];	// 记录后移 
            R[j + gap] = tmp;		// 将待插入记录放到合适位置
        }
    }
}

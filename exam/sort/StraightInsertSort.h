#pragma once
using namespace std;
//直接插入排序
template <class Type>
void straightInsertSort(Type R[], int size) {
    int pos, j;		// pos为待插入记录位置 
    Type tmp;
    for (pos = 1; pos < size; pos++) {
        tmp = R[pos]; 	// 将待插入记录放进临时变量
        // 从后向前查找插入位置
        for (j = pos - 1; tmp < R[j] && j >= 0; j--)
            R[j + 1] = R[j]; // 将大于待插入记录的记录向后移动
        R[j + 1] = tmp; 	// 将待插入记录放到合适位置
    }
}

//折半插入排序（Binary Insertion Sort）：当第i个记录要插入前i－1个有序记录序列时，
//可利用折半查找方式确定插入位置，以减少比较次数。从而达到减少比较次数的目的 
template <class Type>
void  binaryInsertSort(Type R[], int size) {
    int pos, j, low, high, mid;
    Type tmp;
    for (pos = 1; pos < size; pos++) {// 假定第一个记录有序 
        tmp = R[pos];	// 将待排记录R[pos]暂存到tmp
        low = 0; high = pos - 1;// 设置折半查找的范围
        while (low <= high) {	// 折半查找插入位置
            mid = (low + high) / 2;	// 计算中间位置
            if (tmp < R[mid]) high = mid - 1;
            else low = mid + 1;
        }
        for (j = pos - 1; j >= low; j--)
            R[j + 1] = R[j];	// 记录后移
        R[low] = tmp;		// 插入待排序记录
    }
}

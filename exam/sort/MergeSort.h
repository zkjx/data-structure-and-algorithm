#pragma once
using namespace std;
    template <class Type>
    void  merge(Type R[], Type tmp[], int low, int mid, int high) {
        int i = low, j = mid, k = 0;
        while (i < mid && j <= high)// R中记录由小到大地并入tmp
            if (R[i] < R[j])
                tmp[k++] = R[i++]; // 将R[i]和R[j]的小者拷贝到tmp[k]
            else tmp[k++] = R[j++];
        while (i < mid) 		// 前端剩余R[i.. mid-1]复制到tmp
            tmp[k++] = R[i++];
        while (j <= high) 	// 后端剩余R[j..high]复制到tmp
            tmp[k++] = R[j++];
        for (i = 0, k = low; k <= high; )
            R[k++] = tmp[i++];	// 排好序的记录由tmp拷回R
    }

    //递归2-路归并排序。通过递归调用实现对子序列R[low.. high]的排序过程，将其归并为有序段。
    template <class Type>
    void  mergeSort(Type R[], Type tmp[], int low, int high) {
        if (low == high) return;
        int mid = (low + high) / 2; 	// 从中间划分为两个子序列
        mergeSort(R, tmp, low, mid);// 递归归并子序列R[low.. mid] 
        mergeSort(R, tmp, mid + 1, high);// 递归归并子序列R[mid+1.. high]  
        merge(R, tmp, low, mid + 1, high);	// 归并两个子序列
    }

    //2-路归并排序的接口函数。参数为待排序序列R，以及序列大小size。
    template <class Type>
    void mergeSort(Type R[], int size) {
        Type* tmp = new Type[size];	// 辅助数组
        mergeSort(R, tmp, 0, size - 1);
        delete[] tmp;
    }


#pragma once
using namespace std;
    //取关键字key的第i位。参数为关键字key以及当前位i。
    int getDigit(int key, int i) {
        for (int j = 1; j < i; j++)
            key = key / 10;
        key = key % 10;
        return key;
    }

    //按关键字的第i位进行一趟基数排序。参数为待排序序列R，序列大小size以及当前位i。
    const int radix = 10; 		// 基数为10
    template <class Type>
    void LSD(Type R[], int size, int i) {
        Type* bucket = new Type[size];
        int* position = new int[radix];	// 计数器  
        int j, k;
        for (j = 0; j < radix; j++)	// 计数器清0
            position[j] = 0;
        for (j = 0; j < size; j++) {
            k = getDigit(R[j], i);	// 计算每个桶的容量
            position[k]++; ;
        }
        // 按每个桶的容量，分配bucket数组的位置  
        for (j = 1; j < radix; j++)
            position[j] = position[j - 1] + position[j];
        for (j = size - 1; j >= 0; j--) {	// 逆序一趟分配
            k = getDigit(R[j], i); 				  // 按关键字第i位的数值存入bucket中  
            bucket[--position[k]] = R[j];
        }
        for (j = 0; j < size; j++)	// 顺序一趟收集 
            R[j] = bucket[j];  	// 将桶中记录收集到数组R  
        delete[]bucket;
        delete[]position;
    }

    //基数排序。参数为待排序序列R，以及序列大小size。
    template <class Type>
    void radixSort(Type R[], int size) {
        int i, d = 1, max = R[0];
        for (i = 1; i < size; i++)
            if (R[i] > max) max = R[i];	// 求最大关键字  
        while (max = max / 10) d++;  // 求关键字的最大宽度d
        for (i = 1; i <= d; i++)	// 从低位开始，共进行d趟基数排序 
            LSD(R, size, i);
    }


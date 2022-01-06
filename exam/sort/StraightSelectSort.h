#pragma once
using namespace std;
    //直接选择排序
    template <class Type>
    void straightSelectSort(Type R[], int size) {
        int  pos, min, j;// min为一趟排序中最小记录下标
        // pos为待存放当前最小记录的位置
        for (pos = 0; pos < size - 1; pos++) {
            min = pos;
            for (j = pos + 1; j < size; ++j)
                if (R[j] < R[min]) min = j;// 查找最小记录
            // 调用STL中的swap，头文件algorithm	    
            if (pos != min) swap(R[pos], R[min]);
        }
    }
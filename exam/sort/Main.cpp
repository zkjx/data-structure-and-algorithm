
//============================================================================
// @FileName     ：Main.cpp
// @Author       ：04191315_HeXiang
// @Version      ：1.0
// @Date         ：2020.12.3
// Description   ：
/*
随机生成自定义个整型数，
用直接插入排序、希尔排序、冒泡排序、直接选择排序、快速排序、堆排序、归并排序的方法对其排序并统计各排序方法耗时。
 */
 //============================================================================

#define _CRT_SECURE_NO_WARNINGS
#include"BubbleSort.h"
#include"HeapSort.h"
#include"MergeSort.h"
#include"QuickSort.h"
#include"RadixSort.h"
#include"ShellSort.h"
#include"StraightInsertSort.h"
#include"StraightSelectSort.h"
#include<iostream> 
#include<ctime>
#include<stdlib.h>
#include<algorithm>
using namespace std;
int sortSize;
int* sortArray;

void setArray() {
    int size;
    cout << "请自定义数组的规模：";
    cin >> size; cout << endl;
    sortSize = size;
    srand(0);
    sortArray = new int[sortSize];
    cout << "数组随机生成如下：" << endl;
    for (int i = 0; i < sortSize; i++)
    {   
        sortArray[i] = rand() % 101;
        cout << sortArray[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << "\n-----------------------------------" << endl;
}

template <class Type>
void testSort(void(*sort)(Type R[] ,int size)){
    clock_t start, finish;
    double duration;
    cout << "当前数组的规模为："<<sortSize<<endl;
    cout << "当前的数组为：" << endl;
    int* array = new int[sortSize];
    for (int i = 0; i < sortSize; i++)
    {  
        cout << (array[i]=sortArray[i]) << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    start = clock();
    sort(array, sortSize);
    finish = clock();
    duration = (double)(finish - start);
    cout << "\n排序后的数组为：" << endl;
    for (int i = 0; i < sortSize; i++)
    {
        cout << array[i] << " ";
        if ((i + 1) % 10 == 0) cout << endl;
    }
    cout << "\n排序耗时为：" << duration << " ms\n";
    cout << "\n-----------------------------------" << endl;
}



int main()
{
    setArray();
    cout << "直接插入排序：" << endl;
    testSort(straightInsertSort<int>);
    cout << "折半插入排序：" << endl;
    testSort(binaryInsertSort<int>);
    cout << "希尔排序：" << endl;
    testSort(shellSort<int>);
    cout << "直接选择排序：" << endl;
    testSort(straightSelectSort<int>);
    cout << "堆排序：" << endl;
    testSort(heapSort<int>);
    cout << "冒泡排序：" << endl;
    testSort(bubbleSort<int>);
    cout << "快速排序：" << endl;
    testSort(quickSort<int>);
    cout << "归并排序：" << endl;
    testSort(mergeSort<int>);
    cout << "基数排序：" << endl;
    testSort(radixSort<int>);
    cout << "各种排序已完成！" << endl;
    cout << "\n-----------------------------------" << endl;
    system("pause");
    return EXIT_SUCCESS;

}

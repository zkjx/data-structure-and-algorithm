#pragma once
template <class Type>
class Sort {
public:
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
//可利用折半查找（在查找章节已介绍）方式确定插入位置，以减少比较次数。从而达到减少比较次数的目的 
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

//冒泡排序算法
template <class Type>
void bubbleSort(Type R[], int size) {
    int i, j;
    bool flag = true;		// 记录一趟排序后是否发生过交换
    for (i = 1; i < size && flag; ++i) {
        flag = false;		// 假定本趟排序没有交换
        for (j = 0; j < size - i; ++j)
            if (R[j + 1] < R[j]) {	// 逆序		
                swap(R[j], R[j + 1]);	// 调用STL中的swap进行交换
                flag = true;
            }
    }
}

//递归快速排序。参数为待排序序列S，以及排序区间的下界low和上界high。
template <class Type>
void quickSort(Type S[], int low, int high) {
    int pivot;
    if (low >= high) return;
    pivot = partition(S, low, high); // 一次划分，返回枢轴位置
    quickSort(S, low, pivot - 1);	// 对枢轴左边一半快速排序
    quickSort(S, pivot + 1, high);	// 对枢轴右边一半快速排序
}

//一趟快速排序（或一次划分）。参数为待排序序列S，以及排序区间的下界low和上界high。
template <class Type>
int partition(Type S[], int low, int high) {
    Type  tmp = S[low];		    // 暂存轴值
    while (low != high) {		// 开始进行分割
        while (low < high && S[high] >= tmp)high--;	// 找<轴值的记录
        if (low < high) { S[low] = S[high]; low++; }
        // 该记录移动到小下标端
        while (low < high && S[low] <= tmp) low++;	// 找>轴值的记录
        if (low < high) { S[high] = S[low]; high--; }
        // 该记录移动到大下标端
    }
    S[low] = tmp;		// 把轴值回填到分界位置上
    return low;			// 返回枢轴位置
}

//快速排序的接口函数。参数为待排序序列S，以及序列大小size。
template <class Type>
void quickSort(Type S[], int size) {
    quickSort(S, 0, size - 1);
}

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

//堆排序。参数为待排序序列S，以及序列大小size。
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

//向下调整成堆。参数为待排序序列R，要调整的结点编号pos以及序列大小size。
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


//归并相邻的两个有序子序列。将有序序列R[low..mid-1]和R[mid..high]归并为有序序列R[low..high]。
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

//取关键字key的第i位。参数为关键字key以及当前位i。
int getDigit(int key, int i) {
    for (int j = 1; j < i; j++)
        key = key / 10;
    key = key % 10;
    return key;
}

};
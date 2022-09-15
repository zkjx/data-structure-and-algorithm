// 说明：可设计选择轴值的算法，尽量选值处于中间的元素做轴
template <class Type>
int partition( Type S[], int low, int high){ 	
    Type  tmp = S[low];								// 暂存轴值
    while(low != high){								// 开始进行分割
        while (low<high && S[high]>=tmp)high--;			// 大下标端找 < 轴值的记录
        if (low < high) { S[low] = S[high]; low++;}		// 该记录移动到小下标端
        while (low < high && S[low] <=tmp) low++;		// 小下标端找 > 轴值的记录
        if (low < high) { S[high] = S[low]; high--;}		// 该记录移动到大下标端
    } 
    S[low] = tmp;									// 把轴值回填到分界位置上
    return low;									// 返回枢轴位置
}
template <class Type>
void quickSort(Type S[], int low, int high){ 
    int pivot;
    if (low >= high) return; 
    pivot = partition(S, low, high); 					// 一次划分，返回枢轴位置

    quickSort( S, low, pivot-1);						// 对枢轴左边一半快速排序
    quickSort( S, pivot+1, high);						// 对枢轴右边一半快速排序
}
template <class Type>
void quickSort(Type S[], int size){ 	
    quickSort(S, 0, size-1); 
}


template <class Type>
void findJ(Type A[],int n,int j){
	int i = partition (A,1,n);
	while(i!=j)
		if(i<j) i = partition(A,i+1,n);	// 在后半部分继续进行划分
		else    i = partition(A,1,i-1);	// 在前半部分继续进行划分
	cout<<A[i]<<endl;
}




int getDigit(int key,int i) { 
	for(int j=1;j<i;j++)
		key = key/10;  
	key = key%10; 
	return key; 
}

const int radix = 10;
template <class Type>
void LSD(Type R[],int size,int i)  { 
    Type* bucket = new Type[size];  
    int *count = new int[radix];			// 计数器  
    int j,k;
    for(j = 0; j < radix; j++)				// 计数器清0
        count[j] = 0;					 
    for(j = 0; j < size; j++) { 
        k = getDigit(R[j],i);				// 计算每个桶的容量
        count[k]++; ;
    }  
    for(j = 1; j < radix; j++)  
        count[j] = count[j - 1] + count[j]; 	// 按每个桶的容量，分配bucket数组的位置  
    for(j = size - 1; j >= 0; j--){			// 一趟分配：按关键字第i位存入bucket中  
        k = getDigit(R[j],i);
        bucket[--count[k]] = R[j];    
    }  
    for(j = 0; j < size; j++)				// 一趟收集：将桶中内容复制到R  
        R[j] = bucket[j];  
    delete []bucket;
    delete []count;
}

template <class Type>
void radixSort(Type R[],int size){		// 基数排序    
    int i,d=1,max = R[0];
	for(i=1;i<size;i++)
		if(R[i] > max)max = R[i];		// 求最大元素到变量m中  
	while(max = max/10)d++;             // 求关键字的最大宽度d
    for(i = 1; i <= d; i++)				// 进行d趟基数排序 
		LSD(R,size,i);					// 按关键字的第i位进行基数排序 
}  
template <class Type>
void straightInsertSort(Type R[], int size)
{
	int pos,j;						// pos：待插入记录位置 
	Type tmp;
	cout<<"insert sort:\n";
	for (pos=1; pos<size; pos++) {
		tmp = R[pos]; 				// 将待插入记录放进临时变量
		// 从后向前查找插入位置,将大于待插入记录向后移动
		for ( j = pos-1; tmp < R[j] && j >= 0; j--)
			R[j+1] = R[j]; 			// 记录后移 
		R[j+1] = tmp; 				// 将待插入记录放到合适位置
    }
} 
template <class Type>
void  binaryInsertSort(Type R[],int size){
	int pos,j,low,high,mid;
	Type tmp;
	cout<<"binary insert sort:\n";
	for(pos=1;pos<size;pos++){				//假定第一个记录有序 
		tmp = R[pos];						//将待排记录R[pos]暂存到tmp
		low = 0; high = pos-1;				//设置折半查找的范围								
		while(low <= high){				//在R[low..high]中折半查找有序插入位置
			mid = (low+high)/2;			//折半
			if(tmp < R[mid]) high = mid-1;    //插入点在低半区 
			else low = mid+1;                          //插入点在高半区
		}
		for (j=pos-1;j >= low;j--)
			 R[j+1] = R[j];				//记录后移
		R[low] = tmp;				 //插入

	}
}

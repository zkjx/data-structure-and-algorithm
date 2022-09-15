// 将有序的R[low..mid-1]和R[mid..high]归并为有序的R[low..high]
template <class Type>
void merge(Type R[],Type tmp[],int low, int mid, int high){	
 	int i=low, j=mid, k=0;
	//Type *tmp = new Type[high-low+1];
 	while (i<mid && j <= high)							// R中记录由小到大地并入tmp
		if (R[i] < R[j])  tmp[k++] = R[i++];			// 将R[i]和R[j]的小者拷贝到tmp[k]
		else tmp[k++] = R[j++]; 
 	while ( i<mid )  tmp[k++] = R[i++];					// 将剩余的R[low.. mid]复制到tmp
 	while ( j<=high )  tmp[k++] = R[j++];				// 将剩余的R[j..high]复制到tmp
 	for (i=0, k = low; k<=high; ) R[k++] = tmp[i++];	// 排好序的tmp[low..high]拷贝到R[low..high]
 	//delete [] tmp;
} 
template <class Type>
void mergeSort(Type R[],Type tmp[], int low, int high){ 
	if (low == high) return;
	int mid = (low+high)/2;
	mergeSort(R,tmp,low, mid);					// 递归地将R[low.. mid]归并为有序的R[low.. mid]
	mergeSort(R,tmp,mid+1, high);				// 递归地将R[mid+1.. high]归并为有序的R[mid+1.. high]
	merge(R,tmp,low,mid+1,high);				// 将R[low.. mid]和R[mid+1.. high]归并到R[low.. high]
} 
template <class Type>
void mergeSort(Type R[], int size)
{ 
	Type *tmp = new Type[size];
	mergeSort(R,tmp,0, size-1); 
	delete [] tmp;
}

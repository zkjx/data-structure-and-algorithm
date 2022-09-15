
template <class Type>
void straightSelectSort(Type R[], int size)
{	int  pos, min ,j;						// min：一趟选择中最小元素下标
	cout<<"select sort:\n";
 	for (pos = 0; pos < size -1; pos++) {	// pos：待存放最小记录位置
		min = pos;
		for (j = pos+1; j < size; ++j)
			if (R[j] < R[min]) min = j;		// 查找最小记录	 	
		if(pos != min)swap(R[pos],R[min]);					// 交换：tmp = R[pos]; R[pos] = R[min]; R[min] = tmp;
 	}
} 

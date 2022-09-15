template <class Type>
void bubbleSort(Type R[], int size)
{  	int i, j;
   	bool flag=true;						// 记录一趟排序后是否发生过交换
   	for (i = 1; i < size && flag; ++i) {
      		flag = false;				// 假定本趟排序没有交换
      		for (j = 0; j < size-i; ++j)
        	    if (R[j+1] < R[j]){		// 逆序		
					swap(R[j],R[j+1]);		// 交换：tmp = R[j]; R[j] = R[j+1]; R[j+1] = tmp; 
					flag = true;
				}
     	}
  } 

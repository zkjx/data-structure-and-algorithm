template <class Type>
void shellSort(Type R[], int size)
{	int gap, pos, j;					
 	Type tmp;
 	for (gap = size/2; gap > 0; gap /= 2){	// gap:希尔增量,即步长
		for (pos = gap; pos < size; pos++) {	// pos:待插入记录位置
	 	    tmp = R[pos];
		    for (j = pos - gap; j >= 0 && R[j] > tmp;  j -= gap) 
				R[j+gap] = R[j];				// 记录后移 
	 		R[j+gap] = tmp;					// 将待插入记录放到合适位置
		}
	}
} 

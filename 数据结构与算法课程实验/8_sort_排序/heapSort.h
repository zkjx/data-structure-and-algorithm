
template <class Type>
void siftDown( Type R[], int pos, int size )
{ 	int child;
  	Type tmp = R[ pos ];
	    
  	for( ; pos * 2 + 1 < size; pos = child )
	{  child = pos * 2 + 1;
	    if( child != size - 1 && R[ child + 1 ] > R[ child ] )
	         child++;							// 选取两个孩子的大者							
	    if( R[ child ] > tmp )   R[ pos ] = R[ child ];  
		else  break;
	}
  	R[ pos ] = tmp;
}
// 利用大根堆，对数组R的前size个元素排序
template <class Type>
void heapSort(Type R[], int size)				
{	int  i; 
 	//Type tmp;
 	// 创建初始堆，调用siftDown( R, i, size )调整为大根堆
 	for(  i = size / 2 - 1; i >= 0; i-- )		// 从最后一个非叶结点开始调堆
		siftDown( R, i, size );					

 	for ( i = size - 1; i > 0;i--) {	 		// size-1次出队，即（队首）堆顶元素与堆（队）尾元素交换
		swap(R[0],R[i]);							// 交换：tmp = R[0]; R[0] = R[i]; R[i] = tmp;					
	 	siftDown( R, 0, i );					// 自顶向下调堆

	}	
}
 

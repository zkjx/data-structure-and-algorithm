#include<iostream>
#include <ctime>
#include <algorithm>
using namespace std;
#include"heapSort.h"
#include"shellSort.h"
#include"straightInsertSort.h"
#include"straightSelectSort.h"
#include"bubbleSort.h"
#include"quickSort.h"
#include"mergeSort.h"
#include"radixSort.h"
#define N 8
int  A[N] ={236,180,366,145,22,9,416,636};
//int  A[N] ={9,16,22,36,36,45,66,80};
//交换数组中的两个记录
/*
template <class Type>
void Swap(Type &a,Type &b){
	Type tmp = a;
	a = b;
	b = tmp;	
}
*/
// 测试各种排序函数				
template <class Type>
void testSort(void (*sort)( Type R[],int size ))
{
	clock_t start, finish;
	double duration;
	
	srand(1);								// 设定随机函数的种子						
	cout<<"数组规模："<<N<<endl;
	int * array =new int[N];				// 产生随机数组,长度为N
	//for(int i=0;i<N;i++)
	//	cout<<(array[i]=rand() % (N*8))<<"\t";	// 0到N-1之间的随机数

	for(int i=0;i<N;i++)
		cout<<(array[i]=A[i])<<"\t";		
	cout<<endl;

	start = clock();
	sort(array,N);							// 排序
	finish = clock();
	duration = (double)(finish - start);	// 没/ CLOCKS_PER_SEC;

	for(int i=0;i<N;i++)
		cout<<array[i]<<"\t";
	cout<<"排序耗时"<<duration<<"ms\n";
	cout<<"--------------------------------------------------------------------------\n";
}
int main()
{
	cout<<"直接插入排序,"; 
	testSort(straightInsertSort<int>);	
	cout<<"折半插入排序,"; 
	testSort(binaryInsertSort<int>);	
	cout<<"希尔排序,"; 
	testSort(shellSort<int>);	
	cout<<"直接选择排序,"; 
	testSort(straightSelectSort<int>);	
	cout<<"堆排序,"; 
	testSort(heapSort<int>);
	cout<<"冒泡排序,"; 
	testSort(bubbleSort<int>);
	cout<<"快速排序,"; 
	testSort(quickSort<int>);
	cout<<"归并排序,"; 
	testSort(mergeSort<int>);
	cout<<"基数排序,"; 
	testSort(radixSort<int>);
	char x;
	cin>>x;
}

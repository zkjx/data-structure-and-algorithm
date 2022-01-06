/*********Begin**********  和  **********End**********不可删除
在*********Begin*********  和  ********End********之间作答
要求使用指定的类名、对象名、变量名、函数名等，少写漏写不得分

请实现冒泡排序算法。
冒泡排序算法基本思想是对所有相邻记录的关键字值进行比较，如果不满足排序要求（即逆序），则将其交换，最终直到所有记录排好序为止。若在某一趟排序中没有发生交换操作，说明待排序记录已全部有序，排序提前结束。

注意:请按照如下示例格式书写答案，请将外层循环控制变量命名为i，内层循环的控制变量命名为j，标识有无交换发生的变量命名为flag。
template <class Type>
void bubbleSort(Type R[], int size) {
 int i, j;
      bool flag = true;
  ......

}

*/
/***************begin***************/

template<class Type>
void bulleSort(Type R[],int size){
	int i,j;
	bool flag = true;
	for(i=1;i<size&&flag;++i){
		flag=false;
		for(j=0;j<size-1;++j){
			if(R[j+1]<R[j]){
				swap(R[j],R[j+1]);
				flag=true;
			}
		}
	}
}
/****************end****************/

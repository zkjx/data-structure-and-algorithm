#ifndef _SEQLIST_H_
#define _SEQLIST_H_

template <class elemType>					// elemType为顺序表存储的元素类型
class seqList: public List<elemType>
{ 
private:
	elemType *data;							// 利用数组存储数据元素 
    int curLength;							// 当前顺序表中存储的元素个数
    int maxSize;							// 顺序表的最大长度
    void resize();							// 表满时扩大表空间
public:
    seqList(int initSize = 10);				// 构造函数 
	seqList(seqList & sl) ;					// 拷贝构造函数
    ~seqList()  {delete [] data;}			// 析构函数 
    void clear()  {curLength = 0;}			// 清空表，只需修改curLength
	bool empty()const{return curLength==0;}	// 判空
    int size() const  {return curLength;}	// 返回顺序表的当前存储元素的个数 
    void insert(int i,const elemType &value);	// 在位置i上插入一个元素value，表的长度增1
    void remove(int i);						// 删除位置i上的元素value，若删除位置合法，表的长度减1 
    int search(const elemType &value) const ;	// 查找值为value的元素第一次出现的位序
    elemType visit(int i) const;			// 访问位序为i的元素值，“位序”0表示第一个元素，类似于数组下标
    void traverse() const ;					// 遍历顺序表
	void inverse();							// 逆置顺序表
	bool Union(seqList<elemType> &B);
};
template <class elemType>
seqList<elemType>::seqList(int initSize) 
{ 
	if (initSize <= 0) throw badSize();
	maxSize = initSize;						
	data = new elemType[maxSize];			// 创建一个大小为maxSize的顺序表
	curLength = 0;							
} 
template <class elemType>
seqList<elemType>::seqList(seqList & sl) { 
    maxSize = sl.maxSize;						
    curLength = sl. curLength;							
    data = new elemType[maxSize];	
    for (int i = 0; i < curLength; ++i)
        data[i] = sl.data[i];		
}
template <class elemType>
void seqList<elemType>::insert(int i, const elemType &value)
{ 
    if (i < 0 || i > curLength) throw outOfRange();	// 合法的插入位置为[0..n]
    if (curLength == maxSize) resize();			// 表满，扩大数组容量
    for (int j = curLength; j > i; j--)			// 下标j-1在[curLength-1..i]范围
        data[j] = data[j-1];						// 的元素往后移动一步
    data[i] = value; 							// 将 value 置入位序为i的位置
    ++curLength;								// 表的实际长度增1
}

template <class elemType>
void seqList<elemType>::remove(int i) 
{ 
    if (i < 0 || i > curLength-1) throw outOfRange(); 	// 合法的删除位置为[0..n-1] 
    for (int j = i; j < curLength - 1; j++)			// 下标j+1在[i+1..n-1]范围
        data[j] = data[j+1] ;						// 的元素往前移动一步
    --curLength; 									// 表的实际长度减1
}

template <class elemType>
void seqList<elemType>::resize()
{ 
    elemType *p = data;							// p指向原顺序表空间
    maxSize *= 2;									// 表空间扩大2倍
    data = new elemType[maxSize];					// data指向新的表空间
    for (int i = 0; i < curLength; ++i)				
        data[i] = p[i];							// 复制元素
    delete [] p;
}

template<class elemType>
int seqList<elemType>::search(const elemType & value) const
{
    for (int i = 0; i < curLength; i++)
        if (value == data[i]) return i;
    return -1;								// 查找失败返回-1
}

template<class elemType>
elemType seqList<elemType>::visit(int i) const
{
	if (i < 0 || i > curLength-1 ) throw outOfRange();// 合法的访问位置为[0..n-1] 
	return data[i];
}

template<class elemType>
void seqList<elemType>::traverse()const
{
    if(empty())cout<<"List is empty\n";		// 空表没有元素
    else{
        cout<<"output element:\n";
        for (int i = 0; i < curLength; i++)		// 依次访问顺序表中所有元素
            cout<<data[i]<<"  ";  
        cout<<endl;  	 					
    }						
}

template<class elemType>
void seqList<elemType>::inverse() 
{
    elemType tmp;
    for (int i = 0; i < curLength/2; i++){			// 控制交换的次数 
        tmp = data[i];
        data[i] = data[curLength-i-1];
        data[curLength-i-1] = tmp;
    }
}
template<class elemType>
bool seqList<elemType>::Union(seqList<elemType> &B){	
	int m,n,k,i,j;
    m = this->curLength; 			// 当前对象为线性表A
    n = B.curLength;				// m，n分别为线性表A和B的长度
    k = m+n-1;						// k为结果线性表的工作指针（下标）
    i = m-1, j = n-1;				// i，j分别为线性表A和B的工作指针（下标）
    if(m+n > this->maxSize){				// 判断A表空间是否足够大
        resize();						// 空间不够，扩大表空间
    }
    while (i>=0 && j>=0)				// 合并顺序表，直到一个表为空
        if (data[i] >= B.data[j])  data[k--] = data[i--];
        else  data[k--] = B.data[j--];	// 默认当前对象，this指针可省略
    while(j>=0) 						// 将B表的剩余元素复制到A表
        data[k--] = B.data[j--];
    curLength = m+n; 					// 修改A表长度
    return true;
}



#endif

// 和书上代码差别：创建的huffman树左边权值小，右边权值大
#ifndef _HUFFMAN_TREE_H_
#define _HUFFMAN_TREE_H_

template <class T>
class huffmanTree{
private:
    struct  Node{  
        T data;								// 结点数据域
        int weight;							// 结点的权值		  
        int parent, left, right;					// 双亲及左右孩子的下标
        Node() {								// 构造函数
            weight = parent = left = right = 0; 
        };
    };
	struct huffmanCode {			
		T data;
		string code;				// 保存data的哈夫曼编码
		huffmanCode(){ code=""; }	// 构造函数

	};
    Node *hfTree;					// 顺序结构，保存huffman树
	huffmanCode *hfCode;			// 顺序结构，保存结点的huffman编码
    int size;									// 叶结点数
    void selectMin(int m,int& p);				// 选出当前集合中的最小元素
public:
    huffmanTree(int initSize);  	// 构造函数
    ~huffmanTree() {delete [] hfTree;delete []hfCode;}			// 析构函数
	void createHuffmanTree(const T *d, const double *w);//创建哈夫曼树
    void huffmanEncoding();			// 获取huffman编码
    void printHuffmanCode();				// 输出huffman编码
}; 
template <class T>
huffmanTree<T>::huffmanTree(int initSize){
    size = initSize;					// size为初始集合中的结点数
    hfTree = new Node[2*size];
	hfCode = new huffmanCode[size];
}
template <class T>
void huffmanTree<T>::createHuffmanTree(const T *d, const double *w) {  
    int i, min1, min2;				// 最小树、次最小树的下标			
    for( i = size; i <2*size; ++i){	// size个叶结点置初值	
		hfTree[i].data = d[i - size];
		hfTree[i].weight = w[i - size];
		//hfTree[i].parent = hfTree[i].left = hfTree[i].right = 0;
	}     
	
	for( i = size - 1; i > 0; --i){// 进行合并，产生n-1个新结点  	 
		selectMin(i+1,min1);		// 选出parent 的值为0且权值最小的两个结点min1、min2
		hfTree[min1].parent=i;
   		selectMin(i+1,min2);	
		hfTree[min2].parent=i;
		// 新结点i赋值
		hfTree[i].weight =hfTree[min1].weight + hfTree[min2].weight;
		hfTree[i].left = min1;   hfTree[i].right = min2; 
		//hfTree[i].parent = 0;
	}  
} 
template<class T>
void huffmanTree<T>::selectMin(int m,int& p){  
	int j=m;
	while(hfTree[j].parent != 0)j++;		// 跳过已有双亲的结点

	for ( p=j,j+=1 ;j<2*size; j++)			// 向后扫描剩余元素
		if((hfTree[j].weight<hfTree[p].weight) && 0==hfTree[j].parent )
			p = j;							// 如果发现更小的记录，记录它的位置			
}
template <class T>
void huffmanTree<T>::huffmanEncoding() {	 
	int f,p;						// p是当前正在处理的结点，f是p的双亲的下标
	for (int i = size; i < 2*size; ++i){
		hfCode[i - size].data = hfTree[i].data;

        f = hfTree[i].parent; p = i;
		while (f) {
			if (hfTree[f].left == p)
				hfCode[i - size].code = '0' + hfCode[i - size].code;
		    else hfCode[i - size].code = '1' + hfCode[i - size].code;
			p = f; f = hfTree[p].parent;
		}  
	}  
} 
template<class T>
void huffmanTree<T>::printHuffmanCode(){
	for (int i=0; i< size; i++) 
			cout<< hfCode[i].data <<':'
				<< hfCode[i].code << endl;
}

#endif
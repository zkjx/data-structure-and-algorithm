#pragma once
using namespace std;
template <class T>
class huffmanTree {
private:
    struct  Node {
        T data;				            // 结点的数据域
        int weight;			            // 结点的权值		  
        int parent, left, right;		// 双亲及左右孩子的下标
        Node() {				        // 构造函数
            weight = parent = left = right = 0;
        };
    };
    struct huffmanCode {
        T data;
        string code;			        // 保存data的哈夫曼编码
        huffmanCode() { code = ""; }	// 构造函数，编码前code是空串
    };
    Node* hfTree;		                // 顺序结构，保存huffman树
    huffmanCode* hfCode;	            // 顺序结构，保存huffman编码
    int size;			                // 叶结点数
    void selectMin(int m, int& p);	    // 选出当前集合中的最小元素
public:
    huffmanTree(int initSize);  	    // 构造函数
    ~huffmanTree() { delete[] hfTree; delete[]hfCode; }
    void createHuffmanTree(const T* d, const double* w);
                                        // 创建哈夫曼树
    void huffmanEncoding();	            // 获取huffman编码
    void printHuffmanCode();	        // 输出huffman编码
};

//构造函数
template <class T>
huffmanTree<T>::huffmanTree(int initSize) {
    size = initSize;	            // size为初始集合中的结点数
    hfTree = new Node[2 * size];
    // 哈夫曼树采用顺序储存结构
    hfCode = new huffmanCode[size]; // 哈夫曼编码
}

//根据叶结点数据数组d及其权值数组w创建哈夫曼树。
template <class T>
void huffmanTree<T>::createHuffmanTree(const T* d, const double* w) {
    int i, min1, min2;		            // 最小树、次最小树的下标
    for (i = size; i < 2 * size; ++i) {	// size个叶结点赋值
        hfTree[i].data = d[i - size];
        hfTree[i].weight = w[i - size];
    }
    for (i = size - 1; i > 0; --i) {   // 合并产生n-1个新结点  
     // 选出parent 的值为0且权值最小的两棵子树min1、min2作为结点i的左右孩子
        selectMin(i + 1, min1);	hfTree[min1].parent = i;
        selectMin(i + 1, min2);	hfTree[min2].parent = i;
        hfTree[i].weight = hfTree[min1].weight + hfTree[min2].weight;
        hfTree[i].left = min1;
        hfTree[i].right = min2;
    }
}

//选出parent 的值为0且权值最小的子树的根结点的下标。
template<class T>
void huffmanTree<T>::selectMin(int m, int& p) {
    int j = m;
    while (hfTree[j].parent != 0) j++;	    // 跳过已有双亲的结点
    for (p = j, j += 1; j < 2 * size; j++)	// 向后扫描剩余元素
        if ((hfTree[j].weight < hfTree[p].weight)
            && 0 == hfTree[j].parent)
            p = j;			                // 发现更小的记录，记录它的位置
}

//根据哈夫曼树为每个叶结点生成哈夫曼编码。
template <class T>
void huffmanTree<T>::huffmanEncoding() {
    int f, p;		                   // p是当前正在处理的结点，f是p的双亲的下标
    for (int i = size; i < 2 * size; ++i) {
        hfCode[i - size].data = hfTree[i].data;
        p = i;
        f = hfTree[p].parent;
        while (f) {
            if (hfTree[f].left == p)   // p是其双亲f的左孩子，编码+‘0’
                hfCode[i - size].code = '0' + hfCode[i - size].code;
            else  		               // p是其双亲f的右孩子，编码+‘1’
                hfCode[i - size].code = '1' + hfCode[i - size].code;
            p = f;
            f = hfTree[p].parent;
        }
    }
}

template<class T>
void huffmanTree<T>::printHuffmanCode() {
    for (int i = 0; i < size; i++) {
        cout << hfCode[i].data << ':' << hfCode[i].code << endl;
    }

}
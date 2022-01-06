
//============================================================================
// @FileName     ：Main.cpp
// @Author       ：04191315_HeXiang
// @Version      ：1.0
// @Date         ：2020.11.29
// Description   ：树的应用
/*
哈夫曼树和哈夫曼编码：从终端输入若干个字符，统计字符出现的频率，将字符出现的频率作为结点的权值，
建立哈夫曼树，然后对各字符进行哈夫曼编码。最后打印哈夫曼树和对应的哈夫曼编码。
 */
 //============================================================================

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>  
#include<string>
#include<cstdlib>
#include"huffmanTree.h"
using namespace std;

void test_huffmanTree() {
    cout << "请输入一个字符串：" << endl;
    string str;
    getline(cin, str);
    int strLength = str.size();
    char *d = new char[strLength];
    strcpy(d, str.c_str());
    double* w = new double[strLength];
    cout << "\n请依次输入字符串中每个字符相应的权值：" << endl;
    double weight;
    for (int i = 0; i < strLength; i++) {
        cin >> weight;
        w[i] = weight;
    }
    huffmanTree<char> tree(strLength);
    tree.createHuffmanTree(d, w);
    tree.huffmanEncoding();
    cout << "\n" << "字符：" << str << "的哈夫曼编码如下：\n" << endl;
    tree.printHuffmanCode();
    delete[] w,d;
}
int main()
{
    test_huffmanTree();
    cout << "\n-----------------------------------" << endl;
    system("pause");
    return EXIT_SUCCESS;

}

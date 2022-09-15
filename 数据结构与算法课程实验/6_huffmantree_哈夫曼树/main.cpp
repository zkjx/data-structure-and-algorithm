#include<iostream>
#include<string>
#include<cstdlib>
using namespace std;
#include"huffmanTree.h"
int main(){	
	char d[] = "GOLESD ";
	double w[] = {4,6,1,2,1,1,2};
	huffmanTree<char> tree(7);
	tree.createHuffmanTree(d,w);
	tree.huffmanEncoding();
	tree.printHuffmanCode();

	system("pause");
	return 0;
} 

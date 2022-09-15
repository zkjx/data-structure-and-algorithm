#include<queue>
#include<stack>
#include<iostream>
#include <cstdlib>    
using namespace std;
#include"BinaryLinkedList.h"

//创建一棵如下所示的二叉树 (如图所示)   
//                A   
//              /   \   
//             B      C   
//           /   \     \
//          D     E      F
//               /      / \
//              G      H   I
// 
//假定data域为字符型，输入前序序列(*表示NULL为外部结点)：ABD**EG***C*FH**I**
//此时，根据该序列能够唯一确定一棵二叉树
//层次序列同理，即输入带外部结点的层次序列ABCDE*F**G*HI******

template <class T> 
void testBinaryTree(BinaryLinkList<T> &tree)
{  	
	cout<<"输入带外部结点的前序遍历序列(*表示NULL为外部结点)："; tree.preOrderCreate('*');
	cout << "高度为：" << tree.height() << endl;
	cout << "规模为：" << tree.size() << endl;
	cout << "叶子数：" << tree.leafNum() << endl;
	cout << "前序遍历：";  tree.preOrderWithStack();
	cout << "\n中序遍历：";  tree.inOrderWithStack();
	cout << "\n后序遍历：";  tree.postOrderWithStack();  
	cout << "\n层次序遍历："; tree.levelOrderTraverse();
	cout <<endl;
}

int main()
{
	BinaryLinkList<char> tree;
	testBinaryTree(tree);
	system("pause");
	return 0;
}

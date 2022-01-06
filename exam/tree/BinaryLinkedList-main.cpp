
//============================================================================
// @FileName     ：main.cpp
// @Author       ：04191315_HeXiang
// @Version      ：1.0
// @Date         ：2020.11.28
// Description   ：二叉树的定义、递归遍历及其它基本操作的实现
/*
实现二叉链表表示的二叉树，完成二叉树的基本操作：
初始化二叉树、按前序次序建立一个二叉树、检查二叉树是否为空、
按任一种遍历次序（包括按前序、中序、后序、按层次）
输出二叉树中的所有结点、求二叉树的深度、求二叉树中所有结点数、清除二叉树。
 */
 //============================================================================

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<Windows.h>
#include"BinaryLinkedList.h"
using namespace std;

//主界面
int scan() {
	cout << "  =================================================================\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                      二叉树的基本操作                          ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                        【生成树】     …(1)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                        【求树高】     …(2)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                      【求树的规模】   …(3)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                      【树的叶子数】   …(4)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                     【树的前序遍历】  …(5)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                     【树的中序遍历】  …(6)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                     【树的后序遍历】  …(7)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                     【树的层次遍历】  …(8)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                      【清空二叉树】   …(9)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << " ┋                       【退出操作】    …(0)                    ┋\n";
	cout << " ┋                                                                ┋\n";
	cout << "  =================================================================\n";
	int choice;
	cout << "\n                     亲，请输入您要操作的编号：";
	cin >> choice;
	return choice;
}


int main()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl <<
		"                                正在初始化二叉树...........";
	Sleep(1000);
	system("cls");
	BinaryLinkList<char> tree;
	for (;;) {
		switch (scan()) {
		case 1:
			system("cls");
			//*表示NULL为外部节点
			cout << "按带外部节点的前序遍历创建树(*表示NULL为外部节点)" << endl;
			tree.preOrderCreate('*');
			cout <<"树生成成功！"<< endl;
			getchar();
			getchar();
			break;
		case 2:
			system("cls");
			cout << "树的高度为：" << tree.height() << endl;
			getchar();
			getchar();
			break;
		case 3:
			system("cls");
			cout << "树的规模为：" << tree.size() << endl;
			getchar();
			getchar();
			break;
		case 4:
			system("cls");
			cout << "树的叶子数为：" << tree.leafNum() << endl;
			getchar();
			getchar();
			break;
		case 5:
			system("cls");
			cout << "树的前序遍历为：" << endl;
			tree.preOrderWithStack();
			getchar();
			getchar();
			break;
		case 6:
			system("cls");
			cout << "树的中序遍历为：" << endl; 
			tree.inOrderWithStack();
			getchar();
			getchar();
			break;
		case 7:
			system("cls");
			cout << "树的后序遍历为：" << endl;
			tree.postOrderWithStack();
			getchar();
			getchar();
			break;
		case 8:
			system("cls");
			cout << "树的层次遍历为：" << endl;
			tree.levelOrderTraverse();
			getchar();
			getchar();
			break;
		case 9:
			system("cls");
			tree.clear();
			cout << "树已清空！" << endl;
			getchar();
			getchar();
			break;
		case 0:
			system("cls");
			cout << "程序已退出!" << endl;
			exit(0);
			break;
		}
		//system("cls");
	}

    cout << "\n-----------------------------------" << endl;
    system("pause");
    return EXIT_SUCCESS;

}

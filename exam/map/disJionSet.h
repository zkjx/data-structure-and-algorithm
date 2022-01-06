#pragma once
#include<iostream>
using namespace std;

class unionFindSet {
	int size;
	int* parent;
public:
	unionFindSet(int s);
	~unionFindSet(){ if(parent != NULL) delete[] parent;}
	void merge(int rootl, int root2);
	int find(int x);
};

//构造函数，初始化并查集。
unionFindSet::unionFindSet(int n) {
	size = n;
	parent = new int[size];
	memset(parent, -1, sizeof(int) * size); //所有结点的双亲初始化为－1
}

//查找结点所属集合并压缩路径，递归调用返回时顺便将路径上结点的双亲置为根结点。
int unionFindSet::find(int x) {
	if (parent[x] < 0) return x;//当parent[x] < 0时，x即根结点
	return parent[x] = find(parent[x]);//路径压缩
}

//根据规模合并两个集合。
void unionFindSet::merge(int root1, int root2) {
	root1 = find(root1);//查找root1 的树根
	root2 = find(root2);//查找root2的树根
	if (root1 == root2) return;//属于同一个集合无须合并
	if (parent[root1] > parent[root2]) // 负数比较大小，root2规模更大
	{
		parent[root2] += parent[root1];//root1归并到root2, root2规模增大
		parent[root1] = root2;//root1的双亲置为root2
	}
	else {
		parent[root1] += parent[root2];
		parent[root2] = root1;
	}
}

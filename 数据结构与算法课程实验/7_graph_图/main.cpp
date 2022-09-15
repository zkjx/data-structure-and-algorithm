#include<iostream>
#include<queue>
#include<cmath>
using namespace std;
#include"graph.h"
#include"adjListGraph.h"
#include"adjMatrixGraph.h"
#include"DisjointSet.h"
#include"priorityQueue.h"
// 无穷大作为无边标志，可根据实际情况设置，如下图A,B可用0做无边标志
#define INFINITE 0X7FFFFFFF		
#define N 5 // 定义A图的顶点数
#define M 9 // 定义B图的顶点数

const char * d1[] = { "A", "B", "C", "D", "E" };
int A[N][N] = {
	//        A  B  C  D  E
	/*A*/     0, 0, 1, 1, 0,
	/*B*/     0, 0, 0, 1, 1,
	/*C*/     1, 0, 0, 1, 1,
	/*D*/     1, 1, 1, 0, 0,
	/*E*/     0, 1, 1, 0, 0, };			// 无向图,该图有环，无法拓扑排序

const char * d2[] = { "C0", "C1", "C2", "C3","C4","C5","C6","C7","C8" };
int B[M][M] = {
	//C0  C1  C2  C3  C4  C5  C6  C7  C8	
	0, 0, 1, 0, 0, 0, 0, 1, 0,
	0, 0, 1, 1, 1, 0, 0, 0, 0,
	0, 0, 0, 1, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 1, 1, 0, 0,
	0, 0, 0, 0, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 1, 0, 0 };		// 该图为表示课程优先关系的有向无环图，用于测试拓扑排序	

const char *d3[] = { "V0", "V1", "V2", "V3","V4","V5" };
int C[M][M] = {	
	0, 6, 1, 5, 0, 0,
	6, 0, 5, 0, 3, 0,
	1, 5, 0, 5, 6, 4,
	5, 0, 5, 0, 0, 2,
	0, 3, 6, 0, 0, 6,
	0, 0, 4, 2, 6, 0, };				// 该图用于测试最小生成树	


template <class VertexType, class EdgeType>
void testGraph(graph<VertexType,EdgeType>& g)
{
	cout<<"dfs:    "; g.dfsTraverse();
	cout<<"bfs:    "; g.bfsTraverse();	
	g.printGraph();
}
int main()
{ 
	cout<<"----------------------测试邻接矩阵--------------------\n";
	adjMatrix<char*, int> mg(5,0);		// 使用A图,0做无边标记 
	mg.createGraph((char* const*)d1,(int*)A);
	//adjMatrix<char*, int> mg(9,0);	// 使用B图
	//mg.createGraph((char* const*)d2,(int*)B);	// 创建B图
	testGraph(mg);

	cout<<"\n----------------------测试邻接表----------------------\n";
	adjList<char*, int> lg(5);			// 使用A图,0做无边标记
	lg.createGraph((char* const*)d1,(int*)A);
	//adjList<char*, int> lg(9);		// 使用B图
	//lg.createGraph((char* const*)d2,(int*)B);	// 创建B图
	testGraph(lg);

	system("pause");
}

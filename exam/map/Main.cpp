
//============================================================================
// @FileName     ：Main.cpp
// @Author       ：04191315_HeXiang
// @Version      ：1.0
// @Date         ：2020.12.1
// Description   ：
/*

 */
 //============================================================================

#define _CRT_SECURE_NO_WARNINGS
#include<iostream>  
#include<cmath>
#include"Graph.h"
#include"adjMatrixGraph.h"
#include"adjListGraph.h"
#include"priorityQueue.h"
#include"disJionSet.h"
using namespace std;

const char* d1[] = { "A","B","C","D","E" };
int A[5][5] = {
    0,0,1,1,0,
    0,0,0,1,1,
    1,0,0,1,1,
    1,1,1,0,0,
    0,1,1,0,0,
};

char * creatGraphV(int n){
    char* v = new char[n];
    char temp;
    cout << "请依次输入" << n << "顶点（用单个符号表示）" << endl;
    for (int i = 0; i < n; i++) {
        cin >> temp;
        v[i] = temp;
    }
    return v;
}

int** creatGraphE(int n)
{
    int VE_num=n;
    cout << "下面开始创建图的边的关系:" << endl;
    int ** E ;
    int temp;
    cout << "请依次输入顶点间有无边的关系(0-无，1-有)，按行输入" << endl;
    E = new int* [VE_num];
    for (int i = 0; i < VE_num; i++) {
        E[i] = new int[VE_num];
        for (int j = 0; j < VE_num; j++) {
        cin >> temp;
        E[i][j] = temp;
        }
    }

    return E;
}

template<class VertexType,class EdgeType>
void testGraph(graph< VertexType, EdgeType>& g) {
    cout << "dfs:     "; g.dfsTraverse();
    cout << "bfs:     "; g.bfsTraverse();
    g.printGraph();
}

int main()
{
    /*int n; 
    cout << "首先先开始创建图的顶点，请问有几个顶点？" << endl;
    cin >> n;
    char* d2=creatGraphV(n);
    int** B = creatGraphE(n);
    */
    cout << "-----------------测试邻接矩阵-----------------"<<endl;
    adjMatrix<char*, int> mg(5, 0);
    //adjMatrix<char*, int> mg2(n, 0);
    mg.createGraph((char* const*)d1, (int*)A);
    //mg2.createGraph((char* const*)d2, (int*)B);
    testGraph(mg);
    cout << "------------------测试邻接表------------------"<< endl;
    adjList<char*, int> lg(5);
    //adjList<char*, int> lg2(n);
    lg.createGraph((char* const*)d1, (int*)A);
    //lg2.createGraph((char* const*)d2, (int*)B);
    testGraph(lg);

    cout << "\n-----------------------------------" << endl;
    system("pause");
    return EXIT_SUCCESS;

}

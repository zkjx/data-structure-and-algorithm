#pragma once
#include<queue>
#include<iostream>
#include"priorityQueue.h"
#include"disJionSet.h"
#include"Graph.h"
using namespace std;

template <class VertexType, class EdgeType>                         // VertexType顶点的类型；EdgeType边（或弧）的类型
class adjMatrix :public graph<VertexType, EdgeType> {
private:
    VertexType* vertexs;  	                                        // 顶点向量
    EdgeType** edges; 		                                        // 邻接矩阵
    EdgeType  noEdge; 		                                        // 无边标志
    void  dfs(int start) const;                                     // 从start顶点出发深度优先遍历图
public:
    adjMatrix(int size, EdgeType noEdgeFlag);
    ~adjMatrix();
    void createGraph(const VertexType V[], const EdgeType E[]);
    void printGraph()const; 		                                // 输出图
    bool searchEdge(int from, int to) const; 		                // 查找边
    bool insertEdge(int from, int to, EdgeType w); 	                // 插入一条边
    bool removeEdge(int from, int to); 	                            // 删除一条边
    void dfsTraverse() const; 		                                // 调用私有dfs深度优先遍历图
    void bfsTraverse() const; 		                                // 广度优先遍历图
    bool topSort() const;		                                    // 拓扑排序
    void prim(EdgeType noEdge) const; 	                            // prim算法求最小生成树
    void kruskal() const; 		                                    // kruskal算法求最小生成树
    void printMst()const; 		                                    // 输出最小生成树
    void floyd() const;			                                    // 求各顶点间最短路径
    void printFloyed(EdgeType** D, int** pre)const;                 // 输出各顶点间的最短路径
};

//构造函数
template <class VertexType, class EdgeType>
adjMatrix<VertexType, EdgeType>::adjMatrix(int size, EdgeType noEdgeFlag) {
    this->verNum = size;  this->edgeNum = 0;  noEdge = noEdgeFlag;
    this->vertexs = new VertexType[this->verNum]; 	                            // 顶点向量
    edges = new EdgeType * [this->verNum]; 		                        // 邻接矩阵
    for (int i = 0; i < this->verNum; i++) {
        edges[i] = new EdgeType[this->verNum];
        for (int j = 0; j < this->verNum; ++j)
            edges[i][j] = noEdge; 		                            // 邻接矩阵置初值
    }
    this->visited = new bool[this->verNum];		                                // 访问标志数组
    this->TE = new typename graph<VertexType,EdgeType>::mstEdge[this->verNum - 1];// 最小生成树的边集
}

//析构函数
template <class VertexType, class EdgeType>
adjMatrix<VertexType, EdgeType>::~adjMatrix() {
    delete[] vertexs;
    for (int i = 0; i < this->verNum; i++)
        delete[] edges[i];
    delete[] edges;
    delete[] this->visited;
    delete[] this->TE;
}

//查找图中是否存在从from到to的边，其中from和to是顶点在vertexs数组中的下标。
template <class VertexType, class EdgeType>
bool adjMatrix<VertexType, EdgeType>::searchEdge(int from, int to) const {
    if (from < 0 || from > this->verNum - 1 || to < 0 || to > this->verNum - 1) // 下标越界
        return false;
    if (edges[from][to] == noEdge)                                  // 不存在该边
        return false;
    else  return true;
}

/*
在图中插入从from到to的边，其中from和to是顶点在vertexs数组中的下标。
算法分析：
(1) 当该边已经存在且权值为w时，返回false；
(2) 当该边不存在时，置该边为w，边数计数器增大，返回true；
(3) 当该边已经存在且权值不等于w时，更新边上权值为w，返回true。
*/
template <class VertexType, class EdgeType>
bool adjMatrix<VertexType, EdgeType>::insertEdge(int from, int to, EdgeType w) {
    if (from < 0 || from > this->verNum - 1 || to < 0 || to > this->verNum - 1)
        return false; 		        // 下标越界
    if (edges[from][to] == w)	    // 已经存在从from到to权值为w的边
        return false;
    if (edges[from][to] == noEdge)	// 从from到to原来没有边
        ++this->edgeNum;			        // 边数增加
    edges[from][to] = w;		    // 置边上权值为w
    return true;
}

//删除从from到to的边，其中from和to是顶点在vertexs数组中的下标。
template <class VertexType, class EdgeType>
bool adjMatrix<VertexType, EdgeType>::removeEdge(int from, int to) {
    if (from < 0 || from > this->verNum - 1 || to < 0 || to >this->verNum - 1)
        return false; 			        // 下标越界
    if (edges[from][to] == noEdge) 		// 该边不存在
        return false;
    edges[from][to] = noEdge; 		    // 置为无边标志
    --this->edgeNum; 				            // 边数减少
    return true;
}

//创建图，其中V为顶点数组，E为经过降维的邻接矩阵。
template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::createGraph(const VertexType V[], const EdgeType E[]) {
    int i, j;
    for (i = 0; i < this->verNum; i++)
        this->vertexs[i] = V[i];
    for (i = 0; i < this->verNum; i++) {
        for (j = 0; j < this->verNum; j++) {
            if (E[i * this->verNum + j] > 0)
                insertEdge(i, j, E[i * this->verNum + j]);
        }
    }
}

//输出图
template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::printGraph()const {
    int i, j;
    for (i = 0; i < this->verNum; i++) {
        cout << this->vertexs[i] << ":";
        for (j = 0; j < this->verNum; j++) {
            cout << edges[i][j] << " ";
        }
        cout << endl;
    }
}

//私有递归函数dfs：访问从顶点start出发能够深度优先遍历到的所有顶点。
template <class VertexType, class EdgeType>
void  adjMatrix<VertexType, EdgeType>::dfs(int start) const {
    int i;
    cout << this->vertexs[start] << " "; 		// 访问顶点v
    this->visited[start] = true; 			    // 置访问标志为true
    for (i = 0; i < this->verNum; i++) {	    // 选取start的未被访问的邻接点
        if (edges[start][i] != noEdge && this->visited[i] == false)
            dfs(i); 			        // 从i出发继续深度优先遍历图
    }
}

//深度优先遍历图的公共接口函数。
template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::dfsTraverse() const {
    int i, count = 0;			        // count用于统计无向图连通分量的个数
    for (i = 0; i < this->verNum; i++)
        this->visited[i] = false;		        // 置访问标志为false
    for (i = 0; i < this->verNum; i++) {
        if (!this->visited[i]) { 		        // 选取一个未访问过的结点调用dfs
            dfs(i);			            // 若该图是连通图则只调用dfs一次
            count++;
        }
    }
    cout << endl;
    cout << "无向图连通分量个数为：" << count << endl;
}

template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::bfsTraverse()const {
    int v, i, j, count = 0;		        // count可统计连通分量个数
    queue<int> Q;
    for (i = 0; i < this->verNum; i++) 	    // 置访问标志为false
        this->visited[i] = false;
    for (i = 0; i < this->verNum; i++) {
        if (this->visited[i] == true) continue;
        cout << this->vertexs[i] << ' ';  	// 访问顶点i
        this->visited[i] = true; 		        // 置访问标志为true
        Q.push(i);	count++;
        while (!Q.empty()) {
            v = Q.front();  Q.pop();	// 顶点v出队
            if (this->visited[v] == false) {
                for (j = 0; j < this->verNum; ++j) {
                                        // 查找顶点v未被访问的临接点
                    if (edges[v][j] != noEdge && this->visited[j] == false) {
                        cout << this->vertexs[j] << ' '; // 访问顶点j
                        this->visited[j] = true; // 置访问标志为true
                        Q.push(j);
                    }
                }
            }
        }
    }
    cout << endl;
}

//prim算法求最短路径
template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::prim(EdgeType noEdge) const {
    struct Dist {
        int  adjVex;			                // 最小代价边依附的顶点编号
        EdgeType  lowCost;		                // 最小代价
    } *D = new Dist[this->verNum];
    EdgeType minCost;
    int u, i, j, count = 0;
    for (i = 0; i < this->verNum; ++i) {
        this->visited[i] = false;  D[i].lowCost = noEdge;
    }
    u = 0;  this->visited[u] = true;
    for (i = 1; i < this->verNum; ++i) {		        // 选中一个点u入U集合后
        for (j = 0; j < this->verNum; ++j) 	        // 更新u关联的顶点的D值
            if (!this->visited[j] && edges[u][j] != noEdge) {
                if (edges[u][j] < D[j].lowCost) {
                    D[j].lowCost = edges[u][j];	// 更新lowcost
                    D[j].adjVex = u; 		    // 更新adjVex 
                }
            }
        minCost = noEdge;
        for (j = 0; j < this->verNum; ++j)		    // 在V-U中找lowCost最小顶点u
            if (D[j].lowCost < minCost) {
                minCost = D[j].lowCost; u = j;
            }
        this->TE[count].vex1 = D[u].adjVex; 		    // 保存最小生成树的一条边
        this->TE[count].vex2 = u;
        this->TE[count++].weight = D[u].lowCost;
        D[u].lowCost = noEdge;			        // 顶点u已并入U集合
        this->visited[u] = true;
    }
    delete[] D;
}

//kruskal算法求最小生成树
template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::kruskal() const {
    typename graph<VertexType, EdgeType>::mstEdge e{};
    int count = 0;
    unionFindSet S(this->verNum);
    priorityQueue< typename graph<VertexType, EdgeType>::mstEdge> Q;
    for (int i = 0; i < this->verNum; ++i) {          // 用图中的边生成优先级队列
        for (int j = i + 1; j < this->verNum; j++)	//j=i+1开始，防止重复入队
            if (edges[i][j] != noEdge) {
                e.vex1 = i;  e.vex2 = j;  e.weight = edges[i][j];
                Q.enQueue(e);
            }
    }
    while (count < this->verNum - 1) {	            // 选出verNum-1条边
        e = Q.deQueue();		                // 从优先级队列出队一条边
        int u = S.find(e.vex1); 	            // 查找顶点vex1所属子集
        int v = S.find(e.vex2); 	            // 查找顶点vex2所属子集
        if (u != v) {							// 边上的两个顶点不属于同一连通分量
            S.merge(u, v); 	                    // 合并u、v所属子集（连通分量）
            this->TE[count++] = e;		            // 保存最小生成树上的一条边
        }
    }
}

//拓扑排序
template <class VertexType, class EdgeType>
bool adjMatrix<VertexType, EdgeType>::topSort() const {
    queue<int> Q;
    int i, j, curNode, count = 0, * inDegree = new int[this->verNum];
    for (i = 0; i < this->verNum; i++)
        inDegree[i] = 0;
    for (i = 0; i < this->verNum; i++)
        for (j = 0; j < this->verNum; j++)        // 遍历邻接矩阵，求顶点入度
            if (edges[i][j] != noEdge)  ++inDegree[j];
    for (i = 0; i < this->verNum; i++)
        if (inDegree[i] == 0)
            Q.push(i);
    while (!Q.empty()) {
        curNode = Q.front();  Q.pop();      // 出队一个入度为0的顶点
        cout << this->vertexs[curNode] << ' ';    // 输出该顶点
        count++;			                // 计数器+1
        for (j = 0; j < this->verNum; ++j) {      // 邻接点入度减1	
            if (edges[curNode][j] != noEdge)
                if (--inDegree[j] == 0)
                    Q.push(j); 	            // 入度为0的顶点入队列
        }
    }
    cout << endl;
    if (count == this->verNum)
        return true; 		                // 输出全部顶点，拓扑排序成功
    return false; 		                    // 该有向图有环，拓扑排序失败
}

//求各顶点间最短路径  
template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::floyd() const {
    EdgeType** D = new EdgeType * [this->verNum];
    int** pre = new int* [this->verNum];
    int i, j, k;
    for (i = 0; i < this->verNum; ++i) {
        D[i] = new EdgeType[this->verNum];
        pre[i] = new int[this->verNum];
        for (j = 0; j < this->verNum; ++j) {
            D[i][j] = (i == j) ? 0 : edges[i][j];
            pre[i][j] = (edges[i][j] == noEdge) ? -1 : i;
        }
    }
    printFloyed(D, pre);
    cout << "---------------------开始---------------------" << endl;
    //迭代过程
    for (k = 0; k < this->verNum; ++k) {
        for (i = 0; i < this->verNum; ++i) {
            for (j = 0; j < this->verNum; ++j)
                if (D[i][k] != noEdge && D[k][j] != noEdge && D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                    pre[i][j] = pre[k][j];
                }
        }
     printFloyed(D, pre);
     cout << "---------------------------------------------" << endl;
    }
    //printFloyed(D, pre);
    for (i = 0; i < this->verNum; ++i) {
        delete[]D[i];
        delete[]pre[i];
    }
    delete[]D;
    delete[]pre;
}

//输出各顶点间的最短路径
template <class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::printFloyed(EdgeType** D, int** pre) const {
    int i, j;
    cout << "shortest path：\n";
    for (i = 0; i < this->verNum; ++i) {
        for (j = 0; j < this->verNum; ++j)
            cout << D[i][j] << '\t';
        cout << endl;
    }
    cout << "precursor of vertex：\n";
    for (i = 0; i < this->verNum; ++i) {
        for (j = 0; j < this->verNum; ++j)
            cout << pre[i][j] << '\t';
        cout << endl;
    }
}

template<class VertexType, class EdgeType>
void adjMatrix<VertexType, EdgeType>::printMst() const
{   
    for (int i = 0; i < this->verNum - 1; i++) {
        cout << '(' <<vertexs[this->TE[i].vex1] << ','
            <<vertexs[this->TE[i].vex2] << ','
            << this->TE[i].weight << ')';
        cout << endl;
    }
}

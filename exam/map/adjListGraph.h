#pragma once
#include<queue>
#include<iostream>
#include"Graph.h"
#include"priorityQueue.h"
#include"disJionSet.h"
using namespace std;

template <class VertexType, class EdgeType>
class adjList :public graph<VertexType, EdgeType> {
private:
    struct edgeNode {		// 边表结点类型
        int to; 		// 边的终点编号（在顶边表中的下标）
        EdgeType weight;  	// 边上的权值
        edgeNode* next; 	// 指向下一个边表结点
        edgeNode() { }		// 无参构造函数
        edgeNode(int t, EdgeType w, edgeNode* n = NULL) {
            to = t; 	weight = w; 	next = n;
        }
    };
    struct verNode {			// 顶点结点类型
        VertexType vertex;  		// 顶点信息
        edgeNode* firstEdge;  	// 指向第一个邻接点的指针
        verNode(edgeNode* h = NULL) { firstEdge = h; }
    };
    //struct mstEdge {	// 最小生成树的边结点类型
    //    int vex1, vex2;
    //    EdgeType weight;// 边的三元组(始点，终点，权值)
    //    bool operator<(const  mstEdge& e) const {
    //        // 使用优先级队列需重载<
    //        return weight < e.weight;
    //    }
    //};
    verNode* verList;		// 顶点表
    int* topOrder;			// 保存拓扑序列，用于求关键路径
    void  dfs(int start) const;	// 从start号顶点出发DFS
public:
    adjList(int size);
    ~adjList();
    void createGraph(const VertexType V[], const EdgeType A[]);
    void printGraph()const;		// 输出图
    bool searchEdge(int from, int to) const; 	// 查找边
    bool insertEdge(int from, int to, EdgeType w); // 插入一条边
    bool removeEdge(int from, int to); 		// 删除一条边
    void dfsTraverse() const;	// 调用私有dfs深度优先遍历图
    void bfsTraverse() const; 	// 广度优先遍历图
    bool topSort() const; 		// 拓扑排序
    void prim(EdgeType noEdge) const; // prim算法求最小生成树
    void kruskal() const; 		// kruskal算法求最小生成树
    void printMst()const; 		// 输出最小生成树
    bool criticalPath()const;	// 关键路径算法
    bool dijkstra(int start, EdgeType noEdge) const;
    // 求单源点最短路径
    void printDijPath(int from, int to, int pre[]) const;
    // 输出源点到其他顶点的最短路径
};

//构造函数
template <class VertexType, class EdgeType>
adjList<VertexType, EdgeType>::adjList(int size) {
    this->verNum = size;
    this->edgeNum = 0;
    this->verList = new verNode[size];
    this->visited = new bool[this->verNum];
    this->TE = new typename graph<VertexType,EdgeType>::mstEdge[this->verNum - 1];
    topOrder = new int[this->verNum];
}

//析构函数
template <class VertexType, class EdgeType>
adjList<VertexType, EdgeType>::~adjList() {
    int i;
    edgeNode* p;
    for (i = 0; i < this->verNum; i++) {		// 释放边表
        while ((p = verList[i].firstEdge) != NULL) {
            // 释放第i个单链表
            verList[i].firstEdge = p->next;
            delete p;
        }
    }
    delete[] verList; 			// 释放顶点表
    delete[] this->visited;
    delete[] this->TE;
    delete[] topOrder;
}

//查找图中是否存在从from到to的边，其中from和to是顶点在verList数组中的下标。
template <class VertexType, class EdgeType>
bool adjList<VertexType, EdgeType>::searchEdge(int from, int to) const {
    if (from < 0 || from > this->verNum - 1 || to < 0 || to > this->verNum - 1)
        return false; 			// 下标越界
    edgeNode* p = verList[from].firstEdge;
    while (p != NULL && p->to != to)
        p = p->next;
    if (p == NULL) return false; 		// 该边不存在
    else  return true;
}

/*在图中插入从from到to的边，其中from和to是顶点在verList数组中的下标。
算法分析：由于每个顶点的(边表)单链表中均无头结点，所以插入边表结点时要对首元结点单独处理。插入边可分为三种情况：
(1) 当该边已经存在且权值为w时，返回false；
(2) 当该边不存在时，置该边为w，边数计数器增大，返回true；
(3) 当该边已经存在且权值不等于w时，更新边上权值为w，返回true。
*/
template <class VertexType, class EdgeType>
bool adjList<VertexType, EdgeType>::insertEdge(int from, int to, EdgeType w) {
    if (from < 0 || from > this->verNum - 1 || to < 0 || to > this->verNum - 1)
        return false; 			// 下标越界
    edgeNode* p = verList[from].firstEdge, * pre=NULL, * s;
    while (p != NULL && p->to < to) {
        // 查找插入位置，单链表按to的值有序
        pre = p;  p = p->next;
    }
    if (p != NULL && p->to == to) { 		// 该边已经存在
        if (p->weight != w) p->weight = w;	// 修改权值
        else return false;
    }
    else {						// 该边不存在
        s = new edgeNode(to, w, p);
        if (p == verList[from].firstEdge) 	// 插入为首元结点
            verList[from].firstEdge = s;
        else  pre->next = s;		// 在链表其他位置插入结点
        ++this->edgeNum;			// 新增一条边，边数加1
    }
    return true;
}

/*
删除从from到to的边，其中from和to是顶点在vertexs数组中的下标，
同样要注意，由于每个顶点的单链表中均无头结点，所以删除边表结点时要对首元结点单独处理。
*/
template <class VertexType, class EdgeType>
bool adjList<VertexType, EdgeType>::removeEdge(int from, int to) {
    if (from < 0 || from > this->verNum - 1 || to < 0 || to > this->verNum - 1)
        return false; 			// 下标越界
    edgeNode* p = verList[from].firstEdge, * pre = NULL;
    while (p != NULL && p->to < to) { 		// 查找边   
        pre = p;    p = p->next;
    }
    if ((p == NULL) || (p->to > to))		// 该边不存在
        return false;
    if (p->to == to) { 				// 该边存在 
        // 该边是边表中的首元结点
        if (p == verList[from].firstEdge)
            verList[from].firstEdge = p->next;
        else pre->next = p->next;
        delete p;
        --this->edgeNum;
        return true;
    }
}

//创建图，其中V为顶点数组，E为经过降维的邻接矩阵。
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::createGraph(const VertexType V[], const EdgeType A[]) {
    int i, j;
    for (i = 0; i < this->verNum; i++)
        this->verList[i].vertex = V[i];
    for (i = 0; i < this->verNum; i++)
        for (j = 0; j < this->verNum; j++) {
            if (A[i * this->verNum + j] > 0)
                insertEdge(i, j, A[i * this->verNum + j]);
            // insertEdge插入边按to值有序
        }
}

//输出图
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::printGraph()const {
    int i;
    for (i = 0; i < this->verNum; i++) {
        cout << this->verList[i].vertex << ":";
        edgeNode* p = verList[i].firstEdge;
        while (p != NULL) {
            cout << this->verList[p->to].vertex <<","<<p->weight<<" ";
            p = p->next;
        }
        cout << endl;
    }
}

//私有递归函数dfs：访问从顶点start出发能够深度优先遍历到的所有顶点。
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::dfs(int start) const {
    edgeNode* p = this->verList[start].firstEdge;
    cout << this->verList[start].vertex <<" "; 	// 访问顶点v
    this->visited[start] = true; 			// 置访问标志为true
    while (p != NULL) {
        if (this->visited[p->to] == false) // 选取start的未被访问的邻接点
            dfs(p->to); 		// 从p->to出发继续深度优先遍历图
        p = p->next;
    }
}


//深度优先遍历图的公共接口函数。
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::dfsTraverse() const {
    int i, count = 0;			// count用于统计无向图连通分量的个数
    for (i = 0; i < this->verNum; i++)
        this->visited[i] = false;		// 置访问标志为false
    for (i = 0; i < this->verNum; i++) {
        if (!this->visited[i]) { 		// 选取一个未访问过的结点调用dfs
            dfs(i);			// 若该图是连通图则只调用dfs一次
            count++;
        }
    }
    cout << endl;
    cout << "无向图连通分量个数为：" << count << endl;
}

//广度优先遍历算法
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::bfsTraverse()const {
    int v, i, count = 0;			// count可统计连通分量个数
    queue<int> q;
    edgeNode* p;
    for (i = 0; i < this->verNum; i++) 	// 置访问标志为false
        this->visited[i] = false;
    for (i = 0; i < this->verNum; i++) {
        if (this->visited[i] == true) continue;
        cout << this->verList[i].vertex << ' '; 	// 访问顶点i
        this->visited[i] = true; 		// 置访问标志为true
        q.push(i);   count++;	// 顶点i入队
        while (!q.empty()) {
            v = q.front(); q.pop();	// 顶点v出队
            p = this->verList[v].firstEdge;
            while (p != NULL) {	// 查找顶点v未被访问的临接点
                if (this->visited[p->to] == false) {
                    cout << this->verList[p->to].vertex << ' ';
                    // 访问顶点p->to
                    this->visited[p->to] = true; 								// 置访问标志为true
                    q.push(p->to); 	// 顶点p->to入队
                }
                p = p->next;
            }
        }
    }
    cout << endl;
}

//prim算法求最小生成树
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::prim(EdgeType noEdge) const {
    struct Dist {
        int  adjVex;		// 最小代价边依附的顶点编号
        EdgeType  lowCost;	// 最小代价
    }*D = new Dist[this->verNum];
    edgeNode* p;
    EdgeType minCost;
    int u, i, j, count = 0;
    for (i = 0; i < this->verNum; ++i) {
        this->visited[i] = false;
        D[i].lowCost = noEdge;
    }
    u = 0;  this->visited[u] = true;  	// 初始化U集合
    for (i = 1; i < this->verNum; ++i) {		// 选中一个点u入U集合后
        for (p = verList[u].firstEdge; p != NULL; p = p->next)                       						// 更新u关联的顶点的D值
            if (!this->visited[p->to] && D[p->to].lowCost > p->weight) {
                D[p->to].lowCost = p->weight;	// 更新lowcost
                D[p->to].adjVex = u; 		// 更新adjVex 
            }
        minCost = noEdge;
        for (j = 0; j < this->verNum; ++j)		// 在V-U中找lowCost最小顶点u
            if (D[j].lowCost < minCost) {
                minCost = D[j].lowCost;  u = j;
            }
        this->TE[count].vex1 = D[u].adjVex; 		// 保存最小生成树的一条边
        this->TE[count].vex2 = u;
        this->TE[count++].weight = D[u].lowCost;
        D[u].lowCost = noEdge;			// 顶点u已并入U集合
        this->visited[u] = true;
    }
    delete[] D;
}

// kruskal算法求最小生成树
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::kruskal() const {
    int count = 0;
    typename graph<VertexType, EdgeType>::mstEdge e{};
    edgeNode* p;
    unionFindSet S(this->verNum);    		// 并查集S
    priorityQueue<typename graph<VertexType, EdgeType>::mstEdge> Q; 		        // 优先级队列Q
    for (int i = 0; i < this->verNum; ++i) {	// 边入优先级队列
        for (p = this->verList[i].firstEdge; p != NULL; p = p->next)
            if (i < p->to) {			// 防止重复入队
                e.vex1 = i;
                e.vex2 = p->to;
                e.weight = p->weight;
                Q.enQueue(e); 		// 边e入队
            }
    }
    while (count < this->verNum - 1) {	// 选出verNum-1条边
        e = Q.deQueue();		// 从优先级队列出队一条边
        int u = S.find(e.vex1); 	// 查找顶点vex1所属子集
        int v = S.find(e.vex2); 	// 查找顶点vex2所属子集
        if (u != v) {		// 边上的两个顶点不属于同一连通分量
            S.merge(u, v); 	// 合并u、v所属子集（连通分量）
            this->TE[count++] = e;		// 保存最小生成树上的一条边
        }
    }
}

template<class VertexType, class EdgeType>
 void adjList<VertexType, EdgeType>::printMst() const
 {
     for (int i = 0; i < this->verNum - 1; i++) {
         cout << '(' << verList[this->TE[i].vex1].vertex << ',' 
             << verList[this->TE[i].vex2].vertex << ',' 
             << this->TE[i].weight << ')';
         cout << endl;
 }
}

 template<class VertexType, class EdgeType>
 bool adjList<VertexType, EdgeType>::criticalPath() const
 {   if (topSort() == false) return false;
     EdgeType* eVetex = new EdgeType[this->verNum]; //项点的最早开始时间数组
     EdgeType* lVetex = new EdgeType[this->verNum];// 顶点的最晚开始时间数组
     EdgeType eArc;    //活动的最早开始时间
     EdgeType lArc;    //是影的最晚开始时间
     int i, k = 0;
     edgeNode* p;
     for (i = 0; i < this->verNum; ++i)
         eVetex[i] = 0; // eVetex初始化为e
     for (i = 0; i < this->verNum; ++i) {
         int curNode = topOrder[i];//按拓补序列计算eVetex
         for (p = verList[curNode].firstEdge; p != NULL; p = p->next) {
             if (eVetex[p->to] < eVetex[curNode] + p->weight)
                 eVetex[p->to] = eVetex[curNode] + p->weight;
         }
     }
     for (i = 0; i < this->verNum; ++i)
         lVetex[i] = eVetex[this->verNum - 1]; //LVetex初始化为汇点的最早；
     for (i = this->verNum - 2; i >= 0; --i) {//除去汇点，从verNum - 2开始计算
         int curNode = topOrder[i];// 按逆拓扑序列计算LVetex
             for (p = verList[curNode].firstEdge; p != NULL; p = p->next) {
                 if (lVetex[curNode] > lVetex[p->to] - p->weight)
                     lVetex[curNode] = lVetex[p->to] - p->weight;
             }
     }
     for (i = 0; i < this->verNum; ++i) // 求每个活动的eArc和LArc
         for (p = verList[i].firstEdge; p != NULL; p = p->next){
            eArc = eVetex[i];
            lArc = lVetex[p->to] - p->weight;
            char tag = (eArc == lArc) ? '*' : ' ';
            cout << "arc" << k++ << ":\t" << "<" << i << "," << p->to << "," << p->weight << ">"
             << "\t" << eArc << lArc << tag << endl;
 }
     delete[]eVetex;
     delete[]1Vetex;
     return true;
 }

//拓扑排序
template <class VertexType, class EdgeType>
bool adjList<VertexType, EdgeType>::topSort()const {
    queue<int> q;
    edgeNode* p;
    int i, curNode, count = 0, * inDegree = new int[this->verNum];
    for (i = 0; i < this->verNum; i++)
        inDegree[i] = 0;
    for (i = 0; i < this->verNum; i++) {
        // 遍历边表，求顶点入度
        for (p = this->verList[i].firstEdge; p != NULL; p = p->next)
            ++inDegree[p->to];
    }
    for (i = 0; i < this->verNum; i++) 	// 入度为0的顶点入队列
        if (inDegree[i] == 0) q.push(i);
    while (!q.empty()) {
        curNode = q.front();
        q.pop();// 出队一个入度为0的顶点
        cout << this->verList[curNode].vertex << ' ';	// 输出
        // topOrder[count] = curNode;//保存拓扑序列用于求关键路径
        count++;				// 计数器+1
        for (p = this->verList[curNode].firstEdge; p != NULL; p = p->next)
            if (--inDegree[p->to] == 0) 	// 邻接点入度减1
                q.push(p->to); 		// 入度为0的顶点入队列
    }
    cout << endl;
    if (count == this->verNum)
        return true; 		// 输出全部顶点，拓扑排序成功
    return false; 		// 该有向图有环，拓扑排序失败
}

//Dijkstra算法--基于邻接表
template <class VertexType, class EdgeType>
bool adjList<VertexType, EdgeType>::dijkstra(int start, EdgeType noEdge) const {
    if (start < 0 || start > this->verNum - 1)	//源点下标越界
        return false;
    EdgeType* D = new EdgeType[this->verNum];//记录最短路径长度
    int* pre = new int[this->verNum];	// 记录前驱
    edgeNode* p;   EdgeType min;   int i, j, k;
    for (i = 0; i < this->verNum; ++i) {	// 初始化
        this->visited[i] = false;
        D[i] = noEdge;  pre[i] = -1;
    }
    D[start] = 0;
    pre[start] = start;	// start到自身的路径长度置0
    min = D[start];  k = start;

    for (i = 1; i < this->verNum; ++i) {
        this->visited[k] = true;
        // 刷新start到k的邻接点的最短路径长度
        for (p = verList[k].firstEdge; p != NULL; p = p->next)
            if (!this->visited[p->to] &&
                D[p->to] > min + p->weight) {
                D[p->to] = min + p->weight;
                pre[p->to] = k;
            }
        min = noEdge; k = start;
        // 重新找当前路径长度最短且未被访问过的顶点k
        for (j = 0; j < this->verNum; ++j)
            if (!this->visited[j] && D[j] < min) {
                k = j;
                min = D[k];
            }
        if (k != start) {
            printDijPath(start, k, pre);	// 输出start到k的最短路径
            cout << " : " << D[k] << endl;
        }
    }
    delete[]D;
    delete[]pre;
    return  true;
}

//输出从源点from到to的最短路径上的顶点序列
template <class VertexType, class EdgeType>
void adjList<VertexType, EdgeType>::printDijPath(int from, int to, int pre[]) const {
    if (from == to) {		 // 递归出口，遇到源点
        cout << this->verList[from].vertex;
        return;
    }
    printDijPath(from, pre[to], pre);// 递归输出前驱
    cout << "->" << this->verList[to].vertex;
}



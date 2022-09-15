#ifndef _GRAGH_H_
#define _GRAGH_H_
template <class VertexType, class EdgeType> 
class graph {
public:
	int numOfVertex() const { return verNum; }					// 返回图的顶点数
    int numOfEdge() const { return edgeNum; }					// 返回图的边数
    virtual void createGraph(const VertexType V[],const EdgeType E[])=0; // 创建图
    virtual void dfsTraverse()const = 0;						// 深度优先遍历
    virtual void bfsTraverse()const = 0;						// 广度优先遍历
    virtual bool topSort()const=0;							// 拓扑排序
    virtual void prim(EdgeType noEdge) const=0;					// prim算法
    virtual void kruskal() const=0; 							// kruskal算法
    virtual void printMst()const=0; 							// 输出最小生成树
    virtual bool searchEdge(int from, int to) const = 0;			// 查找边
    virtual bool insertEdge(int from, int to, EdgeType w) = 0; 	// 插入权值为w的边
    virtual bool removeEdge(int from, int to) = 0;				// 删除边
	virtual void printGraph()const=0;							// 输出图
protected:
    struct mstEdge {								// 最小生成树的边结点类型
        int vex1, vex2;			
        EdgeType weight;							// 边的三元组(始点，终点，权值)
        bool operator<(const  mstEdge &e) const {  	// 使用优先级队列需要重载<
            return weight < e.weight;
        }
    }*TE;									// 最小生成树的边集
	int verNum, edgeNum;							// 图的顶点数和边数
	bool *visited;									// 访问标志数组
};


#endif

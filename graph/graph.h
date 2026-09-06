#ifndef GRAPH_H
#define GRAPH_H

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_VERTEX_NUM 20

typedef int status;
typedef int KeyType;
typedef enum {DG, DN, UDG, UDN} GraphKind;  //有向图，有向网，无向图，无向网

typedef struct 
{
    KeyType key;
    char others[20];
} VertexType;   //顶点类型定义

typedef struct ArcNode      //表结点类型定义
{
    int adjvex;             //顶点位置编号
    //int weight；
    struct ArcNode *nextarc;    //下一个表结点指针
} ArcNode;

typedef struct VNode        //头结点及其数组类型定义
{
    VertexType data;        //顶点信息
    ArcNode *firstarc;      //指向第一条弧指针
} VNode, AdjList[MAX_VERTEX_NUM];

typedef struct          //邻接表类型定义 
{   
    AdjList vertices;           //头结点数组
    int vexnum, arcnum;         //顶点数，边数
    GraphKind kind;             //图类型
    char name[20];              //图的名字（用于多图管理）
} ALGraph;

/**
 * @brief 创建图，根据数组V和VR
 * @param G 图的引用
 * @param V 顶点数组，头结点数组
 * @param VR 关系对序列VR
 * @return status 构造成功，返回OK；如果V和VR不正确或者关键字重复，返回ERROR
 */
status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2]);

/**
 * @brief 销毁图，清空边集，并讲顶点数和边数置0
 * @param G 图的引用
 * @return status 始终返回OK； 
 */
status DestroyGraph(ALGraph &G);

/**
 * @brief 查找顶点 
 * @param G 图（只读）
 * @param u 待查找的顶点
 * @return int 返回编号；没找到，返回-1
 */
int LocateVex(ALGraph G, KeyType u);

/**
 * @brief 顶点赋值，查找顶点u，并将改结点的值改为value
 * @param G 图的引用
 * @param u 带赋值结点的关键字
 * @param value 赋的值
 * @return status 成功，返回OK；如果查找失败，或者关键字不唯一，返回ERROR
 */
status PutVex(ALGraph &G, KeyType u, VertexType value);

/**
 * @brief 查找第一邻接顶点
 * @param G 图（只读）
 * @param u 待查找顶点的关键字
 * @return int 查找成功，返回顶点u的第一邻接顶点位序；否则，返回-1
 */
int FirstAdjVex(ALGraph G, KeyType u);

/**
 * @brief 查找下一邻接顶点
 * @param G 图（只读）
 * @param v 图G的第一个结点
 * @param w v的邻接结点
 * @return int 返回v相对于w下一个邻接顶点的位序；若位序不存在或顶点不存在，返回-1
 */
int NextAdjVex(ALGraph G, KeyType v, KeyType w);

/**
 * @brief 插入邻接顶点
 * @param G 图的引用
 * @param v 待插入顶点
 * @return status 插入成功，返回OK；否则，返回ERROR
 */
status InsertVex(ALGraph &G, VertexType v);

/**
 * @brief 删除顶点，及其关联的边，注意更新
 * @param G 图的引用
 * @param v 待删除顶点
 * @return status 成功删除，返回OK；如果顶点不存在或者边数为0（顶点存在但没有边），返回ERROR
 */
status DeleteVex(ALGraph &G, KeyType v);

/**
 * @brief 插入弧<v,w>
 * @param G 图的引用
 * @param v 弧尾
 * @param w 弧头
 * @return status 成功，返回OK；如果顶点不存在或边已经存在，返回ERROR
 */
status InsertArc(ALGraph &G, KeyType v, KeyType w);

/**
 * @brief 删除弧
 * @param G 图的引用
 * @param v 弧尾
 * @param w 弧头
 * @return status 成功，返回OK；否则，返回ERROR
 */
status DeleteArc(ALGraph &G, KeyType v, KeyType w);



void visit(VertexType v);


/**
 * @brief 
 * @param G 图
 * @param v 从顶点编号v开始DFS， DFSTraverse的辅助函数
 * @param visited 标记数组
 * @param visit 访问函数
 */
void DFS(ALGraph G, int v, int visited[], void ( *visit)(VertexType ));

/**
 * @brief 深度优先遍历
 * @param G 图的引用？
 * @param visit 访问（输出）函数
 * @return status 
 */
status DFSTraverse(ALGraph &G, void (*visit)(VertexType));

/**
 * @brief 广度优先遍历
 * @param G 图的引用？
 * @param visit 访问（输出）函数
 * @return status 
 */
status BFSTraverse(ALGraph &G, void (*visit)(VertexType));

/**
 * @brief 将图的数据写入到文件FileName中
 * @param G 图（只读）
 * @param FileName 文件名
 * @return status 成功，返回OK；否则，返回ERROR
 */
status SaveGraph(ALGraph G, char FileName[]);

/**
 * @brief 读入文件FileName的数据，创建图的邻接表
 * @param G 图的引用
 * @param FileName 文件名
 * @return status 成功，返回OK；否则，返回ERROR
 */
status LoadGraph(ALGraph &G, char FileName[]);

//额外功能

/**
 * @brief 最短路算法，用于实现附加功能一、二
 * @param G 图
 * @param u 顶点
 * @param dist 最短路数组；路径不存在数组值为-1
 */
void Dijkstra(ALGraph G, int u,int dist[]);

/**
 * @brief 求图G的连通分量个数
 * @param G 图
 * @return int 返回个数
 */
int ConnectedComponentsNums(ALGraph G);

/**
 * @brief 输出函数
 * @param G 图
 */
void PrintGraph(ALGraph G);

#endif
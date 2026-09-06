#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <vector>
#include <utility>
#include "graph.h"

status CreateGraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    int n = 0;
    for (int i = 0; V[i].key != -1; i++)
    {
        n++;
    }
    if (n == 0 || n > MAX_VERTEX_NUM)
    {
        return ERROR;
    }
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (V[i].key == V[j].key)
            {
                return ERROR;
            }
        }
    }
    G.vexnum = n;
    G.arcnum = 0;
    G.kind = UDG;
    for (int i = 0; i < n; i++)
    {
        G.vertices[i].data = V[i];
        G.vertices[i].firstarc = NULL;
    }
    for (int k = 0; VR[k][0] != -1; k++)
    {
        KeyType key1 = VR[k][0];
        KeyType key2 = VR[k][1];
        int v1 = -1, v2 = -1;       //顶点下标
        for (int i = 0; i < n; i++)
        {
            if (V[i].key == key1)
            {
                v1 = i;         //注意是数组下标
            }
            if (V[i].key == key2)
            {
                v2 = i;
            }
        }
        if (v1 == -1 || v2 == -1)
        {
            return ERROR;
        }
        if (v1 == v2)   //环
        {
            continue;
        }
        int flag = 0;
        ArcNode *p = G.vertices[v1].firstarc;
        while (p != NULL)
        {
            if (p->adjvex == v2)
            {
                flag = 1;
                break;
            }
            p = p->nextarc;
        }
        if (flag)
        {
            continue;
        }
        ArcNode *t = (ArcNode *)malloc(sizeof(ArcNode));
        t->adjvex = v2;
        t->nextarc = G.vertices[v1].firstarc;
        G.vertices[v1].firstarc = t;
        t = (ArcNode *)malloc(sizeof(ArcNode));
        t->adjvex = v1;
        t->nextarc = G.vertices[v2].firstarc;
        G.vertices[v2].firstarc = t;
        G.arcnum++;
    }
    return OK;
}

status DestroyGraph(ALGraph &G)
{
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            ArcNode *q = p;
            p = p->nextarc;
            free(q);
        }
        G.vertices[i].firstarc = NULL;
    }
    G.arcnum = 0;
    G.vexnum = 0;
    return OK;
}

int LocateVex(ALGraph G, KeyType u)
{
    int pos = -1;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (G.vertices[i].data.key == u)
        {
            pos = i;
            break;
        }
    }
    return pos;
}

status PutVex(ALGraph &G, KeyType u, VertexType value)
{
    int pos = LocateVex(G, u);      //查找顶点u
    if (pos == -1)
    {
        return ERROR;
    }
    if (LocateVex(G, value.key) != -1)      //赋值的关键字不能重复
    {
        return ERROR;
    }
    G.vertices[pos].data = value;
    return OK;
}

int FirstAdjVex(ALGraph G, KeyType u)
{
    int index = LocateVex(G, u);
    if (!G.vertices[index].firstarc)
    {
        return -1;
    }
    return G.vertices[index].firstarc->adjvex;
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
    int index = LocateVex(G, v);
    if (index == -1)
    {
        return -1;
    }
    ArcNode *p = G.vertices[index].firstarc;
    while (p)
    {
        KeyType key = G.vertices[p->adjvex].data.key;
        if (key == w)
        {
            if (p->nextarc)
            {
                return p->nextarc->adjvex;
            }
            else
            {
                return -1;
            }
        }            
        p = p->nextarc;
    }
    return -1;
}

status InsertVex(ALGraph &G, VertexType v)
{
    if (G.vexnum >= MAX_VERTEX_NUM)     //如果已满
    {
        return ERROR;
    }
    for (int i = 0; i < G.vexnum; i++)      //如果关键字重复
    {
        if (G.vertices[i].data.key == v.key)
        {
            return ERROR;
        }
    }
    //插入
    G.vertices[G.vexnum].data = v;
    G.vertices[G.vexnum].firstarc = NULL;
    G.vexnum++;
    return OK;
}

status DeleteVex(ALGraph &G, KeyType v)
{
    int pos = LocateVex(G, v);
    if (pos == -1) 
    {
        return ERROR;
    }  
    //删除与v有关的边 
    for (int i = 0; i < G.vexnum; i++)
    {
        if (i == pos)
        {
            continue;
        }
        ArcNode *p = G.vertices[i].firstarc;
        ArcNode *q = p;
        while (p)
        {
            if (p->adjvex == pos)
            {
                if (p == G.vertices[i].firstarc)
                {
                    G.vertices[i].firstarc = p->nextarc;
                    free(p);
                    p = G.vertices[i].firstarc;
                    q = p; //注意

                }
                else
                {
                    q->nextarc = p->nextarc;
                    free(p);
                    p = q->nextarc;
                }
            }
            else
            {                
                q = p;
                p = p->nextarc;
            }
        }
    }
    //后删除顶点
    ArcNode *p = G.vertices[pos].firstarc;
    while (p)
    {
        ArcNode *q = p;
        p = p->nextarc;
        free(q);
        G.arcnum--;     //这里就把边数更新完了
    }
    for (int i = pos; i < G.vexnum - 1; i++)
    {
        G.vertices[i] = G.vertices[i + 1];
    }
    G.vexnum--;     //注意更新
    //注意删除顶点后，数组中编号大于pos的结点的编号要减一！
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            if (p->adjvex > pos)
            {
                p->adjvex--;
            }
            p = p->nextarc;
        }
    }
    return OK;
}

status InsertArc(ALGraph &G, KeyType v, KeyType w)
{
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    if (i == -1 || j == - 1)
    {
        return ERROR;
    }
    ArcNode *p = G.vertices[i].firstarc;
    while (p)
    {
        if (p->adjvex == j)
        {
            return ERROR;
        }
        p = p->nextarc;
    }
    ArcNode *t = (ArcNode *)malloc(sizeof(ArcNode));
    t->adjvex = j;
    t->nextarc = G.vertices[i].firstarc;
    G.vertices[i].firstarc = t;
    t = (ArcNode *)malloc(sizeof(ArcNode));
    t->adjvex = i;
    t->nextarc = G.vertices[j].firstarc;
    G.vertices[j].firstarc = t;
    G.arcnum++;
    return OK;
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
{
    int i = LocateVex(G, v);
    int j = LocateVex(G, w);
    int flagi = 0, flagj = 0;
    if (i == -1 || j == -1)
    {
        return ERROR;
    }
    ArcNode *p = G.vertices[i].firstarc;
    ArcNode *q = NULL;
    while (p && !flagi)
    {
        if (p->adjvex == j)
        {
            if (p == G.vertices[i].firstarc)
            {
                G.vertices[i].firstarc = p->nextarc;
                free(p);
                p = NULL;
            }
            else
            {
                q->nextarc = p->nextarc;
                free(p);
                p = NULL;
            }
            flagi = 1;
        }
        else
        {
            q = p;
            p = p->nextarc;
        }
    }
    p = G.vertices[j].firstarc;
    q = NULL;
    while (p && !flagj)
    {
        if (p->adjvex == i)
        {
            if (p == G.vertices[j].firstarc)
            {
                G.vertices[j].firstarc = p->nextarc;
                free(p);
                p = NULL;
            }
            else
            {
                q->nextarc = p->nextarc;
                free(p);
                p = NULL;
            }
            flagj = 1;
        }
        else
        {
            q = p;
            p = p->nextarc;
        }
    }
    if (flagi && flagj)
    {
        G.arcnum--;
        return OK;
    }
    return ERROR;
}

void visit(VertexType v)
{
    printf("%d %s ", v.key, v.others);
}

void DFS(ALGraph G, int v, int visited[], void (*visit)(VertexType ))
{
    visited[v] = 1;
    visit(G.vertices[v].data);
    ArcNode *p = G.vertices[v].firstarc;
    while (p)
    {
        if (!visited[p->adjvex])
        {
            DFS(G, p->adjvex, visited, visit);
        }
        p = p->nextarc;
    }
}

status DFSTraverse(ALGraph &G, void (*visit)(VertexType ))
{
    int visited[MAX_VERTEX_NUM] = {0};
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            DFS(G, i, visited, visit);
        }
    }
    return OK;
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
    int visited[MAX_VERTEX_NUM] = {0};
    std::queue<int> q;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            visit(G.vertices[i].data);
            visited[i] = 1;
            q.push(i);
            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                ArcNode *p = G.vertices[v].firstarc;
                while (p)
                {
                    if (!visited[p->adjvex])
                    {
                        visit(G.vertices[p->adjvex].data);
                        visited[p->adjvex] = 1;
                        q.push(p->adjvex);
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    return OK;
}

status SaveGraph(ALGraph G, char FileName[])
{
    FILE *fp = fopen(FileName, "w");
    if (!fp)
    {
        return ERROR;
    }
    for (int i = 0; i < G.vexnum; i++)
    {
        fprintf(fp, "%d %s ", G.vertices[i].data.key, G.vertices[i].data.others);
    }
    fprintf(fp, "-1 nil ");
    
    int VR[101][2];
    int cnt = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        ArcNode *p = G.vertices[i].firstarc;
        while (p)
        {
            if (p->adjvex > i)
            {
                int key1 = G.vertices[i].data.key;
                int key2 = G.vertices[p->adjvex].data.key;
                if (key1 < key2)
                {
                    VR[cnt][0] = key2;
                    VR[cnt][1] = key1;
                }
                else
                {
                    VR[cnt][0] = key1;
                    VR[cnt][1] = key2;
                }
                cnt++;
            }
            p = p->nextarc;
        }
    }
    
    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = i + 1; j < cnt; j++)
        {
            if (VR[i][0] > VR[j][0] || (VR[i][0] == VR[j][0] && VR[i][1] > VR[j][1]))
            {
                int temp0 = VR[i][0];
                int temp1 = VR[i][1];
                VR[i][0] = VR[j][0];
                VR[i][1] = VR[j][1];
                VR[j][0] = temp0;
                VR[j][1] = temp1;
            }
        }
    }
    
    for (int i = 0; i < cnt; i++)
    {
        fprintf(fp, "%d %d ", VR[i][0], VR[i][1]);
    }
    fprintf(fp, "-1 -1");
    fclose(fp);
    return OK;
}

status LoadGraph(ALGraph &G, char FileName[])
{
    FILE *fp = fopen(FileName, "r");
    if (!fp)
    {
        return ERROR;
    }
    VertexType V[21] = {0};
    KeyType VR[101][2] = {0};
    int cnt = 0;
    do
    {
        fscanf(fp, "%d%s", &V[cnt].key, V[cnt].others);
    } while (V[cnt++].key != -1);
    cnt = 0;

    do
    {
        fscanf(fp, "%d%d", &VR[cnt][0], &VR[cnt][1]);
    } while (VR[cnt++][0] != -1);
    
    CreateGraph(G, V, VR);
    fclose(fp);
    return OK;
}

void Dijkstra(ALGraph G, int u, int dis[])
{
    const int INF = 0x3f3f3f3f;
    int n = G.vexnum;
    for (int i = 0; i < n; i++)
    {
        dis[i] = INF;
    }
    dis[u] = 0;
    using Pair = std::pair<int, int>;
    std::priority_queue<Pair, std::vector<Pair>, std::greater<Pair>> pq;
    pq.push({0, u});
    while (!pq.empty())
    {
        int d = pq.top().first;
        int v = pq.top().second;
        pq.pop();
        if (dis[v] != d)
        {
            continue;
        }
        ArcNode *p = G.vertices[v].firstarc;
        while (p)
        {
            int w = p->adjvex;
            int newdis = dis[v] + 1;
            if (newdis < dis[w])
            {
                dis[w] = newdis;
                pq.push({dis[w], w});
            }
            p = p->nextarc;
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (dis[i] == INF)
        {
            dis[i] = -1;
        }
    }
}

int ConnectedComponentsNums(ALGraph G)
{
    int visited[MAX_VERTEX_NUM] = {0};
    int cnt = 0;
    for (int i = 0; i < G.vexnum; i++)
    {
        if (!visited[i])
        {
            cnt++;
            std::queue<int> q;
            visited[i] = 1;
            q.push(i);
            while (!q.empty())
            {
                int v = q.front();
                q.pop();
                ArcNode *p = G.vertices[v].firstarc;
                while (p)
                {
                    if (!visited[p->adjvex])
                    {
                        visited[p->adjvex] = 1;
                        q.push(p->adjvex);
                    }
                    p = p->nextarc;
                }   
            }
        }
    }
    return cnt;
}

void PrintGraph(ALGraph G)
{
    for (int j = 0; j < G.vexnum; j++)
    {
        ArcNode* p = G.vertices[j].firstarc;
        printf("%d %s", G.vertices[j].data.key, G.vertices[j].data.others);
        while (p)
        {
            printf(" %d", p->adjvex);
            p = p->nextarc;
        }
        printf("\n");
    }
}
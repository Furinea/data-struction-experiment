#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "graph.h"

int LocateGraphByName(ALGraph Gs[], char name[])
{
    for (int i = 0; i < 10; i++)
    {
        if (Gs[i].vexnum != 0 && strcmp(Gs[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

int main()
{
    ALGraph G[10];
    int k = 0;
    int i = 0;
    KeyType u,w;
    VertexType value;
    int l,l2;
    int length;
    VertexType V[21];
    KeyType VR[100][2];
    int dis[21] = {0};
    int op = 1;
    int emptySlot;

    for (int i = 0; i < 10; i++)
    {
        G[i].vexnum = 0;
        G[i].arcnum = 0;
        G[i].name[0] = '\0';
    }
    while (op)
    {
        system("cls");
        printf("      Menu for Graphs based on adjacency tables \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. CreateCraph       11. DFSTraverse\n");
        printf("    	  2. DestroyGraph      12. BFSTraverse\n");
        printf("    	  3. LocateVex         13. VerticesSetLessThanK\n");
        printf("    	  4. PutVex            14. ShortestPathLength\n");
        printf("    	  5. FirstAdjVex       15. ConnectedComponentsNums\n");
        printf("    	  6. NextAdjVex        16. SaveGraph\n");
        printf("    	  7. InsertVex         17. LoadGraph\n");
        printf("    	  8. DeleteVex         18. ChangeGraph\n");
        printf("    	  9. InsertArc         19. PrintTable\n");
        printf("          10. DeleteArc        20. AddGraph\n");
        printf("          21. RemoveGraph      22. FindGraphByName\n");
        printf("          0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~21]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            if (G[k].vexnum != 0)
            {
                printf("图已存在!\n");
            }
            else
            {
                printf("请输入顶点序列和关系对序列:\n");
                i = 0;
                do
                {
                    scanf("%d%s", &V[i].key, V[i].others);
                } while (V[i++].key != -1);
                i = 0;
                do
                {
                    scanf("%d%d", &VR[i][0], &VR[i][1]);
                } while (VR[i++][0] != -1);
                if (CreateGraph(G[k], V, VR) == ERROR)
                {
                    printf("输入数据错，无法创建");
                }
                else
                {
                    printf("创建成功!");
                }
            }
            getchar();
            getchar();
            break;
        case 2:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                DestroyGraph(G[k]);
                printf("图已销毁!\n");
            }
            getchar();
            getchar();
            break;
        case 3:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入要查找的关键字u:\n");
                scanf("%d", &u);
                l = LocateVex(G[k], u);
                if (l == -1)
                {
                    printf("不存在关键字为%d的顶点\n", u);
                }
                else
                {
                    printf("该顶点为 %d %s\n", G[k].vertices[l].data.key, G[k].vertices[l].data.others);
                }
            }
            getchar();
            getchar();
            break;
        case 4:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入要赋值的顶点的关键字:\n");
                scanf("%d", &u);
                l = LocateVex(G[k], u);
                if (l == -1)
                {
                    printf("不存在关键字为%d的顶点\n", u);
                }
                else
                {
                    printf("请输入要赋的值 key others:\n");
                    scanf("%d %s", &value.key, value.others);
                    if (PutVex(G[k], u, value) == ERROR)
                    {
                        printf("关键字不唯一!\n");
                    }
                    else
                    {
                        printf("赋值成功!\n");
                    }
                }
            }
            getchar();
            getchar();
            break;
        case 5:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入要查找第一邻接点的结点的关键字:\n");
                scanf("%d", &u);
                l = LocateVex(G[k], u);
                if (l == -1)
                {
                    printf("不存在关键字为%d的顶点\n", u);
                }
                else
                {
                    l = FirstAdjVex(G[k], u);
                    if (l == -1)
                    {
                        printf("不存在第一邻接点\n");
                    }
                    else
                    {
                        printf("第一邻接点为 %d %s\n", G[k].vertices[l].data.key, G[k].vertices[l].data.others);
                    }
                }
            }
            getchar();
            getchar();
            break;
        case 6:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入u,w(查找u相对w的下一邻接点)\n");
                scanf("%d%d", &u,&w);
                l = LocateVex(G[k], u);
                if (l == -1)
                {
                    printf("不存在关键字为%d的顶点\n", u);
                }
                else
                {
                    l = LocateVex(G[k], w);
                    if (l == -1)
                    {
                        printf("不存在关键字为%d的顶点\n", w);
                    }
                    else
                    {
                        l = NextAdjVex(G[k], u, w);
                        if (l == -1)
                        {
                            printf("不存在下一邻接点\n");
                        }
                        else
                        {
                            printf("下一邻接点为 %d %s\n", G[k].vertices[l].data.key, G[k].vertices[l].data.others);
                        }
                    }
                }
            }
            getchar();
            getchar();
            break;
        case 7:
            printf("请输入要插入的结点的key和others:\n");
            scanf("%d %s", &value.key, value.others);
            if (InsertVex(G[k], value) == ERROR)
            {
                printf("插入失败，请检查关键字或顶点数\n");
            }
            else
            {
                printf("插入成功!");
            }
            getchar();
            getchar();
            break;
        case 8:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入要删除的结点的关键字:\n");
                scanf("%d", &u);
                if (DeleteVex(G[k], u) == ERROR)
                {
                    printf("不存在该顶点!\n");
                }
                else
                {
                    printf("删除成功!\n");
                }
            }
            getchar();
            getchar();
            break;
        case 9:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入要插入的边对应两个顶点的关键字:\n");
                scanf("%d%d", &u, &w);
                if (InsertArc(G[k], u, w) == ERROR)
                {
                    printf("插入失败!请检查顶点和边的存在性\n");
                }
                else
                {
                    printf("插入成功!\n");
                }
            }
            getchar();
            getchar();
            break;
        case 10:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入要删除的边对应两个顶点的关键字:\n");
                scanf("%d%d", &u, &w);
                if (DeleteArc(G[k], u, w) == ERROR)
                {
                    printf("删除失败!请检查顶点和边的存在性\n");
                }
                else
                {
                    printf("删除成功!\n");
                }
            }
            getchar();
            getchar();
            break;
        case 11:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                DFSTraverse(G[k], visit);
            }
            getchar();
            getchar();
            break;
        case 12:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                BFSTraverse(G[k], visit);
            }
            getchar();
            getchar();
            break;
        case 13:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入顶点关键字和目标距离k:\n");
                scanf("%d%d", &u, &length);
                l = LocateVex(G[k], u);
                if (l == -1)
                {
                    printf("不存在关键字为%d的顶点\n", u);
                }
                else if (length < 1)
                {
                    printf("k的值不正确\n");
                }
                else
                {
                    Dijkstra(G[k], l, dis);
                    for (i = 0; i < G[k].vexnum; i++)
                    {
                        if (dis[i] >= 0 && dis[i] < length)
                        {
                            printf("顶点%d %s到目标顶点的距离为%d\n", G[k].vertices[i].data.key, G[k].vertices[i].data.others, dis[i]);
                        }
                    }
                }
            }
            getchar();
            getchar();
            break;
        case 14:
            if (G[k].vexnum == 0)
            {
                printf("图不存在!\n");
            }
            else
            {
                printf("请输入要查找距离的两顶点的关键字:\n");
                scanf("%d%d", &u, &w);
                l = LocateVex(G[k], u);
                l2 = LocateVex(G[k], w);
                if (l == -1 || l2 == -1)
                {
                    printf("顶点不存在!\n");
                }
                else
                {
                    Dijkstra(G[k], l, dis);
                    if (dis[l2] == -1)
                    {
                        printf("不存在路径\n");
                    }
                    else
                    {
                        printf("距离为%d\n", dis[l2]);
                    }
                }
            }
            getchar();
            getchar();
            break;
        case 15:
            if (G[k].vexnum == 0)
            {
                printf("图为空!\n");
            }
            else
            {
                printf("连通分量个数为%d", ConnectedComponentsNums(G[k]));
            }
            getchar();
            getchar();
            break;
        case 16:
            if (G[k].vexnum == 0)
            {
                printf("图为空!\n");
            }
            else
            {
                char filename[100];
                printf("请输入要保存的文件名: ");
                scanf("%s", filename);
                SaveGraph(G[k], filename);
                printf("已保存!\n");
            }
            getchar();
            getchar();
            break;
        case 17:
            if (G[k].vexnum != 0)
            {
                printf("图已存在! 请先销毁或切换到空图位置。\n");
            }
            else
            {
                char filename[100];
                printf("请输入要加载的文件名: ");
                scanf("%s", filename);
                LoadGraph(G[k], filename);
                printf("加载成功!\n");
            }
            getchar();
            getchar();
            break;
        case 18:
            printf("切换图的方式：1-按序号  2-按名称\n");
            int choice;
            scanf("%d", &choice);
            if (choice == 1)
            {
                printf("要切换至第几个图? (1-10)\n");
                l = k;
                scanf("%d", &k);
                if (k < 1 || k > 10)
                {
                    printf("请输入1-10的数字\n");
                    k = l;
                }
                else
                {
                    k--;
                    printf("切换成功! 当前图为 \"%s\"\n", G[k].name);
                }
            }
            else if (choice == 2)
            {
                char tname[20];
                printf("请输入要切换的图名: ");
                scanf("%s", tname);
                int pos = LocateGraphByName(G, tname);
                if (pos == -1)
                {
                    printf("未找到名为 %s 的图\n", tname);
                }
                else
                {
                    k = pos;
                    printf("切换成功! 当前图为 \"%s\"\n", G[k].name);
                }
            }
            else
            {
                printf("无效选择\n");
            }
            getchar();
            getchar();
            break;
        case 19:
            if (G[k].vexnum == 0)
            {
                printf("图为空!\n");
            }
            else
            {
                PrintGraph(G[k]);
            }
            getchar();
            getchar();
            break;
        case 20:
            emptySlot = -1;
            for (int i = 0; i < 10; i++)
            {
                if (G[i].vexnum == 0)
                {
                    emptySlot = i;
                    break;
                }
            }
            if (emptySlot == -1)
            {
                printf("最多支持10个图，无法添加！\n");
            }
            else
            {
                if (G[emptySlot].vexnum != 0)
                {
                    DestroyGraph(G[emptySlot]);
                }
                G[emptySlot].vexnum = 0;
                G[emptySlot].arcnum = 0;
                G[emptySlot].kind = UDG;
                for (int j = 0; j < MAX_VERTEX_NUM; j++)
                {
                    G[emptySlot].vertices[j].firstarc = NULL;
                }
                printf("请输入新图的名称: ");
                scanf("%s", G[emptySlot].name);
                k = emptySlot;
                printf("已添加新图 \"%s\"，当前自动切换到图 %d\n", G[k].name, k + 1);
            }
            getchar();
            getchar();
            break;
        case 21:
            if (G[k].vexnum == 0)
            {       
                printf("当前图已经是空图，无需删除。\n");
            }
            else
            {
                DestroyGraph(G[k]);
                for (int i = k; i < 9; i++)
                {
                    if (G[i+1].vexnum != 0)
                    {
                        G[i] = G[i+1];
                        G[i+1].vexnum = 0;
                        G[i+1].arcnum = 0;
                        G[i+1].name[0] = '\0';
                        for (int j = 0; j < MAX_VERTEX_NUM; j++)
                            {
                                G[i+1].vertices[j].firstarc = NULL;
                            }
                    }
                }
                if (G[9].vexnum != 0)
                {
                    DestroyGraph(G[9]);
                    G[9].vexnum = 0;
                    G[9].arcnum = 0;
                    G[9].name[0] = '\0';
                }
                int firstNonEmpty = -1;
                for (int i = 0; i < 10; i++)
                {
                    if (G[i].vexnum != 0)
                    {
                        firstNonEmpty = i;
                        break;
                    }
                }
                if (firstNonEmpty != -1)
                    {
                        k = firstNonEmpty;
                    }
                else
                    {
                        k = 0;
                    }
                    printf("当前图已移除，自动切换到图 \"%s\" (序号 %d)\n", G[k].name, k + 1);
                }
            getchar();
            getchar();
            break;
        case 22:
            {
                char tname[20];
                printf("请输入要查找位置的图名: ");
                scanf("%s", tname);
                int pos = LocateGraphByName(G, tname);
                if (pos == -1)
                {
                    printf("未找到名为 %s 的图\n", tname);
                }
                else
                {
                    printf("图 \"%s\" 的位置为第 %d 个图（数组下标 %d）\n", tname, pos + 1, pos);
                }
            }
            getchar();
            getchar();
            break;
        case 0:
            break;
        default:
            printf("无效选项\n");
        }
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
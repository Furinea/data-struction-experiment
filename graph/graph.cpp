#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<queue>
#include "graph.h"

status CreateCraph(ALGraph &G, VertexType V[], KeyType VR[][2])
{
    return status();
}

status DestroyGraph(ALGraph &G)
{
    return status();
}

int LocateVex(ALGraph G, KeyType u)
{
    return 0;
}

status PutVex(ALGraph &G, KeyType u, VertexType value)
{
    return status();
}

int NextAdjVex(ALGraph G, KeyType v, KeyType w)
{
    return 0;
}

status InsertVex(ALGraph &G, VertexType v)
{
    return status();
}

status DeleteVex(ALGraph &G, KeyType v)
{
    return status();
}

status InsertArc(ALGraph &G, KeyType v, KeyType w)
{
    return status();
}

status DeleteArc(ALGraph &G, KeyType v, KeyType w)
{
    return status();
}
/*
void visit()
*/
status DFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
    return status();
}

status BFSTraverse(ALGraph &G, void (*visit)(VertexType))
{
    return status();
}

status SaveGraph(ALGraph G, char FileName[])
{
    return status();
}

status LoadGraph(ALGraph &G, char FileName[])
{
    return status();
}

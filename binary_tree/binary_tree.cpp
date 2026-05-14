#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<queue>
#include<stack>
#include "binary_tree.h"

int KeyExistInDef(TElemType definition[], int index, KeyType key)
{
    for (int i = 0; i < index; i++)
    {
        if (definition[i].key == key)
        {
            return 1;
        }
    }
    return 0;
}

status CreateBiTree(BiTree &T, TElemType definition[])
{
    static int index = 0;       //注意一定要用静态变量或者全局变量
    if (definition[index].key == 0)     //递归终止条件1
    {
        T = NULL;
        index++;
        return OK;
    }
    if (definition[index].key == -1)    //递归终止条件2
    {
        return OK;
    }
    T = (BiTree)malloc(sizeof(BiTNode));    //创建新结点
    if (!T)
    {
        return ERROR;
    }
    if (KeyExistInDef(definition, index, definition[index].key))    //检测关键字是否重复
    {
        return ERROR;
    }
    T->data = definition[index];
    index++;
    if (CreateBiTree(T->lchild, definition) == ERROR)   //递归构造左子树
    {
        return ERROR;   
    }
    if (CreateBiTree(T->rchild, definition) == ERROR)   //递归构造右子树
    {
        return ERROR;
    }
    return OK;
}

status ClearBiTree(BiTree &T)
{
    if (!T)     //递归终止条件
    {
        return OK;
    }
    ClearBiTree(T->lchild);
    ClearBiTree(T->rchild);
    free(T);
    T = NULL;
    return OK;
}

status BiTreeEmpty(BiTree T)        //哪里用到？？
{
    if (T && T->data.key == -1)
    {
        return TRUE;
    }
    return FALSE;
}

int BiTreeDepth(BiTree T)
{
    if (!T)
    {
        return 0;
    }
    return (BiTreeDepth(T->lchild) > BiTreeDepth(T->rchild) ? BiTreeDepth(T->lchild) : BiTreeDepth(T->rchild)) + 1;
}

BiTNode *LocateNode(BiTree T, KeyType e)
{
    if (!T)
    {
        return NULL;
    }
    if (T->data.key == e)
    {
        return T;
    }
    BiTree l =  LocateNode(T->lchild, e);   //注意要用到返回值
    if (l)
    {
        return l;
    }
    return LocateNode(T->rchild, e);
}

int KeyExistInTree(BiTree T, KeyType key)
{
    if (!T)
    {
        return 0;
    }
    if (T->data.key == key)
    {
        return 1;
    }
    return KeyExistInTree(T->lchild, key) || KeyExistInTree(T->rchild, key);
}

status Assign(BiTree &T, KeyType e, TElemType value)
{
    int flag = KeyExistInTree(T, value.key);      //一定要从根结点开始查找关键字
    BiTree t = LocateNode(T, e);
    if (t)
    {
        if (flag && t->data.key != value.key)   //判断关键字是否重复
        {
            return ERROR;
        }
        t->data = value;
        return OK;
    }
    return ERROR;
}

BiTNode *GetSibling(BiTree T, KeyType e)
{
    if (!T)
    {
        return NULL;
    }
    if (T->lchild && T->lchild->data.key == e)      //注意要判断孩子是否存在，因为要用到孩子的key
    {
        return T->rchild;
    }
    if (T->rchild && T->rchild->data.key == e)
    {
        return T->lchild;
    }
    BiTree l = GetSibling(T->lchild, e);
    if (l)
    {
        return l;
    }
    return GetSibling(T->rchild, e);
}

status InsertNode(BiTree &T, KeyType e, int LR, TElemType c)
{
    if (KeyExistInTree(T, c.key))
    {
        return ERROR;
    }
    if (LR == -1)
    {
        BiTree newT = (BiTree )malloc(sizeof(BiTNode));
        newT->data = c;
        newT->rchild = T;
        T = newT;
        return OK;
    }
    BiTree t =LocateNode(T, e);
    if (!t)
    {
        return ERROR;
    }
    if (LR == 0)
    {
        BiTree tl = t->lchild;
        BiTree newnode = (BiTree )malloc(sizeof(BiTNode));
        t->lchild = newnode;
        newnode->data = c;
        newnode->lchild = NULL;
        newnode->rchild = tl;
    }
    else
    {
        BiTree tr = t->rchild;
        BiTree newnode = (BiTree )malloc(sizeof(BiTNode));
        t->rchild = newnode;
        newnode->data = c;
        newnode->lchild = NULL;
        newnode->rchild = tr;
    }
    return OK;
}

BiTNode *FindParent(BiTree T, KeyType key)
{
    if (!T || (!T->lchild && !T->rchild))    //为空或没孩子
    {
        return NULL;
    }
    if (T->data.key == key)                 //自己就是根结点
    {
        return NULL;
    }
    if ((T->lchild && T->lchild->data.key == key) || (T->rchild && T->rchild->data.key == key))
    {
        return T;
    }
    BiTree l = FindParent(T->lchild, key);
    if (l)
    {
        return l;
    }
    return FindParent(T->rchild, key);
}

int DegreeNode(BiTree T)
{
    int d = 0;
    if (T->lchild)
    {
        d++;
    }
    if (T->rchild)
    {
        d++;
    }
    return d;
}

status DeleteNode(BiTree &T, KeyType e) //删除树根？
{
    if (!T)
    {
        return ERROR;
    }
    BiTree t = LocateNode(T, e);    
    if (!t)
    {
        return ERROR;
    }
    int d = DegreeNode(t);
    BiTree pa = FindParent(T, e);
    if (d == 0)
    {
        if (!pa)
        {
            T = NULL;
        }
        else
        {
            if (pa->lchild == t)
            {
                pa->lchild = NULL;
            }
            else
            {
                pa->rchild = NULL;
            }
        }
    }
    else if (d == 1)
    {
        BiTree child = (t->lchild != NULL) ? t->lchild : t->rchild;
        if (!pa)
        {
            T = child;
        }
        else
        {
            if (pa->lchild == t)
            {
                pa->lchild = child;
            }
            else
            {
                pa->rchild = child;
            }
        }
    }
    else if (d == 2)
    {
        BiTree l = t->lchild;
        BiTree r = t->rchild;
        BiTree mostright = l;
        while (mostright->rchild)
        {
            mostright = mostright->rchild;
        }
        if (!pa)
        {
            T = l;
        }
        else
        {
            if (pa->lchild == t)
            {
                pa->lchild = l;
            }
            else
            {
                pa->rchild = l;
            }
        }            
        mostright->rchild = r;
    }
    free(t);
    t = NULL;
    return OK;
}

/*
void visit(BiTree node) {
    printf("%d %s ", node->data.key, node.data.other);
}
*/

status PreOrderTraverse(BiTree T, void (*visit)(BiTree))    //非递归，用栈模拟
{
    if (!T)
    {
        return INFEASIBLE;
    }
    std::stack<BiTree> s;
    s.push(T);          //根结点入栈
    while (!s.empty())
    {
        BiTree p = s.top();        
        s.pop();
        visit(p);        
        if (p->rchild)          //注意是右孩子先进栈
        {
            s.push(p->rchild);
        }
        if (p->lchild)
        {
            s.push(p->lchild);
        }
    }
    return OK;
}

status InOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (!T)
    {
        return INFEASIBLE;
    }
    InOrderTraverse(T->lchild, visit);
    visit(T);
    InOrderTraverse(T->rchild, visit);
    return OK;
}

status PostOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (!T)
    {
        return INFEASIBLE;
    }
    PostOrderTraverse(T->lchild, visit);
    PostOrderTraverse(T->rchild, visit);
    visit(T);
    return OK;
}

status LevelOrderTraverse(BiTree T, void (*visit)(BiTree))
{
    if (!T)
    {
        return INFEASIBLE;
    }    
    std::queue<BiTree> q;
    q.push(T);
    while (!q.empty())
    {
        BiTree t = q.front();
        visit(T);
        if (t->lchild)
        {
            q.push(t->lchild);
        }
        if (t->rchild)
        {
            q.push(t->rchild);
        }
        q.pop();
    }
    return OK;
}

void PreOrderPrint(BiTree T,int pos, FILE *fp)
{
    if (T)
    {   
        fprintf(fp, "%d %d %s ", pos, T->data.key, T->data.others);
        PreOrderPrint(T->lchild, pos * 2, fp);
        PreOrderPrint(T->rchild, pos * 2 + 1, fp);
    }
}

status SaveBiTree(BiTree T, char FileName[])
{
    if (!T)
    {
        return INFEASIBLE;
    }
    FILE *fp = fopen(FileName, "w");
    if (!fp)
    {
        return ERROR;
    }
    PreOrderPrint(T, 1, fp);
    fprintf(fp, "0 0 null");
    fclose(fp);
    return OK;
}

void CreateLoadBiTree(BiTree &T, int pos[], TElemType definition[])
{
    int i = 0, j;
    BiTree node[100];
    while (j = pos[i])
    {
        node[j] = (BiTree)malloc(sizeof(BiTNode));
        node[j]->lchild = NULL;
        node[j]->rchild = NULL;
        node[j]->data = definition[i];
        if (j != 1)
        {
            if (j % 2 == 0)
            {
                node[j / 2]->lchild = node[j];
            }
            else
            {
                node[j / 2]->rchild = node[j];
            }
        }
        i++;
    }
    T = node[1];    //注意赋值
}

status LoadBiTree(BiTree &T, char FileName[])
{
    FILE *fp = fopen(FileName, "r");
    if (!fp)
    {
        return ERROR;
    }
    TElemType definition[100];
    int pos[100];
    int i = 0;
    do
    {
        fscanf(fp, "%d%d%s", &pos[i], &definition[i].key, definition[i].others);
    } while (pos[i++]);
    fclose(fp);
    CreateLoadBiTree(T, pos, definition);
    return OK;
}

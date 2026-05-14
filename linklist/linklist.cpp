#include<stdio.h>
#include<stdlib.h>
#include "linklist.h"

status InitList(LinkList &L)
{
    if (!L)
    {
        L = (LinkList)malloc(sizeof(LNode));
        L->next = NULL;
        L->data = 0;
        return OK;
    }
    return INFEASIBLE;
}

status DestroyList(LinkList &L)
{
    if (L)
    {
        LinkList p = L;
        while (p != NULL)
        {
            LinkList t = p;
            p = p->next;
            free(t);
        }
        L = NULL;
        return OK;
    }
    return INFEASIBLE;
}

status ClearList(LinkList &L)
{
    if (L)
    {
        LinkList p = L->next;
        while (p != NULL)
        {
            LinkList t = p;
            p = p->next;
            free(t);
        }
        L->next = NULL;
        return OK;
    }
    return INFEASIBLE;
}

status ListEmpty(LinkList L)
{
    if (L)
    {
        if (L->next == NULL)
        {
            return TRUE;
        }
        return FALSE;
    }
    return INFEASIBLE;
}

int ListLength(LinkList L)
{
    if (L)
    {
        LinkList p = L->next;
        int s = 0;
        while (p != NULL)
        {
            s++;
            p = p->next;
        }
        return s;
    }
    return INFEASIBLE;
}

status GetElem(LinkList L, int i, ElemType &e)
{
    if (L)
    {
        if (i < 1)
        {
            return ERROR;
        }
        LinkList p = L->next;
        int pos = 1;
        while (pos < i && p)
        {
            pos++;
            p = p->next;
        }
        if (pos != i || !p)
        {
            return ERROR;
        }
        e = p->data;
        return OK;
    }
    return INFEASIBLE;
}

int LocateElem(LinkList L, ElemType e)
{
    if (L)
    {
        int i = 1;
        LinkList p = L->next;
        while (p)
        {
            if (p->data == e)
            {
                return i;
            }
            i++;
            p = p->next;
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status PriorElem(LinkList L, ElemType e, ElemType &pre)
{
    if (L)
    {
        LinkList p = L->next;
        if (p->data == e)
        {
            return ERROR;
        }
        while (p->next)
        {
            if (p->next->data == e)
            {
                pre = p->data;
                return OK;
            }
            p = p->next;
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status NextElem(LinkList L, ElemType e, ElemType &next)
{
    if (L)
    {
        LinkList p = L->next;
        if (!p)
        {
            return ERROR;
        }
        while (p->next)
        {
            if (p->data == e)
            {
                next = p->next->data;
                return OK;
            }
            p = p->next;
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status ListInsert(LinkList &L, int i, ElemType e)
{
    if (L)
    {
        if (i < 1)
        {
            return ERROR;
        }
        LinkList p = L;
        int pos = 0;
        while (p && pos < i - 1)
        {
            pos++;
            p = p->next;
        }
        if (pos == i - 1 && p)
        {
            LinkList t = (LinkList)malloc(sizeof(LNode));
            t->data = e;
            t->next = p->next;
            p->next = t;
            return OK;
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status ListDelete(LinkList &L, int i, ElemType &e)
{
    if (L)
    {
        if (i < 1)
        {
            return ERROR;
        }
        LinkList p = L;
        int pos = 0;
        while (pos < i - 1 && p->next)
        {
            pos++;
            p = p->next;
        }
        if (pos == i - 1 && p->next)
        {
            e = p->next->data;
            LinkList t = p->next;
            p->next = t->next;
            free(t);
            return OK;
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status ListTraverse(LinkList L)
{
    if (L)
    {
        LinkList p = L->next;
        while (p)
        {
            printf("%d ", p->data);
            p = p->next;
        }
        /*if (L->next == NULL)
        {
            printf("空线性表");
        }*/
        return OK;
    }
    return INFEASIBLE;
}

status SaveList(LinkList L, char *FileName)
{
    if (L)
    {
        FILE *fp = fopen(FileName, "w");
        LinkList p = L->next;
        while (p)
        {
            fprintf(fp, "%d ", p->data);
            p = p->next;
        }
        fclose(fp);
        return OK; 
    }
    return INFEASIBLE;
}

status LoadList(LinkList &L, char *FileName)
{
    if (!L)
    {
        FILE *fp = fopen(FileName, "r");
        L = (LinkList)malloc(sizeof(LNode));
        L->next = NULL;
        LinkList p = L;
        ElemType e;
        while (fscanf(fp, "%d", &e) != EOF)
        {
            LinkList t = (LinkList)malloc(sizeof(LNode));
            t->data = e;
            p->next = t;
            t->next = NULL;
            p = p->next;
        }
        fclose(fp);
        return OK;
    }
    return INFEASIBLE;
}

status ReverseList(LinkList &L)
{
    if (L)
    {
        LinkList p = L->next;
        LinkList q;
        L->next = NULL;
        while (p)
        {
            q = p->next;
            p->next = L->next;
            L->next = p;
            p = q;
        }
        return OK;
    }
    return INFEASIBLE;
}

status RemoveNthFromEnd(LinkList &L, int n, ElemType &e)
{
    if (L)
    {
        if (L->next == NULL)
        {
            return ERROR;
        }
        int len = ListLength(L);
        if (n < 1 || n > len)
        {
            return ERROR;
        }
        int x = len - n + 1;
        ListDelete(L, x, e);
        return OK;
    }
    return INFEASIBLE;
}

status SortList(LinkList &L)
{
    if (L)
    {
        if (L->next == NULL)
        {
            return ERROR;
        }
        LinkList p = L->next;
        int flag = 1;
        while (flag)
        {
            flag = 0;
            p = L->next;    //每次循环重置
            while (p->next)
            {
                if (p->data > p->next->data)
                {
                    flag = 1;
                    ElemType t = p->data;
                    p->data = p->next->data;
                    p->next->data = t;
                }
                p = p->next;
            }
        }
        return OK;
    }
    return INFEASIBLE;
}

#include<stdio.h>
#include<stdlib.h>
#include "seqlist.h"

status InitList(SqList &L)
{
    if ((L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE)))
    {
        L.listsize = LIST_INIT_SIZE;
        L.length = 0;
        return OK;
    }
    return ERROR;
}

status DestroyList(SqList &L)
{
    if (L.elem)
    {
        free(L.elem); 
        L.elem = NULL;
        L.length = 0;
        L.listsize = 0;
        return OK;
    }
    return INFEASIBLE;
}
   

status ClearList(SqList &L)
{
    if (L.elem)
    {
        L.length = 0;
        return OK;
    }
    return INFEASIBLE;
}

status ListEmpty(SqList L)
{
    if (L.elem)
    {
        if (L.length)
        {
            return FALSE;
        }
        return TRUE;
    }
    return INFEASIBLE;
}

int ListLength(SqList L)
{
    if (L.elem)
    {
        return L.length;
    }
    return INFEASIBLE;
}

status GetElem(SqList L, int i, ElemType &e)
{
    if (L.elem)
    {
        if (i < 1 || i > L.length)
        {
            return ERROR;
        }
        e = L.elem[i - 1];
        return OK;
    }
    return INFEASIBLE;
}

int LocateElem(SqList L, ElemType e)
{
    if (L.elem)
    {
        for (int i = 0; i < L.length; i++)
        {
            if (L.elem[i] == e)
            {
                return i + 1;
            }
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status PriorElem(SqList L, ElemType e, ElemType &pre)
{
    if (L.elem)
    {
        for (int i = 1; i < L.length; i++)
        {
            if (L.elem[i] == e)
            {
                pre = L.elem[i - 1];
                return OK;
            }
        }
        return ERROR;
    }
    return INFEASIBLE;  
}

status NextElem(SqList L, ElemType e, ElemType &next)
{
    if (L.elem)
    {
        for (int i = 0; i < L.length - 1; i++)
        {
            if (L.elem[i] == e)
            {
                next = L.elem[i + 1];
                return OK;
            }
        }
        return ERROR;
    }
    return INFEASIBLE;
}

status ListInsert(SqList &L, int i, ElemType e)
{
    if (L.elem)
    {
        if (i < 1 || i > L.length + 1)
        {
            return ERROR;
        }
        if (L.length == L.listsize)
        {
            if (!(L.elem = (ElemType *) realloc (L.elem, sizeof(ElemType) * (L.listsize + LISTINCREMENT))))
            {
                return ERROR;
            }
            L.listsize += LISTINCREMENT;
        }
        for (int j = L.length - 1; j >= i - 1; j--)
        {
            L.elem[j + 1] = L.elem[j];
        }
        L.elem[i - 1] = e;
        L.length++;
        return OK;
    }
    return INFEASIBLE;
}

status ListDelete(SqList &L, int i, ElemType &e)
{
    if (L.elem)
    {
        e = L.elem[i - 1];        //注意要先取出元素，不能在移动元素后才取出
        if (i < 1 || i > L.length)
        {
            return ERROR;
        }
        for (int j = i - 1; j < L.length - 1; j++)
        {
            L.elem[j] = L.elem[j + 1]; 
        }
        L.length--;
        return OK;
    }
    return INFEASIBLE;
}

status ListTraverse(SqList L)
{
    if (L.elem)
    {
        for (int i = 0; i < L.length; i++)
        {
            printf("%d", L.elem[i]);   //这里假设ElemType为int，如果为其他类型应用相应输出方式
            if (i != L.length - 1)
            {
                printf(" ");
            }
        }
        return OK;
    }
    return INFEASIBLE;
}

status SaveList(SqList L, char *FileName)
{
    if (L.elem)
    {
        FILE *fp;
        fp = fopen(FileName, "w");
        for (int i = 0; i < L.length; i++)
        {
            fprintf(fp, "%d", L.elem[i]);
            if (i != L.length - 1)
            {
                fprintf(fp, " ");
            }
        }
        fclose(fp);
        fp = NULL;
        return OK;
    }
    return INFEASIBLE;
}

status LoadList(SqList &L, char *FileName)      
{
   if (!L.elem)
   {    
        FILE *fp;
        fp = fopen(FileName, "r");
        L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
        L.length = 0;
        L.listsize = LIST_INIT_SIZE;
        ElemType data;
        while (fscanf(fp, "%d", &data) != EOF)
        {
            if (L.length >= L.listsize)
            {
                L.elem = (ElemType *)realloc(L.elem, sizeof(ElemType) * (L.listsize + LISTINCREMENT));
                L.listsize += LISTINCREMENT;
            }
            L.elem[L.length++] = data;
        }
        fclose(fp);
        fp = NULL;
        return OK;
   }
   return INFEASIBLE;
}

status AddList(LISTS &Lists, char ListName[])
{
    if (Lists.length <= 9)
    {
        int i = 0;
        while (ListName[i] != '\0')         //strcpy
        {
            Lists.elem[Lists.length].name[i] = ListName[i];
            i++;
        }
        Lists.elem[Lists.length].name[i] = '\0';
        Lists.elem[Lists.length].L.elem = NULL;
        InitList(Lists.elem[Lists.length].L);
        Lists.length++;
        return OK;
    }
    return ERROR;
}

status RemoveList(LISTS &Lists, char ListName[])
{
    int i = 0;
    while (i < Lists.length)
    {
        int j = 0;
        while (Lists.elem[i].name[j] == ListName[j] && Lists.elem[i].name[j] != '\0')
        {
            j++;
        }
        if (Lists.elem[i].name[j] == ListName[j])
        {
            for (int k = i; k < Lists.length - 1; k++)
            {
                Lists.elem[k] = Lists.elem[k + 1];
            }
            Lists.length--;
            return OK;
        }
        i++;
    }
    return ERROR;
}

int LocateList(LISTS Lists, char ListName[])
{
    int i = 0;
    while (i < Lists.length)
    {
        int j = 0;
        while (Lists.elem[i].name[j] == ListName[j] && Lists.elem[i].name[j] != '\0')
        {
            j++;
        }
        if (Lists.elem[i].name[j] == ListName[j])
        {
            return i + 1;
        }
        i++;
    }
    return 0;
}

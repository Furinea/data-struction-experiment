#include<stdio.h>
#include<stdlib.h>
#include<algorithm>
#include<string.h>
#include "seqlist.h"


status InitList(SqList &L)
{
    if (!L.elem)
    {
        if ((L.elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE)))
        {
            L.listsize = LIST_INIT_SIZE;
            L.length = 0;
            return OK;
        }
    }
    return INFEASIBLE;
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
        if (i <= 0 || i >= L.length + 1) //判断i的位置是否合法
        {
            return ERROR;
        }
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
        if (!fp)
        {
            return ERROR;
        }
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

status RemoveList(LISTS& Lists, char ListName[])
{
    int pos = -1;       
    for (int i = 0; i < Lists.length; i++)
    {
        if (strcmp(Lists.elem[i].name, ListName) == 0)
        {
            pos = i;
            break;
        }
    }
    if (pos != -1)
    {
        DestroyList(Lists.elem[pos].L);      // 注意要释放内存，防止内存泄漏
        for (int i = pos; i < Lists.length - 1; i++) 
        {
            Lists.elem[i] = Lists.elem[i + 1];
        }
        Lists.length--;
        return OK;
    }
    else return ERROR;
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

ElemType MaxSubArray(SqList L)
{
    ElemType ans = L.elem[0];   //注意初始化，不能初始化为0，防止全为负数
    ElemType sum = 0;
    for (int i = 0; i < L.length; i++)
    {
        sum = std::max(L.elem[i], sum + L.elem[i]);     //从当前元素从新开始，或加入前一段子数组
        ans = std::max(ans, sum);       //维护全局最大值
    }
    return ans;
}

int SubArrayNum(SqList L, int k)
{
    int cnt = 0;
    int* prefix_sum = (int* )malloc(sizeof(int) * (L.length + 1));
    prefix_sum[0] = 0;
    for (int i = 0; i < L.length; i++) 
    {
        prefix_sum[i + 1] = prefix_sum[i] + L.elem[i];  //注意数组下标是从0开始，故前缀和数组要后移一位
    }
    for (int i = 0; i < L.length; i++) 
    {
        for (int j = i + 1; j <= L.length; j++) 
        {
            if (prefix_sum[j] - prefix_sum[i] == k) 
            {
                cnt++;
            }
        }
    }
    return cnt;
}

status SortList(SqList L)
{
    if (!L.elem) 
    {
        return INFEASIBLE;
    }
    else if (L.length == 0) 
    {
        return ERROR;
    }
    else
    {
        std::sort(L.elem, L.elem + L.length);
        return OK;
    }
}

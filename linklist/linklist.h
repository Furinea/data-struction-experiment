#ifndef LINKLIST_H
#define LINKLIST_H

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int status;
typedef int ElemType;

typedef struct LNode //单链表（链式结构）结点的定义
{  
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;

typedef struct 
{
    char name[20];
    LinkList list;
} ListTable;        //线性表集合

/**
 * @brief 创建空链表
 * @param L 链表的引用
 * @return status 创建成功返回OK；若L已存在，返回INFEASIBLE
 */
status InitList(LinkList &L);

/**
 * @brief 销毁链表，释放所有结点内存
 * @param L 链表的引用
 * @return status 销毁成功返回OK；若L不存在，返回INFEASIBLE
 */
status DestroyList(LinkList &L);

/**
 * @brief 清空链表，删除所有元素，但保留头结点空间
 * @param L 链表的引用
 * @return status 清空成功返回OK；若L不存在，返回INFEASIBLE
 */
status ClearList(LinkList &L);

/**
 * @brief 判断链表是否为空
 * @param L 链表（只读）
 * @return status L存在且为空返回TRUE，存在且非空返回FALSE；L不存在返回INFEASIBLE
 */
status ListEmpty(LinkList L);

/**
 * @brief 求链表长度
 * @param L 链表（只读）
 * @return int L存在返回结点个数，否则返回INFEASIBLE(-1)
 */
int ListLength(LinkList L);

/**
 * @brief 获取第i个元素的值
 * @param L 链表（只读）
 * @param i 位置（1 <= i <= 长度）
 * @param e 保存取出的元素
 * @return status 成功返回OK；i不合法返回ERROR；L不存在返回INFEASIBLE
 */
status GetElem(LinkList L, int i, ElemType &e);

/**
 * @brief 查找元素e的位置
 * @param L 链表（只读）
 * @param e 待查找的元素
 * @return int 返回首次出现的位置（1~长度），未找到返回0；L不存在返回-1(INFEASIBLE)
 */
int LocateElem(LinkList L, ElemType e);

/**
 * @brief 获取元素e的前驱
 * @param L 链表（只读）
 * @param e 元素
 * @param pre 保存前驱的引用
 * @return status 成功返回OK；前驱不存在（e是首元结点或未找到）返回ERROR；L不存在返回INFEASIBLE
 */
status PriorElem(LinkList L, ElemType e, ElemType &pre);

/**
 * @brief 获取元素e的后继
 * @param L 链表（只读）
 * @param e 元素
 * @param next 保存后继的引用
 * @return status 成功返回OK；后继不存在（e是尾结点或未找到）返回ERROR；L不存在返回INFEASIBLE
 */
status NextElem(LinkList L, ElemType e, ElemType &next);

/**
 * @brief 在第i个位置前插入元素e
 * @param L 链表的引用
 * @param i 位置（1 ~ 长度+1，允许尾部插入）
 * @param e 插入的元素
 * @return status 成功返回OK；i不合法返回ERROR；L不存在返回INFEASIBLE
 */
status ListInsert(LinkList &L, int i, ElemType e);

/**
 * @brief 删除第i个元素，并将其值保存到e
 * @param L 链表的引用
 * @param i 位置（1 ~ 长度）
 * @param e 保存被删除元素
 * @return status 成功返回OK；i不合法返回ERROR；L不存在返回INFEASIBLE
 */
status ListDelete(LinkList &L, int i, ElemType &e);

/**
 * @brief 遍历输出链表所有元素
 * @param L 链表（只读）
 * @return status 遍历成功返回OK；L不存在返回INFEASIBLE
 */
status ListTraverse(LinkList L);

/**
 * @brief 将链表保存到文件
 * @param L 链表（只读）
 * @param FileName 文件名
 * @return status 保存成功返回OK；L不存在返回INFEASIBLE
 */
status SaveList(LinkList L, char *FileName);

/**
 * @brief 从文件读取数据创建链表（L必须为未初始化的空指针）
 * @param L 链表的引用
 * @param FileName 文件名
 * @return status 成功加载返回OK；L已存在或文件错误返回INFEASIBLE
 */
status LoadList(LinkList &L, char *FileName);

//额外功能

/**
 * @brief 链表逆置
 * @param L 链表的引用
 * @return status 逆置成功返回OK；L不存在返回INFEASIBLE
 * @note 头插法反转
 */
status ReverseList(LinkList &L);

/**
 * @brief 删除倒数第n个结点
 * @param L 链表的引用
 * @param n 倒数位置（1 ~ 长度）
 * @param e 保存被删除元素
 * @return status 成功返回OK；链表为空或n无效返回ERROR；L不存在返回INFEASIBLE
 */
status RemoveNthFromEnd(LinkList &L, int n, ElemType &e);

/**
 * @brief 链表排序（冒泡排序改进版）
 * @param L 链表的引用
 * @return status 排序成功返回OK；链表为空返回ERROR；L不存在返回INFEASIBLE
 * @note 冒泡排序改进版
 */
status SortList(LinkList &L);

#endif
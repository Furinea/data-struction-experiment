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

/**
 * @brief 创建链表
 * @param L 链表的引用
 * @return status 如果L不存在，创建一个空表返回OK，否则返回INFEASIBLE
 */
status InitList(LinkList &L);

/**
 * @brief 销毁链表
 * @param L 链表的引用
 * @return status 如果L存在，销毁链表。释放数据元素的内存，返回OK，否则返回INFEASIBLE
 */
status DestroyList(LinkList &L);

/**
 * @brief 清空链表
 * @param L 链表的引用
 * @return status 如果L存在，删除所有元素，但保留空间，返回OK，否则返回INFEASIBLE
 */
status ClearList(LinkList &L);

/**
 * @brief 判断链表是否为空
 * @param L 链表（只读）
 * @return status 如果L存在，L为空返回TRUE，否则返回FALSE；L不存在，返回INFEASIBLE
 */
status ListEmpty(LinkList L);

/**
 * @brief 求链表长度
 * @param L 链表（只读）
 * @return int 如果L存在，返回其长度，否则返回INFEASIBLE(-1)
 */
int ListLength(LinkList L);

/**
 * @brief 获取元素
 * @param L 链表（只读）
 * @param i 第i个元素（1 <= i <= length(L))
 * @param e 取出元素保存到e中
 * @return status 成功获取元素，返回OK；如果i不合法，返回ERROR；如果L不存在，返回INFEASIBLE
 */
status GetElem(LinkList L, int i, ElemType &e);

/**
 * @brief 查找元素
 * @param L 链表（只读）
 * @param e 查找元素e
 * @return int 返回元素e在线性表中的位置(1 ~ length(L))，如果e不存在，返回0(ERROR)，如果L不存在，返回-1(INFEASIBLE)
 */
int LocateElem(LinkList L, ElemType e);

/**
 * @brief 获取元素e的前驱
 * @param L 链表（只读）
 * @param e 元素
 * @param pre 前驱的引用
 * @return status 如果成功，返回OK；如果前驱不存在，返回ERROR；如果链表不存在，返回INFEASIBLE
 */
status PriorElem(LinkList L, ElemType e, ElemType &pre);

/**
 * @brief 获取元素e的后继
 * @param L 链表（引用）
 * @param e 元素
 * @param next 后继的引用
 * @return status 如果成功，返回OK；如果前驱不存在，返回ERROR；如果链表不存在，返回INFEASIBLE
 */
status NextElem(LinkList L, ElemType e, ElemType &next);

/**
 * @brief 在链表的第i个元素前插入元素e
 * @param L 链表的引用
 * @param i 第i个元素（范围1~length(L) + 1）允许在尾部插入新元素
 * @param e 插入元素
 * @return status 成功，返回OK；i的位置不合法，返回ERROR；L不存在，返回INFEASIBLE
 */
status ListInsert(LinkList &L, int i, ElemType e);

/**
 * @brief 删除链表的第i个元素，并保存在e中
 * @param L 链表的引用
 * @param i 元素位置，1~length(L)
 * @param e 保存第i个元素
 * @return status 成功，返回OK；i不合法，返回ERROR；L不存在，返回INFEASIBLE
 */
status ListDelete(LinkList &L, int i, ElemType &e);

/**
 * @brief   遍历链表
 * @param L 链表（只读）
 * @return status 如果L存在，按顺序输出每个元素，并返回OK；否则，返回INFEASIBLE
 */
status ListTraverse(LinkList L);

/**
 * @brief 保存链表到文件中
 * @param L 链表（只读）
 * @param FileName 文件名
 * @return status 成功，返回OK；L不存在，返回INFEASIBLE
 */
status SaveList(LinkList L, char *FileName);

/**
 * @brief 从文件中读取数据到链表（L不存在）
 * @param L 链表的引用
 * @param FileName 文件名
 * @return status 如果L不存在，成功读入，返回OK；否则，返回INFEASIBLE
 */
status LoadList(LinkList &L, char *FileName);

/**
 * @brief 链表逆置
 * @param L 链表的引用
 * @return status 成功，返回OK；否则，返回INFEASIBLE
 * @note 头插法反转
 */
status reverseList(LinkList &L);

/**
 * @brief 删除链表倒数第n个结点
 * @param L 链表的引用
 * @param n 位置(1~len)
 * @param e 保存元素
 * @return status 成功删除，返回OK；表为空，返回ERROR；否则，返回INFEASIBLE 
 */
status RemoveNthFromEnd(LinkList &L, int n, ElemType &e);

/**
 * @brief 链表排序
 * @param L 链表的引用
 * @return status 成功排序，返回OK；L为空，返回EROOR；L不存在，返回INFEASIBLE
 * @note 冒泡排序改进版
 */
status sortList(LinkList &L);

#endif
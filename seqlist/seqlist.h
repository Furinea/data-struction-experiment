#ifndef SEQLIST_H
#define SEQLIST_H

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0         //表示元素不合法
#define INFEASIBLE -1   //表示表有问题
#define OVERFLOW -2
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10

typedef int status;
typedef int ElemType;   //数据元素类型定义

typedef struct 
{
    ElemType *elem;
    int length;         //表长
    int listsize;       //表最大长度
}SqList;
typedef struct          //线性表的集合类型定义
{  
    struct 
    {
        char name[30];
        SqList L;
    } elem[10];
    int length;
}LISTS;
//LISTS Lists;      //线性表集合的定义Lists

/**
 * @brief 初始化线性表
 * @param L 顺序表引用（未初始化的）
 * @return status OK 成功，INFEASIBLE 失败（例如内存不足）
 */
status InitList(SqList &L);

/**
 * @brief 销毁线性表，释放所有内存
 * @param L 顺序表引用，销毁后不能再使用（除非重新初始化）
 * @return 成功返回 OK，否则 返回INFEASIBLE
 */
status DestroyList(SqList &L);

/**
 * @brief 清空线性表，使长度变为0，但保留已分配的内存
 * @param L 顺序表引用
 * @return status OK 成功，INFEASIBLE 失败（如 L 无效）
 */
status ClearList(SqList &L);

/**
 * @brief 判断线性表是否为空
 * @param L 顺序表（只读）
 * @return status 如果表为空返回 TRUE，否则返回 FALSE；若 L 无效返回 INFEASIBLE
 * @note 返回值类型为 status，通常 TRUE=1，FALSE=0，INFEASIBLE=-1
 */
status ListEmpty(SqList L);

/**
 * @brief 获取线性表当前长度（元素个数）
 * @param L 顺序表（只读）
 * @return int 表中元素个数；若 L 无效返回 INFEASIBLE
 */
int ListLength(SqList L);

/**
 * @brief 获取指定位置的元素值
 * @param L 顺序表（只读）
 * @param i 第i个元素，故范围(1 <= i <= L.length)
 * @param e 输出参数，保存获取到的元素值
 * @return status OK 成功，i 不合法 返回ERROR，L无效返回INFEASIBLE
 */
status GetElem(SqList L, int i, ElemType &e);

/**
 * @brief 按值查找第一个匹配元素的位置
 * @param L 顺序表（只读）
 * @param e 要查找的元素值
 * @return 元素的序号（范围 1 ~ L.length），若未找到返回 EROOR；若 L 无效返回 INFEASIBLE
 */
int LocateElem(SqList L, ElemType e);

/**
 * @brief 获取元素 e 的前驱元素
 * @param L 顺序表（只读）
 * @param e 已知元素值（假设唯一，否则取第一个）
 * @param pre 输出参数，保存前驱元素的值
 * @return status OK 成功（存在前驱），ERROR 失败（e 是首元素或不存在），返回INFEASIBLE（L 无效）
 */
status PriorElem(SqList L, ElemType e, ElemType &pre);

/**
 * @brief 获取元素 e 的后继元素
 * @param L 顺序表（只读）
 * @param e 已知元素值
 * @param next 输出参数，保存后继元素的值
 * @return status OK 成功（存在后继），ERROR 失败（e 是尾元素或不存在）返回INFEASIBLE（L 无效）
 */
status NextElem(SqList L, ElemType e, ElemType &next);

/**
 * @brief 将新元素插到线性表L的第i个元素前
 * @param L 顺序表引用
 * @param i 插入位置（1 <= i <= L.length + 1）
 * @param e 要插入的元素值
 * @return status OK 成功，ERROR 失败（位置越界、表满或内存不足），L不存在返回INFEASIBLE
 */
status ListInsert(SqList &L, int i, ElemType e);

/**
 * @brief 删除第i个元素，并返回其值
 * @param L 顺序表引用
 * @param i 删除位置（1 <= i <= L.length）
 * @param e 输出参数，保存被删除的元素值
 * @return status OK 成功，ERROR 失败（位置越界）INFEASIBLE（L 无效）
 */
status ListDelete(SqList &L, int i, ElemType &e);

/**
 * @brief 遍历线性表，依次输出所有元素（如打印到控制台）
 * @param L 顺序表（只读）
 * @return status OK 成功，INFEASIBLE（L 无效）
 * @note 输出格式自行定义，例如："1 2 3 ..."
 */
status ListTraverse(SqList L);

/**
 * @brief 保存线性表到文件中
 * @param L 线性表（只读）
 * @param filename 文件名
 * @return status L存在返回OK，否则返回INFEASIBLE
 */
status SaveList(SqList L, char *FileName);

/**
 * @brief 从文件中读入数据到线性表（前提L不存在）
 * @param L 线性表的引用
 * @param filename 文件名
 * @return status L不存在，读入并返回OK，否则返回INFEASIBLE
 */
status LoadList(SqList &L, char *FileName);

/**
 * @brief 添加新表
 * @param Lists 线性表集合
 * @param ListName 新表名字
 * @return status 如果线性表集合已满，返回ERROR；否则创建一个新线性表并分配内存，返回OK
 */
status AddList(LISTS& Lists, char ListName[]);

/**
 * @brief 删除指定表
 * @param Lists 线性表集合
 * @param ListName 删除表的名字
 * @return status 如果找到该线性表，删除并返回OK；否则，返回ERROR·
 */
status RemoveList(LISTS& Lists, char ListName[]);

/**
 * @brief 查找指定表
 * @param Lists 线性表集合
 * @param ListName 表名字
 * @return int 如果找到该线性表，返回其序号（1~len）；否则，返回ERROR(0)
 */
int LocateList(LISTS Lists, char ListName[]);

#endif
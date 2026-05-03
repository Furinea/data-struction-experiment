#include "seqlist.h"
#include <stdio.h>

int main() {
    printf("========== 顺序表实验全关卡测试 ==========\n\n");

    // ---------- 1. 创建线性表 ----------
    SqList L;   // 未初始化，elem 为随机值，需要先 InitList
    status ret = InitList(L);
    printf("1. InitList: %s, length=%d, listsize=%d\n",
           ret == OK ? "OK" : "FAIL", L.length, L.listsize);

    // ---------- 2. 销毁线性表 ----------
    DestroyList(L);
    printf("2. DestroyList: elem=%p, length=%d, listsize=%d\n",
           L.elem, L.length, L.listsize);
    // 重新创建，供后续测试
    InitList(L);

    // ---------- 3. 清空线性表 ----------
    ListInsert(L, 1, 100);
    ListInsert(L, 2, 200);
    printf("3. Before Clear: length=%d\n", L.length);
    ClearList(L);
    printf("   After Clear: length=%d\n", L.length);

    // ---------- 4. 判空 ----------
    printf("4. ListEmpty: %s\n", ListEmpty(L) ? "TRUE" : "FALSE");
    ListInsert(L, 1, 123);
    printf("   After insert, empty: %s\n", ListEmpty(L) ? "TRUE" : "FALSE");

    // ---------- 5. 长度 ----------
    printf("5. ListLength = %d\n", ListLength(L));

    // ---------- 6. 获取元素 ----------
    ElemType e;
    if (GetElem(L, 1, e) == OK)
        printf("6. GetElem pos1 = %d\n", e);
    else
        printf("6. GetElem failed\n");

    // ---------- 7. 查找元素 ----------
    int pos = LocateElem(L, 123);
    printf("7. LocateElem(123) = %d\n", pos);
    printf("   LocateElem(999) = %d\n", LocateElem(L, 999));

    // ---------- 8. 前驱 ----------
    ElemType pre;
    if (PriorElem(L, 123, pre) == OK)
        printf("8. Prior of 123 = %d\n", pre);
    else
        printf("8. No prior\n");
    // 插入一个元素测试前驱
    ListInsert(L, 1, 50);   // 现在顺序: 50, 123
    if (PriorElem(L, 123, pre) == OK)
        printf("   After insert, prior of 123 = %d\n", pre);

    // ---------- 9. 后继 ----------
    ElemType next;
    if (NextElem(L, 50, next) == OK)
        printf("9. Next of 50 = %d\n", next);
    else
        printf("9. No next\n");

    // ---------- 10. 插入元素（批量）----------
    ClearList(L);
    for (int i = 1; i <= 5; i++)
        ListInsert(L, i, i * 10);
    printf("10. After 5 inserts: ");
    ListTraverse(L);      // 输出 "10 20 30 40 50"
    printf("\n");         // 手动换行，便于阅读

    // ---------- 11. 删除元素 ----------
    ElemType del;
    if (ListDelete(L, 3, del) == OK)
        printf("11. Deleted at pos3: %d\n", del);
    printf("    After deletion: ");
    ListTraverse(L);      // 输出 "10 20 40 50"
    printf("\n");

    // ---------- 12. 遍历（已测）----------
    printf("12. Traverse again: ");
    ListTraverse(L);
    printf("\n");

    // ---------- 13. 读写文件 ----------
    char filename[] = "seqlist_test.txt";
    SaveList(L, filename);
    // LoadList 要求 L 不存在（elem == NULL），所以创建一个未初始化的 SqList
    SqList L2 = {NULL, 0, 0};
    LoadList(L2, filename);
    printf("13. Loaded from file: ");
    ListTraverse(L2);
    printf("\n");
    DestroyList(L2);
    remove(filename);   // 删除临时文件

    // ---------- 14~16. 多线性表管理 ----------
    LISTS myLists;
    myLists.length = 0;

    // 14. 增加新线性表
    char name1[] = "ListA";
    char name2[] = "ListB";
    AddList(myLists, name1);
    AddList(myLists, name2);
    printf("14. After adding two lists, total = %d\n", myLists.length);

    // 为 ListA 插入数据
    if (myLists.length >= 1) {
        SqList &refA = myLists.elem[0].L;
        ListInsert(refA, 1, 100);
        ListInsert(refA, 2, 200);
    }
    printf("    ListA elements: ");
    ListTraverse(myLists.elem[0].L);
    printf("\n");

    // 15. 移除线性表
    RemoveList(myLists, name1);
    printf("15. After removing ListA, total = %d\n", myLists.length);
    if (myLists.length >= 1) {
        printf("    Remaining list name: %s\n", myLists.elem[0].name);
    }

    // 16. 查找线性表
    int idx = LocateList(myLists, name2);
    printf("16. Locate ListB: index = %d\n", idx);   // 应返回 1
    idx = LocateList(myLists, name1);
    printf("    Locate ListA: index = %d\n", idx);   // 应返回 0

    // 清理剩余的表
    for (int i = 0; i < myLists.length; i++)
        DestroyList(myLists.elem[i].L);
    DestroyList(L);

    printf("\n========== 所有关卡测试结束 ==========\n");
    return 0;
}
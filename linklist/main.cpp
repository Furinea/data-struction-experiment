#include "linklist.h"
#include <stdio.h>
#include <stdlib.h>

// 辅助函数：打印测试结果状态
void printStatus(status s, const char* msg) {
    if (s == OK) printf("[OK] %s\n", msg);
    else if (s == INFEASIBLE) printf("[INFEASIBLE] %s\n", msg);
    else if (s == ERROR) printf("[ERROR] %s\n", msg);
    else if (s == OVERFLOW) printf("[OVERFLOW] %s\n", msg);
    else printf("[UNKNOWN] %s\n", msg);
}

int main() {
    printf("========== 单链表实验测试（按头文件注释规范） ==========\n\n");

    // 1. 初始化：L 不存在（显式设为 NULL）
    LinkList L = NULL;
    printf(">>> 第一次初始化（L 不存在）\n");
    status ret = InitList(L);
    printStatus(ret, "InitList");
    if (ret != OK) return 1;

    // 2. 判空 && 长度
    printf("\n>>> 判空、长度测试\n");
    printf("ListEmpty = %d (期望 1)\n", ListEmpty(L));
    printf("ListLength = %d (期望 0)\n", ListLength(L));

    // 3. 插入元素（位置 1 到 5）
    printf("\n>>> 插入元素 10,20,30,40,50 到尾部\n");
    for (int i = 1; i <= 5; i++) {
        ret = ListInsert(L, i, i * 10);
        if (ret != OK) printf("插入位置 %d 失败\n", i);
    }
    printf("当前链表: ");
    ListTraverse(L);
    printf("\n");

    // 4. 长度、判空再次验证
    printf("\n>>> 当前长度 = %d\n", ListLength(L));
    printf("ListEmpty = %d (期望 0)\n", ListEmpty(L));

    // 5. GetElem
    printf("\n>>> GetElem 测试\n");
    ElemType e;
    ret = GetElem(L, 3, e);
    if (ret == OK) printf("第3个元素 = %d\n", e);
    else printStatus(ret, "GetElem");

    // 6. LocateElem
    printf("\n>>> LocateElem 测试\n");
    int pos = LocateElem(L, 40);
    printf("元素 40 的位置 = %d\n", pos);
    pos = LocateElem(L, 99);
    printf("元素 99 的位置 = %d\n", pos);

    // 7. PriorElem / NextElem
    printf("\n>>> PriorElem / NextElem 测试\n");
    ElemType pre, next;
    ret = PriorElem(L, 40, pre);
    if (ret == OK) printf("40 的前驱 = %d\n", pre);
    else printStatus(ret, "PriorElem");
    ret = NextElem(L, 40, next);
    if (ret == OK) printf("40 的后继 = %d\n", next);
    else printStatus(ret, "NextElem");

    // 8. ListDelete
    printf("\n>>> 删除第3个元素\n");
    ret = ListDelete(L, 3, e);
    if (ret == OK) printf("删除了元素 %d\n", e);
    ListTraverse(L);
    printf("\n");

    // 9. ClearList（清空后保留头结点）
    printf("\n>>> 清空链表\n");
    ret = ClearList(L);
    printStatus(ret, "ClearList");
    printf("清空后长度 = %d, 判空 = %d\n", ListLength(L), ListEmpty(L));

    // 10. 重新插入 2,4,6,8,10
    printf("\n>>> 重新插入 2 4 6 8 10\n");
    for (int i = 1; i <= 5; i++) ListInsert(L, i, i * 2);
    ListTraverse(L);
    printf("\n");

    // 11. reverseList 逆置
    printf("\n>>> 逆置链表\n");
    ret = reverseList(L);
    printStatus(ret, "reverseList");
    ListTraverse(L);
    printf("\n");

    // 12. RemoveNthFromEnd 删除倒数第2个
    printf("\n>>> 删除倒数第2个结点\n");
    ElemType del;
    ret = RemoveNthFromEnd(L, 2, del);
    if (ret == OK) printf("删除了元素 %d\n", del);
    ListTraverse(L);
    printf("\n");

    // 13. sortList 排序
    printf("\n>>> 排序链表\n");
    ret = sortList(L);
    printStatus(ret, "sortList");
    ListTraverse(L);
    printf("\n");

    // 14. SaveList 保存到文件
    char filename[] = "linklist_test.txt";
    printf("\n>>> 保存链表到文件 %s\n", filename);
    ret = SaveList(L, filename);
    printStatus(ret, "SaveList");

    // 15. LoadList（要求 L 不存在，所以先销毁当前 L）
    printf("\n>>> 销毁当前链表，准备从文件加载\n");
    DestroyList(L);
    L = NULL;   // 确保 L 不存在
    printf("调用 LoadList 前 L = %p\n", L);
    ret = LoadList(L, filename);
    if (ret == OK) {
        printf("从文件加载成功，加载的链表: ");
        ListTraverse(L);
        printf("\n");
    } else {
        printStatus(ret, "LoadList");
    }
    remove(filename); // 删除临时文件

    // 16. 第二次初始化（此时 L 已经存在，应返回 INFEASIBLE）
    printf("\n>>> 第二次初始化（L 已存在）\n");
    ret = InitList(L);
    printStatus(ret, "InitList (should be INFEASIBLE)");

    // 17. 销毁链表
    printf("\n>>> 销毁链表\n");
    ret = DestroyList(L);
    printStatus(ret, "DestroyList");
    printf("销毁后 L = %p\n", L);

    // 18. 再次初始化（L 已不存在）
    printf("\n>>> 再次初始化（L 已不存在）\n");
    ret = InitList(L);
    printStatus(ret, "InitList again");
    DestroyList(L);

    printf("\n========== 测试结束 ==========\n");
    return 0;
}
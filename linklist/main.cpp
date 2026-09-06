#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linklist.h"


int main() 
{
    ListTable L[10];          // 最多管理10张表
    int tableCount = 0;       // 当前已创建的表数量
    int current = -1;         // 当前正在操作的表索引（-1表示未选中任何表）
    int op = 1;
    ElemType e, pre, next;
    int i, j;
    char filename[100];
    char tableName[20];

    // 初始化所有表指针为 NULL
    for (i = 0; i < 10; i++) 
    {
        L[i].list = NULL;
        L[i].name[0] = '\0';
    }

    while (op) 
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    1. 创建新表          7. LocateElem\n");
        printf("    2. 销毁当前表        8. PriorElem\n");
        printf("    3. 清空当前表        9. NextElem \n");
        printf("    4. 判空当前表        10. ListInsert\n");
        printf("    5. 求当前表长        11. ListDelete\n");
        printf("    6. GetElem           12. ListTraverse\n");
        printf("    13. 批量初始化当前表  14. reverseList\n");
        printf("    15. RemoveNthFromEnd 16. sortList\n");
        printf("    17. 保存当前表到文件  18. 从文件加载到当前表\n");
        printf("    19. 切换当前表       20. 删除指定表\n");
        printf("    21. 查找表位置       0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    当前表: %s\n", (current != -1) ? L[current].name : "未选择");
        printf("    请选择你的操作[0~21]:");
        scanf("%d", &op);

        switch (op) 
        {
        case 1: // 创建新表
        {
            if (tableCount >= 10) 
            {
                printf("表数量已达上限（最多10张）！\n");
            } 
            else 
            {
                printf("请输入新表的名称: ");
                scanf("%s", tableName);
                // 检查表名是否已存在
                int exist = 0;
                for (i = 0; i < tableCount; i++) 
                {
                    if (strcmp(L[i].name, tableName) == 0) 
                    {
                        exist = 1;
                        break;
                    }
                }
                if (exist) 
                {
                    printf("表名已存在，请使用其他名称！\n");
                } 
                else 
                {
                    if (InitList(L[tableCount].list) == OK) 
                    {
                        strcpy(L[tableCount].name, tableName);
                        current = tableCount;  // 自动切换到新表
                        tableCount++;
                        printf("表 '%s' 创建成功，并已切换至该表。\n", tableName);
                    } 
                    else 
                    {
                        printf("表创建失败！\n");
                    }
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 2: // 销毁当前表
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            } 
            else 
            {
                if (DestroyList(L[current].list) == OK) 
                {
                    printf("表 '%s' 已销毁。\n", L[current].name);
                    // 移除该表，后面的表前移
                    for (i = current; i < tableCount - 1; i++) 
                    {
                        L[i] = L[i + 1];
                    }
                    tableCount--;
                    if (tableCount == 0) 
                    {
                        current = -1;
                    }
                    else 
                    {
                        current = 0;  // 切换到第一张表
                    }
                } 
                else 
                {
                    printf("销毁失败！\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 3: // 清空当前表
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else if (ClearList(L[current].list) == OK) 
            {
                printf("清空成功！\n");
            }
            else 
            {
                printf("清空失败！\n");
            }
            getchar();
            getchar();
            break;
        }

        case 4: // 判空
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                j = ListEmpty(L[current].list);
                if (j == TRUE) 
                {
                    printf("当前表为空。\n");
                }
                else if (j == FALSE) 
                {
                    printf("当前表非空。\n");
                }
                else 
                {
                    printf("表不存在！\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 5: // 求长
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                j = ListLength(L[current].list);
                if (j == INFEASIBLE) 
                {
                    printf("表不存在！\n");
                }
                else 
                {
                    printf("当前表长度为 %d\n", j);
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 6: // GetElem
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入位置 i: ");
                scanf("%d", &i);
                if (GetElem(L[current].list, i, e) == OK)
                {
                    printf("第 %d 个元素值为 %d\n", i, e);
                }
                else 
                {
                    printf("位置不合法或表不存在\n");
                }
            }
            getchar();
            getchar();
            break;
        }

        case 7: // LocateElem
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入要查找的元素值: ");
                scanf("%d", &e);
                j = LocateElem(L[current].list, e);
                if (j == ERROR) 
                {
                    printf("未找到元素 %d\n", e);
                }
                else if (j == INFEASIBLE) 
                {
                    printf("表不存在\n");
                }
                else 
                {
                    printf("元素 %d 的位置是 %d\n", e, j);
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 8: // PriorElem
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入元素: ");
                scanf("%d", &e);
                if (PriorElem(L[current].list, e, pre) == OK)
                {
                    printf("前驱为 %d\n", pre);
                }
                else 
                {
                    printf("无前驱或表不存在\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 9: // NextElem
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入元素: ");
                scanf("%d", &e);
                if (NextElem(L[current].list, e, next) == OK)
                {
                    printf("后继为 %d\n", next);
                }
                else 
                {
                    printf("无后继或表不存在\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 10: // ListInsert
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入插入位置和元素值: ");
                scanf("%d%d", &i, &e);
                if (ListInsert(L[current].list, i, e) == OK)
                {
                    printf("插入成功\n");
                }
                else 
                {
                    printf("插入失败\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 11: // ListDelete
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入要删除的位置: ");
                scanf("%d", &i);
                if (ListDelete(L[current].list, i, e) == OK)
                {
                    printf("删除成功，被删元素值为 %d\n", e);
                }
                else 
                {
                    printf("删除失败\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 12: // ListTraverse
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("当前表元素: ");
                if (ListTraverse(L[current].list) == INFEASIBLE)
                {
                    printf("表不存在");
                }
                printf("\n");
            }
            getchar(); 
            getchar();
            break;
        }

        case 13: // 批量初始化（要求当前表为空）
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else if (L[current].list->next != NULL) 
            {
                printf("当前表非空，无法批量初始化！\n");
            } 
            else 
            {
                printf("请连续输入整数，以0结束输入:\n");
                int pos = 1;
                while (1) 
                {
                    scanf("%d", &e);
                    if (e == 0) 
                    {
                        break;
                    }
                    if (ListInsert(L[current].list, pos++, e) != OK) 
                    {
                        printf("插入失败，停止输入\n");
                        break;
                    }
                }
                printf("批量输入完成。\n");
            }
            getchar(); 
            getchar();
            break;
        }

        case 14: // reverseList
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else if (ReverseList(L[current].list) == OK) 
            {
                printf("反转成功\n");
            }
            else 
            {
                printf("反转失败\n");
            }
            getchar(); 
            getchar();
            break;
        }

        case 15: // RemoveNthFromEnd
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入 n（删除倒数第 n 个结点）: ");
                scanf("%d", &i);
                if (RemoveNthFromEnd(L[current].list, i, e) == OK)
                {
                    printf("删除倒数第 %d 个结点成功，其值为 %d\n", i, e);
                }
                else 
                {
                    printf("删除失败\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 16: // sortList
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else if (SortList(L[current].list) == OK) 
            {
                printf("排序成功\n");
            }
            else 
            {
                printf("排序失败\n");
            }
            getchar(); 
            getchar();
            break;
        }

        case 17: // 保存当前表到文件
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入要保存的文件名（如 exp1.txt）: ");
                scanf("%s", filename);
                if (SaveList(L[current].list, filename) == OK)
                {
                    printf("保存成功\n");
                }
                else 
                {
                    printf("保存失败\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 18: // 从文件加载到当前表（会先清空当前表）
        {
            if (current == -1) 
            {
                printf("未选中任何表！\n");
            }
            else 
            {
                printf("请输入要加载的文件名: ");
                scanf("%s", filename);
                // 加载前先清空当前表（保留头结点）
                DestroyList(L[current].list);
                if (LoadList(L[current].list, filename) == OK)
                {
                    printf("加载成功\n");
                }
                else 
                {
                    printf("加载失败，请检查文件是否存在或格式正确\n");
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 19: // 切换当前表（按表名）
        {
            if (tableCount == 0) 
            {
                printf("还没有任何表，请先创建表。\n");
            } 
            else 
            {
                printf("当前已有的表: ");
                for (i = 0; i < tableCount; i++) 
                {
                    printf("%s ", L[i].name);
                }
                printf("\n请输入要切换的表名: ");
                scanf("%s", tableName);
                int idx = -1;
                for (i = 0; i < tableCount; i++) 
                {
                    if (strcmp(L[i].name, tableName) == 0) 
                    {
                        idx = i;
                        break;
                    }
                }
                if (idx != -1) 
                {
                    current = idx;
                    printf("已切换到表 '%s'\n", L[current].name);
                } 
                else 
                {
                    printf("表 '%s' 不存在\n", tableName);
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 20: // 删除指定表（按表名）
        {
            if (tableCount == 0) 
            {
                printf("没有表可删除。\n");
            } 
            else 
            {
                printf("请输入要删除的表名: ");
                scanf("%s", tableName);
                int idx = -1;
                for (i = 0; i < tableCount; i++) 
                {
                    if (strcmp(L[i].name, tableName) == 0) 
                    {
                        idx = i;
                        break;
                    }
                }
                if (idx == -1) 
                {
                    printf("表 '%s' 不存在\n", tableName);
                } 
                else 
                {
                    DestroyList(L[idx].list);
                    // 移除该表，后面的表前移
                    for (i = idx; i < tableCount - 1; i++)
                    {
                        L[i] = L[i + 1];
                    }
                    tableCount--;
                    if (tableCount == 0) 
                    {
                        current = -1;
                    }
                    else if (current == idx) 
                    {
                        current = 0; // 若删除的是当前表，切到第一张
                    }
                    else if (current > idx) 
                    {
                        current--;
                    }
                    printf("表 '%s' 已删除\n", tableName);
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 21: // 查找表位置（按表名返回索引）
        {
            if (tableCount == 0) 
            {
                printf("没有表。\n");
            } 
            else 
            {
                printf("请输入要查找的表名: ");
                scanf("%s", tableName);
                int idx = -1;
                for (i = 0; i < tableCount; i++) 
                {
                    if (strcmp(L[i].name, tableName) == 0) 
                    {
                        idx = i;
                        break;
                    }
                }
                if (idx != -1)
                {
                    printf("表 '%s' 位于索引 %d (0-based)\n", tableName, idx);
                }
                else
                {
                    printf("表 '%s' 不存在\n", tableName);
                }
            }
            getchar(); 
            getchar();
            break;
        }

        case 0:
        {
            break;
        }

        default:
        {
            printf("无效选项，请重新输入。\n");
            getchar(); 
            getchar();
            break;
        }
        }
    }

    // 程序结束前销毁所有表，释放内存
    for (i = 0; i < tableCount; i++) 
    {
        DestroyList(L[i].list);
    }
    printf("欢迎下次再使用本系统！\n");
    return 0;
}
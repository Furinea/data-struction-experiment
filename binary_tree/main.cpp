#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "binary_tree.h"

//根据树名查找在多树管理列表中的索引（0-based），未找到返回 -1
int FindTreeByName(ListTree &treeList, char *name);

int main()
{
    ListTree treeList;
    treeList.length = 0;
    memset(treeList.elem, 0, sizeof(treeList.elem));

    int op = 1;
    int cur = -1;
    char filename[100] = "tree_data.txt";   //具体文件
    TElemType definition[100];
    KeyType key, key2;
    TElemType value;
    BiTree t, t2, t3;
    int LR;
    int depth;

    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("     Menu  for  Binary  Tree  Management System\n");
        printf("------------------------------------------------------\n");
        printf("  基本操作:\n");
        printf("    1. AddTree (创建新树)     2. RemoveTree (删除树)\n");
        printf("    3. SwitchTree (切换当前树) 4. RenameTree (重命名)\n");
        printf("    5. ListAllTrees (列出所有树)\n");
        printf("   25. FindTreeByName (按名称查找树)\n");
        printf("  当前树操作 (cur=%d, name=%s):\n", cur+1, (cur>=0?treeList.elem[cur].name:"无"));
        printf("    6. CreateBiTree   7. DestroyBiTree   8. ClearBiTree\n");
        printf("    9. BiTreeEmpty   10. BiTreeDepth    11. LocateNode\n");
        printf("   12. Assign        13. GetSibling     14. InsertNode\n");
        printf("   15. DeleteNode    16. PreOrder       17. InOrder\n");
        printf("   18. PostOrder     19. LevelOrder     20. MaxPathSum\n");
        printf("   21. LowestCommonAncestor  22. InvertTree\n");
        printf("   23. SaveBiTree    24. LoadBiTree\n");
        printf("    0. Exit\n");
        printf("------------------------------------------------------\n");
        printf("请选择: ");
        scanf("%d", &op);
        if (cur == -1 && op >= 6 && op <= 24 && op != 0)
        {
            printf("当前没有可操作的树，请先添加树或切换树！\n");
            getchar();
            getchar();
            continue;
        }

        switch (op)
        {
        case 1:
            if (treeList.length >= 10)
            {
                printf("最多管理10棵树！\n");
            }
            else
            {
                printf("请输入新树的名字: ");
                scanf("%s", treeList.elem[treeList.length].name);
                treeList.elem[treeList.length].T = NULL;
                treeList.length++;
                printf("添加成功，当前树数量: %d\n", treeList.length);
                if (cur == -1)
                {
                    cur = 0;
                }
            }
            break;
        case 2:
            if (treeList.length == 0)
            {
                printf("无树可删除\n");
                break;
            }
            printf("当前树列表:\n");
            for (int i = 0; i < treeList.length; i++)
            {
                printf("  %d. %s\n", i+1, treeList.elem[i].name);
            }
            printf("请输入要删除的树编号(1~%d): ", treeList.length);
            int idx;
            scanf("%d", &idx);
            if (idx < 1 || idx > treeList.length)
            {
                printf("无效编号\n");
                break;
            }
            idx--;
            if (treeList.elem[idx].T)
            {
                ClearBiTree(treeList.elem[idx].T);
            }
            for (int i = idx; i < treeList.length - 1; i++)
            {
                treeList.elem[i] = treeList.elem[i+1];
            }
            treeList.length--;
            if (cur == idx)
            {
                cur = (treeList.length > 0 ? 0 : -1);
            }
            else if (cur > idx)
            {
                cur--;
            }
            printf("删除成功\n");
            break;
        case 3:
            if (treeList.length == 0)
            {
                printf("没有树可切换\n");
                break;
            }
            printf("当前树列表:\n");
            for (int i = 0; i < treeList.length; i++)
            {
                printf("  %d. %s\n", i+1, treeList.elem[i].name);
            }
            printf("请选择要切换的树编号: ");
            scanf("%d", &idx);
            if (idx >= 1 && idx <= treeList.length)
            {
                cur = idx - 1;
                printf("已切换到树: %s\n", treeList.elem[cur].name);
            }
            else
            {
                printf("无效编号\n");
            }
            break;
        case 4:
            printf("请输入新名字: ");
            scanf("%s", treeList.elem[cur].name);
            printf("重命名成功\n");
            break;
        case 5:
            printf("当前共有 %d 棵树:\n", treeList.length);
            for (int i = 0; i < treeList.length; i++)
            {
                printf("  %d. %s %s\n", i+1, treeList.elem[i].name,
                       (treeList.elem[i].T ? "(非空)" : "(空)"));
            }
            break;
        case 6:
            if (treeList.elem[cur].T != NULL)
            {
                printf("当前树已存在，请先销毁或清空\n");
            }
            else
            {
                printf("请输入先序遍历序列（key others，key=0表示空子树，key=-1结束）:\n");
                int i = 0;
                do
                {
                    scanf("%d%s", &definition[i].key, definition[i].others);
                } while (definition[i++].key != -1);
                if (CreateBiTree(treeList.elem[cur].T, definition) == OK)
                {
                    printf("创建成功\n");
                }
                else
                {
                    printf("创建失败（可能关键字重复或序列错误）\n");
                }
            }
            break;
        case 7:
            if (DestroyBiTree(treeList.elem[cur].T) == OK)
            {
                printf("销毁成功\n");
            }
            else
            {
                printf("销毁失败（树不存在）\n");
            }
            break;
        case 8:
            if (ClearBiTree(treeList.elem[cur].T) == OK)
            {
                printf("清空成功\n");
            }
            else
            {
                printf("清空失败\n");
            }
            break;
        case 9:
            if (BiTreeEmpty(treeList.elem[cur].T) == TRUE)
            {
                printf("二叉树为空\n");
            }
            else
            {
                printf("二叉树非空\n");
            }
            break;
        case 10:
            depth = BiTreeDepth(treeList.elem[cur].T);
            if (depth == 0)
            {
                printf("树不存在\n");
            }
            else
            {
                printf("深度为 %d\n", depth);
            }
            break;
        case 11:
            printf("输入要查找的关键字: ");
            scanf("%d", &key);
            t = LocateNode(treeList.elem[cur].T, key);
            if (t)
            {
                printf("找到: %d %s\n", t->data.key, t->data.others);
            }
            else
            {
                printf("未找到\n");
            }
            break;
        case 12:
            printf("输入结点关键字及新值(key others): ");
            scanf("%d%s", &key, value.others);
            printf("输入新关键字的key: ");
            scanf("%d", &value.key);
            if (Assign(treeList.elem[cur].T, key, value) == OK)
            {
                printf("赋值成功\n");
            }
            else
            {
                printf("赋值失败\n");
            }
            break;
        case 13:
            printf("输入结点关键字: ");
            scanf("%d", &key);
            t = GetSibling(treeList.elem[cur].T, key);
            if (t)
            {
                printf("兄弟结点: %d %s\n", t->data.key, t->data.others);
            }
            else
            {
                printf("无兄弟\n");
            }
            break;
        case 14:
            printf("输入父结点关键字, 插入方向(0左/1右), 新结点数据(key others): ");
            scanf("%d%d%d%s", &key, &LR, &value.key, value.others);
            if (InsertNode(treeList.elem[cur].T, key, LR, value) == OK)
            {
                printf("插入成功\n");
            }
            else
            {
                printf("插入失败\n");
            }
            break;
        case 15:
            printf("输入要删除的关键字: ");
            scanf("%d", &key);
            if (DeleteNode(treeList.elem[cur].T, key) == OK)
            {
                printf("删除成功\n");
            }
            else
            {
                printf("删除失败\n");
            }
            break;
        case 16:
            PreOrderTraverse(treeList.elem[cur].T, visit);
            printf("\n");
            break;
        case 17:
            InOrderTraverse(treeList.elem[cur].T, visit);
            printf("\n");
            break;
        case 18:
            PostOrderTraverse(treeList.elem[cur].T, visit);
            printf("\n");
            break;
        case 19:
            LevelOrderTraverse(treeList.elem[cur].T, visit);
            printf("\n");
            break;
        case 20:
            printf("最大路径和: %d\n", MaxPathSum(treeList.elem[cur].T));
            break;
        case 21:
            printf("输入两个结点的关键字: ");
            scanf("%d%d", &key, &key2);
            t = LowestCommonAncestor(treeList.elem[cur].T, key, key2);
            if (t)
            {
                printf("最近公共祖先: %d %s\n", t->data.key, t->data.others);
            }
            else
            {
                printf("未找到公共祖先\n");
            }
            break;
        case 22:
            InvertTree(treeList.elem[cur].T);
            printf("翻转完成\n");
            break;
        case 23:
            printf("输入文件名: ");
            scanf("%s", filename);
            if (SaveBiTree(treeList.elem[cur].T, filename) == OK)
            {
                printf("保存成功\n");
            }
            else
            {
                printf("保存失败\n");
            }
            break;
        case 24:
            if (treeList.elem[cur].T != NULL)
            {
                printf("当前树非空，请先清空或销毁\n");
            }
            else
            {
                printf("输入文件名: ");
                scanf("%s", filename);
                if (LoadBiTree(treeList.elem[cur].T, filename) == OK)
                {
                    printf("加载成功\n");
                }
                else
                {
                    printf("加载失败\n");
                }
            }
            break;
            case 25:
            {
                char searchName[30];
                printf("请输入要查找的树名: ");
                scanf("%s", searchName);
                int pos = FindTreeByName(treeList, searchName);
                if (pos == -1)
                {
                    printf("未找到树 '%s'\n", searchName);
                }
                else
                {
                    printf("树 '%s' 的位置索引是 %d（对应第 %d 棵树）\n", searchName, pos, pos+1);
                }
            }
            break;
        case 0:
            break;
        default:
            printf("无效选项\n");
        }
        if (op != 0)
        {
            getchar();
            getchar();
        }
    }
    for (int i = 0; i < treeList.length; i++)
    {
        if (treeList.elem[i].T)
        {
            DestroyBiTree(treeList.elem[i].T);
        }
    }
    printf("欢迎下次使用！\n");
    return 0;
}

// 根据树名查找在多树管理列表中的索引（0-based），未找到返回 -1
int FindTreeByName(ListTree &treeList, char *name)
{
    for (int i = 0; i < treeList.length; i++)
    {
        if (strcmp(treeList.elem[i].name, name) == 0)
            {
                return i;
            }
    }
    return -1;
}
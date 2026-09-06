#ifndef BINARY_TREE
#define BINARY_TREE

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int KeyType;    //关键字类型定义
typedef int status;

typedef struct          //二叉树结点类型定义
{
    KeyType key;
    char others[20];
} TElemType;

typedef struct BiTNode  //二叉链表结点定义
{
    TElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

typedef struct         //二叉树集合定义
{
    struct 
    {
        char name[30];
        BiTree T;
    } elem[10];
    int length;
} ListTree;


/**
 * @brief 检测序列中是否存在重复关键字
 * @param definition 先序序列数组
 * @param index 序列中待检测的范围长度（前index个元素）
 * @param key 待检测的关键字
 * @return int 存在返回1，否则返回0
 */
int KeyExistInDef(TElemType definition[], int index, KeyType key);

/**
 * @brief 销毁二叉树，释放所有结点内存，并将根指针置为 NULL，树结构不再可用
 * @param T 二叉树的引用（待销毁的树）
 * @return status 销毁成功返回 OK；若 T 本身为 NULL（树不存在）返回 INFEASIBLE
 * @note 销毁后无法再对 T 进行任何操作，除非重新创建
 */
status DestroyBiTree(BiTree &T);

/**
 * @brief 清空二叉树，释放所有结点内存，使树变为空树（根结点为 NULL），但保留树的存储结构（可重新插入）
 * @param T 二叉树的引用
 * @return status 清空成功返回 OK；若树不存在（T 为 NULL）返回 INFEASIBLE
 * @note 与 DestroyBiTree 的区别：清空后树为空，但仍可继续使用（如插入新结点）
 */
status ClearBiTree(BiTree &T);

/**
 * @brief 根据先序序列创建二叉树
 * @param T 二叉树的引用，创建后指向根结点
 * @param definition 以先序序列给出的结点数组（关键字为0，表示空结点；为-1，表示结束）
 * @return status 创建成功返回OK；如果序列中存在重复关键字，返回ERROR
 * @note 调用KeyExistInDef检测序列中是否存在重复关键字
 */
status CreateBiTree(BiTree &T, TElemType definition[]);

/**
 * @brief 判断二叉树是否为空
 * @param T 二叉树（只读）
 * @return status 若为空树返回TRUE，否则返回FALSE
 * @note 约定关键字-1表示结点为空
 */
status BiTreeEmpty(BiTree T);

/**
 * @brief 求二叉树的深度
 * @param T 二叉树（只读）
 * @return int 二叉树的深度（根结点深度为1）
 */
int BiTreeDepth(BiTree T);

/**
 * @brief 查找关键字为e的结点
 * @param T 二叉树（只读）
 * @param e 待查找的关键字
 * @return BiTNode* 找到返回结点指针，否则返回NULL
 */
BiTNode *LocateNode(BiTree T, KeyType e);

/**
 * @brief 检测树中是否存在指定关键字（Assign的辅助函数）
 * @param T 树（只读）
 * @param key 要检测的关键字
 * @return int 存在返回1，否则返回0
 */
int KeyExistInTree(BiTree T, KeyType key);

/**
 * @brief 给指定关键字的结点赋新的数据值
 * @param T 二叉树的引用
 * @param e 目标结点的关键字
 * @param value 要赋给结点的数据
 * @return status 赋值成功返回OK；若结点不存在或新值的关键字冲突，返回ERROR
 * @note 调用LocateNode查找结点，并调用KeyExistInTree检测关键字是否重复
 */
status Assign(BiTree &T, KeyType e, TElemType value);

/**
 * @brief 获得指定结点的兄弟结点
 * @param T 二叉树（只读）
 * @param e 目标结点的关键字
 * @return BiTNode* 找到兄弟结点返回其指针，否则返回NULL
 */
BiTNode *GetSibling(BiTree T, KeyType e);

/**
 * @brief 插入结点
 * @param T 二叉树的引用
 * @param e 待插入结点的父结点关键字
 * @param LR 插入方向：0表示作为左孩子，1表示作为右孩子,结点e的原有左子树或右子树则为结点c的右子树；
 * LR==-1时，将c作为新根结点，原树作为c的右子树
 * @param c 待插入的结点数据
 * @return status 插入成功返回OK；若父结点e不存在或c.key已在树中则返回ERROR
 */
status InsertNode(BiTree &T, KeyType e, int LR, TElemType c);

/**
 * @brief 查找指定结点的父结点（DeleteNode的辅助函数）
 * @param T 树根指针
 * @param key 待查找结点的关键字
 * @return BiTNode* 返回父结点指针；若未找到或其为根，返回NULL
 * @note 递归查找
 */
BiTNode *FindParent(BiTree T, KeyType key);

/**
 * @brief 计算结点的度（孩子个数）
 * @param T 结点指针
 * @return int 度（0、1或2）
 */
int DegreeNode(BiTree T);

/**
 * @brief 删除关键字为e的结点
 * 
 * 算法思路：
 * 1. 查找关键字为e的结点及双亲结点。
 * 2. 若未找到，返回ERROR。
 * 3. 根据被删结点的度处理：
 *    - 度为0：直接删除，双亲对应指针置空。
 *    - 度为1：双亲指向该结点的唯一孩子。
 *    - 度为2：用e的左孩子代替被删除位置，e的右子树作为左子树中最右结点的右子树。
 * 4. 释放被删结点内存。
 * 
 * @param T 二叉树的引用
 * @param e 待删除结点的关键字
 * @return status 删除成功返回OK，否则返回ERROR
 */
status DeleteNode(BiTree &T, KeyType e);


void visit(BiTree node);


/**
 * @brief 先序遍历二叉树并打印结点数据
 * @param T 二叉树（只读）
 * @param visit
 * @return status 遍历成功返回OK；若树不存在返回INFEASIBLE
 */
status PreOrderTraverse(BiTree T, void (*visit)(BiTree));

/**
 * @brief 中序遍历二叉树并打印结点数据
 * @param T 二叉树（只读）
 * @param visit
 * @return status 遍历成功返回OK；若树不存在返回INFEASIBLE
 */
status InOrderTraverse(BiTree T, void (*visit)(BiTree));

/**
 * @brief 后序遍历二叉树并打印结点数据
 * @param T 二叉树（只读）
 * @param visit
 * @return status 遍历成功返回OK；若树不存在返回INFEASIBLE
 */
status PostOrderTraverse(BiTree T, void (*visit)(BiTree));

/**
 * @brief 层序遍历二叉树并打印结点数据
 * @param T 二叉树（只读）
 * @param visit
 * @return status 遍历成功返回OK；若树不存在返回INFEASIBLE
 */
status LevelOrderTraverse(BiTree T, void (*visit)(BiTree));

/**
 * @brief 按结点在满二叉树的位置，先序输出二叉树，SaveBiTree的辅助函数
 * @param T 二叉树的引用
 * @param fp 文件指针
 * @return void
 */
void PreOrderPrint(BiTree T,int pos, FILE *fp);

/**
 * @brief 将二叉树的结点数据写入文件
 * @param T 二叉树（只读）
 * @param FileName 文件名
 * @return status 写入成功返回OK；文件打开失败返回ERROR
 * @note 输出带空枝的先序序列，以0结尾
 */
status SaveBiTree(BiTree T, char FileName[]);

/**
 * @brief 创建二叉树，LoadBiTree函数的辅助函数
 * @param T 二叉树的引用
 * @param pos 结点在满二叉树的位置
 * @param definition 结点信息
 * @return void
 */
void CreateLoadBiTree(BiTree &T, int pos[], TElemType definition[]);

/**
 * @brief 从文件读取二叉树信息并创建二叉树
 * @param T 二叉树的引用
 * @param FileName 文件名
 * @return status 创建成功返回OK；文件打开失败返回ERROR
 * @note 读取带空枝的先序序列，内部调用CreateBiTree
 */
status LoadBiTree(BiTree &T, char FileName[]);

//额外功能

/**
 * @brief 求最大路径和
 * @param T 二叉树（只读）
 * @return int 返回最大路径和；若T不存在，返回0
 */
int MaxPathSum(BiTree T);

/**
 * @brief 最近公共祖先
 * @param T 二叉树
 * @param e1 结点
 * @param e2 结点
 * @return BiTree 返回最近公共祖先；若不存在，返回NULL
 */
BiTree LowestCommonAncestor(BiTree T, KeyType e1, KeyType e2);

/**
 * @brief 翻转二叉树，使所有结点左右互换
 * @param T 二叉树
 * @return status 始终返回OK
 */
status InvertTree(BiTree& T);



#endif
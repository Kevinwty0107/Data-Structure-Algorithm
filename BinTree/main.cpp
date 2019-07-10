#include <iostream>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

using namespace std;

struct BinTreeNode;
typedef struct BinTreeNode * PBinTreeNode;  //封装结点类型
struct BinTreeNode
{
    char info;
    PBinTreeNode llink;
    PBinTreeNode rlink;
};
typedef BinTreeNode * BinTree;  //封装二叉树类型
typedef BinTree * PBinTree;     //再次封装便于传值

BinTree createEmptyBinTree()    //创建空二叉树
{
    BinTree btree = (BinTree)malloc(sizeof(struct BinTreeNode));
    if (btree == NULL)  //判断内存调用是否成功
    {
        cout<<"Out of space!"<<endl;
        return NULL;
    }
    btree->info = '0';
    btree->llink = NULL;
    btree->rlink = NULL;
    return btree;
}

int isNull(BinTree btree)    //判断二叉树是否为空
{
    return (btree == NULL);
}

PBinTreeNode root(BinTree btree)    //寻找子树根结点
{
    if (isNull(btree))
    {
        cout<<"Empty bintree!"<<endl;
        return NULL;
    }
    return btree;
}

PBinTreeNode leftchild(PBinTreeNode p)    //寻找某结点左子树
{
    if (isNull(p))
    {
        cout<<"Empty node!"<<endl;
        return NULL;
    }
    return p->llink;
}

PBinTreeNode rightchild(PBinTreeNode p)    //寻找某结点右子树
{
    if (isNull(p))
    {
        cout<<"Empty node!"<<endl;
        return NULL;
    }
    return p->rlink;
}

void postOrder(BinTree btree)    //后根周游
{
    if (btree == NULL)
        return;
    postOrder(leftchild(btree));
    postOrder(rightchild(btree));
    cout<<' '<<root(btree)->info;    //输出访问结点信息
}

int height(BinTree btree)    //计算高度
{
    if (btree == NULL)    //空树，访问完毕，高度减一
        return -1;
    int hei1 = height(btree->llink);    //左子树高度
    int hei2 = height(btree->rlink);    //右子树高度
    return (hei1 > hei2 ? hei1 : hei2) + 1;    //取较大子树高度
}

int countNode(BinTree btree)    //计算叶子结点数
{
    if (btree == NULL)   //空树，访问完毕，结点数不变
        return 0;
    if (btree->llink == NULL && btree->rlink == NULL)    //叶子结点，结点数加1
        return 1;
    return (countNode(btree->llink) + countNode(btree->rlink));    //返回左右子树叶子结点之和
}

int construct(char * pre, char * mid, int n, PBinTree btree)    //由先根序列和对称序列构造二叉树，参数用PBinTree为了进行传址调用
{
    int i = 0;    //i为先根序列中某结点在中根序列中下标
    int sig1, sig2;    //sig1，sig2为左右子树构造成功与否标志
    if (n == 0)     //序列访问完毕，子树构建成功
    {
        *btree = NULL;
        return TRUE;
    }
    while (mid[i] != pre[0] && i < n)    //寻找中根序列下标值
        i++;
    if (i == n)    //找遍中根序列没有发现，返回失败标志
    {
        *btree = NULL;
        return FALSE;
    }
    *btree = createEmptyBinTree();
    (*btree)->info = pre[0];
    sig1 = construct(pre + 1, mid, i, &(*btree)->llink);    //以mid[i]为中心，左边序列压入左子树
    sig2 = construct(pre + i + 1, mid + i + 1, n - i - 1, &(*btree)->rlink);    //以mid[i]为中心，右边序列压入右子树
    if (sig1 && sig2)    //左右子树都构建成功，返回成功标志
        return TRUE;
    else return FALSE;
}

int main()
{
    char pre[9] = {'A', 'B', 'D', 'C', 'E', 'G', 'F', 'H', 'I'}, mid[9] = {'D', 'B', 'A', 'E', 'G', 'C', 'H', 'F', 'I'};
    BinTree btree;
    if (construct(pre, mid, 9, &btree))
    {
        cout<<"Bintree constructed successfully."<<endl;
        cout<<"The height of the bintree is "<<height(btree)<<"."<<endl;    //求高度
        cout<<"The number of its leaf nodes is "<<countNode(btree)<<"."<<endl;    //求叶子结点个数
        cout<<"The postorder list of the bintree is:";    //求后根周游序列
        postOrder(btree);
        cout<<'.';
    }
    else
        cout<<"Data given went wrong.";
    return 0;
}

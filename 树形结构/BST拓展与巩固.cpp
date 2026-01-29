/*
| Day1 | BST统计节点数                     | 手写：递归统计BST的总节点数/叶子节点数                                   | 统计结果正确，理解递归统计的逻辑                                         |
| Day2 | BST找前驱/后继                    | 手写：找指定节点的中序前驱/后继节点                                      | 前驱/后继节点查找正确，理解BST的中序特性                                 |
| Day3 | BST求最值                        | 手写：递归/迭代找BST的最大值/最小值                                      | 两种方式结果一致，理解“左小右大”的特性                                   |
| Day4 | BST对比复习                      | 对比BST和普通二叉树的区别，整理核心差异                                  | 能口述3个核心差异（如中序升序、插入规则）|
| Day5 | BST综合练习                      | 手写：BST的拷贝（复制一棵BST）| 拷贝后的BST和原树结构、值一致，无内存泄漏                               |
| Day6-7 | BST复盘 | 闭卷手写BST所有核心代码，梳理常见错误和注意事项 | 代码一次性写对，能口述“删除双孩子节点”的完整逻辑 |
*/
/*
    Time  : 2026/1/29
    Author: await-2313
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct BSTNode{
    int data;
    struct BSTNode* lchild;
    struct BSTNode* rchild;
}BSTNode,*BSTree;
BSTNode* create_bstnode(int key);
int insert_bst(BSTree* root,int key);
void in_order_traverse(BSTree root);
BSTNode* search_bst(BSTree root,int key);

//功能
int countBstNodeRecursive(BSTree root);//BST统计节点数
int countBstLeafNodesRecursive(BSTree root);//BST统计叶子结点数
int countBstTwoDegreeNodes(BSTree root);//BST统计二度节点个数
// BSTNode* find_min_bst(BSTree root);//BST中序后继
// BSTNode* find_max_bst(BSTree root);//BST中序前驱


//测试
void test01(BSTree root);//测试统计节点功能
void test02(BSTree root);//测试统计叶子结点功能
// void test03(BSTree root);//找出BST中序遍历的前驱和后继
int main(){

    int arr[] = {5,4,1,3,88,7,6,12,9,13};
    BSTree root = NULL;
    for(int i=0,len = sizeof(arr)/sizeof(int);i<len;i++)
        insert_bst(&root,arr[i]);
    
    test01(root);
    test02(root);
    // test03(root);
    return 0;
}

BSTNode* create_bstnode(int key)
{
    BSTNode* curr = (BSTNode*)malloc(sizeof(BSTNode));
    curr->data = key;
    curr->lchild = NULL,curr->rchild = NULL;
    return curr;
}
int insert_bst(BSTree*root,int key){
    if(!*root){
        *root = create_bstnode(key);
        return 1;
    }else if(key<(*root)->data) return insert_bst(&((*root)->lchild),key);
    else if(key>(*root)->data) return insert_bst(&((*root)->rchild),key);
    else return 0;
}
void in_order_traverse(BSTree root)
{
    if(!root)return;
    in_order_traverse(root->lchild);
    printf("%d ",root->data);
    in_order_traverse(root->rchild);
}
BSTNode* search_bst(BSTree root,int key)
{
    if(!root)return NULL;
    if(key == root->data)return root;
    else if(key>root->data)return search_bst(root->rchild,key);
    else if(key<root->data)return search_bst(root->lchild,key);
}

int countBstNodeRecursive(BSTree root)//BST统计节点数
{
    int count_lchild = 0,count_rchild = 0;
    if(!root) return 0;
    if(root->lchild) count_lchild = countBstNodeRecursive(root->lchild);
    if(root->rchild) count_rchild = countBstNodeRecursive(root->rchild);
    return count_lchild +  count_rchild + 1;//加上自己
}


int countBstLeafNodesRecursive(BSTree root)//BST统计叶子结点数
{
    if(!root) return 0;
    int count_lchild_leafNodes = 0,count_rchild_leafNodes = 0;
    if(root->lchild) count_lchild_leafNodes = countBstLeafNodesRecursive(root->lchild);
    if(root->rchild) count_rchild_leafNodes = countBstLeafNodesRecursive(root->rchild);
    if((!root->lchild)&&(!root->rchild)) return 1;//本身是叶子结点
    else return count_lchild_leafNodes+count_rchild_leafNodes;
}


int countBstTwoDegreeNodes(BSTree root)//BST统计二度节点个数
{
    // d2  +  1 = d0  度数和+1 = 节点数之和
    return countBstLeafNodesRecursive(root)+1;
}

BSTNode* find_min_bst(BSTree root)//BST中序后继
{
    if(!root)return NULL;
    while(root->lchild){
        root =root->lchild;
    }
    return root;
}


BSTNode* find_max_bst(BSTree root)//BST中序前驱
{
    if(!root)return NULL;
    while(root->rchild){
        root = root->rchild;
    }
    return root;
}

void test01(BSTree root){//测试统计节点功能
    
    int n = countBstNodeRecursive(root);
    printf("the total number of Nodes is : %d \n",n);
}

void test02(BSTree root){    //测试统计叶子结点功能    
    int n = countBstLeafNodesRecursive(root);
    int d = countBstTwoDegreeNodes(root);
    printf("the total number of leaf Nodes is : %d \n",n);
    printf("the total number of Nodes with two children is : %d \n",d);
}

/* void test03(BSTree root){//测试找BST的中序前驱和后继
    puts("in_order_traverse is :\n");
    in_order_traverse(root);
    puts("\n");

    puts("please input the number: ");
    int  n ;
    scanf("%d",&n);
    BSTNode* curr = search_bst(root,n);
    printf("the front Nodes is : %d \n",find_max_bst(curr->lchild)->data);
    printf("the rear  Nodes is : %d \n",find_min_bst(curr->rchild)->data);
} */
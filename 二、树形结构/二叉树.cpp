/*
### 1. 二叉树
| 序号 | 核心操作                | 功能说明                     |
|------|-------------------------|------------------------------|
| 1    | 先序创建二叉树          | 按先序序列（-1表空节点）创建 |
| 2    | 前序遍历                | 根→左→右递归遍历             |
| 3    | 中序遍历                | 左→根→右递归遍历             |
| 4    | 后序遍历                | 左→右→根递归遍历             |
| 5    | 层序遍历                | 用队列按层输出节点值         |
| 6    | 求树高                  | 递归计算左右子树最大高度+1   |
| 7    | 销毁二叉树              | 后序遍历释放所有节点内存     |
*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 100
typedef struct BTNode{
    int data;
    struct BTNode* lchild;
    struct BTNode* rchild;
}BTNode,*Bitree;

//前序遍历创建二叉树
Bitree create_btree(int arr[],int*idx){     //传索引idx的指针，便于递归
    int val = arr[(*idx)++];
    if( val== -1) return NULL;
    Bitree node = (Bitree)malloc(sizeof(BTNode));
    node->data = val;                                           //根
    node->lchild = create_btree(arr,idx);                       //左
    node->rchild = create_btree(arr,idx);                       //右
    return node;                                                //返回根
}

void pre_order(Bitree root){
    if(!root) return;
    printf("%d ",root->data);
    pre_order(root->lchild);
    pre_order(root->rchild);
}

void in_order(Bitree root){
    if(!root) return;
    in_order(root->lchild);
    printf("%d ",root->data);
    in_order(root->rchild);
}

void post_order(Bitree root){
    if(!root) return;
    post_order(root->lchild);
    post_order(root->rchild);
    printf("%d ",root->data);
}

void level_order(Bitree root){
    if(!root) return;
    BTNode* queue[MAX_SIZE];
    int front = 0,rear = 0;
    queue[rear++] = root;
    while(front!=rear){
        BTNode* p = queue[front++];
        printf("%d ",p->data);
        if(p->lchild!=NULL)queue[rear++] =p->lchild;
        if(p->rchild!=NULL)queue[rear++] = p->rchild;
    }
}

int get_bt_height(Bitree root){
    if(!root) return 0;
    int left_h = get_bt_height(root->lchild);
    int right_h = get_bt_height(root->rchild);
    return (left_h >right_h? left_h:right_h)+1;
}

/* void destroy_btree(Bitree root){
    if(!root) return;
    destroy_btree(root->lchild);
    destroy_btree(root->rchild);
    free(root);
} */
//上述销毁函数逻辑正确，但不够规范，存在风险,需要将释放后的指针置零，需要用到二级指针
void destroy_bitree(Bitree*root){
    if(!*root) return ;
    destroy_bitree(&((*root)->lchild));
    destroy_bitree(&((*root)->rchild));
    free(*root);
    *root = NULL;
}
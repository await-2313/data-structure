/*
        Time    2026/1/30
        Author  await-2313
*/
//BST的复制
#include<stdio.h>
#include<stdlib.h>
typedef struct BSTNode{
    int data;
    struct BSTNode*lchild;
    struct BSTNode*rchild;
}BSTNode,*BSTree;
BSTNode* create_bstnode(int key);  //创建BST节点
int insert_bst(BSTree* root,int key);//插入BST节点
void in_order_traverse(BSTree root);//中序遍历
int copy_bst_in_order(BSTree root,BSTree* new_root);
BSTree bst_copy(BSTree root);
int destory_bst_post_order(BSTree root);

int main(){
    int arr[] = {5,4,1,3,8,7,6,12,9,13};
    BSTree root = NULL;
    for(int i=0,len=sizeof(arr)/sizeof(int);i<len;i++)
        insert_bst(&root,arr[i]);

    in_order_traverse(root);
    puts("\n");


    //两种复制函数
    BSTree new_root = NULL;
    copy_bst_in_order(root,&new_root);
    in_order_traverse(new_root);
    puts("\n");

    BSTree root_2 = NULL;
    root_2 = bst_copy(root);
    in_order_traverse(root_2);
    puts("\n");

    //后序遍历删除树
    int status_1 = destory_bst_post_order(new_root);
    int status_2 = destory_bst_post_order(root_2);
    if(status_1&&status_2){
        puts("destory succcess!");
    }else puts("failed destory");
}
BSTNode* create_bstnode(int key){
    BSTNode* new_bstnode = (BSTNode*)malloc(sizeof(BSTNode));
    if(!new_bstnode) return NULL;
    new_bstnode->data = key;
    new_bstnode->lchild = NULL;
    new_bstnode->rchild = NULL;
    return new_bstnode;
}

int insert_bst(BSTree* root,int key){//若根为空，则新节点替换根节点
    if(!*root){
        BSTNode* curr = create_bstnode(key);
        *root = curr;
        return 1;
    }else if(key==(*root)->data)  return 0;
    else if(key>(*root)->data) return insert_bst(&((*root)->rchild),key);
    else return insert_bst(&((*root)->lchild),key);
}

void in_order_traverse(BSTree root){
    if(!root) return;
    in_order_traverse(root->lchild);
    printf("%d ",root->data);
    in_order_traverse(root->rchild);
}

int copy_bst_in_order(BSTree root,BSTree* new_root){
    if(!root) return 0;
    
    BSTree curr = create_bstnode(root->data);
    *new_root = curr;
    
    copy_bst_in_order(root->lchild,&((*new_root)->lchild));
    copy_bst_in_order(root->rchild,&((*new_root)->rchild));
    return 1;
}

BSTree bst_copy(BSTree root){
    if(!root) return    NULL;
    BSTNode* curr = create_bstnode (root->data);
    curr->lchild = bst_copy(root->lchild);
    curr->rchild = bst_copy(root->rchild);
    return curr;
}

int destory_bst_post_order(BSTree root){
    if(!root) return 0;
    destory_bst_post_order(root->lchild);
    destory_bst_post_order(root->rchild);
    free(root);
    root = NULL;
    return 1;
}


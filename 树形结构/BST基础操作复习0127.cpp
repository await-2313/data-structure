//写BST插入、查找、删除、释放操作
//2026/01/27
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
BSTNode* search_bst(BSTree root, int key);//查找节点
int delete_bstnode(BSTree root,int key);//删除节点

void test01();//验证创建、插入

int main(){

    //test01();
    return 0;
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

void test01()
{
    int arr[]= {1,2,5,3,7,4,6,9};
    BSTree root = NULL;
    int i=0,num = sizeof(arr)/sizeof(int);
    for(;i<num;i++)
        insert_bst(&root,arr[i]);
    in_order_traverse(root);
}

BSTNode* search_bst(BSTree root,int key){
    if(!root) return NULL;
    if(key== root->data) return root;
    if(key<root->data) return search_bst(root->lchild,key);
    else return search_bst(root->rchild,key);
}

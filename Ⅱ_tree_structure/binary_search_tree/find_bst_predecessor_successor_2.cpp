//中序遍历暴力求解前驱后继
/*
        Time    2026/1/29
        Author  await-2313
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct BSTNode{
    int data;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;


BSTNode* create_bstnode(int key);  //创建BST节点
int insert_bst(BSTree* root,int key);//插入BST节点
void in_order_traverse(BSTree root);//中序遍历
BSTNode* search_bst(BSTree root, int key);//查找节点
void in_order(BSTree root,int key,BSTree* predecessor,BSTree* successor);//中序遍历递归
int find_bst_predecessor_successor();//封装函数

int main(){

    find_bst_predecessor_successor();
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

BSTNode* search_bst(BSTree root,int key){
    if(!root) return NULL;
    if(key== root->data) return root;
    if(key<root->data) return search_bst(root->lchild,key);
    else return search_bst(root->rchild,key);
}

void in_order(BSTree root,int key,BSTree* predecessor,BSTree* successor)//中序遍历递归
{
    if(!root) return;

    in_order(root->lchild,key,predecessor,successor);

    if(*successor) return;//后继已经得到，退出
    if(root->data<key){
        *predecessor = root;
    }else if(root->data>key){
        *successor = root;
    }

    in_order(root->rchild,key,predecessor,successor);

}
int find_bst_predecessor_successor(){
    
    int arr[]={5,4,1,3,8,7,6,12,9,13};
    BSTree root = NULL;
    for(int i=0,len = sizeof(arr)/sizeof(int);i<len;i++)
        insert_bst(&root,arr[i]);
    puts("in-order-traverse is : ");
    in_order_traverse(root);
    puts("\n");

    puts("plese test,input the number : ");
    int n;
    while(scanf("%d",&n))
    {
        BSTNode* status = search_bst(root,n);
        if(!status){
            puts("inputs error!");
            return 0;
        }
        BSTree predecessor = NULL,successor = NULL;
        in_order(root,n,&predecessor,&successor);
        if(predecessor) printf("%d predecessor is %d \n",n,predecessor->data);
        else puts("Not exit predecessor");
        if(successor)printf("%d successor is : %d \n",n,successor->data);
        else puts("Not exit successor");
    }
    return 1;
}
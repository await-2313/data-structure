//写BST插入、查找、删除操作
//      2026/1/19
#include<stdio.h>
#include<stdlib.h>
typedef struct BSTNode{
    int data;
    struct BSTNode* lchild;
    struct BSTNode* rchild;
}BSTNode,*BSTree;

/* BSTNode*create_bstnode(int key){
    BSTNode* root = (BSTNode*)malloc(sizeof(BSTNode));
    if(!root) return NULL;
    return root;
}
    忘记初始化 */
BSTNode*create_bstnode(int key){
    BSTNode* root = (BSTNode*)malloc(sizeof(BSTNode));
    if(!root) return NULL;
    root->data =key;
    root->lchild = NULL,root->rchild=NULL;
    return root;
}

/* int insert_bst(BSTree* root,int key){
    if(!*root){
        BSTNode* new_bstnode = create_bstnode(key);
        *root = new_bstnode;
        return 1;
    }else if((*root)->data == key) return 0;
    else if(key>(*root)->data) insert_bst(&((*root)->rchild),key);
    else insert_bst(&((*root)->lchild),key);
}
    后两种情况没有返回值 */

int insert_bst(BSTree* root,int key){
    if(!*root){
        BSTNode* new_bstnode = create_bstnode(key);
        *root = new_bstnode;
        return 1;
    }else if((*root)->data == key) return 0;
    else if(key>(*root)->data) return insert_bst(&((*root)->rchild),key);
    else return insert_bst(&((*root)->lchild),key);
}

//查找
BSTNode* search_bst(BSTree root,int key){
    if(!root||root->data == key) return root; //空节点或找到
    if(key>root->data) return search_bst(root->rchild,key);
    else return search_bst(root->lchild,key);
}

BSTNode*find_min_bst(BSTree root){
    if(!root)return NULL;
    while(root->lchild){
        root = root->lchild;
    }
    return root;
}

//删除操作
/* int delete_bst(BSTree*root,int key){
    
    
一、if(!root) return 0;//空节点
二、if(key<(*root)->data)return delete_bst(root,key);
二、if(key>(*root)->data)return delete_bst(root,key);
    
    //找到Key节点
    else{
        BSTree temp = *root;
        //右子树为空
        if(!(*root)->rchild){ 
            *root = (*root)->lchild;
三、    }else if(!(*root)->rchild){//左树为空，右树不空
            *root = (*root)->lchild;
        }else{
            //左右树都不空
            BSTNode*  min_bstnode = find_min_bst((*root)->rchild);
            (*root)->data = min_bstnode->data;
            delete_bst(&((*root)->rchild),min_bstnode->data);
        }
四、    free(temp);
        return 1;
    一、指针类型写错
    二、函数参数传错
    三、与上一句重复
    四、只有单颗树需要free，双树在狄贵忠释放内存    
        }
} */

int delete_bst(BSTree*root,int key){
    if(!*root) return 0;//空节点
    if(key<(*root)->data)return delete_bst(&((*root)->lchild),key);
    if(key>(*root)->data)return delete_bst(&((*root)->rchild),key);
    
    //找到Key节点
    else{
        BSTree temp = *root;
        //右子树为空
        if(!(*root)->rchild){ 
            *root = (*root)->lchild;
            free(temp);
        }else if(!(*root)->lchild){//左树为空，右树不空
            *root = (*root)->rchild;
            free(temp);
        }else{
            //左右树都不空
            BSTNode*  min_bstnode = find_min_bst((*root)->rchild);
            (*root)->data = min_bstnode->data;
            delete_bst(&((*root)->rchild),min_bstnode->data);
        }
        
        return 1;
    }
}
//找到指定节点的中序前驱和中序后继
//第一种方法，parent指针

/*
        Time    2026/1/29
        Author  await-2313
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct BSTNode{
    int data;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
    struct BSTNode *parent;
}BSTNode,*BSTree;
BSTNode* create_bstnode(int key);
int insert_bst(BSTree *root,int key);//插入，维护父指针
void in_order_traverse(BSTree root);
void puts_inorder_traverse(BSTree root);
BSTNode*search_bstnode(BSTree root,int key);
BSTNode* find_inorder_predecessor(BSTree root,int key);//查找key值的中序前驱predeessor
BSTNode* find_inorder_successor(BSTree root,int key);//查找key值的中序后继successor

//测试
void test01(BSTree *root,int arr[],int len){
    for(int i=0;i<len;i++){
        insert_bst(root,arr[i]);
    }
    puts_inorder_traverse(*root);

    puts("please input one number to be searched : ");
    int n;
    while(scanf("%d",&n)){
        BSTNode *curr = search_bstnode(*root,n);
        if(!curr){
            puts("find error!\n");
            break;
        }else{
            puts("find succeed!\n");
            if(!curr->parent) printf("%d hasn't parent \n",curr->data);
            else printf("%d parent  is : %d \n",curr->data,curr->parent->data);
            puts("please input one number to be searched : ");
        } 
    }
}
void test02(BSTree root)
{
    //测试查找前驱功能
    puts("please input one number to be finded_inorder_predecessor  : ");
    int n;
    while(scanf("%d",&n)){
        BSTNode* curr = find_inorder_predecessor(root,n);
        if(curr){
            printf("%d find_inorder_predecessor is : %d \n",n,curr->data);
        }else return;
    }
}
void test03(BSTree root)
{
    //测试查找后继功能
    puts("please input one number to be finded_inorder_successor  : ");
    int n;
    while(scanf("%d",&n)){
        BSTNode* curr = find_inorder_successor(root,n);
        if(curr){
            printf("%d find_inorder_successor is : %d \n",n,curr->data);
        }else return;
    }
}
int main(){
    int arr[] = {5,4,1,3,8,7,6,12,9,13};
    BSTree root = NULL;

    test01(&root,arr,sizeof(arr)/sizeof(int));

    test02(root);//测试查找前驱功能

    test03(root);    //测试查找后继功能

    return 0;
}
BSTNode* create_bstnode(int key)
{
    BSTNode* curr = (BSTNode*)malloc(sizeof(BSTNode));
    if(!curr){
        printf("create_bstnode error\n");
        return NULL;
    }

    curr->data = key;
    curr->lchild = NULL, curr->rchild = NULL, curr->parent = NULL;
    return curr;
}

void in_order_traverse(BSTree root){
    if(!root)return;
    in_order_traverse(root->lchild);
    printf("%d ",root->data);
    in_order_traverse(root->rchild);
}
void puts_inorder_traverse(BSTree root){
    puts("In Order Traverse is : \n");
    in_order_traverse(root);
    puts("\n");
}
BSTNode*search_bstnode(BSTree root,int key){
    if(!root) return NULL;
    if(key == root->data) return root;
    if(key<root->data) return search_bstnode(root->lchild,key);
    else return search_bstnode(root->rchild,key);
}

int insert_bst(BSTree *root,int key){
    BSTNode* curr = create_bstnode(key);
    if(!*root){
        *root = curr;
        return 1;
    }
    BSTree temp =*root;
    BSTNode* parent = NULL;
    
    while(temp){
        parent = temp;
        if(key<temp->data){
            temp = temp->lchild;
        }else if(key>temp->data){
            temp = temp->rchild;
        }else {  //key已经插入
            printf("insert_bst error!\n");
            free(curr);
            return 0;
        }
    }
    
    curr->parent = parent;
    if(key < parent->data){
        parent->lchild = curr; // 关键字更小，挂为左孩子
    }else{
        parent->rchild = curr; // 关键字更大，挂为右孩子
    }
    return 1;
}

BSTNode* find_inorder_predecessor(BSTree root,int key)//查找key值的中序前驱
{
    BSTNode* curr = search_bstnode(root,key);
    if(!curr){
        puts("failed error !");     //不存在key节点。树空或key不存在
        return NULL;
    }
    if(curr->lchild){               //有左子树，找左子树最大值
        BSTNode* temp = curr->lchild;
        while(temp->rchild){
            temp = temp->rchild;
        }
        return temp;
    }else{                          //无左子树
        //找第一个以自己为右子树的父节点
        BSTNode*low = curr;
        BSTNode* high = curr->parent;
        while(high){
            if(high->rchild == low){
                return high;
            }else{
                low = high;
                high = high->parent;
            }
        }
        puts("failed find error");
        return NULL;
    }
}

BSTNode* find_inorder_successor(BSTree root,int key)//查找key值的中序后继successor
{
    BSTNode* curr = search_bstnode(root,key);
    if(!curr){
        puts("failed error !");         //不存在key节点
        return NULL;
    }
    if(curr->rchild){
        //存在右子树，找右子树的最小值
        BSTNode* temp = curr->rchild;
        while(temp->lchild){
            temp = temp->lchild;
        }
        return temp;
    }else{
        //不存在右子树，找第一个以自己为左子树的f父节点
        BSTNode* low = curr;
        BSTNode* high = curr->parent;
        while(high){
            if(high->lchild == low){
                return high;
            }else{
                low = high;
                high = high->parent;
            }
        }
        puts("failed find error");
        return NULL;
    }
}
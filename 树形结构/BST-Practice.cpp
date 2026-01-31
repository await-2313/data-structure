/*
        Time:   2026/1/31
        Author: await-2313
        闭卷手写BST所有核心代码
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct BSTNode{
    int data;
    struct BSTNode *lchild,*rchild;
}BSTNode,*BSTree;
typedef struct Node{
    int data;
    struct Node*lchild,*rchild;
    struct Node*parent;
}Node,*Tree;
BSTNode* create_bstnode(int key);
int insert_bst(BSTree* root,int key);
void in_order_traverse(BSTree root);
void puts_in_order_bst(BSTree root);
void level_order_traverse(BSTree root);
BSTree find_min_bstnode(BSTree root);
BSTree find_max_bstnode(BSTree root);
BSTNode* search_bstnode(BSTree root,int key);
int delete_bstnode(BSTree*root,int key);
int destory_bst(BSTree *root);
void init_bst(BSTree *root,int arr[],int len){
    for(int i=0;i<len;i++){
        insert_bst(root,arr[i]);
    }
}
void test01(BSTree root){
    puts("Original BSTree is : ");
    puts_in_order_bst(root);
    level_order_traverse(root);
    puts("the min-bstnode and max_bstnode is : ");
    printf("%d %d\n",find_min_bstnode(root)->data,find_max_bstnode(root)->data);

    puts("test deletion function,plese inputs the number to delete :");
    int n;
    while(scanf("%d",&n)){
        BSTNode* curr = search_bstnode(root,n);
        if(!curr){
            printf("failed search the number which is %d \nEnding in deletion...\n",n);
            break;
        }
        int status = delete_bstnode(&root,curr->data);
        if(status) {
            puts("Succeeding in deletion ,please input the next number : ");
            puts_in_order_bst(root);
            level_order_traverse(root);
        }else{
            puts("failed deletion,status error ");
            break;
        }
    }

    puts("test destory funtion");
    if(destory_bst(&root)){
        if(!root){
            puts("Succeeding in destory ");
        }else puts("error ! root not equal to NULL");
    }else puts("error ! failed destory");

}
void find_predecessorAndsuccessor(BSTree root,BSTree*pre,BSTree*suc,int key);
void test02(BSTree root){
    puts("test find_predecessorAndsuccessor ");
    puts("Original BSTree is :");
    puts_in_order_bst(root);
    puts("please inputs a number : ");

    int n;
    while(scanf("%d",&n)){
        BSTNode* curr = search_bstnode(root,n);
        if(!curr){
            puts("inputs error ");
            break;
        }
        else{
            BSTree pre = NULL,suc = NULL;
            find_predecessorAndsuccessor(root,&pre,&suc,n);
            if(pre)   
                printf("%d----",pre->data);
            printf("%d",n);
            if(suc)
                printf("----%d\n",suc->data);
            else printf("\n");
            puts("please continue : \n");
        }
    }
}
Node* create_node(int key);
int insert_bst(Tree *root,int key);
Node* search_bstnode(Tree root,int key);
Node* find_inorder_predecessor(Tree root,int key);//查找key值的中序前驱
Node* find_inorder_successor(Tree root,int key);//查找key值的中序后继successor
int copy_bst_in_order(BSTree root,BSTree* new_root);
BSTree bst_copy(BSTree root);
int destory_bst_post_order(BSTree* root);
void test03(BSTree root){
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
    int status_1 = destory_bst_post_order(&new_root);
    int status_2 = destory_bst_post_order(&root_2);
    if(status_1&&status_2){
        puts("destory succcess!");
    }else puts("failed destory");
}


int main(){
    int arr[] = {5,4,1,3,8,7,6,12,9,13};
    BSTree root =NULL;
    init_bst(&root,arr,sizeof(arr)/sizeof(int));

    //test01(root);
    //test02(root);
    test03(root);
    return 0;
}

BSTNode* create_bstnode(int key){
    BSTNode* curr = (BSTNode*)malloc(sizeof(BSTNode));
    if(!curr) return NULL;

    curr->data = key;
    curr->lchild = NULL;
    curr->rchild = NULL;
    return curr;
}
int insert_bst(BSTree* root,int key)
{
    BSTNode *temp = create_bstnode(key);
    if(!temp){
        puts("insert error ! space contribution failed ! ");
        return 0;
    }
    if(!*root){
        *root = temp;
        return 1;
    }else if((*root)->data == key){
        puts("insert error ! key has exited !");
        return 0;
    }
    else if( key<(*root)->data){
        return insert_bst(&((*root)->lchild),key);
    }else{
        return insert_bst(&((*root)->rchild),key);
    }
}
void in_order_traverse(BSTree root){
    if(!root) return ;
    in_order_traverse(root->lchild);
    printf("%d ",root->data);
    in_order_traverse(root->rchild);
}
void puts_in_order_bst(BSTree root){
    in_order_traverse(root);
    printf("\n");
}
void level_order_traverse(BSTree root){
    if(!root) {
        puts("Not a BSTree error ! ");
        return;
    }
    BSTree queue[50];
    int front=0,rear=0;
    
    queue[rear++] = root;
    int times = rear-front;
    while(front<rear){
        BSTree temp = queue[front++];
        printf("%d ",temp->data);
        if(temp->lchild) queue[rear++] = temp->lchild;
        if(temp->rchild) queue[rear++] = temp->rchild;
        times--;
        if(!times){
            puts("\n");
            puts("-----------");
            times = rear-front;
        }
    }
}
BSTree find_min_bstnode(BSTree root)
{
    if(!root) return NULL;
    while(root->lchild){
        root = root->lchild;
    }
    return root;
}
BSTree find_max_bstnode(BSTree root){
    if(!root) return NULL;
    while(root->rchild){
        root = root->rchild;
    }
    return root;
}
BSTNode* search_bstnode(BSTree root,int key)
{
    if(!root) return NULL;
    if(key == root->data)return root;
    if(key<root->data)return search_bstnode(root->lchild,key);
    else return search_bstnode(root->rchild,key);
}
int delete_bstnode(BSTree*root,int key)
{
    if(!*root){
        puts("deletion failed error ! ");
        return 0;
    } 
    if(key<(*root)->data)return delete_bstnode(&((*root)->lchild),key);
    else if(key>(*root)->data)return delete_bstnode(&((*root)->rchild),key);
    else{
        //key == (*root)
        BSTree temp = *root;
        if(!((*root)->rchild)){
            *root = (*root)->lchild;
            
        }else if(!((*root)->lchild)){
            *root = (*root)->rchild;
            
        }else{
            BSTNode* min_node = find_min_bstnode((*root)->rchild);
            (*root)->data = min_node->data;
            return delete_bstnode(&((*root)->rchild),min_node->data);
        }
        free(temp);
        temp = NULL;
        return 1;
    }
}
int destory_bst(BSTree* root){
    if(!*root) return 0;
    destory_bst(&((*root)->lchild));
    destory_bst(&((*root)->rchild));
    free(*root);
    *root =NULL;
    return 1;
}
void find_predecessorAndsuccessor(BSTree root,BSTree*pre,BSTree*suc,int key){
    //默认key存在
    if(!root) return;
    find_predecessorAndsuccessor(root->lchild,pre,suc,key);
    if(*suc) return;
    if(root->data<key){
        *pre = root;
    }else if(root->data>key){
        *suc = root;
    }
    find_predecessorAndsuccessor(root->rchild,pre,suc,key);
}
Node* create_node(int key){
    Node* curr = (Node*)malloc(sizeof(Node));
    if(!curr) return NULL;
    curr->data = key;
    curr->lchild = NULL;
    curr->parent=NULL;
    curr->rchild = NULL;
    return curr;
}
int insert_bst(Tree *root,int key){
    Node* curr = create_node(key);
    if(!*root){
        *root = curr;
        return 1;
    }
    Tree temp =*root;
    Node* parent = NULL;
    
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
Node* search_bstnode(Tree root,int key)
{
    if(!root) return NULL;
    if(key == root->data)return root;
    if(key<root->data)return search_bstnode(root->lchild,key);
    else return search_bstnode(root->rchild,key);
}
Node* find_inorder_predecessor(Tree root,int key)//查找key值的中序前驱
{
    Node* curr = search_bstnode(root,key);
    if(!curr){
        puts("failed error !");     //不存在key节点。树空或key不存在
        return NULL;
    }
    if(curr->lchild){               //有左子树，找左子树最大值
        Node* temp = curr->lchild;
        while(temp->rchild){
            temp = temp->rchild;
        }
        return temp;
    }else{                          //无左子树
        //找第一个以自己为右子树的父节点
        Node*low = curr;
        Node* high = curr->parent;
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
Node* find_inorder_successor(Tree root,int key)//查找key值的中序后继successor
{
    Node* curr = search_bstnode(root,key);
    if(!curr){
        puts("failed error !");         //不存在key节点
        return NULL;
    }
    if(curr->rchild){
        //存在右子树，找右子树的最小值
        Node* temp = curr->rchild;
        while(temp->lchild){
            temp = temp->lchild;
        }
        return temp;
    }else{
        //不存在右子树，找第一个以自己为左子树的f父节点
        Node* low = curr;
        Node* high = curr->parent;
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
int destory_bst_post_order(BSTree *root){
    if(!*root) return 0;
    destory_bst_post_order(&((*root)->lchild));
    destory_bst_post_order(&((*root)->rchild));
    free(*root);
    *root = NULL;
    return 1;
}

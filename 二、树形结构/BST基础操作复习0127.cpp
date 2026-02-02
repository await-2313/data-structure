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
BSTNode* find_min_bst(BSTree root);//查找最小值
int delete_bstnode(BSTree root,int key);//删除节点
void level_order_traverse(BSTree root);//层序遍历

void test01();//验证创建、插入
void test02();//验证查找、删除


int main(){

    //test01();
    test02();
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


BSTNode* find_min_bst(BSTree root)//查找最小值节点
{
    if(!root) return NULL;
    while(root->lchild){
        root = root->lchild;
    }
    return root;
}

int delete_bstnode(BSTree* root,int key)//删除节点
{
    if(!*root) return 0;
    if(key>(*root)->data)       return delete_bstnode(&((*root)->rchild),key);
    else if(key<(*root)->data)  return delete_bstnode(&((*root)->lchild),key);
    else {
        //找到key节点
        BSTree temp = *root;
        if(!(*root)->rchild){
            (*root) = (*root)->lchild;
            free(temp);
        }else if(!(*root)->lchild){
            (*root) = (*root)->rchild;
            free(temp);
        }else{
            BSTNode* min_bstnode = find_min_bst((*root)->rchild);
            (*root)->data = min_bstnode->data;
            delete_bstnode(&((*root)->rchild),min_bstnode->data);       //从右子树删除min_bstnode,不能直接参数&min_bstnode
        }
        return 1;
    }
}


void level_order_traverse(BSTree root)//层序遍历
{
    if(!root){
        printf("NULL Tree !!\n");
        return;
    }
    BSTree queue[50];
    int front =0,rear =0;
    int count_level = 1;

    queue[rear++] = root;
    while(front<rear){
        BSTree curr = queue[front++];
        if(curr->lchild) queue[rear++] = curr->lchild;
        if(curr->rchild) queue[rear++] = curr->rchild;
        printf(" %d ",curr->data);
        count_level--;
        if(!count_level){
            puts("\n--------\n");
            count_level = rear-front;
        }
    }
}

void test02()
{
    int arr[]= {5,4,1,3,8,7,6,12,9,13};
    BSTree root = NULL;
    int i=0,num = sizeof(arr)/sizeof(int);
    for(;i<num;i++)
        insert_bst(&root,arr[i]);
    printf("In_order_traverse, BSTree show:\n");
    in_order_traverse(root);
    printf("\n");

    int n;
    printf("Welcome to test the function of 'searching' and 'deletion'\n\n");
    printf("we begin to search the number\nplese input the number:");
    while(scanf("%d",&n)){
        BSTNode* curr = NULL;
        curr = search_bst(root,n);
        if(!curr){
            printf("not search for %d\n\n",n);
            break;
        }else printf("You succeed in finding the number : %d !!\n",n);
    }

    puts("we begin to delete the number\n");
    puts("Before deletion,the BSTree is shown by level_order_traverse\n");
    level_order_traverse(root);

    puts("Plese input the deletion number : ");
    while(scanf("%d",&n)){
        int status = delete_bstnode(&root,n);
        if(!status){
            puts("Deletion error!\n");
            break;
        }else{
            printf("You succeeded in deleting the number : %d \n",n);
            puts("BSTree is shown by level_order_traverse\n");
            level_order_traverse(root);
            printf("In_order_traverse, BSTree show:\n");
            in_order_traverse(root);
            printf("\n");
            
            puts("Plese input the deletion number : ");
        }
    }

}

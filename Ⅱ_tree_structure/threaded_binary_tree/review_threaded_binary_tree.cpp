/*
        Time:   2026/2/15
        Author: awiat-2313
*/
//| Day5 | 线索二叉树复习 | 闭卷手写线索化+线索遍历核心代码 | 代码无语法错误，编译运行通过 |
//中序线索化递归函数+初始化线索二叉树   利用线索实现中序遍历（无需栈）    找线索二叉树指定节点的前驱/后继节点
//| Day7 | 线索二叉树综合练习 | 手写：先序线索化二叉树+先序线索遍历 | 先序线索化逻辑正确，遍历输出符合预期 |

#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 50
typedef struct ThreadNode{
    int val;
    struct ThreadNode*lchild,*rchild;
    int ltag,rtag;
}ThreadNode,*ThreadTree;

ThreadNode* createThreadNode(int key);
ThreadNode* createThreadTreePreOrderRecursive(int arr[],int len,int*idx);
void inOrderThreadingRecursive(ThreadNode* root,ThreadNode** pre);
void inOrderThreadTreeTraverse(ThreadTree root);
ThreadNode* findThreadPredecessorInOrder(ThreadNode * cur);
ThreadNode* findThreadSuccessorInOrder(ThreadNode* cur);
void preOrderThreadingRecursive(ThreadTree root,ThreadNode** pre);
void preOrderThreadTreeTraverse(ThreadTree root);

void inOrderTraverseCheck(ThreadTree root)
{
    if(!root)return;
    if(root->ltag == 0)inOrderTraverseCheck(root->lchild);
    printf("%d ",root->val);
    if(root->rtag == 0)inOrderTraverseCheck(root->rchild);
}
void levelOrderTraverseCheck(ThreadTree root)
{
    if(!root)return ;

    ThreadTree queue[MAX_SIZE];
    int front = 0,rear = 0;

    queue[rear++] = root;
    int times = rear - front;
    while(front != rear)
    {
        ThreadNode* cur = queue[front++];
        printf("%d ",cur->val);
        times --;
        if(!cur->ltag && cur->lchild) queue[rear++] = cur->lchild;
        if(!cur->rtag && cur->rchild) queue[rear++] = cur->rchild;
        if(times == 0)
        {
            putchar('\n');
            puts("------------");
            times = rear-front;
        }
    }
}
void preOrderTraverseCheck(ThreadTree root)
{
    if(!root) return ;
    printf("%d ",root->val);
    if(root->ltag == 0)preOrderTraverseCheck(root->lchild);
    if(root->rtag == 0)preOrderTraverseCheck(root->rchild);
}

ThreadTree test01()
{
    //测试 造树功能
    int arr[] = {5,4,1,-1,3,-1,-1,-1,8,7,6,-1,-1,-1,12,9,-1,-1,13,-1,-1};
    int len = sizeof(arr)/sizeof(int);
    int idx = 0;

    ThreadTree root = createThreadTreePreOrderRecursive(arr,len,&idx);
    inOrderTraverseCheck(root);
    putchar('\n');
    levelOrderTraverseCheck(root);
    return root;
}
void test02(ThreadTree root)
{
    //测试 线索化和中序线索化遍历功能
    if(! root) return;
    ThreadNode* pre = NULL;
    inOrderThreadingRecursive(root,&pre);
    inOrderTraverseCheck(root);
    putchar('\n');
    inOrderThreadTreeTraverse(root);
}
void test03(ThreadTree root)
{
    //测试查找前驱后继功能
    puts("predecessor -- current -- successor ");
    ThreadNode * cur = NULL;
    for( int i =0; i< 3 ;i++)
    {
        if( i == 0) cur = root;
        else if ( i ==1 ) cur = root ->rchild;
        else if( i == 2) cur = root ->lchild ->lchild;
        ThreadNode* predecessor = findThreadPredecessorInOrder(cur);
        ThreadNode* successor = findThreadSuccessorInOrder(cur);
        
        if(predecessor && successor) printf("   %d  -----   %d   -----   %d\n",predecessor->val,cur->val,successor->val);
        else if(predecessor) printf("   %d  -----   %d   -----   NULL\n",predecessor->val,cur->val);
        else if(successor)   printf("NULL  -----   %d   -----   %d\n",cur->val,successor->val);
    }
}
void test04()
{
    //测试前序线索化和前序线索化遍历

    int arr[] = {5,4,1,-1,3,-1,-1,-1,8,7,6,-1,-1,-1,12,9,-1,-1,13,-1,-1};
    int len = sizeof(arr)/sizeof(int);
    int idx = 0;
    ThreadNode* pre = NULL;
    ThreadTree root = createThreadTreePreOrderRecursive(arr,len,&idx);
    
    
    preOrderThreadingRecursive(root,&pre);

    preOrderTraverseCheck(root);
    putchar('\n');
    preOrderThreadTreeTraverse(root);
}
int main()
{
    ThreadTree root = test01();
    test02(root);
    test03(root);
    test04();
    return 0;
}
ThreadNode* createThreadNode(int key)
{
    ThreadNode* t = (ThreadNode*)malloc(sizeof(ThreadNode));
    if(!t){
        puts("error ! failed to createThreadNode ");
        return NULL;
    }

    t->val = key;
    t->lchild=NULL;
    t->rchild=NULL;
    t->ltag=0;
    t->rtag=0;
    return t;
}
ThreadNode* createThreadTreePreOrderRecursive(int arr[],int len,int*idx)
{
    if(*idx>=len||arr[*idx] == -1)
    {
        if(arr[*idx]==-1){
            (*idx)++;
        }
        return NULL;
    }
    ThreadNode* cur = createThreadNode(arr[*idx]);
    (*idx)++;
    cur->lchild = createThreadTreePreOrderRecursive(arr,len,idx);
    cur->rchild = createThreadTreePreOrderRecursive(arr,len,idx);
    return cur;
}
void inOrderThreadingRecursive(ThreadNode* root,ThreadNode** pre)
{
    if(!root) return;
    inOrderThreadingRecursive(root->lchild,pre);
    if(*pre && (*pre)->rchild == NULL)
    {
        (*pre)->rchild = root;
        (*pre)->rtag = 1;
    }
    if(!root->lchild)
    {
        root->lchild  = *pre;
        root->ltag = 1;
    }
    *pre = root;
    inOrderThreadingRecursive(root->rchild,pre);
}
void inOrderThreadTreeTraverse(ThreadTree root)
{
    if(!root) return ;

    //找到中序遍历第一个节点
    while(root && root->ltag ==0)
    {
        root = root->lchild;
    }
    while(root)
    {
        printf("%d ",root->val);
        if(root->rtag) root = root->rchild;
        else{
            //找到中序遍历下一个节点---右子树的最左子树
            root = root->rchild;
            while(root && root->ltag == 0)
            {
                root = root->lchild;
            }
        }
    }
    putchar('\n');
}
ThreadNode* findThreadPredecessorInOrder(ThreadNode * cur)
{
    if(!cur){
        puts("error ! failed to findThreadPredecessorInOrder ");
        return NULL;
    }
    if(cur->ltag)return cur->lchild;
    else{
        //找到左子树的最右节点
        cur = cur->lchild;
        while(cur && cur ->rtag == 0)
        {
            cur = cur->rchild;
        }
        return cur;
    }
}
ThreadNode* findThreadSuccessorInOrder(ThreadNode* cur)
{
    if(!cur)
    {
        puts("error ! failed to findThreadSuccessorInOrder ");
        return NULL;
    }

    if(cur->rtag)return cur->rchild;
    else{
        //找右子树的最左节点
        cur = cur->rchild;
        while(cur && cur->ltag == 0)
        {
            cur = cur->lchild;
        }
        return cur;
    }
}
void preOrderThreadingRecursive(ThreadTree root,ThreadNode** pre)
{
    //先序线索化二叉树
    if(!root) return;

    if(*pre && (*pre)->rchild == NULL)
    {
        (*pre)->rchild = root;
        (*pre)->rtag  =1;
    }
    if(!root->lchild)
    {
        root->lchild = *pre;
        root->ltag = 1;
    }
    *pre = root;
    if(root->ltag == 0)preOrderThreadingRecursive(root->lchild,pre);
    if(root->rtag == 0)preOrderThreadingRecursive(root->rchild,pre);
}
void preOrderThreadTreeTraverse(ThreadTree root)
{
    if(!root) return ;

    //前序遍历第一个节点为根节点
    while(root)
    {
        printf("%d ",root->val);

        //有直接后继
        if(root->rtag)  
        {
            root = root->rchild;
        }else{
            //先左
            if(root->ltag==0) root = root->lchild;
            else root = root->rchild; //    rtag=0
        }
    }
    putchar('\n');
}




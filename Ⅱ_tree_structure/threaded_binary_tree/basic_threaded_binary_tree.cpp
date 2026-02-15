/*
    Time:   2026/2/2
    Author: await-2313
*/
/*

| Day1 | 线索二叉树基础 | 学习线索化概念，手写：线索二叉树节点结构体（增加ltag/rtag、前驱/后继指针） | 能解释ltag/rtag含义（0-孩子，1-线索），结构体定义正确 |
| Day2 | 中序线索化二叉树 | 手写：中序线索化递归函数+初始化线索二叉树 | 线索化后，空指针正确指向前驱/后继，无内存泄漏 |
| Day3 | 中序线索二叉树遍历 | 手写：利用线索实现中序遍历（无需栈） | 遍历输出和普通中序一致，理解“线索替代栈”的核心逻辑 |
| Day4 | 线索二叉树反向查找 | 手写：找线索二叉树指定节点的前驱/后继节点 | 前驱/后继查找正确，无需遍历整棵树 |


*/
#include<stdio.h>
#include<stdlib.h>
#define MAX_SIZE 10
typedef struct ThreadNode
{
    int val;
    struct ThreadNode *lchild,*rchild;
    int ltag,rtag;//0--孩子  1--线索
}ThreadNode,*ThreadTree;

typedef struct TreeNode
{
    int val;
    struct TreeNode* lchild,*rchild;
}TreeNode,*Tree;


TreeNode* create_treenode(int key);
Tree create_tree_Recursive(int arr[],int*idx);
Tree construct_tree_preorder_iterative(int arr[],int *idx,int len);//迭代实现前序遍历构造二叉树

ThreadNode* create_node(int key);
ThreadTree construct_threadtree_preorder_iterative(int arr[],int *idx,int len);//迭代实现前序遍历造树
ThreadNode* inorder_threading_recursive(ThreadTree root,ThreadTree* pre);//中序递归线索化二叉树
void in_order_traverse_Thread(ThreadTree root);  //验证线索化是否正确，输出中序遍历结果
void in_order_traverse_check(ThreadTree root){
    if(!root) return;
    in_order_traverse_check(root->lchild);
    printf("%d ",root->val);
    in_order_traverse_check(root->rchild);
}
// ThreadNode* find_thread_predecessor(ThreadTree root ,int key);//找线索二叉树前驱节点
ThreadNode* find_thread_predecessor(ThreadTree p);//找线索二叉树中序前驱节点
ThreadNode* find_thread_successor(ThreadTree p);//找线索二叉树中序后继节点


ThreadTree test01()
{
    //验证二叉树线索化功能
    int arr[] = {5,4,1,-1,3,-1,-1,-1,8,7,6,-1,-1,-1,12,9,-1,-1,13,-1,-1};//前序遍历,-1代表空节点
    int idx = 0;
    ThreadTree pre =NULL;

    //造树
    ThreadTree root = construct_threadtree_preorder_iterative(arr,&idx,sizeof(arr)/sizeof(int));
    in_order_traverse_check(root);
    puts("\n");
    //线索化
    root = inorder_threading_recursive(root,&pre);
    //验证
    in_order_traverse_Thread(root);
    puts("\n");
    
    return root;
}
void test02(ThreadNode* root)
{
    ThreadNode* predecessor = find_thread_predecessor(root);
    ThreadNode* successor = find_thread_successor(root);
    
    //验证找前驱和后继的功能
    if(predecessor)   printf("%d pre is %d \n",root->val,predecessor->val);
    else    printf("%d pre is NULL \n",root->val);

    
    if(successor)   printf("%d next is %d \n",root->val,successor->val);
    else    printf("%d next is NULL \n",root->val);

}
int main()
{
    
    ThreadTree root = test01();
    test02(root->rchild);
    return 0;
}

ThreadNode* create_node(int key)
{
    ThreadTree curr = (ThreadNode*)malloc(sizeof(ThreadNode));
    if(!curr)
    {
        puts("error create_thread_node");
        return NULL;
    }
    curr->val = key;
    curr->lchild=NULL;
    curr->rchild=NULL;
    curr->ltag=0;
    curr->rtag=0;
    return curr;
}
TreeNode* create_treenode(int key)
{
    Tree curr = (TreeNode*)malloc(sizeof(TreeNode));
    if(!curr) return NULL;
    curr->val = key;
    curr->lchild = NULL;
    curr->rchild = NULL;
    return curr;
}
Tree create_tree_Recursive(int arr[],int*idx)
{
    int data = arr[(*idx)++];
    if( data == -1) return NULL;
    TreeNode* root = (Tree)malloc(sizeof(TreeNode));
    root->val = data;
    root->lchild = create_tree_Recursive(arr,idx);
    root->rchild = create_tree_Recursive(arr,idx);
    return root;
}
Tree construct_tree_preorder_iterative(int arr[],int *idx,int len)//迭代实现前序遍历构造二叉树
{
    if(arr[*idx] == -1||len==0) 
    {
        if(*idx<len)
        {
            (*idx)++;
        }
        return NULL;
    }
    TreeNode* stack[50];
    int top=-1;

    Tree root = create_treenode(arr[*idx]);
    (*idx)++;
    stack[++top] = root;
    while(top!=-1&&*idx<len)
    {
        TreeNode* curr = stack[top];//get_stack()
        if(arr[*idx]!=-1)
        {
            TreeNode* temp = create_treenode(arr[*idx]);
            curr->lchild = temp;
            stack[++top] = temp;    //push_stack
            (*idx)++;
        }else{
            (*idx)++;

            while(top!=-1&&*idx<len)
            {
                //找到栈内第一个有右孩子的节点
                TreeNode* temp = stack[top--];//pop_stack()
                if(arr[*idx]!=-1)
                {
                    temp->rchild = create_treenode(arr[*idx]);
                    stack[++top] = temp->rchild; //push_stack
                    (*idx)++;
                    break;
                }else{
                    (*idx)++;
                }
            }
        }
    }
    return root;
}
ThreadTree construct_threadtree_preorder_iterative(int arr[],int *idx,int len)//迭代实现前序遍历造树
{
    if(len == 0 ||*idx >= len || arr[*idx] == -1) 
    {
        if(*idx<len)
        {
            (*idx)++;
        }
        return NULL;
    }
    ThreadNode* stack[50];
    int top=-1;

    ThreadTree root = create_node(arr[*idx]);
    (*idx)++;
    stack[++top] = root;
    while(top!=-1&&*idx<len)
    {
        ThreadNode* curr = stack[top];//get_stack()
        if(arr[*idx]!=-1)
        {
            ThreadNode* temp = create_node(arr[*idx]);
            curr->lchild = temp;
            stack[++top] = temp;    //push_stack
            (*idx)++;
        }else{
            (*idx)++;

            while(top!=-1&&*idx<len)
            {
                //找到栈内第一个有右孩子的节点
                ThreadNode* temp = stack[top--];//pop_stack()
                if(arr[*idx]!=-1)
                {
                    temp->rchild = create_node(arr[*idx]);
                    stack[++top] = temp->rchild; //push_stack
                    (*idx)++;
                    break;
                }else{
                    (*idx)++;
                }
            }
        }
    }
    return root;
}
ThreadNode* inorder_threading_recursive(ThreadTree root,ThreadTree* pre)//中序递归线索化二叉树
{   
    if(!root) return NULL;
    inorder_threading_recursive(root->lchild,pre);
    if(*pre&&!(*pre)->rchild){
        (*pre)->rchild = root;
        (*pre)->rtag = 1;
    }
    if(!root->lchild){
        root->lchild = *pre;
        root->ltag=1;
    }
    *pre=root;
    inorder_threading_recursive(root->rchild,pre);
    return root;
}
void in_order_traverse_Thread(ThreadTree root)  //验证线索化是否正确，输出中序遍历结果
{
    if(!root)return ;
    ThreadNode* curr = root;
    
    //找到中序遍历第一个节点
    while(curr&&curr->ltag==0)
    {
        curr = curr->lchild;
    }
    
    while(curr)
    {
        printf("%d ",curr->val);
        if(curr->rtag)
        {
            curr = curr->rchild;
        }else{
            //找中序后继(右子树的最左节点)
            curr = curr->rchild;
            while(curr&&curr->ltag == 0)
            {
                curr = curr->lchild;
            }
        }
    }
}
/* 
    Q:  如何设计函数的参数呢？我现在有两种方案，一种是直接传要找前驱的节点的地址，另一种是传根节点和要找前驱的节点的val，你觉得应该是哪种方案呢？
    A:优先选择直接传要找前驱的节点的地址（指针） 作为参数，这是符合线索二叉树设计初衷、且高效的方案。

两种方案的对比分析
    方案 1：传「目标节点的指针」（推荐）
        函数原型示例：ThreadNode* find_predecessor(ThreadNode* p);
    
    核心优势：
        1.符合线索二叉树的设计初衷：
            线索二叉树的核心价值就是「通过节点自身的指针 / 标记，无需遍历整树就能定位前驱 / 后继」，直接传目标节点指针，
        能完全体现这个优势（查找过程只围绕p节点及其子树 / 线索展开，无冗余操作）；
        
        2.效率最高：查找前驱的时间复杂度是O(h)（h 为树高，仅找左子树最右 / 右子树最左时会遍历子树，无整树遍历），且无需额外步骤找节点；
        3.逻辑简洁：不需要先从根节点找 “值为 val 的节点”，直接基于目标节点的ltag/lchild/rchild推导前驱，代码少、不易出错；
        4.避免值冲突：如果树中存在重复 val 的节点，传 val 会无法确定 “到底找哪个节点的前驱”，传指针能精准定位唯一节点。
        5.适用场景：只要你能拿到目标节点的指针（比如遍历树时缓存节点指针、或构建树时记录关键节点指针），就选这种方案 —— 这也是线索二叉树前驱 / 后继查找的标准实现方式。
    
    方案 2：传「根节点 + 目标节点的 val」（不推荐）
        函数原型示例：ThreadNode* find_predecessor(ThreadTree root, int val);

    核心问题：
        1、违背线索二叉树的设计初衷：为了找前驱，你需要先从根节点遍历整树找到 “val 对应的节点”（这一步已经遍历了整树 / 部分树），
        再基于该节点找前驱 —— 完全失去了 “无需遍历整树找前驱” 的核心要求；
        
        2.效率低且冗余：多了 “找节点” 的步骤，时间复杂度至少是O(n)（n 为节点数），抵消了线索二叉树的优势；
        3.存在值冲突风险：若树中有多个节点 val 相同，无法确定目标节点，只能返回第一个匹配的节点，逻辑不严谨；
        4.参数冗余：找前驱的核心逻辑和根节点无关（仅和目标节点的ltag/ 指针有关），传根节点只是为了 “先找节点”，属于额外负担。
        5.仅有的适用场景：只有一种情况可考虑 —— 你完全拿不到目标节点的指针，只能通过 val 定位（比如用户只输入 val，无节点指针缓存），但这是 “无奈之选”，而非最优解。

以下为对第二种方法的思考
ThreadNode* find_thread_predecessor(ThreadTree root ,int key)//找线索二叉树前驱节点
{
    if(!root){
        puts("error ! root ==  NULL");
        return  NULL;
    }
    ThreadNode* curr = root;
    while(curr)
    {
        if(curr->val == key)
        {
            //线索前驱
            if(curr->ltag) return curr->lchild;
            else
            {    
                //找其左子树的最右节点
                curr = curr->lchild;
                while(curr->rchild)
                {
                    curr= curr->rchild;
                }
                return curr;
            }

        }else{
            //利用迭代栈前序遍历找key值
            
        }
    }
    //没找到key值
    printf("error ! not exist the threadnode is %d \n",key);
} 
*/
ThreadNode* find_thread_predecessor(ThreadTree p)//找线索二叉树前驱节点
{
    if(!p)
    {
        puts("error ! find_thread_predecessor");
        return NULL;
    }
    if(p->ltag)
    {
        return p->lchild;
    }else{
        //找p左孩子的最右节点
        ThreadNode* curr = p->lchild;
        while(curr->rchild && curr->rtag == 0)
        {
            curr = curr->rchild;
        }
        return curr;
    }
}
ThreadNode* find_thread_successor(ThreadTree p)//找线索二叉树中序后继节点
{
    if(!p)
    {
        puts("error ! find_thread_successor");
        return NULL;
    }
    if(p->rtag)
    {
        return p->rchild;
    }else{
        //找右孩子最左节点为后继
        ThreadNode* curr = p->rchild;
        while(curr->lchild&&curr->ltag == 0)
        {
            curr = curr->lchild;
        }
        return curr;
    }
}
    /* // Tree construct_tree_preorder_iterative(int arr[],int *idx,int len)
    // {
    //     //前序遍历迭代造树
    //     if(arr[*idx] == -1) return NULL;//空树
        
    //     stack stack;
    //     Tree root = create_treenode(arr[(*idx)++]);
    //     stack.init_stack();
    //     stack.push_stack(root);
    //     while(!stack.is_empty()||*idx < len)
    //     {
    //         TreeNode* pre = stack.get_top();
    //         int data = arr[(*idx)++];
    //         if(data!=-1)
    //         {
    //             TreeNode* temp = create_treenode(data);
    //             pre->lchild = temp;
    //             stack.push_stack(temp);
    //         }else{
    //             pre = stack.pop_stack();
    //             data = arr[(*idx)++];
    //             if(data!=-1){
    //             TreeNode* temp = create_treenode(data);
    //             pre->rchild = temp;
    //             stack.push_stack(temp);
    //             }else{
    //                 //data == -1
                    
    //                 while(*idx<len&&arr[*idx] == -1){
    //                     (*idx)++;
    //                     pre = stack.pop_stack();
    //                 }
    //                 //处理右孩子
    //                 pre->rchild = create_treenode(arr[*idx]);
    //                 stack.push_stack(arr[*idx]);
    //                 *idx++;               
    //             }
    //         }
    //     }

    //     return root;
    // }


    // ThreadNode* create_test_tree()
    // {
    //     int arr[]={5,4,1,-1,3,-1,-1,-1,8,7,6,-1,-1,-1,12,9,-1,-1,13,-1,-1};
    //     int len = sizeof(arr)/sizeof(int);
    //     int idx=0;
    //     ThreadNode* stack[len];
    //     int top = -1;
    //     ThreadTree root = create_node(arr[0]);
        
    //     stack[++top] = root;//根节点入栈
    //     ThreadNode* pre = root;
    //     while(top!=-1||idx!=len){
            
    //     }


    //     return root;
    // }
 */

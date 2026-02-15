/*
        Time:   2026/2/6
        Author: await-2313
*/
//用迭代方式实现前序后续层序造树
#include<stdio.h>
#include<stdlib.h>
#define Capacity_stack 50
typedef struct TreeNode{
    int val;
    struct TreeNode* lchild;
    struct TreeNode* rchild;
}TreeNode,*Tree;
typedef struct stack{
    TreeNode* stack[Capacity_stack];
    int top;
}Stack;
int init_stack(Stack*s)
{
    if(!s)return 0;
    s->top=-1;
    return 1;
}
int is_empty(Stack*s)
{
    if(!s){
        puts("error ! fail to check is_empty");
        return 0;
    }
    if(s->top ==-1)return 1;
    else return 0;
}
int push_stack(Stack*s,TreeNode* root)
{
    if(!s){
        puts("error ! fail to push_stack");
        return 0;
    }
    if(s->top == Capacity_stack-1){
        puts("fail to push_stack ! plese extend the capacity ");
        return 0;
    }else{
        s->stack[++(s->top)] = root;
        return 1;
    }
}
TreeNode* pop_stack(Stack* s)
{
    if(is_empty(s)){
        puts("empty stack fail to pop_stack");
        return NULL;
    }
    TreeNode* curr = s->stack[s->top];
    s->top--;
    return curr;
}
TreeNode* get_top(Stack*s)
{
    if(is_empty(s)){
        puts("error ! fail to get_top");
        return NULL;
    }
    return s->stack[s->top];
}
TreeNode* create_node(int key)
{
    TreeNode* curr = (TreeNode*)malloc(sizeof(TreeNode));
    if(!curr){
        puts("fail to create_node");
        return NULL;
    }
    curr->val = key;
    curr->lchild=NULL;
    curr->rchild=NULL;
    return curr;
}
TreeNode* construct_tree_preorder_iterative(int arr[],int*idx,int len)//先序遍历迭代造树
{
    if(len ==0||arr[*idx]==-1)
    {
        (*idx)++;
        return NULL;
    }

    Stack s;
    Tree root =NULL;

    init_stack(&s);
    root = create_node(arr[*idx]);
    (*idx)++;
    push_stack(&s,root);

    while(!is_empty(&s)&&*idx<len)
    {
        TreeNode*pre = get_top(&s);
        if(arr[*idx]!=-1)
        {
            TreeNode* temp = create_node(arr[*idx]);
            pre->lchild = temp;
            (*idx)++;
            push_stack(&s,temp);
        }else{
            //无左孩子
            (*idx)++;
            while(!is_empty(&s)&&*idx<len)
            {
                pre = pop_stack(&s);
                if(arr[*idx]!=-1)
                {
                    TreeNode* temp = create_node(arr[*idx]);
                    pre->rchild = temp;
                    (*idx)++;
                    push_stack(&s,temp);
                    break;
                }else{
                    (*idx)++;
                }
            }
        }
    }

    return root;
}

void preOrderTraverse(TreeNode* root)
{
    if(!root) return;
    printf("%d ",root->val);
    preOrderTraverse(root->lchild);
    preOrderTraverse(root->rchild);
}
void inOrderTraverse(Tree root)
{
    if(!root)return;
    inOrderTraverse(root->lchild);
    printf("%d ",root->val);
    inOrderTraverse(root->rchild);
}
void postOrderTraverse(Tree root)
{
    if(!root) return ;
    postOrderTraverse(root->lchild);
    postOrderTraverse(root->rchild);
    printf("%d ",root->val);   
}
void preOrderTraverseIterative(Tree root)
{
    if(!root) return;
    
    Stack s;
    init_stack(&s);

    //dfs流程:
    //先将根节点和它的所有左孩子入栈

    while(root)
    {
        printf("%d ",root->val);
        push_stack(&s,root);
        root = root->lchild;
    }

    //依次出栈，将出栈节点的右孩子入栈，同时入栈右孩子的所有左子树
    while(!is_empty(&s))
    {
       TreeNode* t = pop_stack(&s);
       TreeNode* r = t->rchild;
       while(r)
       {
            printf("%d ",r->val);
            push_stack(&s,r);
            r = r->lchild;
       }
    }
    //前序遍历是入栈时调用
    putchar('\n');
}
void preOrderTraverseIterative_funtion_two(Tree root)
{
    if(!root)return ;
    Stack s;
    init_stack(&s);
    push_stack(&s,root);
    
    while(!is_empty(&s))
    {
        TreeNode* cur = pop_stack(&s);
        printf("%d ",cur->val);
        if(cur->rchild) push_stack(&s,cur->rchild);
        if(cur->lchild) push_stack(&s,cur->lchild);
    }
    putchar('\n');
}
void inOrderTraverseItertive(Tree root)
{
    if(!root)return;

    Stack s;
    init_stack(&s);

    //dfs流程:
    //先将根节点和它的所有左孩子入栈

    while(root)
    {
        push_stack(&s,root);
        root = root->lchild;
    }

    //依次出栈，将出栈节点的右孩子入栈，同时入栈右孩子的所有左子树
    while(!is_empty(&s))
    {
       TreeNode* t = pop_stack(&s);
       printf("%d ",t->val);
       TreeNode* r = t->rchild;
       while(r)
       {
            push_stack(&s,r);
            r = r->lchild;
       }
    }
    //中序遍历是出栈时调用  左-根-右
    putchar('\n');

}
void inOrderTraverseIterative_function_two(Tree root)
{
    /* 核心思路
    中序没有 “反序压入”，但栈的作用依然是 “存待回溯的根节点”：
        1.从根出发，把所有左节点依次压栈（只压栈，不打印），直到最左节点；
        2.弹出最左节点 → 打印（左）；
        3.弹出的节点作为 “根” → 处理它的右节点（重复步骤 1-2）；
        4.右节点处理完后，栈顶就是上层的 “根” → 弹出打印（根），再处理上层根的右节点 */
    if(!root)return;
    Stack s;
    init_stack(&s);
    TreeNode* cur = root;

    while(cur||!is_empty(&s))
    {
        //左节点全部压入栈
        while(cur)
        {
            push_stack(&s,cur);
            cur =cur->lchild;
        }
        //弹出栈顶元素并打印
        cur = pop_stack(&s);
        printf("%d ",cur->val);

        //处理根的右节点
        cur = cur->rchild;
    }
    putchar('\n');
}
void postOrderTraverseIterative(Tree root)
{
    if(!root)return;
    Stack s;
    Stack result;
    init_stack(&s);
    init_stack(&result);

    //dfs流程
    //后续遍历 左-右-根 逆序为根-右-左，对应为“前序遍历”

    //先将根节点右子树全部压入栈
    while(root)
    {
        push_stack(&s,root);
        push_stack(&result,root);
        root = root->rchild;
    }

    //弹出栈顶并压入左孩子的全部右孩子
    while(!is_empty(&s))
    {
        TreeNode* t = pop_stack(&s);
        TreeNode* l = t->lchild;
        while(l)
        {
            push_stack(&s,l);
            push_stack(&result,l);
            l=l->rchild;
        }
    }

    //后序遍历是特殊的“前序遍历”，在入栈时保存逆序结果
    while(!is_empty(&result))
    {
        TreeNode* t = pop_stack(&result);
        printf("%d ",t->val);
    }
    putchar('\n');
}
void postOrderTraverseIterative_function_two(Tree root)
{
    //单循环 根-右-左 实现后序遍历
    if(!root)return;
    Stack s;
    Stack result;
    init_stack(&s);
    init_stack(&result);
    
    push_stack(&s,root);
    
    while(!is_empty(&s))
    {
        TreeNode* t =pop_stack(&s);
        push_stack(&result,t);
        
        if(t->lchild)push_stack(&s,t->lchild);
        if(t->rchild)push_stack(&s,t->rchild);
    }
    
    //逆序输出
    while(!is_empty(&result))
    {
        TreeNode*t = pop_stack(&result);
        printf("%d ",t->val);
    }
    putchar('\n');

}
void destoryTreepostOrderIterative(Tree root)
{
    //单循环 根-右-左 实现后序遍历
    if(!root)return;
    Stack s;
    Stack result;
    init_stack(&s);
    init_stack(&result);
    
    push_stack(&s,root);
    
    while(!is_empty(&s))
    {
        TreeNode* t =pop_stack(&s);
        push_stack(&result,t);
        
        if(t->lchild)push_stack(&s,t->lchild);
        if(t->rchild)push_stack(&s,t->rchild);
    }
    
    //逆序输出
    while(!is_empty(&result))
    {
        TreeNode*t = pop_stack(&result);
        free(t);
        t = NULL;
    }
    puts("destroy success !");
}
/* TreeNode* construct_tree_inorder_iterative(int arr[],int*idx,int len)//中序遍历迭代造树

    仅中序遍历无法造树

    举例说明：假设中序遍历序列（带 - 1）为 [-1, 1, -1, 2, -1]，可以对应两种不同的树：
    
        2                    1
    1                           2

    中序遍历的核心问题是：根节点始终夹在左右子树中间，无法从序列中直接确定 “哪一个节点是整棵树的根”。
*/


void level_order_traverse(Tree root)
{
    if(!root) return;
    TreeNode* queue[Capacity_stack];
    int front = 0,rear=0;
    queue[rear++] = root;
    int times = rear-front;
    while(front<rear)
    {
        TreeNode* curr = queue[front++];
        times--;
        printf("%d ",curr->val);
        if(curr->lchild) queue[rear++] = curr->lchild;
        if(curr->rchild) queue[rear++] = curr->rchild;
        if(times == 0)
        {
            printf("\n");
            printf("---------------\n");
            times = rear-front;
        }
    }
}
void test01()
{
    int arr[] = {5,4,1,-1,3,-1,-1,-1,8,7,6,-1,-1,-1,12,9,-1,-1,13,-1,-1};//前序遍历,-1代表空节点
    int idx=0;

    Tree root = construct_tree_preorder_iterative(arr,&idx,sizeof(arr)/sizeof(int));
    
    inOrderTraverse(root);
    puts("\n");
    level_order_traverse(root);
    preOrderTraverseIterative(root);
    preOrderTraverseIterative_funtion_two(root);
    inOrderTraverseItertive(root);
    inOrderTraverseIterative_function_two(root);
    postOrderTraverseIterative(root);
    postOrderTraverseIterative_function_two(root);
    destoryTreepostOrderIterative(root);

}


int main()
{
    test01();
    
    return 0;
}
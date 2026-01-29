/*BST基础操作
| 日期 | 核心任务                          | 具体内容                                                                 | 验收标准                                                                 |
|------|-----------------------------------|--------------------------------------------------------------------------|--------------------------------------------------------------------------|
| Day1 | BST插入                           | 手写：结构体定义+创建节点+插入（二级指针）| 能解释“二级指针”的作用，插入后根节点指向正确                             |
| Day2 | BST查找+遍历                      | 手写：查找节点+中序遍历                                                  | 查找存在/不存在的节点返回正确，中序遍历为升序                             |
| Day3 | BST删除（简单场景）| 手写：删除叶子节点+删除只有单孩子的节点                                  | 删除后中序遍历仍为升序，节点内存释放正确                                 |
| Day4 | BST删除（复杂场景）| 手写：删除有双孩子的节点（找右子树最小节点）| 能解释“找后继节点”的原因，删除后树结构正确                               |
| Day5 | BST复习                          | 闭卷手写BST插入/查找/删除所有代码                                         | 代码无语法错误，编译运行通过                                             |
| Day6 | BST错题修正                      | 整理删除双孩子节点、二级指针传参的错误，重新实现                         | 错误点标注原因，修正后代码运行正确                                       |
| Day7 | BST综合练习                      | 手写：从数组构建BST，删除指定节点后遍历验证                              | 构建+删除+遍历全流程无bug，结果符合预期                                 |
*/
//          2026/1/19
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
typedef struct BSTNode{
    int data;
    struct BSTNode* lchild;
    struct BSTNode* rchild;
}BSTNode,*BSTree;

/* void BST_insert(BSTree root,int key){
    if(!root) return;
    if(key>root->data){
        BST_insert(root->rchild,key);
    }else{
        BST_insert(root->lchild,key);
    }
} */

BSTNode* create_BSTNode(int key){
    BSTNode* node =(BSTNode*)malloc(sizeof(BSTNode));
    if(!node) return NULL;
    node->data = key;
    node->lchild = NULL,node->rchild = NULL;
    return node;
}

int bst_insert(BSTree *root,int key){            //获取父母节点，指向该节点，或使用二级指针直接修改
    if(!*root){
        *root = create_BSTNode(key);
        return (*root!=NULL)? 1:-1;
    }
    if((*root)->data == key) return 0;   
    if(key>(*root)->data) return bst_insert(&((*root)->rchild),key);
    else return bst_insert(&((*root)->lchild),key);
}

BSTNode* search_bstnode(BSTree root,int key){       //查找节点
    if(!root) return NULL;
    if(key == root->data) return root;              //前两句可以合并
    if(key>root->data) return search_bstnode(root->rchild,key);
    else return search_bstnode(root->lchild,key);
}

void in_order_traverse(BSTree root){
    if(!root) return;
    in_order_traverse(root->lchild);
    printf("%d ",root->data);
    in_order_traverse(root->rchild);
}

BSTNode* find_min_bstnode(BSTree root){
    if(!root) return NULL;
    while(root->lchild){
        root = root->lchild;
    }
    return root;
}

int delete_bst(BSTree* root,int key){
    if(!*root) return 0;
    if(key>(*root)->data)return delete_bst(&((*root)->rchild),key);
    else if(key<(*root)->data)return delete_bst(&((*root)->lchild),key);
    else{
        //找到Key值
        BSTNode* temp = *root;
        if(!(*root)->lchild){
            *root = (*root)->rchild; //更新root值,需要二级指针
            free(temp);
        }else if(!(*root)->rchild){
            *root = (*root)->lchild;
            free(temp);
        }else{
            BSTNode* min_node = find_min_bstnode((*root)->rchild);//找到右子树的最小值(最接近root的较大值)
            (*root)->data = min_node->data;
            
            /* delete_bst(&min_node,min_node->data); */
            
        /*  你的写法delete_bst(&min_node, min_node->data)无法解决问题，因为修改的是局部指针变量，而非树结构中父节点指向 min_node 的指针，会导致节点残留、内存泄漏；
            标准写法bst_delete(&((*root)->rchild), min_node->key)是最优解，核心是传递 “右子树根指针的地址”，让递归能找到并修改 min_node 父节点的指针，真正移除节点并维护树结构；
            核心原则：修改树的节点指向时，必须传递「树结构中实际指向该节点的指针的地址」（比如父节点的 lchild/rchild 的地址），而非局部指针变量的地址。 

            一、核心比喻：指针是 “写着门牌号的纸条”
            假设：
            min_node 节点的内存地址是 0x100（相当于 “门牌号 100 的房子”）；
            父节点 p 的p->lchild 是一张纸条，上面写着0x100（指向这栋房子）；
            你定义的局部变量min_node 是另一张纸条，也抄了0x100（和父节点的纸条指向同一栋房子）。
            你的操作：delete_bst(&min_node, min_node->data) 本质是把你手里的这张纸条改成了 NULL（擦掉门牌号，写个 “无”）；但父节点 p 手里的那张纸条，
            依然写着0x100—— 它还是指向原来的房子，只是你手里的纸条不指向了而已。
        */
            
            delete_bst(&((*root)->rchild),min_node->data);
        }
        return 1;
    }
}
//对此函数作出几点解释
//1.为什么使用二级指针
/*
    1、二级指针的核心作用：在函数内修改外部 / 上层的一级指针本身的值（而非指针指向的内容），本质是解决 C 语言 “值传递” 导致的副本修改无效问题；
    2、递归版 BST 删除必须用二级指针：因为递归栈帧的独立性，修改一级指针副本无法更新父节点的 lchild/rchild 指向，只有二级指针能直接操作父节点的指针；
    3、二级指针的使用场景：只要需要 “跨函数 / 跨栈帧修改指针变量本身的值”，就需要用二级指针（C++ 里可用引用&替代，逻辑更直观）。
*/

//2.为什么不使用父节点parent来更新一级指针？
/*
你这个问题问到了核心！你说的 “通过父节点 parent->lchild/parent->rchild 来修改子节点指向” 的思路完全可行，并不是错误的 —— 但这种 “传 parent 参数”
的写法，在递归场景下会让代码复杂度飙升、易出错，而二级指针的写法能天然规避这些问题，这才是选择二级指针的核心原因。

    int bst_delete_with_parent(BSTree curr, BSTree parent, int is_left, int key);
二、传 parent 参数的写法有哪些 “致命问题”？
    你能看到，这种写法确实能通过父节点修改子节点指向，但有 3 个无法回避的问题，也是为什么实际开发中不用这种方式的原因：
    问题 1：根节点需要特殊处理（最大的坑）
        根节点没有父节点（parent=NULL），此时无法通过parent->lchild/rchild修改指向 —— 函数内修改的curr只是栈帧副本，
        外部的root指针不会同步更新，必须通过返回值 / 全局变量 / 额外指针参数来传递新根，逻辑瞬间变复杂。
    问题 2：需要额外传递 “父子关系标记”（is_left）
        递归时必须告诉函数 “当前节点是父节点的左孩子还是右孩子”，否则函数不知道该修改parent->lchild还是parent->rchild—— 多一个参数就多一层出错可能（比如传反了 is_left，直接导致树结构错乱）。
    问题 3：递归逻辑不 “自洽”，代码冗余
        删除双孩子节点时，递归删除右子树最小节点的过程中，又要重复处理 “找 min_node 的父节点 + 标记父子关系”，代码冗余且易出错；
        而二级指针的写法，递归时只需要传递 “当前节点指针的地址”，无需关心父节点和父子关系。

四、总结：为什么选二级指针，而不是多传 parent 参数？
    1、二级指针的核心是绕开 “父节点” 这个中间层：直接操作 “需要修改的指针本身的地址”，不管是根节点还是普通节点，处理逻辑完全一致，无需特殊情况；
    2、传 parent 参数的写法虽然可行，但引入了 “根节点特殊处理”“is_left 标记” 等额外复杂度，新手极易踩坑，而二级指针写法更符合递归 “自顶向下” 的自然逻辑；
    3、本质上，二级指针是 C 语言 “值传递” 规则下，跨栈帧修改指针变量的最简洁、最通用的方式—— 传 parent 参数只是 “间接绕路”，而二级指针是 “直接命中目标”。
*/
void level_order_traverse(BSTree root){
    if(!root) return;
    int front = 0,rear = 0;
    BSTree queue[50];
    int key = 0;
    queue[rear++] = root;
    key = rear-front;
    while(front<rear){
        BSTNode* node =queue[front++]; 
        printf("%d ",node->data);
        if(node->lchild) queue[rear++] = node->lchild;
        if(node->rchild) queue[rear++] = node->rchild;
        key--;
        if(key == 0) {
            printf("\n----\n");
            key = rear-front;
        }
    }
}
void test02(BSTree root){
    printf("中序遍历为:\n");
    in_order_traverse(root);
    printf("\n层序遍历为:\n");
    level_order_traverse(root);
    printf("\n");
}
void test01(){
    int data[] = {4,1,6,2,9,5,7,10};
    BSTree root = create_BSTNode(data[0]);
    for(int i=1,len = sizeof(data)/sizeof(int);i<len;i++){
        bst_insert(&root,data[i]);
    }
    test02(root);

    int arr[] = {3,8,44,55,13};
    for(int i=0,len = sizeof(arr)/sizeof(int);i<len;i++){
        bst_insert(&root,arr[i]);
        printf("第%d次插入,新值为%d  \n",i+1,arr[i]);
        test02(root);
    }
    
}

int main(){
    
    SetConsoleOutputCP(CP_UTF8);
    test01();
    
    return 0;
}
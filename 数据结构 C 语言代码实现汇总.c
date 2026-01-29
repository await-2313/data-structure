/*
 * 数据结构C语言代码实现汇总
 * 包含：线性结构、树形结构、哈希表、排序算法
 * 可单独编译运行，也可拆分模块测试
 */
#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 10 // 队列/层序遍历用的最大容量

// ====================== 1. 单链表 ======================
typedef struct ListNode {
    int data;
    struct ListNode *next;
} ListNode, *LinkList;

// 创建单链表节点
ListNode* create_list_node(int data) {
    ListNode *node = (ListNode*)malloc(sizeof(ListNode));
    if (!node) { printf("内存分配失败\n"); return NULL; }
    node->data = data;
    node->next = NULL;
    return node;
}

// 头插法创建链表
LinkList create_list_head(int arr[], int len) {
    if (len <= 0) return NULL;
    LinkList head = create_list_node(arr[0]);
    for (int i = 1; i < len; i++) {
        ListNode *node = create_list_node(arr[i]);
        node->next = head;
        head = node;
    }
    return head;
}

// 尾插法创建链表
LinkList create_list_tail(int arr[], int len) {
    if (len <= 0) return NULL;
    LinkList head = create_list_node(arr[0]);
    ListNode *tail = head;
    for (int i = 1; i < len; i++) {
        ListNode *node = create_list_node(arr[i]);
        tail->next = node;
        tail = node;
    }
    return head;
}

// 遍历单链表
void traverse_list(LinkList head) {
    ListNode *p = head;
    while (p) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

// 删除单链表指定值节点
int delete_list_node(LinkList *head, int data) {
    if (!*head) return 0;
    ListNode *p = *head, *pre = NULL;
    // 删除头节点
    if (p->data == data) {
        *head = p->next;
        free(p);
        return 1;
    }
    // 找目标节点前驱
    while (p && p->data != data) {
        pre = p;
        p = p->next;
    }
    if (!p) return 0;
    pre->next = p->next;
    free(p);
    return 1;
}

// 反转单链表（迭代版）
LinkList reverse_list(LinkList head) {
    ListNode *pre = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    return pre;
}

// 销毁单链表
void destroy_list(LinkList *head) {
    ListNode *p = *head, *q = NULL;
    while (p) {
        q = p->next;
        free(p);
        p = q;
    }
    *head = NULL;
}

// ====================== 2. 链式栈 ======================
typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

typedef struct LinkStack {
    StackNode *top;
    int size;
} LinkStack;

// 初始化栈
LinkStack* init_stack() {
    LinkStack *stack = (LinkStack*)malloc(sizeof(LinkStack));
    stack->top = NULL;
    stack->size = 0;
    return stack;
}

// 栈判空
int is_stack_empty(LinkStack *stack) {
    return stack->top == NULL;
}

// 入栈
int push_stack(LinkStack *stack, int data) {
    StackNode *node = (StackNode*)malloc(sizeof(StackNode));
    if (!node) return 0;
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return 1;
}

// 出栈
int pop_stack(LinkStack *stack) {
    if (is_stack_empty(stack)) return -1;
    StackNode *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;
}

// 销毁栈
void destroy_stack(LinkStack *stack) {
    while (!is_stack_empty(stack)) {
        pop_stack(stack);
    }
    free(stack);
}

// ====================== 3. 循环队列 ======================
typedef struct CirQueue {
    int data[MAX_SIZE];
    int front;
    int rear;
} CirQueue;

// 初始化队列
void init_queue(CirQueue *queue) {
    queue->front = 0;
    queue->rear = 0;
}

// 队列判空
int is_queue_empty(CirQueue *queue) {
    return queue->front == queue->rear;
}

// 队列判满
int is_queue_full(CirQueue *queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

// 入队
int enqueue(CirQueue *queue, int data) {
    if (is_queue_full(queue)) return 0;
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    return 1;
}

// 出队
int dequeue(CirQueue *queue) {
    if (is_queue_empty(queue)) return -1;
    int data = queue->data[queue->front];
    queue->front = (queue->front + 1) % MAX_SIZE;
    return data;
}

// ====================== 4. 二叉树 ======================
typedef struct BTNode {
    int data;
    struct BTNode *lchild;
    struct BTNode *rchild;
} BTNode, *BiTree;

// 先序创建二叉树（-1表示空节点）
BiTree create_btree(int arr[], int *idx) {
    int val = arr[(*idx)++];
    if (val == -1) return NULL;
    BiTree node = (BiTree)malloc(sizeof(BTNode));
    node->data = val;
    node->lchild = create_btree(arr, idx);
    node->rchild = create_btree(arr, idx);
    return node;
}

// 前序遍历
void pre_order(BiTree root) {
    if (!root) return;
    printf("%d ", root->data);
    pre_order(root->lchild);
    pre_order(root->rchild);
}

// 中序遍历
void in_order(BiTree root) {
    if (!root) return;
    in_order(root->lchild);
    printf("%d ", root->data);
    in_order(root->rchild);
}

// 后序遍历
void post_order(BiTree root) {
    if (!root) return;
    post_order(root->lchild);
    post_order(root->rchild);
    printf("%d ", root->data);
}

// 层序遍历
void level_order(BiTree root) {
    if (!root) return;
    BTNode *queue[MAX_SIZE];
    int front = 0, rear = 0;
    queue[rear++] = root;
    
    while (front != rear) {
        BTNode *p = queue[front++];
        printf("%d ", p->data);
        if (p->lchild) queue[rear++] = p->lchild;
        if (p->rchild) queue[rear++] = p->rchild;
    }
}

// 求二叉树高度
int get_bt_height(BiTree root) {
    if (!root) return 0;
    int left_h = get_bt_height(root->lchild);
    int right_h = get_bt_height(root->rchild);
    return (left_h > right_h ? left_h : right_h) + 1;
}

// 销毁二叉树
void destroy_btree(BiTree *root) {
    if (!*root) return;
    destroy_btree(&((*root)->lchild));
    destroy_btree(&((*root)->rchild));
    free(*root);
    *root = NULL;
}

// ====================== 5. 二叉排序树（BST） ======================
typedef struct BSTNode {
    int key;
    struct BSTNode *lchild;
    struct BSTNode *rchild;
} BSTNode, *BSTree;

// 创建BST节点
BSTNode* create_bst_node(int key) {
    BSTNode *node = (BSTNode*)malloc(sizeof(BSTNode));
    if (!node) return NULL;
    node->key = key;
    node->lchild = node->rchild = NULL;
    return node;
}

// BST插入节点
int bst_insert(BSTree *root, int key) {
    if (!*root) {
        *root = create_bst_node(key);
        return (*root != NULL) ? 1 : -1;
    }
    if ((*root)->key == key) return 0;
    if (key < (*root)->key) return bst_insert(&((*root)->lchild), key);
    else return bst_insert(&((*root)->rchild), key);
}

// BST查找节点
BSTNode* bst_search(BSTree root, int key) {
    if (!root || root->key == key) return root;
    if (key < root->key) return bst_search(root->lchild, key);
    else return bst_search(root->rchild, key);
}

// 找BST最小节点
BSTNode* bst_find_min(BSTree root) {
    if (!root) return NULL;
    while (root->lchild) root = root->lchild;
    return root;
}

// BST删除节点
int bst_delete(BSTree *root, int key) {
    if (!*root) return 0;
    if (key < (*root)->key) return bst_delete(&((*root)->lchild), key);
    else if (key > (*root)->key) return bst_delete(&((*root)->rchild), key);
    else {
        BSTNode *temp = *root;
        if (!(*root)->lchild) {
            *root = (*root)->rchild;
            free(temp);
        } else if (!(*root)->rchild) {
            *root = (*root)->lchild;
            free(temp);
        } else {
            BSTNode *min_node = bst_find_min((*root)->rchild);
            (*root)->key = min_node->key;
            bst_delete(&((*root)->rchild), min_node->key);
        }
        return 1;
    }
}

// ====================== 6. 哈希表（拉链法） ======================
#define TABLE_SIZE 10
typedef struct HashNode {
    int key;
    int value;
    struct HashNode *next;
} HashNode;

typedef struct HashTable {
    HashNode *table[TABLE_SIZE];
} HashTable;

// 哈希函数（取模）
int hash_func(int key) {
    return key % TABLE_SIZE;
}

// 初始化哈希表
void init_ht(HashTable *ht) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        ht->table[i] = NULL;
    }
}

// 哈希表插入键值对
int ht_insert(HashTable *ht, int key, int value) {
    int idx = hash_func(key);
    HashNode *node = (HashNode*)malloc(sizeof(HashNode));
    if (!node) return 0;
    node->key = key;
    node->value = value;
    node->next = ht->table[idx];
    ht->table[idx] = node;
    return 1;
}

// 哈希表查找
int ht_search(HashTable *ht, int key) {
    int idx = hash_func(key);
    HashNode *p = ht->table[idx];
    while (p) {
        if (p->key == key) return p->value;
        p = p->next;
    }
    return -1;
}

// ====================== 7. 经典排序算法 ======================
// 打印数组
void print_arr(int arr[], int len) {
    for (int i = 0; i < len; i++) printf("%d ", arr[i]);
    printf("\n");
}

// 快速排序-分区
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i+1];
    arr[i+1] = arr[high];
    arr[high] = temp;
    return i+1;
}

// 快速排序
void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quick_sort(arr, low, pi-1);
        quick_sort(arr, pi+1, high);
    }
}

// 归并排序-合并
void merge(int arr[], int low, int mid, int high) {
    int n1 = mid - low + 1;
    int n2 = high - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[low+i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid+1+j];
    
    int i = 0, j = 0, k = low;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

// 归并排序
void merge_sort(int arr[], int low, int high) {
    if (low < high) {
        int mid = low + (high - low)/2;
        merge_sort(arr, low, mid);
        merge_sort(arr, mid+1, high);
        merge(arr, low, mid, high);
    }
}

// ====================== 测试主函数（可按需注释测试模块） ======================
int main() {
    // 1. 单链表测试
    int arr_list[] = {1,2,3,4,5};
    LinkList head = create_list_tail(arr_list, 5);
    printf("单链表遍历："); traverse_list(head);
    delete_list_node(&head, 3);
    printf("删除3后："); traverse_list(head);
    head = reverse_list(head);
    printf("反转后："); traverse_list(head);
    destroy_list(&head);
    printf("--------------------\n");

    // 2. 链式栈测试
    LinkStack *stack = init_stack();
    push_stack(stack, 1); push_stack(stack, 2); push_stack(stack, 3);
    printf("栈出栈：%d\n", pop_stack(stack));
    printf("栈大小：%d\n", stack->size);
    destroy_stack(stack);
    printf("--------------------\n");

    // 3. 循环队列测试
    CirQueue queue;
    init_queue(&queue);
    enqueue(&queue, 1); enqueue(&queue, 2); enqueue(&queue, 3);
    printf("队列出队：%d\n", dequeue(&queue));
    printf("队列空？%d\n", is_queue_empty(&queue));
    printf("--------------------\n");

    // 4. 二叉树测试
    int arr_bt[] = {1,2,-1,4,-1,-1,3,5,-1,-1,-1};
    int idx = 0;
    BiTree root_bt = create_btree(arr_bt, &idx);
    printf("二叉树前序："); pre_order(root_bt); printf("\n");
    printf("二叉树层序："); level_order(root_bt); printf("\n");
    printf("二叉树高度：%d\n", get_bt_height(root_bt));
    destroy_btree(&root_bt);
    printf("--------------------\n");

    // 5. BST测试
    int arr_bst[] = {8,5,7,9,2,4,1,6};
    BSTree root_bst = NULL;
    for (int i = 0; i < 8; i++) bst_insert(&root_bst, arr_bst[i]);
    printf("BST中序："); in_order(root_bst); printf("\n");
    bst_delete(&root_bst, 5);
    printf("删除5后："); in_order(root_bst); printf("\n");
    destroy_btree(&root_bst);
    printf("--------------------\n");

    // 6. 哈希表测试
    HashTable ht;
    init_ht(&ht);
    ht_insert(&ht, 1, 100); ht_insert(&ht, 11, 200);
    printf("哈希表查1：%d\n", ht_search(&ht, 1));
    printf("哈希表查11：%d\n", ht_search(&ht, 11));
    printf("--------------------\n");

    // 7. 排序测试
    int arr_sort[] = {8,5,7,9,2,4,1,6};
    int len = sizeof(arr_sort)/sizeof(int);
    quick_sort(arr_sort, 0, len-1);
    printf("快速排序："); print_arr(arr_sort, len);
    int arr_sort2[] = {8,5,7,9,2,4,1,6};
    merge_sort(arr_sort2, 0, len-1);
    printf("归并排序："); print_arr(arr_sort2, len);

    return 0;
}
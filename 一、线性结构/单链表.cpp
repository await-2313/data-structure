/*
### 1. 单链表
| 序号 | 核心操作                | 功能说明                     |
|------|-------------------------|------------------------------|
| 1    | 创建节点                | 为单个节点分配内存并初始化   |
| 2    | 头插法建表              | 从头部插入节点构建链表       |
| 3    | 尾插法建表              | 从尾部插入节点构建链表       |
| 4    | 遍历链表                | 按顺序输出所有节点值         |
| 5    | 删除指定值节点          | 找到并释放目标节点，调整指针 |
| 6    | 反转链表                | 迭代法反转节点指针指向       |
| 7    | 销毁链表                | 释放所有节点内存，避免泄漏   |
*/
#include<stdio.h>
#include<stdlib.h>
typedef int DataType;
typedef struct list_node{
    DataType data;
    struct list_node* next;
}ListNode,*LinkList;

LinkList create_list_node(DataType new_data);//创建节点
void head_insert(LinkList head,DataType new_data);//头插法插入节点构建链表;
void behind_insert(LinkList head,DataType new_data);//尾插法构建链表
LinkList behind_insert_from_arry(DataType arr[],int len);//尾插法构建链表
void traverse_list(LinkList head);//遍历链表
int delete_list_node(LinkList head,int data);//删除指定值的节点
int reverse_list(LinkList head);//翻转链表
int delete_list(LinkList head);//销毁链表
void test01(){
    //检验前四个功能;
    LinkList head = create_list_node(-1);
    traverse_list(head);

    //头插法
    int arr[] = {1,2,3,4,5,6,7};
    for(int i=0,len = sizeof(arr)/sizeof(int);i<len;i++){
        head_insert(head,arr[i]);
        traverse_list(head);
    }

    //尾插法
    LinkList head02 = create_list_node(-1);
    traverse_list(head02);
    for(int i=0,len = sizeof(arr)/sizeof(int);i<len;i++){
        behind_insert(head02,arr[i]);
        traverse_list(head02);
    }
    
    LinkList head03 = behind_insert_from_arry(arr,sizeof(arr)/sizeof(int));
    traverse_list(head03);
}
void test02(){
    int arr[] = {1,2,3,4};

    LinkList head02 = create_list_node(-1);
    traverse_list(head02);
    for(int i=0,len = sizeof(arr)/sizeof(int);i<len;i++){
        behind_insert(head02,arr[i]);
        traverse_list(head02);
    }
    printf("\n");
    /* int key = delete_list_node(head02,4);
    printf("%d\n",key);
    traverse_list(head02); */
    /* int key = reverse_list(head02);
    if(!key) traverse_list(head02);
    else printf("no_reverse\n"); */
    delete_list(head02);
    traverse_list(head02);
}
int main(){
    //test01();
    test02();
    return 0;
}

LinkList create_list_node(DataType new_data){
    LinkList curr = (LinkList)malloc(sizeof(ListNode));
    if(!curr){
        printf("内存分配失败\n");
        return NULL;
    }
    curr->data = new_data;
    curr->next = NULL;
    return curr;
}
void head_insert(LinkList head,DataType new_data){
    LinkList new_list_node = create_list_node(new_data);
    new_list_node->next = head->next;
    head->next = new_list_node;
}
void behind_insert(LinkList head,DataType new_data){
    LinkList new_list_node = create_list_node(new_data);
    LinkList curr = head;
    while(curr->next!=NULL){
        curr = curr->next;
    }
    curr->next = new_list_node;
}
LinkList behind_insert_from_arry(DataType arr[],int len){
    LinkList head = create_list_node(-1);
    LinkList rear = head;
    for(int i=0;i<len;i++){
        LinkList curr = create_list_node(arr[i]);
        rear->next = curr;
        rear = curr;
    }
    return head;
}
void traverse_list(LinkList head){
    LinkList curr = head->next;
    if(curr == NULL) {
        printf("error\n");
        return ;
    }
    while(curr!= NULL){
        printf("%d ",curr->data);
        curr = curr->next;
    }
    printf("\n");
}
int delete_list_node(LinkList head,int delete_data){
    if(head ->next == NULL) return -1;
    LinkList curr = head->next;
    LinkList pre = head;
    int index = -1;
    while(curr!=NULL){
        if(curr->data ==delete_data ){
            pre->next = curr->next;
            free(curr) ;
            curr = NULL;
            index =0;
            break; 
        }
        pre = pre->next;
        curr = curr->next;
    }
    if(index == 0)return 0;
    else return -1;
}
int reverse_list(LinkList head){
    if(head->next == NULL) return -1;
    if(head->next->next == NULL) return -1;
    LinkList pre = NULL;
    LinkList curr = head->next;
    LinkList behind = curr->next;                                   //pre--curr--behind
    while(behind!=NULL){                                            //head--N1--N2
        curr->next = pre;
        pre = curr;
        curr = behind;
        behind = behind->next;
    }
    curr->next = pre;
    head->next = curr;
    return 0;

    //AI写的，没有头结点的翻转，根据curr设置pre next
/*     LinkList reverse_list(LinkList head) {
    ListNode *pre = NULL, *curr = head, *next = NULL;
    while (curr) {
        next = curr->next;
        curr->next = pre;
        pre = curr;
        curr = next;
    }
    return pre;
} */
}
int delete_list(LinkList head){
    if(head->next == NULL) return -1;
    LinkList curr = head->next;
    while(curr!= NULL){
        LinkList node = curr;
        curr = curr->next;
        free(node);
    }
    head->next=NULL;
    return 0;
}

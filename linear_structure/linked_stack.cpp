/*
### 2. 链式栈
| 序号 | 核心操作                | 功能说明                     |
|------|-------------------------|------------------------------|
| 1    | 初始化栈                | 创建栈结构并初始化栈顶/大小  |
| 2    | 判空                    | 判断栈是否为空               |
| 3    | 入栈                    | 头插法将节点压入栈顶         |
| 4    | 出栈                    | 弹出栈顶节点并释放内存       |
| 5    | 销毁栈                  | 逐个出栈并释放栈结构内存     |
*/
#include<stdio.h>
#include<stdlib.h>
typedef struct stacknode{
    int data;
    struct stacknode*next;
}stack_node;
typedef struct LinkStack{
    stack_node* top;
    int size;
}LinkStack;
LinkStack* init_stack(){//创建栈结构并初始化栈顶和大小
    LinkStack* stack = (LinkStack*)malloc(sizeof(LinkStack));
    stack->size = 0;
    stack->top = NULL;
    return stack;
}
int is_stack_empty(LinkStack* stack){
    return stack->top == NULL;
}
int push_stack(LinkStack* stack,int data){
    stack_node* node = (stack_node*)malloc(sizeof(stack_node));
    if(!node) return -1;
    node->data = data;
    node->next = stack->top;
    stack->top = node;
    stack->size++;
    return 0;
}
int pop_stack(LinkStack* stack){
    if(is_stack_empty(stack)) return -1;
    stack_node* temp = stack->top;
    int data = stack->top->data;
    stack->top = temp->next;
    free(temp);
    stack->size--;
    return data;;
}
void destroy_stack(LinkStack* stack){
    while(!is_stack_empty(stack)){
        pop_stack(stack);
    }
    free(stack);
}
void test01(){
    //测试
    LinkStack* stack = init_stack();
    int arr[] = {1,2,3,4,5,6};
    for(int i=0,len = sizeof(arr)/sizeof(int);i<len;i++){
        push_stack(stack,arr[i]);
    }
    printf("\n");

    while(!is_stack_empty(stack)){
        int data = pop_stack(stack);
        printf("%d ",data);
    }
    printf("\n");
}
int main(){
    test01();
    return 0;
}
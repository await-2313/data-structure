/*
### 3. 循环队列
| 序号 | 核心操作                | 功能说明                     |
|------|-------------------------|------------------------------|
| 1    | 初始化队列              | 初始化队头/队尾指针          |
| 2    | 判空                    | 判断队列是否为空             |
| 3    | 判满                    | 留空位法判断队列是否满       |
| 4    | 入队                    | 循环后移队尾，插入元素       |
| 5    | 出队                    | 循环后移队头，取出元素       |
*/
#include<stdio.h>
#include<stdlib.h>
#define MAXSIZE 100
typedef struct CirQueue{
    int data[MAXSIZE];
    int front;
    int rear;
}CirQueue;

void init_queue(CirQueue* queue){//             | 1    | 初始化队列              | 初始化队头/队尾指针          |
    queue->front = 0;
    queue->rear = 0;
}

int is_queue_empty(CirQueue* queue){//          | 2    | 判空                    | 判断队列是否为空             |
    return queue->front == queue->rear;
}

int is_queue_full(CirQueue* queue){//           | 3    | 判满                    | 留空位法判断队列是否满       |
    return (queue->rear+1)%MAXSIZE == queue->rear;
}

int enqueue(CirQueue* queue,int data){//        | 4    | 入队                    | 循环后移队尾，插入元素       |
    if(is_queue_full(queue)) return 0;
    queue->data[queue->rear] = data;
    queue->rear = (queue->rear+1)%MAXSIZE;
    return 1;
}

int dequeue(CirQueue* queue){//                 | 5    | 出队                    | 循环后移队头，取出元素       |
    if(is_queue_empty(queue)) return -1;
    int data = queue->data[queue->front];
    queue->front = (queue->front+1)%MAXSIZE;
    return data;
}
#define _CRT_SECURE_NO_WARNINGS 1
#define MAXSIZE 100
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
//Status 是函数类型，其值是函数结果状态代码
typedef int Status;
typedef char ElemType;
#include<stdio.h>
#include<stdlib.h>
//------------------------------顺序队列----------------------------------------
//定义
typedef struct {
	ElemType* base;//初始化的动态分配存储空间
	int front;//头指针
	int rear;//尾指针--->用来控制base的指向
}SqQueue;

//队列的初始化
Status InitQueue(SqQueue* Q) {
	Q->base = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);
	if (Q->base == NULL) exit(OVERFLOW);
	Q->front = Q->rear= 0;//头尾指针置空
	return OK;
}

//求队列长度
int QueueLength(SqQueue Q) {
	return ((Q.rear - Q.front + MAXSIZE) % MAXSIZE);
}

//循环队列入队
Status EnQueue(SqQueue* Q, ElemType e)
{
	if ((Q->rear + 1) % MAXSIZE == Q->front)//队满
		return ERROR;
	Q->base[Q->rear] = e;
	Q->rear = (Q->rear + 1) % MAXSIZE;
	return OK;
}

//循环队列出队
Status DeQueue(SqQueue* Q, ElemType* e)
{
	if (Q->front == Q->rear)//队空
		return ERROR;
	*e = Q->base[Q->front];
	Q->front = (Q->front+1) % MAXSIZE;
	return OK;
}

//取队头元素
ElemType GetHead(SqQueue Q) {
	if (Q.front != Q.rear)//队列不为空
		return Q.base[Q.front];//返回队头元素的值，但头指针不变
	return ERROR;
}
//----------------------------链队-----------------------------
//定义结点结构
typedef struct QNode
{
	ElemType data;
	struct QNode* next;
}QNode,*QueuePtr;
//定义头指针，尾指针
typedef struct {
	QueuePtr front;
	QueuePtr rear;
}LinkQueue;


//链队列的初始化
Status InitQueue(LinkQueue* Q)
{
	Q->front = Q->rear = (QueuePtr)malloc(sizeof(QNode));//头结点,开辟一个空间
	if (!Q->front) exit(OVERFLOW);
	Q->front->next = NULL;//将头结点的链域置空
	return OK;
}

//销毁链队列
Status DestroyQueue(LinkQueue* Q)
{
	while (Q->front)
	{
		QNode* P = Q->front->next;//保留结点，避免找不到
		free(Q->front);
		Q->front=P;//Q->rear=Q->front->next;free(Q->front);Q->front=Q->rear;另一种写法
	}
	Q->rear = NULL;
	return OK;
}

//将元素e入队
Status EnQueue(LinkQueue* Q, ElemType e)
{
	QNode* p = (QueuePtr)malloc(sizeof(QNode));//开辟新结点
	if (!p) exit(OVERFLOW);
	p->data = e;
	p->next = NULL;//初始化新结点
	Q->rear->next = p;//接在原链表后面
	Q->rear = p;//将尾指针指向新结点
	return OK;
}

//链队列出队
Status DeQueue(LinkQueue* Q, ElemType* e)
{
	if (Q->front == Q->rear)//队空条件
		return ERROR;
	QNode* p = Q->front->next;//保存要出队的结点的位置
	*e = p;//存放要出队的元素
	Q->front->next = p->next;//修改头指针方向
	if (Q->rear == p)//如果队伍里面只有一个元素，出队之后需要对尾指针进行处理，不然在释放结点空间后，尾指针会变成野指针
		Q->rear = Q->front;
	free(p);
	return OK;
}

//求链队列的队头元素
Status Gethead_Q(LinkQueue Q, ElemType* e)
{
	if (Q.front == Q.rear)//队空
		return ERROR;
	*e=Q.front->next->data;
	return OK;
}
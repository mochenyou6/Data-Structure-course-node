#define _CRT_SECURE_NO_WARNINGS 1

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100
#define OK 1
#define OVERFLOW -1
#define TRUE 1
#define FALSE -1
#define ERROR -1

typedef  int SElemType;
typedef  int Status;

//------------------------ 顺序栈------------------------------------
typedef struct SqStack//顺序栈的结构
{
	SElemType* base;
	SElemType* top;
	int StackSize;
}SqStack;

Status InitStack(SqStack* S)//初始化顺序栈
{
	S->base = (SElemType*)malloc(MAXSIZE * sizeof(SElemType));
	if (!S->base)exit(OVERFLOW);//判读空间是否成功开辟
	S->top = S->base;//此时为空栈；
	return OK;//初始化成功
};

Status StackEmpty(SqStack S)//顺序栈判断是否为空
{
	if (S.top == S.base) //栈空的条件
		return TRUE;
	else 
		return FALSE;
};

int StackLength(SqStack S)//求顺序栈的长度
{
	return S.top - S.base;
};

//清空顺序栈
Status ClearStack(SqStack* S)
{
	if(S->base)
	  S->top = S->base;//让栈顶指针指向栈底，此时满足空栈的条件
	return OK;//操作成功
}

//销毁顺序栈
Status DestroyStack(SqStack *S)
{
	if (!S->base)
	{
		free(S->base);//释放空间
		S->base = NULL;//置空指针，防止变成野指针
		S->top = NULL;
		S->StackSize = 0;
	}
	return OK;
};

//顺序栈的入栈
//1.判断栈是否满
//2.赋值
//3.top指针后移
Status Push(SqStack *S,SElemType e)
{
	if ((S->top - S->base) == S->StackSize)
		return ERROR;//判断是否栈满
	*S->top = e;
	S->top++;//*(S->top)++=e;
	return OK;
};

//顺序栈的出栈
//1.判断是否为空
//2.top指针下移
//3.取值
Status Pop(SqStack* S, SElemType* e)
{
	if (S->base == S->top)
		return ERROR;
	S->top--;
	*e = *S->top;
	return OK;
};

//-----------------------------------链栈--------------------------------------------
//定义链栈结构，运算受限的单链表
typedef struct StackNode
{
	SElemType data;
	struct StackNode* next;
}StackNode,*LinkStack;
//注意：链栈中指针的方向为栈顶指向栈底，表尾为栈顶，表头为栈底

//初始化链栈
Status InitStack_Link(LinkStack* S)//二级指针，指向链栈的头指针
{
	*S = NULL;//修改头指针指向
	return OK;
};

//判断链栈是否为空
Status StackEmpty_Link(LinkStack S)
{
	if (S == NULL)
		return TRUE;
	else
		return FALSE;
}

//链栈的入栈
Status Push_Link(LinkStack* S, SElemType e)
{
	StackNode* p = (StackNode*)malloc(sizeof(StackNode));
	if (p == NULL) return ERROR;
	p->data = e;
	p->next = *S;
	*S = p;
	return OK;
};

//链栈的出栈
Status Pop_Link(LinkStack* S, SElemType* e)
{
	if (*S==NULL)
		return ERROR;
	*e = (*S)->data;
	StackNode* p = *S;//保存当前结点，准备释放
	(*S) = (*S)->next;
	free(p);//删除结点，防止内存泄漏
	return OK;
};

//取栈顶元素
SElemType GetTop(LinkStack S)
{
	if(!S)
	return S->data;
};
//S指针指向栈顶元素


int main()
{

	return 0;
}
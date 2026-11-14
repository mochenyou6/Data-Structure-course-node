#define _CRT_SECURE_NO_WARNINGS 1

#define LIST_INIT_SIZE 100
#define MAXSIZE 1000
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2

#include<stdio.h>
#include<stdlib.h>

typedef int ElemType;
typedef int Status;

//---------------------------------顺序表--------------------------------------------
//定义顺序表的类型
// 静态内存表
//typedef struct SqList
//{
//	ElemType elem[LIST_INIT_SIZE];//线性表1的容量
//	int length;//当前长度
//}SqList;

typedef struct {
	ElemType* elem;
	int length;
}SqList;//顺序表类型

//多项式的顺序存储结构类型定义
typedef struct {
	float p;//系数
	int e;//指数
}Polynomial;

//typedef struct {
//	Polynomial* elem;//存储空间的基地址
//	int length;//多项式中当前项的个数
//}SqList;//多项式的顺序存储结构类型为SqList

//线性表的初始化
Status InitList_Sq(SqList * L) {
	L->elem = (ElemType*)malloc(sizeof(ElemType) * MAXSIZE);//为顺序表分配空间
	if (!L->elem) exit(OVERFLOW);//存储分配失败
	L->length = 0;//空表长度为0
	return OK;
};

//摧毁线性表L
void DestroyList_Sq(SqList* L) {
	if (!L)
		return;
	if (L->elem)
	{
		free(L->elem);//释放存储空间
		L->elem = NULL;
	}
	L->length = 0;
};

//清空线性表L
void ClearList(SqList* L) {
	L->length = 0;//将线性表置为空表
};

//求线性表的长度
int GetLength(SqList L) {
	return (L.length);
};

//判断线性表是否为空
int IsEmpty(SqList L) {
	if (L.length == 0)
		return 1;
	else
		return 0;
};

//根据位置i获得相应位置的取值
int GetElem(SqList L, int i, ElemType* e) {
	if (i<1 || i>L.length)
		return ERROR;//判断i值是否合理
	else
		*e = L.elem[i - 1];//第i-1个存储单元存储着第i个数据
	return OK;
};

//按值查找，找到返回其序号
int LocateELem(SqList L, ElemType e) {
	for (int i = 0; i < L.length - 1; i++)
		if (L.elem[i] = e)
			return (i + 1);
	return 0;//查找失败，返回0
};

//顺序表的插入
Status ListInsert_Sq(SqList* L, int i, ElemType e) {
	if (i<1 || i>(L->length + 1))
	{
		return ERROR;
	}
	int j = 0;//判断插入位置是否合法
	if (L->length == MAXSIZE)
		return ERROR;//判断是否满了
	for (j = L->length-1;j >= i-1; j--)
	{
		L->elem[j + 1] = L->elem[j];
	}//元素后移
	L->elem[i-1] = e;//插入
	L->length++;
	return OK;
};

//顺序表的删除
Status ListDelete_Sq(SqList* L, int i, ElemType* e) {
	if (i<1 || i>L->length)
		return ERROR;//判断i是否合法
	*e = L->elem[i - 1];//保存i值
	for (int j = i; j < L->length; j++)
	{
		L->elem[j-1] = L->elem[j];
	}//元素前移
	L->length--;//表长-1
	return OK;
}

//----------------------------链表-----------------------------------------
//定义链表结点
typedef struct LNode {
	ElemType data;//结点的数据域
	struct LNode* next;//结点的指针域

}LNode,*LinkList;//LinkList为指向结构体LNode的指针类型

//单链表的初始化
Status InitList_L(LinkList* L) {
	*L = (LNode *)malloc(sizeof(LNode));//开辟了头结点
	if (*L==NULL)
		return ERROR;//判断是否开辟成功
	(*L)->next = NULL;//初始化
	return OK;
}

//判断单链表是否为空（含有头结点）
int ListEmpty(LinkList L) {//若L为空表，则返回1，否则返回0
	if (L->next)//非空
		return 0;
	else
		return 1;
}

//单链表的销毁
Status DestroyList_L(LinkList* L) {
	LNode* p = NULL;
	while (*L)
	{
		p = *L;
		(*L) = (*L)->next;
		free(p);
	}
	return OK;
}

//单链表的清空
Status ClearList(LinkList* L) {
	LNode* p, * q;
	p = (*L)->next;
	while (p)//逐个释放
	{
		q = p->next;
		free(p);
		p = q;
	}
	(*L)->next = NULL;//头结点指针域置空
	return OK;
}

//求链表的表长
int Length_L(LinkList L) {
	int Len = 0;
	LNode* p = L->next;
	while (p)
	{
		Len++;
		p = p->next;
	}
	return Len;
}

//取单链表中第i个元素的内容
Status GetElem_L(LinkList L, int i, ElemType* e)
{
	int j=1;
	LNode* p = L->next;//初始化
	while (j < i && p)
	{
		p = p->next;
		j++;//向后扫描，直到p指向第i个元素
	}
	if (!p||j>i)
		return ERROR;//第i个元素不存在
	*e = p->data;//获取第i个元素
	return OK;
}

//按值查找-根据指定数据获得该数据所在的位置
LNode* LocateElem_L(LinkList L, ElemType e) {
	//找到返回值为e的数据元素地址，查找失败返回NULL
	LNode* p = L->next;
	while (p&&p->data!=e)
	{
		p=p->next;
	}
	return p;
}
	
//按值查找-找到位置序号
int LocateElem_Link(LinkList L, ElemType e)
{
	LNode* p = L->next;
	int j = 1;
	while (p && p->data != e)
	{
		p = p->next;
		j++;
	}
	if (p)
		return j;
	else
		return 0;
}

//在第i个结点前插入值为e的新结点
Status ListInsert(LinkList L,int i, ElemType e)
{
	LNode* p = L;
	int j = 0;
	while (p&&j<i-1)
	{
		p = p->next;
		j++;
	}//找到i-1这个结点
	if (!p||j>i-1)
		return ERROR;//插入位置非法
	LNode* s = (LNode*)malloc(sizeof(LNode));
	if (!s)
		return ERROR;
	s->data = e;
	s->next = p->next;
	p->next = s;//插入结点
	return OK;
}

//删除第i个结点
Status ListDelete_L(LinkList L, int i, ElemType* e)
{
	LNode* p, * q;
	p = L;
	int j = 0;
	while (p->next && j < i - 1)
	{
		p = p->next;
		j++;
	}//寻找第i-1个结点
	if (!(p->next) || j > i - 1)
		return ERROR;//位置不合理
	q = p->next;
	*e = q->data;//保存数据域
	p->next = q->next;
	free(q);//释放删除结点的空间
	return OK;
}

//单链表的建立——头插法
void CreatList_H(LinkList* L, int n) {
	(*L) = (LNode*)malloc(sizeof(LNode));//创建一个头结点
	(*L)->next = NULL;//初始化头结点
	for (int i = n; i > 0; i--)//循环插入结点
	{
		LNode* p = (LNode*)malloc(sizeof(LNode));//开辟一个结点空间
		scanf("%d", &(p->data));//输入一个结点数据域的值
		p->next = (*L)->next;
		(*L)->next = p;//改变结点指向，插入结点
	}
}

//单链表的建立--尾插法
void CreateList_R(LinkList L, int n)
{
	LNode* tail = L;//创建尾指针
	 for(int i=0;i<n;i++)//循环插入
	{
		LNode* p = (LNode*)malloc(sizeof(LNode));//开辟新结点的空间
		if (p == NULL)
			exit(OVERFLOW);
		p->next = NULL;//置空
		tail->next = p;//插入
		tail = p;//移动尾指针
	}

}

//---------------------------------------循环链表-----------------------------------------------
LinkList Connect(LinkList Ta, LinkList Tb)//将两个单循环链表连接在一起
{
	//假设Ta，Tb都是非空的单循环链表
	LNode* p = Ta->next;
	Ta->next = Tb->next->next;
	free(Tb->next);
	Tb->next = p;
	return Tb;

}

//-----------------------------------双向链表--------------------------------------------------
//双向链表的结点定义
typedef struct DuLNode {
	ElemType data;
	struct DuLNode* prior, * next;//双指针，即指向下一个结点，也指向上一个结点
}DuLNode,*DuLinkList;

//找到第i个位置的元素，并返回地址
DuLinkList GetElem_Dul(DuLinkList L, int i)
{
	DuLNode* p = L;
	for (int j = 0; j < i ; j++)
	{
		p = p->next;
	}
	return p;
}

//双向链表的插入
Status ListInsert_Dul(DuLinkList* L, int i, ElemType e)
{
	DuLNode* p;
	if (!(p = GetElem_Du(L, i)))
		return ERROR;//判断i位置是否合理
	DuLNode* q = (DuLNode*)malloc(sizeof(DuLNode));
	if (!p)
		exit(OVERFLOW);
	q->data = e;

	q->prior = p->prior;
	p->prior->next = q;
	p->prior = q;
	q->next = p;//断开四个指针，重塑
	return OK;
}

//双向链表的删除
Status ListDelete_DuL(DuLinkList* L, int i, ElemType* e)
{
	DuLNode* p;
	if(!(p=GetElem_Dul(*L,i)))
		return ERROR;
	*e = p->data;
	p->prior->next = p->next;
	p->next->prior = p->prior;
	free(p);
	return OK;
}

//线性表的合并
void union_L(LinkList* La, LinkList Lb)
{
	if (!La ||!Lb)//指针判断，为空则直接返回
		exit(1);//*La为空才代表空表，La为空只能代表没有表
	int La_len = Length_L(*La);
	int Lb_len = Length_L(Lb);//找到两个表的长度，便于插入
	for (int i = 1; i <= Lb_len; i++)//循环插入
	{
		int e = 0;
		GetElem_L(Lb, i, &e);
		if (!LocateElem_L(*La, e))//判断La中是否有相应的元素
		{
			ListInsert(*La,++ La_len, e);
		}
	}
}

//有序表合并--顺序表实现
void MergeList_Sq(SqList La, SqList Lb, SqList* Lc)
{
	ElemType* pa = La.elem;
	ElemType* pa_last = La.elem + La.length - 1;

	ElemType* pb = Lb.elem;//表头指针，用来遍历
	ElemType* pb_last = Lb.elem + Lb.length - 1;//表尾指针，便于判断是否全部读取

	ElemType* pc = Lc->elem;
	Lc->length = La.length + Lb.length;
	Lc->elem = (ElemType*)malloc(Lc->length * sizeof(ElemType));//创建一个新的顺序表

	while (pa <= pa_last && pb < pb_last)//当两个表都不为空的时候，挨个遍历
	{
		if (*pa >= *pb)
			*pc++ = *pb++;
		else
			*pc++ = *pa++;
	}

	while (pa <= pa_last)//Lb为空，直接逐个将La放入Lc中
	{
		*pc++ = *pa++;
	}

	while (pb <= pb_last)
	{
		*pc++ = *pb++;
	}
}
//链表实现合并有序表
void MergeList_L(LinkList* La, LinkList* Lb, LinkList* Lc)
{
	LNode* pa = (*La)->next;
	LNode* pb = (*Lb)->next;
	*Lc = *La;
	LNode* pc = *Lc;
	while (pa && pb)//此时两个指针都不为空
	{
		if (pa->data <= pb->data)//将小结点插入到pc后面
		{
			pc->next = pa;
			pc = pa;
			pa = pa->next;
			
		}
		else
		{
			pc->next = pb;//插入小结点
			pc = pb;//移动pc指针，方便下一次插入
			pb = pb->next;//移动pb指针，方便下一次判断
		}
		
	}
	pc->next = pa ? pa : pb;//插入剩余结点
	free(*Lb);//释放头指针
}

//案例分析
//稀疏多项式运算
typedef struct PNode
{
	float coef;//系数
	int expn;//指数
	struct PNode* next;
}PNode,*Polynomial_L;

//建立多项式的链表
void CreatePolyn(Polynomial_L* P, int n)
{
	(*P) = (PNode*)malloc(sizeof(PNode));//开辟头结点
	if (!*P)
		exit(OVERFLOW);
	(*P)->next = NULL;
	for (int i = 1; i <= n; i++)//循环插入n个数
	{
		PNode* s = (PNode*)malloc(sizeof(PNode));//为新结点开辟空间
		if (!s) exit(OVERFLOW);
		scanf("%f", &(s->coef));//输入系数
		scanf("%d", &(s->expn));//输入指数

		PNode* pre=*P;
		PNode* q = (*P)->next;
		while (q && q->expn < s->expn)//一直循环直到找到新结点的指数大于q所指结点指针的值
		{
			pre = q;
			q = q->next;
		}
		
		s->next = q;
		pre->next = s;//在pre和q指针之间插入s
	}
}
#include<math.h>
Polynomial_L* Plus(Polynomial_L* Pa, Polynomial_L* Pb)
{
	PNode* qa = (*Pa)->next;
	PNode* qb = (*Pb)->next;//利用qa和qb来遍历两个多项式的链表
	PNode* qc = *Pa;//利用qc来标记新链表，在Pa的基础上进行修改

	while (qa && qb)
	{
		if (qa->expn == qb->expn)//指数相等的情况
		{
			qa->coef = qa->coef + qb->coef;//系数先相加
			PNode* temp_qb = qb;//保留结点位置，在系数相加后，该结点失去作用，准备释放
			qb = qb->next;//后移指针
			if (fabs(qa->coef) < 1e-6)//float型和0进行判断可能会导致结果出错，所以采用绝对值来进行判断
			{
				PNode* temp = qa;//保留结点位置，准备释放
				qa = qa->next;
				qc->next = qa;
				free(temp);
			}
			else//系数不为0则后移指针
			{
				qc = qa;
				qa = qa->next;
			}
			free(temp_qb);
		}
		else if (qa->expn > qb->expn)//判断指数大小
		{
			qc->next = qb;
			qc = qb;
			qb = qb->next;
		}
		else
		{
			qc->next = qa;
			qc = qa;
			qa = qa->next;
		}

	}
	//当qa或者qb指针有一个为空时，将剩余的结点全部接在pc后面
	if (qa)
	{
		qc->next = qa;
	}
	else
	{
		qc->next = qb;
	}
	free(*Pb);//释放表Pb的头结点
	return Pa;//返回新多项式链表
}

//图书管理系统
//既可以用顺序表实现，也可以用单链表实现
//如果查找较多，则用顺序表
//如果插入和删除较多，则用单链表

//结构体定义
typedef struct Book
{
	char id[20];//ISBN
	char name[50];//书名
	int price;//价格
}Book;
//顺序表
//typedef struct {
//	Book* elem;
//	int length;
//}SqList;

//单链表
//typedef struct LNode {
//	Book data;
//	struct LNode* next;
//}LNode,*LinkList;

//这里写了上面就会报错，所以我先注释掉了
#define _CRT_SECURE_NO_WARNINGS 1
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

#define MAXLEN 255
//--------------------------------顺序串-------------------------------------
typedef struct {
	char ch[MAXLEN + 1];//存储串的一维数组，强调是字符型  为了算法的直观和方便，ch[0]会闲置不用
	int length;//串当前长度
}SString;

//------------------------------------链串----------------------------------
//链表—优点：操作方便    缺点：存储密度较低---->块链：将多个字符存放在一个结点中，以克服其缺点

//串的链式存储结构-->块链结构
#define chunksize 80//块的大小可由用户定义
typedef struct Chunk {
	char ch[chunksize];
	struct Chunk* next;
}Chunk;
 
typedef struct {
	Chunk* head, * tail;//串的头指针和尾指针
	int curlen;			//串的当前长度
}LString;				//字符串的块链结构

//现实生活中查找，匹配较多，所以串用顺序存储结构更加方便

//串的模式匹配算法
//BF算法
int Index_BF(SString S, SString T) {
	int i = 1;//指向S，遍历S
	int j = 1;//指向T，遍历T
	while (i <= S.length && j <= T.length)//设置边界条件
	{
		if (S.ch[i] == T.ch[j])//相等时指针后移
		{
			i++;
			j++;
		}
		else//不匹配时，主串指针后移一位，模式串指针回退到第一个
		{
			i = i - j + 2;//回退时 i-(j-1)是回退到匹配前的位置【（j-1）是模式串指针移动的次数】，再+1就是下一个位置
			j = 1;
		}
	}
	if (j > T.length)//这里不能有等号，如果S=“xab”,T="abc",当i越界退出循环时，此时j=T.length，如果这里有等于号，结果就会出错
		return i - T.length;
	else
		return 0;
}

//写法2
int Index_BF(SString S, SString T,int pos) {
	int i = pos;//指向S，从指定位置开始遍历
	int j = 1;//指向T，遍历T
	while (i <= S.length && j <= T.length)//设置边界条件
	{
		if (S.ch[i] == T.ch[j])//相等时指针后移
		{
			i++;
			j++;
		}
		else//不匹配时，主串指针后移一位，模式串指针回退到第一个
		{
			i = i - j + 2;//回退时 i-(j-1)是回退到匹配前的位置【（j-1）是模式串指针移动的次数】，再+1就是下一个位置
			j = 1;
		}
	}
	if (j > T.length)//这里不能有等号，如果S=“xab”,T="abc",当i越界退出循环时，此时j=T.length，如果这里有等于号，结果就会出错
		return i - T.length;
	else
		return 0;
}

//KMP算法
// 前面部分都一样，只是在处理i和j上不一样
#define MAXSIZE 1000;
int Index_KMP(SString S, SString T, int pos)
{
	int i = pos;//从指定位置开始匹配
	int j = 1;
	int next[1000];
	get_next(T, next);//先得到模式串的next数组
	while (i <= S.length && j <= T.length)//设置边界
	{
		if (j == 0 || S.ch[i] == T.ch[j])
		{
			i++, j++;
		}
		else
		{
			j = next[j];
		}
	}
	if (j > T.length)
		return i - T.length;
	else
		return 0;
}

void get_next(SString T, int next[])
{
	int i = 1;       // 进度：next[1..i] 已确定，本轮要算 next[i+1]
	int j = 0;       // j-1 = T[1..i-1] 的最长公共前后缀长度
					//（j 指向前缀的下一个待比较字符）
	next[1] = 0;     // 初始化：约定 next[1] = 0
	while (i < T.length)          // 填到 next[T.length] 为止
	{
		if (j == 0 || T.ch[i] == T.ch[j])
		{
			i++, j++;
			next[i] = j;   // 当前最长公共前后缀长度+1（即失配时 j 的跳转目标）
		}
		else
		{
			j = next[j];   // 不匹配，回退到次长的公共前后缀候选继续试
		}
	}
}

void get_nextval(SString T,int nextval[])
{
	int i = 1;
	int j = 0;
	nextval[1] = 0;
	while (i<T.length)
	{
		if (j == 0 || T.ch[i] == T.ch[j])
		{
			i++, j++;
			if (T.ch[i] != T.ch[j])
				nextval[i] = j;
			else
				nextval[i] = nextval[j];//更改的地方
		}
		else
			j = nextval[j];
	}
}

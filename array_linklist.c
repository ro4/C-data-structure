/*
Description: C语言数组实现链表
Author: FAN
Date: 2014/4/18
Blog: thefrp.sinaapp.com
*/

#include<stdio.h>
#include<stdlib.h>

typedef int ListItem;
typedef struct alist *List;
typedef struct alist{
	int n;	//链表元素个数
	int maxsize;	
	ListItem *table; //表元素数组
}Alist;

//定义接口
List ListInit(int size);	//初始化链表
int ListEmpty(List L);	//测试链表是否为空
int ListLength(List L);	//返回链表的长度
ListItem ListRetrieve(int k,List L);	//返回第K个元素
int ListLocate(ListItem x,List L);	//查找x元素所处的位置
void ListInsert(int k,ListItem x,List L);	//在K出插入x元素
ListItem ListDelete(int k,List L);	 //删除第K个元素
void PrintList(List L);		//打印全部元素
void FreeList(List L);	//释放malloc动态申请的内存，防止内存泄漏

//定义小函数

void Error(char *ch);
void ItemShow(ListItem li);

int main()
{
	int i ;
	List L = ListInit(10);
	for(i=0;i<L->maxsize;i++)
		ListInsert(i,i+3,L);
	printf("打印全部元素：\n");
	PrintList(L);
	printf("显示第五个元素：");
	ItemShow(ListRetrieve(5,L));
	printf("删除第五个元素：%d\n",ListDelete(5,L));
	printf("打印全部元素：\n");
	PrintList(L);

	FreeList(L);
	return 0;
}

void Error(char *ch)
{
	printf("%s\n",ch );
}

void ItemShow(ListItem li)
{
	printf("%d\n",li );
}

List ListInit(int size)
{
	List L = (List)malloc(sizeof *L);
	L->table = (ListItem*)malloc(size*sizeof(ListItem));
	L->maxsize = size;
	L->n = 0;
	return L;
}

int ListEmpty(List L)
{
	return L->n == 0;
}

int ListLength(List L)
{
	return L->n;
}

ListItem ListRetrieve(int k,List L)
{
	if(k<1||k>L->n)
		Error("out of bounds ");
	return L->table[k-1];
}

int ListLocate(ListItem x,List L)
{
	int i;
	for(i = 0;i<L->n;i++)
		if(L->table[i]==x) 
			return i;
	return 0;
}

void ListInsert(int k,ListItem x,List L)
{
	int i;
	if(k<0||k>L->n)
		Error("out of bounds ");
	if(L->n == L->maxsize)
		Error("out of Memeory");
	for(i=L->n-1;i>=k;i--)
		L->table[i+1]=L->table[i];
	L->table[k] = x;
	L->n++;
}

ListItem ListDelete(int k,List L)
{
	int i;
	ListItem x;
	x = L->table[k-1];
	if(k<0||k>L->n)
		Error("out of bounds");
	for(i=k;i<L->n;i++)
		L->table[i-1] = L->table[i];
	L->n--;
	return x;
}

void PrintList(List L)
{
	int i;
	for(i=0;i<L->n;i++)
		ItemShow(L->table[i]);
}

void FreeList(List L)
{
	free(L->table);
	free(L);
}

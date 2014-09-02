/**
Description: C语言冒泡排序，插入排序和选择排序的实现
Author: FAN
Date: 2014/4/19
Blog: thefrp.sinaapp.com
ps: 在vs2012正常运行
*/

#include<stdio.h>

typedef int Item;

//宏定义几个基本操作
#define less(A,B) (key(A)<key(B))
#define eq(A,B) (!less(A,B) && !less(B,A))
#define swap(A,B) {Item t = A; A = B; B = t}
#define compswap(A,B) if(less(B,A)) swap(A,B);

//定义函数接口
void bubble(Item a[],int l,int r);
void insertion(Item a[],int l,int r);
void selection(Item a[],int l,int r);

//定义插入排序和选择排序要用的子函数
void insert(Item a[],int l,int i);
int mini(Item a[],int l,int r);

int main()
{
	//todo
}

void bubble(Item a[],int l,int r)
{
	int i,j;
	for(i=l+1;i<=r;i++)
		for(j=i;j>1;j--)
			compswap(a[j-1],a[j]);
}

void insert(Item a[],int l,int i)
{
	Item v = a[i];
	while(i>l &&less(v,a[i-1]))
	{
		a[i] = a[i-1];
		i--;
	}
}

void insertion(Item a[],int l,int r)
{
	int i;
	for(i=l+1;i<r;i++)
		insert(a,l,i);
}

int mini(Item a[],int i,int r)
{
	int j;min = i;
	for(j = i+1;j<=r;j++)
		if(less(a[j],a[min]))
			min =j;
		return min;
}

void selection(Item a[],int l,int r)
{
	int i;
	for(i=l;i<r;i++)
	{
		int j = mini(a,i,r);
		swap(a[i],a[j]);
	}
}



// Eight_Queens.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <iostream>
using namespace std;
#define Number 8

static int kinds = 1, x[Number];

int fit(int i, int j)
{
	int ans = 1; //判断(i,j )处是否能放点,返回为 0时不可以,为 1时可以
	int a = i, b = j;
	while (b >= 1) { //同行
		b--;
		if (x[b] == a)
			ans = 0;
	}
	a = i; b = j; //左上斜对角 
	while ((b >= 1) && (a >= 1) && ans)
	{
		b--;
		a--;
		if (x[b] == a)
			ans = 0;
	}
	a = i; b = j; //左下斜对角 
	while ((b >= 1) && (a <= Number - 2) && ans)
	{
		b--;
		a++;
		if (x[b] == a)
			ans = 0;
	}
	return ans;
}

void ShowRes()
{ //输出结果
	printf("第 %d种排列方法:\n", kinds);
	for (int i = 0; i < Number; i++)
	{
		for (int j = 0; j < Number; j++)
		{
			if (j == x[i])
				printf("1");
			else
				printf("0");
		}
		printf("\n");
	}
	printf("\n");
	kinds++;
}

void Eight_Queen(int j)
{
	if (j == Number)
		ShowRes();
	for (int i = 0; i < Number; i++)
	{
		if (fit(i, j) == 1)
		{
			x[j] = i;
			Eight_Queen(j + 1);

		}
	}
}

int main()
{
	printf("##############################################################################\n");
	printf("八皇后问题：\n设8皇后问题的解为 (x1, x2, x3, …,x8), \n约束条件为：在8x8的棋盘上，其中任意两个xi 和xj不能位于棋盘的同行、同列及同对角线。\n要求用一位数组进行存储，输出所有可能的排列。\n");
	printf("##############################################################################\n");
	Eight_Queen(0);
	printf("八皇后问题一共有%d种可能的排列。\n", kinds - 1);
	system("pause");
    return 0;
}


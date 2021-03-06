// Sorting.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#pragma warning (disable:4996)

#define MAX 20
int length = 0;

void HalfSorting(int str[MAX])
{
	for (int i = 2; i <= length; ++i)
	{
		str[0] = str[i];
		int low = 1, high = i - 1;
		while (low <= high) {
			int m = (low + high) / 2;
			if (str[0] < str[m])
				high = m - 1;
			else
				low = m + 1;
		}
		for (int j = i - 1; j >= high + 1; --j)
			str[j + 1] = str[j];
		str[high + 1] = str[0];
	}
	printf("折半排序的结果为:\n");
	for (int i = 1; i <= length; i++)
		printf("%d\t", str[i]);
	printf("\n");
}

void Poping(int str[MAX])
{
	int temp;
	for (int j = 1; j <length; j++)
	{
		for (int i = 1; i <length; i++)
		{
			if (str[i] > str[i + 1])
			{
				temp = str[i];
				str[i] = str[i + 1];
				str[i + 1] = temp;
			}
		}
	}
	printf("冒泡排序结果是：\n");
	for (int i = 1; i <= length; i++)
		printf("%d\t", str[i]);
	printf("\n");
}

int Partition(int str[MAX], int low, int high)
{
	str[0] = str[low];
	int pivotkey = str[low];
	while (low < high)
	{
		while ((low < high) && (str[high] >= pivotkey))
			--high;
		str[low] = str[high];
		while ((low < high) && (str[low] <= pivotkey))
			++low;
		str[low] = str[high];
	}
	str[low] = str[0];
	return low;
}

void FastSorting(int str[MAX], int low, int high)
{
	int pivotkey;
	if (low < high)
	{
		pivotkey = Partition(str, low, high);
		FastSorting(str, low, pivotkey - 1);
		FastSorting(str, pivotkey + 1, high);
	}
}

void EasyChoosing(int str[MAX])
{
	int temp = 0, num = -1;
	for (int i = 1; i < length; ++i)
	{
		int min = 999;
		for (int j = i; j < length; j++)
		{
			if (str[j] < min)
			{
				min = str[j];
				num = j;
			}
		}
		if (i != num)
		{
			temp = str[i];
			str[i] = str[num];
			str[num] = temp;
		}
	}
	printf("简单选择排序的结果为:\n");
	for (int i = 1; i <= length; i++)
		printf("%d\t", str[i]);
	printf("\n");
}

void Merge(int str1[MAX], int str2[MAX], int i, int m, int n)
{
	int k, j;
	for (j = m + 1, k = i; i <= m && j <= n; ++k)
	{
		if (str1[i] <= str1[j])
			str2[k] = str1[i++];
		else
			str2[k] = str1[j++];
	}
	if (i <= m)
	{
		for (int p = i; p <= m; p++)
			str2[k++] = str1[p];
	}
	if (j <= n)
	{
		for (int p = j; p <= n; p++)
			str2[k++] = str1[p];
	}
}

void Msort(int str1[MAX], int str2[MAX], int s, int t)
{
	int str3[MAX];
	if (s == t)
		str2[s] = str1[s];
	else {
		int m = (s + t) / 2;
		Msort(str1, str3, s, m);
		Msort(str1, str3, m + 1, t);
		Merge(str3, str2, s, m, t);
	}
}

void CombineSorting(int str[MAX])
{
	Msort(str, str, 1, length);
	printf("归并排序的结果为：\n");
	for (int i = 1; i <=length; i++)
	{
		printf("%d\t", str[i]);
	}
	printf("\n");
}

void HeadAdjust(int str[MAX], int s, int m)
{
	int rc = str[s];
	for (int j = 2 * s; j <= m; j *= 2)
	{
		if (j < m&&str[j] < str[j + 1])
			++j;
		if (!(rc < str[j]))
			break;
		str[s] = str[j];
		s = j;
	}
	str[s] = rc;
}

void PileSorting(int str[MAX])
{
	int temp;
	for (int i = length / 2; i > 0; --i)
		HeadAdjust(str, i, length);
	for (int i = length; i > 1; --i)
	{
		temp = str[1];
		str[1] = str[i];
		str[i] = temp;
		HeadAdjust(str, 1, i - 1);
	}
	printf("堆排序的结果为:\n");
	for (int i = 1; i <= length; i++)
		printf("%d\t", str[i]);
	printf("\n");
}

int main()
{
	int j, str[MAX], cho;
	printf("请输入一组关键字序列:(以0结束)\n");
	scanf("%d", &str[1]);
	for (j = 2; str[j - 1] != 0; j++)
		scanf("%d", &str[j]);
	length = j - 2;
	while (1)
	{
		printf("请选择排序方式:(1为折半排序, 2为冒泡排序, 3为快速排序, 4为篱单查找排序,5为归并排序, 6为堆排序，0为退出)\n");
		scanf("%d", &cho);
		switch (cho)
		{
		case 1:
			HalfSorting(str);
			break;

		case 2:
			Poping(str);
			break;

		case 3:
		{
			FastSorting(str, 1, length);
			printf("快速排序的结果为：\n");
			for (int i = 1; i <= length; i++)
				printf("%d\t", str[i]);
			printf("\n");
			break;
		}

		case 4:
			EasyChoosing(str);
			break;

		case 5:
			CombineSorting(str);
			break;

		case 6:
			PileSorting(str);
			break;

		case 0:
			exit(0);

		}
	}
	system("pause");
    return 0;
}


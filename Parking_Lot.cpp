// Parking_Lot.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>

#define MAXLENGTH 4			//停车场车位数
#define price	1			//车辆停放时间按每分收的钱
#pragma warning (disable:4996)


typedef struct node {		//车辆节点
	char num[8];
	double money;
	int arrive_hour, arrive_minute;
	int leave_hour, leave_minute;
}CAR;		

typedef struct {			//停车场栈
	int x[MAXLENGTH];		//判断某车位有无车标志——1有车/0无车
	CAR *P[MAXLENGTH];		//车辆信息
	int length;				//停车场已有车数量
}Parking;			

typedef struct car {
	CAR *data;
	struct car *next;
}QueueNode;			//等待队列节点

typedef struct {
	QueueNode *head;
	QueueNode *rear;
}LinkQueueCar;			//等待队列内车节点


void InitParking(Parking *p);				//初始化停车场栈

void InitQueue(LinkQueueCar *Q);			//初始化等待队列

void PRINT(CAR *p);							//打印出站车的信息

void Arrival(Parking *p, LinkQueueCar *W);	//车辆到达

void Leave(Parking *pr, LinkQueueCar *W);	//车辆离开

void List(Parking *s);						//目前停车场状态

void InitParking(Parking *p)				//初始化停车场栈
{
	p->length = 0;
	for (int i = 0; i < MAXLENGTH; i++)
	{
		p->x[i] = 0;						//该车位无车
		p->P[i] = (CAR *)malloc(sizeof(CAR));
	}
}

void InitQueue(LinkQueueCar *Q)				//初始化等待队列
{
	Q->head = NULL;
	Q->rear = NULL;
	/*Q->head = (QueueNode *)malloc(sizeof(QueueNode));
	if (Q->head != NULL)
	{
		Q->head->next = NULL;
		Q->rear = Q->head;
	}*/
}

void PRINT(CAR *p)//打印出站车的信息
{
	printf("车牌号：%s\n", p->num);
	printf("进站时间为: %d : %d \n", p->arrive_hour, p->arrive_minute);
	printf("出站时间为: %d : %d \n", p->leave_hour, p->leave_minute);
	p->money = price  * (p->leave_hour - p->arrive_hour) ;
	printf("停车消费共：%lf元\n", p->money);
	free(p);
}

void Arrival(Parking *p, LinkQueueCar *W)//车辆到达
{
	CAR *c;
	c = (CAR*)malloc(sizeof(CAR));
	printf("请输入车牌号:\n");
	getchar();
	scanf("%s", &c->num);
	printf("请输入进站时间(如12：22，输入12 22，按24小时输入):\n");
	getchar();
	scanf("%d%d", &c->arrive_hour, &c->arrive_minute);
	if (p->length < MAXLENGTH)//车放入停车栈
	{
		for (int i = 0; i<MAXLENGTH; i++) {
			if (p->x[i] == 0)
			{
				p->x[i] = 1;
				printf("车辆在停车场第%d位置.\n", i + 1);
				p->P[i] = c;
				break;
			}
		}
		p->length++;		//停车栈车数量加一
	}
	else
	{
		QueueNode *t;//把车放在等待队列
		printf("该车须等待!\n");
		t = (QueueNode *)malloc(sizeof(QueueNode));
		t->data = (CAR*)malloc(sizeof(CAR));
		strcpy(t->data->num, c->num);
		t->data->arrive_hour = c->arrive_hour;
		t->data->arrive_minute = c->arrive_minute;
		t->data->leave_hour = c->leave_hour;
		t->data->leave_minute = c->leave_minute;
		t->data->money = c->money;
		t->data = c;
		t->next = NULL;
		if (W->head == NULL) {
			W->head = t;
			W->rear = t;
		}
		else if (W->head->next == NULL) {
			W->head->next = t;
			W->rear = t;
		}
		else {
			W->rear->next = t;
			W->rear = t;
		}
	}
}

void Leave(Parking *pr, LinkQueueCar *W) //车辆离开
{
	int room;
	if (pr->length > 0)
	{
		while (1)
		{
			printf("\n请输入车在车场的位置：");
			scanf("%d", &room);
			room -= 1;
			if (room >= 0 && room <= pr->length)
				break;
		}
		SYSTEMTIME sys;
		GetLocalTime(&sys);
		pr->P[room]->leave_hour = sys.wHour;
		pr->P[room]->leave_minute = sys.wMinute;
		PRINT(pr->P[room]);
		pr->x[room] = 0;
		pr->length--;
		if (W->head != NULL)
		{
			printf("请等待队列首位的车进入\n");
			//Arrival(pr, W);
			//int h,m;
			//CAR *c = (CAR*)malloc(sizeof(CAR));
			//c = W->head->data;
			/*h = W->head->data->arrive_hour;
			c->arrive_hour = h;
			m = W->head->data->arrive_minute;
			c->arrive_minute = m;
			strncpy(c->num, W->head->data->num, sizeof(c->num));*/
			pr->x[room] = 1;
			printf("车辆%s在停车场第%d位置.\n", W->head->data->num,room + 1);
			pr->P[room] = W->head->data;
			W->head = W->head->next;
			pr->length++;
		}
		else
			printf("等待队列里没有车.\n");
	}
	else
		printf("\n停车场里没有车\n");
}

void List(Parking *s)
{
	if (s->length > 0)
	{
		printf("\n目前停车信息如下:\n");
		printf("位置\t车牌号\t到达时间\n");
		for (int i = 0; i < s->length; i++)
			printf("%d\t%s\t%d:%d\n", i+1, s->P[i]->num, s->P[i]->arrive_hour, s->P[i]->arrive_minute);
		printf("\n");
	}
	else
		printf("停车场里没有车\n");
}


int main()
{
	printf("#####################################################################################\n");
	printf("某商场有一个100个车位的停车场，当车位未满时，等待的车辆可以进入并计时；\n当车位已满时，必须有车辆离开，等待的车辆才能进入；\n当车辆离开时计算停留的的时间，并且按照每小时1元收费。\n汽车的输入信息格式可以是（进入 / 离开，车牌号，进入 / 离开时间），\n要求可以随时显示停车场内的车辆信息以及收费历史记录。\n");
	printf("#####################################################################################\n");
	Parking myPark;
	LinkQueueCar Wait;		//等待队列
	InitParking(&myPark);
	InitQueue(&Wait);
	int ch;
	while (1)
	{
		printf("=========================================================\n");
		printf("1.车辆到达\n2.车辆离开\n3.当前状态\n4.退出\n");
		printf("请选择——");
		while (1)
		{
			scanf("%d", &ch);
			if (ch > 0 && ch < 5)
				break;
			else
				printf("\n输入错误，请重新输入：");
		}
		switch (ch)
		{
		case 1:
			Arrival(&myPark, &Wait);
			break;

		case 2:
			Leave(&myPark, &Wait);
			break;

		case 3:
			List(&myPark);
			break;

		case 4:
			exit(0);

		default:
			break;
		}
	}
	system("pause");
    return 0;
}


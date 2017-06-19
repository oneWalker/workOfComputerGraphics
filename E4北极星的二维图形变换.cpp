/////////////////////////////////////////////////////////
//程序名称：E4 北极星”图案的5种二维图形变换
//编译环境：visual studio 2012,EasyX_2014冬至版
//
////////////////////////////////////////////////////////
#include <graphics.h>      // 就是需要引用这个图形库
#include <math.h>
#include <cstring>
#include <stack>
#include <conio.h>
#include <iostream>
using namespace std;
#define PAI 3.1415926
typedef struct{
	float m[17][3];
}Matrix;

float xo[17], yo[17];

void delay(int n) 
{
	while (n>0) n--;
}

void mulMatrix(Matrix *m1, Matrix *m2)//计算矩阵的数组的具体的数组
{
	float t[17][3];
	for (int i = 0; i<17; i++)
	{
		for (int j = 0; j<3; j++)
		{
			t[i][j] = 0;
		}
	}
	for (int i = 0; i<17; i++)
	{
		for (int j = 0; j<3; j++)  
		{
			for (int k = 0; k<3; k++)
			{
				t[i][j] += (m1->m[i][k])*(m2->m[k][j]);
			}
		}
	}
	for (int i = 0; i<17; i++)
		for (int j = 0; j<3; j++)
			m1->m[i][j] = t[i][j];
}

void setpoint(float x, float y)//具体确定每个点的坐标
{
	float b = 0, r = 40;
	xo[0] = x; yo[0] = y;
	for (int i = 2; i <= 16; i = i + 2)
	{
		xo[i] = x + r*sin((i - 1)*PAI / 8 + b);
		yo[i] = y - r*cos((i - 1)*PAI / 8 + b);
	}

	xo[1] = x + 2.5*r*sin(b); xo[9] = x - 2.5*r*sin(b);
	yo[1] = y - 2.5*r*cos(b);yo[9] = y + 2.5*r*cos(b);
	for (int i = 3; i <= 15; i = i + 4)
	{
		xo[i] = x + 2 * r*sin((i - 1)*PAI / 8 + b);
		yo[i] = y - 2 * r*cos((i - 1)*PAI / 8 + b);
	}
	xo[5] = x + 1.5*r*cos(b);xo[13] = x - 1.5*r*cos(b);
	yo[5] = y + 2 * r*sin(b); yo[13] = y - 2 * r*sin(b);
	
}

void drawline(float x, float y)//对北极星进行画线
{
	 int i;
	 for (i = 1; i<16; i++)
	 {
		 line(xo[i], yo[i], xo[i + 1], yo[i + 1]);
	 }
	 line(xo[1], yo[1], xo[16], yo[16]);
	 for (i = 1; i <= 16; i++)
	 {
		 line(xo[0], yo[0], xo[i], yo[i]);
	 }
     
	

	setfillcolor(RED);
	for (i = 1; i<=16; i=i+2)
		floodfill((xo[0] + xo[i] + xo[i + 1]) / 3, (yo[0] + yo[i] + yo[i + 1]) / 3, RED);
	
}


void Translation(int x, int y, Matrix *m1)//平移函数
{
	cleardevice();
	Matrix *n = new Matrix;
	n->m[0][0] = 1;
	n->m[0][1] = 0;
	n->m[0][2] = 0;
	n->m[1][0] = 0;
	n->m[1][1] = 1;
	n->m[1][2] = 0;
	n->m[2][0] = -x;
	n->m[2][1] = -y;
	n->m[2][2] = 1;
	mulMatrix(m1, n);
	for (int i = 0; i <= 16; i++)
	{
		xo[i] = m1->m[i][0];
		yo[i] = m1->m[i][1];
	}
	drawline(xo[0], yo[0]);
	delay(4000000);
}

void Proportion(int d, Matrix *m1)//按照一定进行放大
{
	cleardevice();
	Matrix *n = new Matrix;
	n->m[0][0] = d;
	n->m[0][1] = 0;
	n->m[0][2] = 0;
	n->m[1][0] = 0;
	n->m[1][1] = d;
	n->m[1][2] = 0;
	n->m[2][0] = 0;
	n->m[2][1] = 0;
	n->m[2][2] = 1;
	mulMatrix(m1, n);
	for (int i = 0; i <= 16; i++)
	{
		xo[i] = m1->m[i][0];
		yo[i] = m1->m[i][1];
	}
	drawline(xo[0], yo[0]);
	delay(40000000);
}

void Shear(int x, Matrix *m1)//错切变换模型
{
	cleardevice();
	Matrix *n = new Matrix;
	n->m[0][0] = 1;
	n->m[0][1] = 0;
	n->m[0][2] = 0;
	n->m[1][0] = x;
	n->m[1][1] = 1;
	n->m[1][2] = 0;
	n->m[2][0] = 0;
	n->m[2][1] = 0;
	n->m[2][2] = 1;
	mulMatrix(m1, n);
	for (int i = 0; i <= 16; i++)
	{
		xo[i] = m1->m[i][0];
		yo[i] = m1->m[i][1];
	}
	drawline(xo[0], yo[0]);
	delay(40000000);
}

void Rotation(float x, Matrix *m1)//对北极星进行旋转
{
	cleardevice();
	Matrix *n = new Matrix;
	n->m[0][0] = cos(x);
	n->m[0][1] = sin(x);
	n->m[0][2] = 0;
	n->m[1][0] = -sin(x);
	n->m[1][1] = cos(x);
	n->m[1][2] = 0;
	n->m[2][0] = 0;
	n->m[2][1] = 0;
	n->m[2][2] = 1;
	mulMatrix(m1, n);
	for (int i = 0; i <= 16; i++)
	{
		xo[i] = m1->m[i][0];
		yo[i] = m1->m[i][1];
	}
	drawline(xo[0], yo[0]);
	delay(40000000);
}

void Symmetry(Matrix *m1)//对称函数
{
	cleardevice();
	setpoint(xo[0], yo[0]);
	drawline(xo[0], yo[0]);
	Matrix *n = new Matrix;
	n->m[0][0] = -1;
	n->m[0][1] = 0;
	n->m[0][2] = 0;
	n->m[1][0] = 0;
	n->m[1][1] = 1;
	n->m[1][2] = 0;
	n->m[2][0] = 0;
	n->m[2][1] = 0;
	n->m[2][2] = 1;
	mulMatrix(m1, n);
	for (int i = 0; i <= 16; i++)
	{
		xo[i] = m1->m[i][0];
		yo[i] = m1->m[i][1];
	}
	drawline(xo[0], yo[0]);
	delay(40000000);
}


void main()
{
	int i;
	xo[0] = 250;
	yo[0] = 250;
	initgraph(640,660);   // 这里和 TC 略有区别
	
	setbkcolor(WHITE);// 设置背景色为白色
	cleardevice();// 用背景色清空屏幕
	setcolor(RED);
	setpoint(xo[0], yo[0]);
	drawline(xo[0], yo[0]);
	Matrix *m = new Matrix;
	for (int i = 0; i <= 17; i++){
		m->m[i][0] = xo[i];
	}
	for (int i = 0; i <= 17; i++){
		m->m[i][1] = yo[i];
	}
	for (int i = 0; i <= 17; i++){
		m->m[i][2] = 1;
	}
	delay(4000000);//画出北极星的图像
	getch();
	Translation(100, 100, m);//进行平移
	getch();
	Translation(-100, -100, m);//平移回原来的位置
	getch();
	Shear(1, m);//进行错切变换
	getch();
	Shear(-1, m);//回到原位置
	getch();
	Translation(250, 250, m);//平移到原点附近进行旋转到视图位置
	Rotation(45, m);
	Translation(-250, -250, m);
	getch();
	Translation(250, 250, m);//回到原位置
	Rotation(-45, m);
	Translation(-250, -250, m);
	getch();	
	Proportion(2, m);//按照一定比例进行放大
	getch();
	Translation(320, 250, m);//将放大后的北极星进行对称变换
	Symmetry(m);
	Translation(-320, -250, m);
	getch(); 
	// 按任意键继续
	closegraph();          // 关闭图形界面
}
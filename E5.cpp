/////////////////////////////////////////////////////////
//程序名称：E5 绘制所示图形的三视图、正轴测投影
//编译环境：visual studio 2012,EasyX_2014冬至版
//
//遇到的问题：二维数组一定要赋初值，不然后面无法装进数组
////////////////////////////////////////////////////////
#include <graphics.h>      // 就是需要引用这个图形库
#include <math.h>
#include <cstring>
#include <stack>
#include <conio.h>
#include <iostream>
using namespace std;
float point[19][4] = {{0,0,42,1},{55,0,42,1},{55,0,10,1}, 
	{70,0,10,1},{70,0,0,1},{70,40,0,1},{0,40,0,1},
           {0,40,27,1},{0,30,27,1},{0,30,42,1},{10,30,42,1},
           {10,10,42,1},{55,10,42,1},{55,10,10,1},{30,10,10,1},
           {30,40,10,1},{20,40,27,1},{20,30,27,1},{70,40,10,1}};
 int edge[27][2] = {{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},
       {8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},
       {15,16},{16,17},{17,18},{1,10},{2,13},{3,14},{4,19},  
       {6,19},{8,17},{9,18},{11,18},{12,15},{16,19}};
float xo[19], yo[19],zo[19];
int E1,E2;
void DrawZ(){//主视图
	float TZ[19][4]={};
	int i,j,k;
	float Z[4][4]={{-1,0,0,0},{0,0,0,0},{0,0,-1,0},{100,0,50,1}};
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<4; j++)  
		{
			for (int k = 0; k<4; k++)
			{
				TZ[i][j] =TZ[i][j]+point[i][k]*Z[k][j];
			}
		}
	}
	for(int i=0;i<19;i++){
		for(int j=0;j<4;j++){
			TZ[i][j]=TZ[i][j]*3;
		}
	}
	for(int i=0;i<27;i++){
		    E1=edge[i][0]-1;
			E2=edge[i][1]-1;
			line(TZ[E1][0],TZ[E1][2],TZ[E2][0],TZ[E2][2]);
	}
}
void DrawC(){//侧视图
	int i,j,k;
	float TC[19][4]={};
	float C[4][4]={{0,0,0,0},{1,0,0,0},{0,0,-1,0},{150,0,50,1}};
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<4; j++)  
		{
			for (int k = 0; k<4; k++)
			{
				TC[i][j] =TC[i][j]+point[i][k]*C[k][j];
			}
		}
	}
	for(i=0;i<19;i++){
		for(int j=0;j<4;j++){
			TC[i][j]=TC[i][j]*3;
		}
	}
	for(i=0;i<27;i++){
		    E1=edge[i][0]-1;
			E2=edge[i][1]-1;
			line(TC[E1][0],TC[E1][2],TC[E2][0],TC[E2][2]);
	}
};
void DrawF(){//俯视图
	int i,j,k;
	float TC[19][4]={};
	float C[4][4]={{-1,0,0,0},{0,0,1,0},{0,0,0,0},{100,0,100,1}};
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<4; j++)  
		{
			for (int k = 0; k<4; k++)
			{
				TC[i][j] =TC[i][j]+point[i][k]*C[k][j];
			}
		}
	}
	for(i=0;i<19;i++){
		for(int j=0;j<4;j++){
			TC[i][j]=TC[i][j]*3;
		}
	}
	for(i=0;i<27;i++){
		    E1=edge[i][0]-1;
			E2=edge[i][1]-1;
			line(TC[E1][0],TC[E1][2],TC[E2][0],TC[E2][2]);
	}
};
void DrawM(){//主轴侧影图
	int i,j,k;
	float TC[19][4]={};
	float C[4][4]={{-0.707,0,0.408,0},{0.707,0,0.408,0},{0,0,-0.8165,0},{180,0,100,1}};
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<4; j++)  
		{
			for (int k = 0; k<4; k++)
			{
				TC[i][j] =TC[i][j]+point[i][k]*C[k][j];
			}
		}
	}
	for(i=0;i<19;i++){
		for(int j=0;j<4;j++){
			TC[i][j]=TC[i][j]*3;
		}
	}
	for(i=0;i<27;i++){
		    E1=edge[i][0]-1;
			E2=edge[i][1]-1;
			line(TC[E1][0],TC[E1][2],TC[E2][0],TC[E2][2]);
	}
};
void main()
{
	initgraph(640,480);   // 这里和 TC 略有区别
	
	setbkcolor(WHITE);// 设置背景色为白色
	cleardevice();// 用背景色清空屏幕
	setcolor(RED);
	DrawZ();//主视图
	DrawC();//侧视图
	DrawF();//俯视图
	DrawM();//主轴侧影图
	_getch(); 
	// 按任意键继续
	closegraph();          // 关闭图形界面
}
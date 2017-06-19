/////////////////////////////////////////////////////////
//程序名称：E6 画立方体的正轴测或透视消隐图
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
void Drawline(float x[][4]){ //绘制图形
	int i;
	for(i=0;i<27;i++){
		    E1=edge[i][0]-1;
			E2=edge[i][1]-1;
			line(x[E1][0],x[E1][2],x[E2][0],x[E2][2]);
	}

}
void MulMatrix(float m1[][4],float m2 [][4]){
	int i,j,k;
	float TC[19][4]={};
	float TR[19][4]={};
	float C[4][4]={{-0.707,0,0.408,0},{0.707,0,0.408,0},{0,0,-0.8165,0},{120,0,100,1}};//主轴侧影变换矩阵
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<4; j++)  
		{
			for (int k = 0; k<4; k++)
			{
				TC[i][j] =TC[i][j]+m1[i][k]*m2[k][j];
			}
		}
	}
	for (int i = 0; i<19; i++)
	{
		for (int j = 0; j<4; j++)  
		{
			for (int k = 0; k<4; k++)
			{
				TR[i][j] =TR[i][j]+TC[i][k]*C[k][j];
			}
		}
	}
	for(i=0;i<19;i++){
		for(int j=0;j<4;j++){
			TR[i][j]=TR[i][j]*3;
		}
	}
	Drawline(TR);
}
void Rotation(){
	int i;
	BeginBatchDraw();
	for(i=0;i<360;i++){
		float R[4][4]={{cos(i),sin(i),0,0},{-sin(i),cos(i),0,0},{0,0,1,0},{0,0,0,1}};
		//旋转变换矩阵（实际的旋转矩阵是Z轴的矩阵，但是由于最终变换是将其压制在XOZ平面，因此实际效果图是绕Y轴旋转）
		MulMatrix(point,R);
	    FlushBatchDraw();
		Sleep(100);
        cleardevice();
	}
	EndBatchDraw();
}
void main()
{
	initgraph(640,480);   // 这里和 TC 略有区别
	
	setbkcolor(WHITE);// 设置背景色为白色
	cleardevice();// 用背景色清空屏幕
	setcolor(RED);
	Rotation();
	_getch(); 
	// 按任意键继续
	closegraph();          // 关闭图形界面
}
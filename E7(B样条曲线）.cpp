/////////////////////////////////////////////////////////
//程序名称：E7 绘制B样条曲线以及特征多边形样式
//编译环境：visual studio 2012,EasyX_2014冬至版
//操作说明：启动程序，在页面上进行选取点的坐标，同时
//按下ctrl和鼠标左键则对点进行绘制，按鼠标右键或者说
//点击x图标则退出
////////////////////////////////////////////////////////
#include <graphics.h>      // 就是需要引用这个图形库
#include <math.h>
#include <cstring>
#include <stack>
#include <conio.h>
#include <iostream>
using namespace std;
#define N 10 
 float px[N],py[N];
void bsline(float x[],float y[],int m){//B样条曲线方程式
	 float a0,a1,a2,a3,b0,b1,b2,b3; 
      int k,dx,dy; 
      float i,t,dt; 
	  dt=1/(float)m; //设置采样间距，设置t的初始值
   for(k=0;k<m;k++) 
   { 
   if(k==0) 
   moveto(x[k]+100,300-y[k]); 
     lineto(x[k]+100,300-y[k]); 
   } 
   for(k=0;k<m-3;k++) //计算每个采样点的并用近似曲线
   { 
      a0=(x[k]+4*x[k+1]+x[k+2])/6; 
      a1=(x[k+2]-x[k])/2; 
      a2=(x[k]-2*x[k+1]+x[k+2])/2; 
      a3=-(x[k]-3*x[k+1]+3*x[k+2]-px[k+3])/6; 
 
      b0=(y[k]+4*y[k+1]+y[k+2])/6; 
      b1=(y[k+2]-y[k])/2; 
      b2=(y[k]-2*y[k+1]+y[k+2])/2; 
      b3=-(y[k]-3*y[k+1]+3*y[k+2]-y[k+3])/6; 
      for(i=0;i<m;i+=0.1) 
      { 
         t=i*dt; 
         dx=100+a0+a1*t+a2*t*t+a3*t*t*t; 
        dy=300-(b0+b1*t+b2*t*t+b3*t*t*t); 
         if(i==0.0) 
           moveto(dx,dy); 
         lineto(dx,dy); 
      } 
    } 
 }
void main() 
{ 
   initgraph(680,480); 
 
   setbkcolor(WHITE); 
   setcolor(RED); 
    int n=0;
	MOUSEMSG m;		// 定义鼠标消息
	int x1,y1,x2,y2;
	while(true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		switch(m.uMsg)
		{
			case WM_LBUTTONDOWN:
				// 如果点左键的同时按下了 Ctrl 键
				n++;
				if (m.mkCtrl)//按下ctrl建则进行画图
				{rectangle(m.x-1, m.y-1, m.x+1, m.y+1);
				   px[n-1]=m.x-100;
				   py[n-1]=300-m.y;
				   bsline(px,py,n);
				   n=0;
				}
				else
				{	// 画一个小方块并获得相应的鼠标点
					rectangle(m.x-1, m.y-1, m.x+1, m.y+1);
					px[n-1]=m.x-100;
					py[n-1]=300-m.y;
				}
				break;
			case WM_RBUTTONUP:
				return;	// 按鼠标右键退出程序
		}
	}
    _getch(); 
    closegraph(); 
} 

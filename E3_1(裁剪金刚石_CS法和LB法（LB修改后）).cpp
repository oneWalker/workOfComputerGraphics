/////////////////////////////////////////////////////////
//程序名称：E3_1编程实现直线段的裁剪算法（裁剪金刚石）（用Choen-Sutherlan法和Liang-Barsky直线裁剪方法）
//编译环境：visual studio 2012,EasyX_2014冬至版

////////////////////////////////////////////////////////
#include <graphics.h>      // 就是需要引用这个图形库
#include <cmath>
#include <cstring>
#include <stack>
#include <conio.h>
#include <iostream>
using namespace std;
#define maxn 25   	//定义是N边形的金刚石

float XL=320,XR=540,YT=240,YB=20;//定义裁剪区域的边界

const double pi=acos(-1);
int n,m,G[maxn][maxn],vis[maxn][maxn];
struct point{
	double x,y;
};
point p[maxn];
/////////////////////////////////////////////////////////////
///////////中点画线法///////////////////////////////////////
/*通过利用坐标的特性进行画线，碰到的问题主要是求斜率时缺少考
虑除数为0时会出现的异常程序中止，以及if条件语句中貌似只能够
进行单条语句判断，写成其他形式会造成少情况考虑不周的漏画*/
///////////////////////////////////////////////////////////
void MidLine(int x0,int y0,int x1,int y1,int color){//中点画线法
int a,b,delta1,delta2,d,x,y;float m;
   if (x1<x0){d=x0,x0=x1,x1=d;d=y0,y0=y1,y1=d;}//只探讨右半轴（x>0）的情况，左半轴交换未知数后类似
    a=y0-y1,b=x1-x0;if (b==0) m=-1*a*100;//避免当除数为0时所出现报错  
    else m=(float)a/(x0-x1);//m必须是浮点数
	x=x0,y=y0;  
    putpixel(x,y,color);         
    if (m>=0&&m<=1)  /*注：当m即斜率为0-1之间的情况下，不能写成（0<m<1）！=1（会导致少画线）或者0<m<1（会导致不能够进行判断），此时判别公式是
		*/
    {d=2*a+b;delta1=2*a,delta2=2*(a+b);  
     while (x<x1)  
     {  if (d<=0)    
	    {   x++,y++,d+=delta2;}  
        else    
		{   x++,d+=delta1;  }  
        putpixel(x,y,color);  
     }}  
    else if (m<=0&&m>=-1)   //注：当m即斜率为-1-0之间的情况下画线
    {d=2*a-b;delta1=2*a-2*b,delta2=2*a;  
     while (x<x1)  
     {  if (d>0) 
	    {   x++,y--,d+=delta1;}  
        else   
		{   x++,d+=delta2;  }  
        putpixel(x,y,color);  
     }  }  
    else if (m>1)  //注：当m即斜率大于1时的画线方法
    {d=a+2*b;delta1=2*(a+b),delta2=2*b;  
     while (y<y1)  
     {  if (d>0) 
	    {   x++,y++,d+=delta1;}  
        else    
		{   y++,d+=delta2;  }  
        putpixel(x,y,color);  
     }  }  
    else  //注：当m即斜率小于-1的画线情况
    {d=a-2*b;delta1=-2*b,delta2=2*(a-b);      
     while (y>y1)  
     {  if (d<=0)   
	     {   x++,y--,d+=delta2;}  
        else    
		{   y--,d+=delta1;  }  
        putpixel(x,y,color);  
     }
	}  
}
/////////////////////////////////////////////////////////////
///////////Choen-Sutherlan法///////////////////////////////////////
/*通过编码来进行判断和进行裁剪的方法*/
///////////////////////////////////////////////////////////
int encode(float x, float y, int *code) 
{ int c; 
  c=0;
  if (x<XL)c=c|1 ;
  else if (x>XR) c=c|2;
  if (y<YB)c=c|4;
  else if (y>YT) c=c|8;
  *code=c;
  return 0;
  }
int C_S_LineClip(float x1,float y1,float x2,float y2) 
{int code1,code2,code;
 float x,y;
 encode(x1,y1,&code1);
 encode(x2,y2,&code2);
 while (code1 !=0 || code2 != 0)
   {if ((code1 & code2) != 0) return 0;//显然不可见
    code=code1;
    if (code1==0) code=code2; 
	 if ((1 & code) != 0)//线段与窗口左边求交
      {x=XL;
       y=y1+(y2-y1)*(XL-x1)/(x2-x1);}
    else if ((2 & code) != 0)//线段与窗口右边进行求交
      {x=XR;
       y=y1+(y2 -y1)*(XR-x1)/(x2-x1);  }
    else if ((4 & code) != 0)//线段与窗口下边进行求交
      {y=YB;
       x=x1+(x2-x1)*(YB-y1)/(y2-y1);}
    else if ((8 & code) != 0)//线段与上边求交
      {y=YT;
       x=x1+(x2-x1)*(YT-y1)/(y2-y1);  }
	 if (code==code1)
      {x1=x; y1=y; encode(x,y, &code1); }
    else
      {x2=x; y2=y; encode(x,y, &code2); }    }
    MidLine(x1,y1,x2,y2,GREEN);
    return 0;    }
/////////////////////////////////////////////////////
//////////Liang-Barsky裁剪方法/////////////////////
/*该代码存在的情况下需要把CS裁剪算法进行注释掉才能够运行，并且画出的图形不是完美的*/
///////////////////////////////////////////////////
bool ClipT(float p,float q,float *u1,float *u2){
float r;
if(p<0){
	r=q/p;
	if(r>*u2) {return FALSE;}
	else if(r>*u1){ return *u1=r;return TRUE;}
}
else if(p>0){
	r=q/p;//修改两者应该一致或者相当于未交换
	if(r<*u1){return FALSE;}
	if(r<*u2){*u2=r;return TRUE;}
}
else{ if(q<0)return FALSE;
return TRUE;}
}
void LB_LineClip( float x1,float y1,float x2,float y2)
{
	float dx,dy,d;
   float u1=0;float u2=1;
	dx=x2-x1;
	dy=y2-y1;
	if(ClipT(-dx,x1-XL,&u1,&u2)) 
		if(ClipT(dx,XR-x1,&u1,&u2)) 
			if(ClipT(-dy,y1-YB,&u1,&u2))
				if(ClipT(dy,YT-y1,&u1,&u2))
					MidLine(x1+u1*dx,y1+u1*dy,x1+u2*dx,y1+u2*dy,GREEN);
}
/////////////////////////////////////////////////////
//////////BresenhamLine画线方法/////////////////////
/*与上面中点画法类似，但是里面遇到一个问题就是除数为0
不能够做类似公式化处理，必须进行人工赋予值*/
/*
void BresenhamLine(int x0,int y0,int x1,int y1,int color){//BresenhamLine画线方法
 int x,y,d,dx,dy,i;
 float m;
 if (x1<x0){d=x0,x0=x1,x1=d;d=y0,y0=y1,y1=d;}//只探讨右半轴（x>0）的情况，左半轴交换未知数后处理
 int e;
 dx=x1-x0;dy=y1-y0;
 if(dx==0)m=-5;//注：避免当除数为0时所出现报错，此次不能够用中点画线法的类似处理公式
 else m=(float)dy/dx;
 if(m>=0&&m<=1){//注：当m即斜率为0-1之间的情况
 e=-dx;x=x0;y=y0;
 for(i=0;i<=dx;i++)
 { putpixel(x,y,color);
   x++;e+=2*dy;
   if(e>=0)
   { y++;e-=2*dx;}
 }
}
else if(m<=0&&m>=-1){//注：当m即斜率为-1-0之间的情况下画线
  e=-dx;x=x0;y=y0;
 for(i=0;i<=dx;i++)
 { putpixel(x,y,color);
   x++;e-=2*dy;
   if(e>=0)
   { y--;e-=2*dx;}
 }
}
else if(m>1){//注：当m即斜率大于1时的画线方法
   e=-dy;x=x0;y=y0;
 for(i=0;i<=dy;i++)
 { putpixel(x,y,color);
   y++;e+=2*dx;
   if(e>=0)
   { x++;e-=2*dy;}
 }
 }
else//注：当m即斜率小于-1的画线情况
{
  e=-dy;x=x0;y=y0;
  for(i=0;i<=-dy;i++)
  { putpixel(x,y,color);
   y--;e+=2*dx;
   if(e>=0)
  { x++;e+=2*dy;
   }
   }
 }
}*/
void divide(int x,int y,int r){		//圆心是x,y,半径是r
	double thita=2.0*pi/maxn;
	for(int i=0;i<maxn;i++){
		double tem=i*thita;
		p[i].x=r*cos(tem)+x;
		p[i].y=r*sin(tem)+y;
	}
}
stack<int> s;

void euler(int u) //欧拉回路
{    
for(int v = 0; v <maxn; v++) if(G[u][v] && !vis[u][v]) 
{
     vis[u][v] = vis[v][u] = 1;  //定义为无向图  
     euler(v);  // 打印的顺序是逆序的：最先打印的边实际上应该最后经过     
     MidLine((int)p[u].x,(int)p[u].y,(int)p[v].x,(int)p[v].y,RED);//中点画线方法
     //BresenhamLine((int)p[u].x,(int)p[u].y,(int)p[v].x,(int)p[v].y,RED);// BresenhamLine画线方法
       //getch(); //加上这一句变成 手动
	//C_S_LineClip((int)p[u].x,(int)p[u].y,(int)p[v].x,(int)p[v].y);//Choen-Sutherlan法
    LB_LineClip( (int)p[u].x,(int)p[u].y,(int)p[v].x,(int)p[v].y);//Liang-Barsky直线裁剪方法
  } 
}
void main(){
	memset(G, 1, sizeof(G));
    initgraph(640, 480);   // 这里和 TC 略有区别
	divide(320,240,220);
    euler(0);//欧拉回路的构建
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}


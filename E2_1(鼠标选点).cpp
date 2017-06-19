/////////////////////////////////////////////////////////
//程序名称：通过鼠标选取坐标进行画线（用中点画线法和BresenhamLine画线方法）
//编译环境：visual studio 2012,EasyX_2014冬至版
////////////////////////////////////////////////////////
#include <graphics.h>
#include <conio.h>

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


/////////////////////////////////////////////////////
//////////BresenhamLine画线方法/////////////////////
/*与上面中点画法类似，但是里面遇到一个问题就是除数为0
不能够做类似公式化处理，必须进行人工赋予值*/
////////////////////////////////////////////////////
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
  { x++;e+=2*dy;}
   }
 }
}

void main()
{
	// 初始化图形窗口
	initgraph(640, 480);
	int n=0;
	MOUSEMSG m;		// 定义鼠标消息
	int x1,y1,x2,y2;
	while(true)
	{
		// 获取一条鼠标消息
		m = GetMouseMsg();

		switch(m.uMsg)
		{
			/*case WM_MOUSEMOVE:
				// 鼠标移动的时候画红色的小点
				putpixel(m.x, m.y, RED);
				break;*/

			case WM_LBUTTONDOWN:
				// 如果点左键的同时按下了 Ctrl 键
				n++;
				if (m.mkCtrl)
					// 画一个大方块
					rectangle(m.x-10, m.y-10, m.x+10, m.y+10);
				else
				{	// 画一个小方块
					rectangle(m.x-1, m.y-1, m.x+1, m.y+1);
				}
				if(n%2==1){
				x1=m.x;y1=m.y;
				}
				else	if(n%2==0){x2=m.x;y2=m.y;
				MidLine(x1,y1,x2,y2,RED);//选择中点画直线方法
				BresenhamLine(x1,y1,x2,y2,RED);//选择Bresenham画直线方法
				}
				break;
			case WM_RBUTTONUP:
				return;	// 按鼠标右键退出程序
		}
	}
	// 关闭图形窗口
	closegraph();
}

#include <graphics.h>      // 就是需要引用这个图形库
#include <conio.h>
#include<math.h>
#include<stdio.h>
#define PI 3.1415926
void main()
{    float t;    
    int x0=320,y0=240;    
    int n,i,j,r;    
	int x[50],y[50];   
   printf("Please input n(15<=n<=25) and r(100<r<=220)(advice):\n");    
   scanf("%d,%d",&n,&r);    
   initgraph(640,480);    
   setcolor(RED);      
     t=2*PI/n;       
	 for(i=0;i<n;i++)    
	 {        
		 x[i]=x0+r*cos(i*t);       
		 y[i]=y0+r*sin(i*t);   
	 }   
	 for(i=0;i<=n-2;i++)    
	 {        
		 for(j=i+1;j<=n-1;j++)               
	    line(x[i],y[i],x[j],y[j]);  
	 }    
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}

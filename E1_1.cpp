#include <graphics.h>      // 就是需要引用这个图形库
#include <conio.h>
void main()
{ 
   initgraph(640, 480);
   setcolor(RED);
   int x;
   for(x=160;x<=480;x+=20)
   { 
   line(160,240,x,120);
   line(x,120,480,240);
   line(480,240,x,360);
   line(x,360,160,240); 
	}
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}
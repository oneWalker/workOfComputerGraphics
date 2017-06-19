#include <graphics.h>      // 就是需要引用这个图形库
#include <conio.h>
void main()
{  
	initgraph(280,140); 
	setfillcolor(RED);
	int point1[]={100,0,128,0,48,80,150,80,170,100,0,100,100,0};
	solidpolygon((POINT*)point1, 6);
	setfillcolor(YELLOW);
    int point2[]={0,100,20,120,220,120,128,28,113,43,170,100,0,100};
	solidpolygon((POINT*)point2, 6);
	setfillcolor(BLUE);
    int point3[]={76,80,128,28,220,120,228,100,128,0,48,80,76,80};
	solidpolygon((POINT*)point3, 6);
    setcolor(RED); 
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}

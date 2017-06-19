/////////////////////////////////////////////////////////
//程序名称：一笔画金刚石
//编译环境：visual studio 2012,EasyX_2014冬至版

//
#include <graphics.h>      // 就是需要引用这个图形库
#include <cmath>
#include <cstring>
#include <stack>
#include <conio.h>
using namespace std;
#define maxn 5  				//定义是N边形的金刚石
const double pi=acos(-1);
int n,m,G[maxn][maxn],vis[maxn][maxn];
struct point{
	double x,y;
};
point p[maxn];
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
     line((int)p[u].x,(int)p[u].y,(int)p[v].x,(int)p[v].y);
    //getch(); 加上这一句变成手动
  } 
}  
void main(){
	memset(G, 1, sizeof(G));
    initgraph(640, 480);   // 这里和 TC 略有区别
	setcolor(RED);//设置画线的颜色
	divide(320,240,220);
	euler(0);
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}

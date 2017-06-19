
#include <graphics.h>      // 就是需要引用这个图形库
#include <cmath>
#include <cstring>
#include <stack>
#include <conio.h>
using namespace std;
#define maxn 11				//分成多少份
const double pi=acos(-1);
int w[maxn+4][maxn+4];
struct point{
	double x,y;
};
point p[maxn+4];
void divide(int x,int y,int r){		//圆心是x,y,半径是r
	double thita=2.0*pi/maxn;
	for(int i=0;i<maxn;i++){
		double tem=i*thita;
		p[i].x=r*cos(tem)+x;
		p[i].y=r*sin(tem)+y;
	}
}
stack<int> s;
void dfs(int x){
	s.push(x);
	for(int i=0;i<maxn;i++){
		if(w[i][x]){
		//	getchar();					//加上这句为手动模式，否则为自动模式
			line((int)p[x].x,(int)p[x].y,(int)p[i].x,(int)p[i].y);
			w[i][x]=w[x][i]=0;
			dfs(i);
			break;
		}
	}
}
void fleury(int x){
	s.push(x);
	int brige;
	while(!s.empty()){
		brige=1;
		for(int i=0;i<maxn;i++){
			if(w[i][s.top()]){
				brige=0;
				break;
			}
		}
		if(brige)
			s.pop();
		else{
			int tem=s.top();
			s.pop();
			dfs(tem);
		}
	}
}
void main(){
	memset(w,1,sizeof(w));
    initgraph(640, 480);   // 这里和 TC 略有区别
	divide(300,300,100);
	fleury(0);
    getch();               // 按任意键继续
    closegraph();          // 关闭图形界面
}
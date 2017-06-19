//先用鼠标点下点，点击“画线”，则将点利用抛物样条曲线画成一个环（运行前将项目属性里面的字符集【使用Unicode字符集】改成【使用多字符字符集】，否则“画线”将是乱码）
//叉掉窗口退出
#include<math.h>
#include<graphics.h>
#include<stdlib.h>
#include<stdio.h>

typedef struct mat{
	int m,n;
	double **value;
	mat(int mm,int nn):m(mm),n(nn){
		value=new double*[mm];
		for(int i=0;i<mm;i++)
			value[i]=new double[nn];
	}
	mat(int mm,int nn,double ** ptr):m(mm),n(nn){
		value=new double*[mm];
		for(int i=0;i<mm;i++)
			value[i]=new double[nn];
		for(int i=0;i<mm;i++)
			for(int j=0;j<nn;j++)
				value[i][j]=*((double*)ptr+i*nn+j);
	}
	mat(const mat& mat1){
		m=mat1.m;
		n=mat1.n;
		value=new double*[m];
		for(int i=0;i<m;i++){
			value[i]=new double[n];
			memmove(value[i],mat1.value[i],sizeof(double)*n);
		}
	}
	~mat(){
		for(int i=0;i<m;i++){
			delete[] value[i];
			value[i]=0;
		}
		delete[] value;
		value=0;
	}
	mat operator *(mat mat1){
		if(n!=mat1.m)
			exit(1);
		mat ans(m,mat1.n);
		for(int i=0;i<m;i++){
			for(int j=0;j<mat1.n;j++){
				ans.value[i][j]=0;
				for(int k=0;k<n;k++)
					ans.value[i][j]+=value[i][k]*mat1.value[k][j];
			}
		}
		return ans;
	}
}mat;

bool inrect(int x,int y,int left,int top,int right,int bottom){
	return x<=right&&x>=left&&y<=top&&y>=bottom;
}
#define RECT_(name_,left_,top_,right_,bottom_) RECT name_;\
	name_.left=left_;\
	name_.right=right_;\
	name_.top=top_;\
	name_.bottom=bottom_;
#define RECT_ARR_(rect) rect.left,rect.top,rect.right,rect.bottom

const int MM=200;
double point[100][2];int top=1;
int main(){
	initgraph(800,600);
	RECT_(button1,0,40,85,0)
	solidrectangle(RECT_ARR_(button1));
	settextstyle(30,20,0);
	outtextxy(0,0,LPCTSTR("画线"));
	mat m0(MM,4);
	for(int i=0;i<MM;i++){
		for(int j=0;j<4;j++){
			m0.value[i][j]=pow(i*0.5/(MM-1),3-j);
		}
	}
	double m1_array[4][4]={{-4,12,-12,4},{4,-10,8,-2},{-1,0,1,0},{0,1,0,0}};
	mat m1(4,4,(double**)m1_array);
	while(1){
		MOUSEMSG msg;
		msg=GetMouseMsg();
		if(msg.uMsg==WM_LBUTTONUP&&!inrect(msg.x,msg.y,RECT_ARR_(button1))){
			point[top][0]=msg.x;
			point[top++][1]=msg.y;
			solidcircle(msg.x,msg.y,3);
		}
		if(top>=4&&msg.uMsg==WM_LBUTTONUP&&inrect(msg.x,msg.y,RECT_ARR_(button1))){
			point[0][0]=point[top-1][0];
			point[0][1]=point[top-1][1];
			point[top][0]=point[1][0];
			point[top++][1]=point[1][1];
			point[top][0]=point[2][0];
			point[top][1]=point[2][1];
			mat k=m0*m1;
			for(int i=0;i<=top-3;i++){
				mat m2(4,2,(double**)(point+i));
				mat out=k*m2;
				for(int j=0;j<MM;j++)
					solidcircle(out.value[j][0],out.value[j][1],2);
			}
			top=1;
		}
	}

}
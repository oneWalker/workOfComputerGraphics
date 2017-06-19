//实验6，初步消隐，当面在视野时，显示其边
//http://wenku.baidu.com/link?url=jayIDSsqZwvwPhwIVgFEmqyf9kV0Y7gWIl6LElq6wItEXJNriN5KoibwUHFbQzBIQxEAQEllA3kGl7Ou1LqfDgXvJUoN6g2_4oLDOADEdP_
//http://wenku.baidu.com/link?url=xzs-47KpaaDgZ7k_tAqXCeoZNXsTuac1WOxa9O2-JPg-j7DbNAjOH4J-osQM9ViNBsC5gBi2bfgaAkVDYFTvudCf4BqaTkpYp15u-ak_WTe
//esayx冬至版
//运行叉掉窗口退出
#include<cstdio>
#include<graphics.h>
#include<vector>
#include<cmath>
#define PI 3.14159

typedef struct XYZH{
	union{
		struct{double x,y,z,h;};
		double xyzh[4];
	};
	XYZH(){}
	XYZH(double xx,double yy,double zz,double hh):x(xx),y(yy),z(zz),h(hh){}
}XYZH;

typedef struct Mat4_4{
	union{
		double value[4][4];
		struct {double v00,v01,v02,v03,v10,v11,v12,v13,v20,v21,v22,v23,v30,v31,v32,v33;};
	};
	Mat4_4(){}
	Mat4_4(XYZH v1,XYZH v2,XYZH v3,XYZH v4){
		for(int i=0;i<4;i++)
			value[0][i]=v1.xyzh[i];
		for(int i=0;i<4;i++)
			value[1][i]=v2.xyzh[i];
		for(int i=0;i<4;i++)
			value[2][i]=v3.xyzh[i];
		for(int i=0;i<4;i++)
			value[3][i]=v4.xyzh[i];
	}
	Mat4_4(double a[4][4]){
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++)
				value[i][j]=a[i][j];
	}
	Mat4_4 operator *(Mat4_4 m){
		Mat4_4 ans;
		for(int i=0;i<4;i++)
			for(int j=0;j<4;j++){
				ans.value[i][j]=0;
				for(int k=0;k<4;k++)
					ans.value[i][j]+=value[i][k]*m.value[k][j];
			}
		return ans;
	}
}Mat4_4;

typedef struct Matn_4{
	std::vector<XYZH> value;
	void push_back(XYZH xyzh){value.push_back(xyzh);}
	Matn_4 operator *(Mat4_4 m){
		Matn_4 ans;
		for(int i=0;i<value.size();i++){
			XYZH xyzh;
			for(int j=0;j<4;j++){
				double sum=0;
				for(int k=0;k<4;k++)
					sum+=value[i].xyzh[k]*m.value[k][j];
				xyzh.xyzh[j]=sum;
			}
			ans.value.push_back(xyzh);
		}
		return ans;
	}
}Matn_4;

void line_(int x1,int y1,int x2,int y2){
	line(x1,600-y1,x2,600-y2);
}

int main(){
	double point[20][4] = {{0,0,42,1},{55,0,42,1},{55,0,10,1}, 
	{70,0,10,1},{70,0,0,1},{70,40,0,1},{0,40,0,1},
           {0,40,27,1},{0,30,27,1},{0,30,42,1},{10,30,42,1},
           {10,10,42,1},{55,10,42,1},{55,10,10,1},{30,10,10,1},
	{30,40,10,1},{20,40,27,1},{20,30,27,1},{70,40,10,1},{0,0,0,1}};
	int edge[30][2] = {{1,2},{2,3},{3,4},{4,5},{5,6},{6,7},{7,8},
       {8,9},{9,10},{10,11},{11,12},{12,13},{13,14},{14,15},
       {15,16},{16,17},{17,18},{1,10},{2,13},{3,14},{4,19},  
	{6,19},{8,17},{9,18},{11,18},{12,15},{16,19},{20,1},{20,7},{20,5}};

	int d_index[60]={3,4,19,16,15,14,15,16,17,18,11,12,18,17,8,9,2,13,12,11,10,1,6,5,20,7,19,6,7,8,17,16,11,18,9,10,13,14,15,12,20,5,4,3,2,1,2,3,14,13,4,5,6,19,20,1,10,9,8,7};
	int m_index[12][2]={{1,6},{7,12},{13,16},{17,22},{23,26},{27,32},{33,36},{37,40},{41,46},{47,50},{51,54},{55,60}};
	int point_visible[20];
	memset(point_visible,0,sizeof(point_visible));

	Matn_4 m1;
	for(int i=0;i<20;i++)
		m1.value.push_back(XYZH(point[i][0],point[i][1],point[i][2],point[i][3]));

	double ang1=PI/4,ang2=PI/90*(35+16.0/60);
	double arr[4][4]={{cos(ang1),0,-sin(ang1)*sin(ang2),0},{-sin(ang1),0,-cos(ang1)*sin(ang2),0},{0,0,cos(ang2),0},{0,0,0,1}};
	Mat4_4 m_t1(arr);
	double arr2[4][4]={{3,0,0,0},
						{0,3,0,0},
						{0,0,3,0},
						{0,0,0,1}};
	Mat4_4 m_t2(arr2);
	m1=m1*m_t2;
	Matn_4 m1_backup=m1;

	double arr3[4][4]={{cos(PI/180),sin(PI/180),0,0},
						{-sin(PI/180),cos(PI/180),0,0},
						{0,0,1,0},
						{0,0,0,0}};
	double arr4[4][4]={{1,0,0,0},
						{0,cos(PI/180),sin(PI/180),0},
						{0,-sin(PI/180),cos(PI/180),0},
						{0,0,0,0}};
	Mat4_4 m_t3=//Mat4_4(XYZH(1,0,0,0),XYZH(0,1,0,0),XYZH(0,0,1,0),XYZH(-30,-10,-10,0))*
		Mat4_4(arr3);//*Mat4_4(arr4)*
		//Mat4_4(XYZH(1,0,0,0),XYZH(0,1,0,0),XYZH(0,0,1,0),XYZH(30,10,10,0));

	Matn_4 m2;
	

	Mat4_4 m_up=Mat4_4(XYZH(1,0,0,0),XYZH(0,0,-1,0),XYZH(0,0,0,0),XYZH(0,0,-20,0));
	Mat4_4 m_right=Mat4_4(XYZH(0,0,0,0),XYZH(-1,0,0,0),XYZH(0,0,1,0),XYZH(-20,0,0,0));
	Mat4_4 m_face=Mat4_4(XYZH(1,0,0,0),XYZH(0,0,0,0),XYZH(0,0,1,0),XYZH(0,0,0,0));

	initgraph(800,600);
	BeginBatchDraw();
	while(1){
		cleardevice();
		m1=m1*m_t3;
		m2=m1*m_t1;
		Sleep(10);
		memset(point_visible,0,sizeof(point_visible));
		for(int i=0;i<12;i++){
			int a=m_index[i][0]-1,b=m_index[i][1]-1;
			int t=d_index[a+1]-1,p=d_index[a+2]-1,q=d_index[a]-1;
			XYZH m(m2.value[p].x-m2.value[t].x,m2.value[p].y-m2.value[t].y,m2.value[p].z-m2.value[t].z,0),n(m2.value[q].x-m2.value[t].x,m2.value[q].y-m2.value[t].y,m2.value[q].z-m2.value[t].z,0);
			if(m.z*n.x-m.x*n.z>=0){
				for(int j=a;j<=b;j++)
					point_visible[d_index[j]-1]=1;
			}
		}
		for(int i=0;i<30;i++)
			if(point_visible[edge[i][0]-1]&&point_visible[edge[i][1]-1])
				line_((int)(m2.value[edge[i][0]-1].x)+400,(int)(m2.value[edge[i][0]-1].z)+300,(int)(m2.value[edge[i][1]-1].x)+400,(int)(m2.value[edge[i][1]-1].z)+300);
		FlushBatchDraw();
	}
	EndBatchDraw();

	getchar();getchar();
	return 0;



}
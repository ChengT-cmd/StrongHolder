#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>
#include <#.hpp>

#ifdef WIN32
#include <windows.h>
#endif
#define MAXN 101

#pragma GCC optimize(3)

using namespace std;

struct coordinate
{
	double x,z;
} loc[MAXN][2],res[MAXN*(MAXN-1)/2],circle;

double radius=0,matrix[3][3];
int n,cnt;

coordinate calc()
{
	matrix[0][1]=matrix[1][0]*matrix[2][2]-matrix[2][0]*matrix[1][2];
	matrix[0][2]=matrix[1][1]*matrix[2][0]-matrix[2][1]*matrix[1][0];
	return (coordinate)
	{
		matrix[0][1]/matrix[0][0],matrix[0][2]/matrix[0][0]
	};
}

double get_distance(coordinate a,coordinate b)
{
	return sqrt(pow(a.x-b.x,2)+pow(a.z-b.z,2));
}

bool In_Cir(coordinate point)
{
	return get_distance(point,circle)<=radius+0.001;
}

coordinate solve(double A1,double B1,double C1,double A2,double B2,double C2)
{
	if(A1*B2-A2*B1==0) return circle;
	return (coordinate)
	{
		(C1*B2-C2*B1)/(A1*B2-A2*B1),(A1*C2-A2*C1)/(A1*B2-A2*B1)
	};
}

void get_MinCir()
{
	double temp;
	for(int i=1; i<=cnt; i++)
		if(!In_Cir(res[i]))
		{
			circle.x=res[i].x,circle.z=res[i].z,radius=0;
			for(int j=1; j<i; j++)
				if(!In_Cir(res[j]))
				{
					circle.x=(res[i].x+res[j].x)/2.0,circle.z=(res[i].z+res[j].z)/2.0,radius=get_distance(res[i],circle);
					for(int k=1; k<j; k++)
						if(!In_Cir(res[k]))
						{
							circle=solve(2*(res[j].x-res[i].x),2*(res[j].z-res[i].z),pow(res[j].x,2)+pow(res[j].z,2)-pow(res[i].x,2)-pow(res[i].z,2),
							             2*(res[k].x-res[j].x),2*(res[k].z-res[j].z),pow(res[k].x,2)+pow(res[k].z,2)-pow(res[j].x,2)-pow(res[j].z,2));
							radius=get_distance(circle,res[k]);
						}

				}
		}

}

int main(int argc, char **argv)
{
//	#ifdef WIN32
//		system("color f0");
//	#endif
	cout<<"输入数据总数："; 
	//freopen("stronghold.txt","r",stdin);
	scanf("%d",&n);
	if(n<1)
	{
		#ifdef WIN32
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		#endif
		cout<<"[IOS/ERR]Invalid input operation: number out of expect!\n";
		#ifdef WIN32
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		#endif
		system("pause");
		exit(-2);
	}
	if(n>100)
	{
		#ifdef WIN32
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		#endif
		cout<<"[IOS/ERR]Invalid input operation:你辛苦了，可是用不到那么多数据!\n";
		#ifdef WIN32
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
		#endif
		system("pause");
		exit(-2);
	}
	for(int i=1; i<=n; i++)
	{
		cout<<"输入第"<<i<<"个数据的详细信息:";
		scanf("%lf%lf%lf%lf",&loc[i][0].x,&loc[i][0].z,&loc[i][1].x,&loc[i][1].z);
	}
	for(int i=1; i<=n; i++)
		for(int j=1; j<i; j++)
		{
			matrix[1][1]=loc[i][0].z-loc[i][1].z;
			matrix[1][2]=loc[i][1].x-loc[i][0].x;
			matrix[2][1]=loc[j][0].z-loc[j][1].z;
			matrix[2][2]=loc[j][1].x-loc[j][0].x;
			matrix[1][0]=loc[i][1].x*loc[i][0].z-loc[i][0].x*loc[i][1].z;
			matrix[2][0]=loc[j][1].x*loc[j][0].z-loc[j][0].x*loc[j][1].z;
			matrix[0][0]=matrix[1][1]*matrix[2][2]-matrix[1][2]*matrix[2][1];
			if(matrix[0][0]==0)continue;
			res[++cnt]=calc();
		}
	for(int i=1; i<=cnt; i++)
		printf("x=%.3lf,z=%.3lf\n",res[i].x,res[i].z);
	random_shuffle(res+1,res+cnt+1);
	get_MinCir();
	printf("\nThe final result is:\n");
	printf("x=%.3lf,z=%.3lf\nr=%.3lf\n",circle.x,circle.z,radius);
	fstream fout;
	fout.open(".\\outputfile.txt",ios::app | ios::app);
	if(fout.is_open())
	{
		time_t now=time(0);
		char* dt=ctime(&now);
		fout<<"Stronghold-BE:\n";
		fout<<dt<<endl;
		for(int i = 1;i <= cnt;i ++)
		{
			fout<<"x="<<res[i].x<<",z="<<res[i].z<<endl;
		}
		fout<<"\nThe final result is:\n";
		fout<<"x="<<circle.x<<",z="<<circle.z<<endl<<"r="<<radius<<"\n";
		#ifdef WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_GREEN);
		#endif
		cout<<"\nThe result saved successfully.Go \".\\outputfile.txt\" for more info.\n自动保存成功！查看\".\\outputfile.txt\"以获取此次及历史计算信息\n";
		fout<<"========================\n\n\n";
	}
	else
	{
		#ifdef WIN32
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		#endif
		cout<<"[DBG/STDERR]:File Not Found!\nPlease manual-save the final resuit!\nOr you will lose two(or more) ender-eye!\n[标准错误 类]自动保存无原因失败，请手动保存!\n";
	}
	#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	#endif
	system("pause");
	return 0;
}

/*
3
213.143 186.249 249.371 230.546
160.671 320.414 203.410 361.804
197.878 491.893 244.787 529.617

x=940.578,z=1075.704
x=972.749,z=1115.041
x=1022.559,z=1155.098

The final result is:
x=981.568,z=1115.401
r=57.062
*/


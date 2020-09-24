#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <ctime>
#include <fstream>
#include <iostream>

#ifdef WIN32
	#include <windows.h>
#endif
#define MAXN 101

using namespace std;

struct coordinate
{
	double x,z;
} loc[MAXN],res[MAXN*(MAXN-1)/2],circle;

double f[MAXN],radius=0;
int n,cnt;
const double pai=3.141592653589793238462643383279502884197169399375105820974944;

coordinate calc(int i,int j)
{
	coordinate result;
	result.x=(loc[i].x*cos(f[i])*sin(f[j])-loc[j].x*sin(f[i])*cos(f[j])+(loc[i].z-loc[j].z)*sin(f[i])*sin(f[j]))/sin(f[j]-f[i]);
	result.z=(loc[j].z*cos(f[i])*sin(f[j])-loc[i].z*sin(f[i])*cos(f[j])-(loc[i].x-loc[j].x)*cos(f[i])*cos(f[j]))/sin(f[j]-f[i]);
	return result;
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
	for(int i = 1;i <= cnt;i ++)
		if(!In_Cir(res[i]))
		{
			circle.x=res[i].x,circle.z=res[i].z,radius=0;
			for(int j = 1;j < i;j ++)
				if(!In_Cir(res[j]))
				{
					circle.x=(res[i].x+res[j].x)/2.0,circle.z=(res[i].z+res[j].z)/2,radius=get_distance(res[i],circle);
					for(int k = 1;k < j;k ++)
						if(!In_Cir(res[k]))
						{
							circle=solve(2*(res[j].x-res[i].x),2*(res[j].z-res[i].z),pow(res[j].x,2)+pow(res[j].z,2)-pow(res[i].x,2)-pow(res[i].z,2),
							             2*(res[k].x-res[j].x),2*(res[k].z-res[j].z),pow(res[k].x,2)+pow(res[k].z,2)-pow(res[j].x,2)-pow(res[j].z,2));
							radius=get_distance(circle,res[k]);
						}

				}
		}

}

int main(int argc ,char **argv)
{
//	if(!fout.is_open())
//	{
//		cout<<"[DBG/ERR]:Failed Open Output File!\n";
//		exit(-1);
//	}
	//freopen("stronghold.txt","r",stdin);
	cout<<"输入数据总数:";
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
	for(int i = 1;i <= n;i ++)
	{
		cout<<"输入第"<<i<<"个数据的详细信息:";
		scanf("%lf%lf%lf",&loc[i].x,&loc[i].z,&f[i]);
		f[i]*=pai/180.0;
	}
	for(int i = 1;i <= n;i ++)
		for(int j = 1;j < i;j ++)
		{
			if(f[i] == f[j])
			{
				continue;
			}
			res[++cnt] = calc(i,j);
		}
	for(int i = 1;i <= cnt;i ++)
	{
		printf("x=%.3lf,z=%.3lf\n",res[i].x,res[i].z);
	}
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
		fout<<"Stronghold-JE:\n";
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
		cout<<"[DBG/STDERR]:File Not Found!\nPlease manual-save the final resuit!\nOr you will lose two(or more) ender-eye!\n[标准错误 类]自动保存失败，请手动保存!\n";
	}
	#ifdef WIN32
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_BLUE);
	#endif
	system("pause");
	return 0;
}

/*****************************
4
-99.442 1028.999 118.2
-132.154 1112.965 129.0
-101.789 964.026 110.4
-165.525 874.021 99.3

x=-503.171,z=812.522
x=-489.586,z=819.806
x=-498.074,z=816.649
x=-486.503,z=821.459
x=-493.562,z=820.303
x=-484.069,z=821.857

The final result is:
x=-493.620,z=817.189
r=10.631
 ******************************/


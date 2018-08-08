#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <math.h>

using namespace std;

ifstream fin("world.in");
ofstream fout("world.out");
#define cin fin
#define cout fout

struct num
{
	int value,pos;
	num() { value=pos=0; }
};

num A[50006];
int b[50006],f[50006];
int sl[50006],sr[50006],bl[50006],br[50006];
long long ans1,ans2,ans;
int n;

bool _cmp(num a,num b)
{
	return a.value<b.value;
}
/*------------树状数组-------------*/
void add(int pos) //表示增加一个大小为pos(已离散化)的数 
{
	for (;pos<=n;pos+=(pos & (-pos))) f[pos]++;
}

long long ask(int pos) //询问比pos(已离散化)小的数的个数 
{
	int sum=0;
	for (;pos>0;pos-=(pos & (-pos))) sum+=f[pos];
	return sum;
}
/*---------------------------------*/
int main()
{
	int npos=1;
	cin >> n;
	for (int i=1;i<=n;i++) 
	{
		cin >> A[i].value;
		A[i].pos=i;  //记录原始位置 
	}
	sort(A+1,A+n+1,_cmp);
	for (int i=1;i<=n;i++) //离散化 
	{
		b[A[i].pos]=npos;
		if (A[i].value!=A[i+1].value) npos++; 
	}

	memset(f,0,sizeof f);
	for (int i=1;i<=n;i++)
	{
		sl[i]=ask(b[i]-1);  //处理i左边比TA小和大的数的个数 
		bl[i]=i-1-ask(b[i]);
		add(b[i]);
	}

	memset(f,0,sizeof f);
	for (int i=n;i>0;i--)
	{
		sr[i]=ask(b[i]-1); // 处理i右边比TA小和大的数的个数 
		br[i]=(n-i)-ask(b[i]);
		add(b[i]);
	}

	for (int i=1;i<=n;i++)
	{
		ans1+=sl[i]; //统计a的方案数 
		ans2+=bl[i]; //统计b的方案数 
	}
	ans=ans1*ans2;

	for (int i=1;i<=n;i++) //利用容斥原理去掉重复 
	{
		ans-=sr[i]*br[i]; //ac重复 
		ans-=bl[i]*br[i]; //ad重复
		ans-=sl[i]*sr[i]; //bc重复
		ans-=sl[i]*bl[i]; //bd重复
	}
	cout << ans << endl;
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

const double eps = 0.000001;
const int MAXN = 9;

int sign[MAXN],a[MAXN],b[MAXN];
bool _in[MAXN];

inline double calc(double v1,double v2,int s)
{
	return s==0?v1+v2:(s==1?v1-v2:(s==2?v1*v2:v1/v2));
}

bool check()
{
	double val;
	val=calc(calc(calc(a[0],a[1],sign[0]),a[2],sign[1]),a[3],sign[2]);
	if (abs(val-24)<=eps)
		return 1;
	val=calc(calc(a[0],a[1],sign[0]),calc(a[2],a[3],sign[2]),sign[1]);
	if (abs(val-24)<=eps)
		return 1;
	val=calc(calc(a[0],calc(a[1],a[2],sign[1]),sign[0]),a[3],sign[2]);
	if (abs(val-24)<=eps)
		return 1;
	val=calc(a[0],calc(calc(a[1],a[2],sign[1]),a[3],sign[2]),sign[0]);
	if (abs(val-24)<=eps)
		return 1;
	val=calc(calc(a[0],a[1],sign[0]),calc(a[2],a[3],sign[2]),sign[1]);
	if (abs(val-24)<=eps)
		return 1;
	val=calc(a[0],calc(a[1],calc(a[2],a[3],sign[2]),sign[1]),sign[0]);
	if (abs(val-24)<=eps)
		return 1;	
	return 0;		
}

bool dfs2(int k)
{
	if (k==3)
		return check();
	for (int i=0;i<4;i++)
	{
		sign[k]=i;
		if (dfs2(k+1))
			return 1;
	}
	return 0;
}

bool dfs1(int k)
{
	if (k==4)
		return dfs2(0);
	bool ans=0;
	for (int i=0;i<4;i++)
	{
		if (_in[i])
			continue;
		_in[i]=1;
		a[k]=b[i];
		ans|=dfs1(k+1);
		_in[i]=0;
	}
	return ans;
}

int main()
{
	freopen("24.in","r",stdin);
	freopen("24.out","w",stdout);

	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		for (int i=0;i<4;i++)
			scanf("%d",&b[i]);
		printf("%s\n",dfs1(0)?"Yes":"No");
	}
	return 0;
}

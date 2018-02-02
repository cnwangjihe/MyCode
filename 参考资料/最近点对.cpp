#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
using namespace std;
const int N = 105000;
struct node
{
	double zx,zy;
}xu[N],zhan[N],jie[N];
int top;
int n;
double ans;
int cmpx(struct node x,struct node y)
{
	return x.zx<y.zx;
}
int cmpy(struct node x,struct node y)
{
	return x.zy<y.zy;
}
double dis(struct node x,struct node y)
{
	double res=(x.zx-y.zx)*(x.zx-y.zx)+(x.zy-y.zy)*(x.zy-y.zy);
	res=sqrt(res);
	return res;
}
void Solve(int l,int r)
{
	if(l==r)
		return;
	int mid=(l+r)>>1;
	double zhong=xu[mid].zx;
	Solve(l,mid);
	Solve(mid+1,r);
	top=0;
	int i=l,j=mid+1,k=l;
	while(i<=mid && j<=r)
	{
		if(xu[i].zy<xu[j].zy)
		{
			jie[k++]=xu[i];
			if(zhong-xu[i].zx<ans)
				zhan[++top]=xu[i];
			i++;
		}
		else
		{
			jie[k++]=xu[j];
			if(xu[j].zx-zhong<ans)
				zhan[++top]=xu[j];
			j++;
		}
	}
	while(i<=mid)
	{
		jie[k++]=xu[i];
		if(zhong-xu[i].zx<ans)
			zhan[++top]=xu[i];
		i++;
	}
	while(j<=r)
	{
		jie[k++]=xu[j];
		if(xu[j].zx-zhong<ans)
			zhan[++top]=xu[j];
		j++;
	}
	for(i=l;i<=r;i++)
		xu[i]=jie[i];
	for(i=1;i<=top;i++)
	{
		for(j=i+1;j<=i+5 && j<=top;j++)
		{
			double now=dis(zhan[i],zhan[j]);
			if(now<ans)
				ans=now;
		}
	}
}
int main()
{
	scanf("%d",&n);
	int i;
	for(i=1;i<=n;i++)
		scanf("%lf%lf",&xu[i].zx,&xu[i].zy);
	sort(xu+1,xu+n+1,cmpx);
	ans=dis(xu[1],xu[2]);
	Solve(1,n);
	printf("%.3f\n",ans);
	return 0;
}

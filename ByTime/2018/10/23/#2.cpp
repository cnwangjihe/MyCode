#include <bits/stdc++.h>
using namespace std;

const int emth[13]={0,31,28,31,30,31,30,31,31,30,31,30,31};
int yr[10005],mth[15];
int grt;

int calc(int yy,int mm,int dd)
{
	if(yy==0) return mth[mm-1]+dd;
	return yr[yy-1]+mth[mm-1]+dd;
}

bool check(int x)
{
	if(x==1) return 0;
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return 0;
	return 1;
}

void solve()
{
	int yy,mm,dd,sum=0;
	scanf("%d-%d-%d",&yy,&mm,&dd);
	sum=calc(yy,mm,dd);
	sum=abs(sum-grt);
	cerr << yr[yy-1] << endl;
//	cerr<<yy<<" "<<mm<<" "<<dd<<" "<<sum<<" "<<grt<<" "<<endl;
	if(check(sum)) printf("Niubi\n");
	else printf("Haixing\n");
	
}

int main()
{
//	freopen("r.in","r",stdin);
//	freopen("r.out","w",stdout);
	
	yr[0]=366;
	for(int i=1;i<10000;i++)
	{
		if(i%100==0 && i%400!=0) yr[i]=yr[i-1]+365;
		else if(i%100==0) yr[i]=yr[i-1]+366;
		else if(i%4==0) yr[i]=yr[i-1]+366;
		else yr[i]=yr[i-1]+365;
	}
	for(int i=1;i<=12;i++)
		mth[i]=mth[i-1]+emth[i];
	
	grt=calc(1926,8,17);
	
	int t;
	scanf("%d",&t);
	while(t>0)
	{
		t--;
		solve();
	}
	
	
	return 0;
}

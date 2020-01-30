#include <bits/stdc++.h>
using namespace std;

const int mx=1e5+10;
const int oo=1e8+10;
int n,k,m,s;
int a[mx],sl[mx],sr[mx],vl[mx],vr[mx];

void init()
{
	scanf("%d%d%d%d",&n,&k,&m,&s);
	int x;
	for(int i=1;i<=n;i++) a[i]=oo,vl[i]=vr[i]=0;
	for(int i=0;i<m;i++) scanf("%d",&x),a[x]=-1;
}

queue<int> que;
stack<int> stk;

int cnt=0;

int main()
{
	freopen("reverse.in","r",stdin);
	freopen("reverse.out","w",stdout);
	
	init();
		
	a[s]=0;
	que.push(s);
	int u,half=(k-(k&1))>>1;
//	cerr << half << '\n';
	while(!que.empty())
	{
		u=que.front(); que.pop();
		int pos=-1;
		for(int i=u+1+(k&1),l=(u-half+1),r=(i+half-1);i<=n && i<=u+k-1 && r<=n;i+=2,l++,r++)
		{
		//	cerr << l << ' ' << r << endl;
			pos=i;
			if(l<1) continue;
			if(a[i]==-1) continue;
			if(a[i]<=a[u]+1 && vr[i] && i<sr[i]-2)
			{
				int tmp=(sr[i]-2-i)>>1;
				l+=tmp,r+=tmp;
				i=sr[i]-2;
				continue;
			}
			if(a[i]>a[u]+1) a[i]=a[u]+1,sr[i]=u+k-1,vr[i]=1,stk.push(i),que.push(i);//,cerr<<i<<" ";
		}
		if(pos!=-1)
			while(!stk.empty()) sr[stk.top()]=pos,vr[stk.top()]=1,stk.pop();
		pos=-1;
		for(int i=u-1-(k&1),l=(i-half+1),r=(u+half-1);i>=1 && i>=u-k+1 && l>=1;i-=2,l--,r--)
		{
			pos=i;	
			if(r>n) continue;
			if(a[i]==-1) continue;
			if(a[i]<=a[u]+1 && vl[i] && i>sl[i]+2)
			{
				int tmp=(i-sl[i]-2)>>1;
				l-=tmp,r-=tmp;
				i=sl[i]+2;
				continue;
			}			
			if(a[i]>a[u]+1) a[i]=a[u]+1,sl[i]=u-k+1,vl[i]=1,stk.push(i),que.push(i);//,cerr<<i<<" ";
		}
		if(pos!=-1)
			while(!stk.empty()) sl[stk.top()]=pos,vl[stk.top()]=1,stk.pop();
	}
	
	for(int i=1;i<=n;i++)
		if(a[i]==oo) printf("-1 ");
		else printf("%d ",a[i]);
	putchar('\n');
	
	return 0;
}

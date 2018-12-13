// Date    : 2018-12-12 19:56:30
// Author  : Wangjihe (wangjihe.mail@gmail.com)
// Link    : wangjihe.cf

#include <bits/stdc++.h>

using namespace std;


const int INF  = 100000009,
		  MAXN = 25,
		  MAXC = 320009;
const double eps = 1e-10;

struct Ttime
{
	int i,j,t;
	double v;
	Ttime(){i=j=t=0;}
	Ttime(int i,int j,int t,double v):i(i),j(j),t(t),v(v){}
};

Ttime s[MAXC];
int mp[MAXN][MAXN];
double ans=0;
double sx[MAXN],ex[MAXN],sy[MAXN],ey[MAXN],x[MAXN],y[MAXN],v[MAXN],r[MAXN],e[MAXN];
int _head[MAXC],_next[MAXC],_node[MAXC],_cur[MAXC];
int dis[MAXC];
double _val[MAXC];
int tp=0,fp=0,cnt,S,T;
int n,m;
queue<int> q;

int read()
{
	int sum=0;char c=getchar();
	while(!isdigit(c)) c=getchar();
	while(isdigit(c)) sum=sum*10+(c^48),c=getchar();
	return sum;
}

inline bool _cmp(Ttime A,Ttime B){return A.v<B.v;}

inline double pow2(double a) {return a*a;}

void refresh(double &x,double &y)
{
	double nx=x*cos(2)+y*sin(2),ny=y*cos(2)-x*sin(2);
	x=nx,y=ny;
	return ;
}

bool calc(int i,int j)
{
	int minus=(ex[i]-sx[i]<eps?-1:1);
	double k,tmp,a,b,c,x1,x2,delta,aacos,mint,maxt,vt;

	k=(ey[i]-sy[i])/(ex[i]-sx[i]+eps);
	tmp=ey[i]+eps-y[j]-k*ex[i];

	a=pow2(k)+1;
	b=2*k*tmp-2*x[j];
	c=pow2(tmp)+pow2(x[j])-pow2(r[i]);
	delta=pow2(b)-4*a*c;
	if (delta<-eps)
		return 0;

	x1=(-b+sqrt(delta))/(2*a);
	x2=(-b-sqrt(delta))/(2*a);
	aacos=sqrt(pow2(k)+1);

	vt=v[i]/aacos;

	x1=minus*(x1-sx[i])/vt;
	x2=minus*(x2-sx[i])/vt;

	mint=0;
	maxt=minus*(ex[i]-sx[i])/vt;

	x1=min(maxt,max(mint,x1));
	x2=min(maxt,max(mint,x2));
	if (x1>x2)
		swap(x1,x2);
	if (x2-x1<eps)
		return 0;
	s[tp++]=Ttime(i,j,1,x1),s[tp++]=Ttime(i,j,-1,x2);
	return 1;
}

void _connect(int a,int b,double v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

bool bfs()
{
	int u,v;
	for (int i=0;i<=cnt;i++)
		dis[i]=-1,_cur[i]=_head[i];
	while (!q.empty())
		q.pop();
	q.push(S);
	dis[S]=0;
	while (!q.empty())
	{
		u=q.front();
		q.pop();
		for (int i=_head[u];~i;i=_next[i])
		{
			v=_node[i];
			if (_val[i]>eps && !~dis[v])
				dis[v]=dis[u]+1,q.push(v);
		}
	}
	return ~dis[T];
}

double dfs(int u,double Max)
{
	if (u==T || Max<eps)
		return Max;
	double filled=0,got;
	int v;
	for (int &i=_cur[u];~i;i=_next[i])
	{
		v=_node[i];
		if (dis[v]!=dis[u]+1)
			continue;
		got=dfs(v,min(Max-filled,_val[i]));
		if (got>eps)
		{
			_val[i]-=got;
			_val[i^1]+=got;
			filled+=got;
			if (filled+eps>=Max)
				break;
		}
	}
	return filled;
}

int main()
{
	freopen("2732.in","r",stdin);
	freopen("2732.out","w",stdout);
	memset(_head,-1,sizeof _head);
	n=read(),m=read();
	S=m+1;T=m+2;cnt=T;
	for (int i=1;i<=n;i++)
		x[i]=read(),y[i]=read(),refresh(x[i],y[i]);
	for (int i=1;i<=m;i++)
	{
		sx[i]=read(),sy[i]=read(),ex[i]=read(),ey[i]=read(),v[i]=read(),r[i]=read(),e[i]=read();
		refresh(sx[i],sy[i]),refresh(ex[i],ey[i]);
		for (int j=1;j<=n;j++)
			calc(i,j);
	}
	sort(s,s+tp,_cmp);
	int ct=0;
	double tmp;
	bool flag;
	for (int i=1;i<=m;i++)
		_connect(S,i,e[i]),_connect(i,S,0);
	for (int i=0;i<tp;i++)
	{
		ct+=s[i].t;
		mp[s[i].i][s[i].j]+=s[i].t;
		if (i==tp-1)
			continue;
		if (s[i].v+eps<s[i+1].v)
		{
			if (!ct)
				continue;
			tmp=s[i+1].v-s[i].v;
			for (int j=1;j<=n;j++)
			{
				flag=0;
				for (int k=1;k<=m;k++)
					if (mp[k][j])
					{
						if (!flag)
						{
							cnt++;          
							_connect(cnt,T,tmp);
							_connect(T,cnt,0);
							flag=1;
						}
						_connect(k,cnt,INF);
						_connect(cnt,k,0);
					}
			}
		}
	}
	while (bfs())
		ans+=dfs(S,INF);
	printf("%.6f\n",ans);
	return 0;
}
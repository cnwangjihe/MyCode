#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100009;

struct Tnum{int v,i;};

Tnum b[MAXN],c[MAXN];
int qs[MAXN],js[MAXN],_in[MAXN],a[MAXN];
int n,m,ans,k1,k2;
int p1,p2,t1,s;

int findp(int p)
{
	int l=0,r=k1+1,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (b[mid].i>=p)
			r=mid;
		else
			l=mid;
	}
	return r;
}
int findv(int v)
{
	int l=0,r=k1+1,mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (b[mid].v>v)
			r=mid;
		else
			l=mid;
	}
	return l;
}

int findc(int v,int l,int r)
{
	l--,r++;
	int mid;
	while (l+1<r)
	{
		mid=(l+r)/2;
		if (c[mid].v<=v)
			l=mid;
		else
			r=mid;
	}
	return l;
}

inline int read()
{
	int tmp=0,w=1;
	char ch=0;
	while(ch<'0' || ch>'9') {if(ch=='-') w=-1;ch=getchar();}
	while(ch>='0' && ch<='9') tmp=(tmp<<1)+(tmp<<3)+ch-'0',ch=getchar();
	return tmp*w;
}

int main()
{
//	int st=clock();
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int T;
	T=read();
	for (int cn=1;cn<=T;cn++)
	{
		n=read(),m=read();
		ans=0;
		k1=0,k2=0,b[0].v=-1;
		memset(_in,0,sizeof _in);
		memset(qs,0,sizeof qs);
		memset(js,0,sizeof js);
		c[0].v=-1;
		int last=0;
		for (int i=1;i<=n;i++)
		{
			a[i]=read();
			if (a[i]<=b[k1].v) 
			{
				if (a[i]>b[k1-1].v && a[i]>c[k2].v)
				{
					k2++;
					if (qs[b[k1].i]==0)
						last=b[k1].i,qs[last]=k2;
					c[k2].v=a[i],c[k2].i=i;
				}
			}
			else
			{
				k1++,ans++;
				b[k1].v=a[i],b[k1].i=i;
				if (last>0) 
					js[last]=k2;
				_in[i]=k1;
			}
		}
		if (last>0)
			js[last]=k2;
		int pos,v,tmp;
		for (int i=1;i<=m;i++)
		{
			pos=read(),v=read();
			if (v<=a[pos])
			{
				if (_in[pos])
				{
					if (v>b[_in[pos]-1].v)
						tmp=v,s=1;
					else
						tmp=b[_in[pos]-1].v,s=0;
					if (qs[pos])
						printf("%d\n",ans-1+s+(js[pos]-findc(tmp,qs[pos],js[pos])));
					else
						printf("%d\n",ans-1+s);
				}
				else
					printf("%d\n",ans);
			}
			else
				printf("%d\n",(findp(pos)>findv(v)+1)?ans:ans-(findv(v)-findp(pos)));
		}
	}
//	cerr << "time: "<< clock()-st << endl;
	return 0;
}

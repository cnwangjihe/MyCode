#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

const int MAXN = 10009,
		  MAXM = MAXN*2;

int _head[MAXN],_node[MAXM],_val[MAXM],_next[MAXM];
int s[MAXN],f[MAXN],q[MAXN],ans[MAXN],dep[MAXN];
int size,root,n,k,fp,tp;
bool done[MAXN];

bool read(int &x){  
    x=0;char c=getchar();  
    while(c<'0' || c>'9')c=getchar();  
    while(c>='0' && c<='9'){  
        x=x*10+c-'0';  
        c=getchar();  
    }   
    return 1;
}  
void write(int x){  
    if(x==0){putchar(48);return;}  
    int len=0,dg[20];  
    while(x>0){dg[++len]=x%10;x/=10;}  
    for(int i=len;i>=1;i--)putchar(dg[i]+48);  
}  

void _connect(int a,int b,int v)
{
	_next[fp]=_head[a];
	_node[fp]=b;
	_val[fp]=v;
	_head[a]=fp++;
	return ;
}

void _getroot(int u,int fa,int size)
{
	int v;
	s[u]=1,f[u]=0;
	for (int i=_head[i];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa || done[v])
			continue;
		_getroot(v,u,size);
		s[u]+=s[v];
		f[u]=max(f[u],s[v]);
	}
	f[u]=max(f[u],size-s[u]);
	if (f[u]<f[root])
		root=u;
	return ;
}

void _getdeep(int u,int fa)
{
	int v;
	q[tp++]=dep[u];
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (v==fa || done[v])
			continue;
		dep[v]=dep[u]+_val[i];
		_getdeep(v,u);
	}
	return ;
}

int calc(int u,int d)
{
	int ans=0;
	tp=0;
	dep[u]=d;
	_getdeep(u,0);
	sort(q,q+tp);
	int j=tp-1;
	for (int i=0;i<j;i++)
	{
		while (i<j && q[i]+q[j]>k)
			j--;
		ans+=j-i;
	}
	return ans;
}

int solve(int u,int size)
{
	int v;
	root=u;
	_getroot(u,0,size);
	u=root;
//	cerr << u << endl;
	done[u]=1;
	ans[u]=calc(u,0);
	for (int i=_head[u];~i;i=_next[i])
	{
		v=_node[i];
		if (done[v])
			continue;
		ans[u]-=calc(v,_val[i]);
		ans[u]+=solve(v,s[v]);
	}
	return ans[u];
}

int main()
{
	int a,b,v;
	while (read(n) && read(k) && n && k)
	{
//		scanf("%d",&n);
		fp=0;
		memset(done,0,sizeof done);
		memset(_head,-1,sizeof _head);
		for (int i=1;i<n;i++)
		{
			read(a);
			read(b);
			read(v);
			_connect(a,b,v);
			_connect(b,a,v);
		}
//		scanf("%d",&k);
		write(solve(1,n)); 
		putchar('\n');
	}
	return 0;
}
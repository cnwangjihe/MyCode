#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

struct Tnode
{
	int C[2],size;
	Tnode()
	{
		C[0]=C[1]=-1;
		size=0;
	}
};

const int MAXN = 100009,
		  MAXM = 32;

Tnode t[MAXN*MAXM];
int a[MAXN];
bool rev[MAXM];
int n,fp=1,k;
long long ans=0;

int _new() {return fp++;}

void _add(int v)
{
	int u=0;
	for (int i=(1<<30),j=30;i;i>>=1,j--)
	{
		t[u].size++;
		if (~t[u].C[((i&v)!=0)^rev[j]])
			u=t[u].C[((i&v)!=0)^rev[j]];
		else
			t[u].C[((i&v)!=0)^rev[j]]=_new(),
			u=t[u].C[((i&v)!=0)^rev[j]];
	}
	t[u].size++;
	return ;
}

void _reverse(int v)
{
	for (int i=(1<<30),j=30;i;i>>=1,j--)
	{
		if (!(v&i)) continue;
		rev[j]^=1;
	}
	return ;
}

int _ask(int v)
{
	int ans=0,u=0;
	for (int i=(1<<30),j=30;i;i>>=1,j--)
	{
		if ((i&v) && (~t[u].C[rev[j]]))
			ans+=t[t[u].C[rev[j]]].size;
		if (~t[u].C[((i&v)!=0)^rev[j]])
			u=t[u].C[((i&v)!=0)^rev[j]];
		else break;
	}
	return ans;
}
/*
void _check(int u,int k,int c,int j)
{
	if (u==-1) return ;
	printf("%d:%d\n",k+c*(1<<j),t[u].size);
	_check(t[u].C[0],k+c*(1<<j)+c,0,j-1);
	_check(t[u].C[1],k+c*(1<<j),1,j-1);
}
*/
int main()
{
	freopen("bit.in","r",stdin);
	freopen("bit.out","w",stdout);
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for (int i=1;i<=n;i++)
	{
		if (i!=1) _reverse(a[i]);
	//	cout << _ask(k) << '\n';
	//	for (int j=0;j<32;j++) cout << rev[j] << ' ';
		_add(a[i]);
	//	_check(0,0,0,31);
	//	cout << '\n';
	//	cout << _ask(k) << '\n';
	//	cerr << "rev[2]:" << rev[2] << '\n';
		ans=ans+(long long)_ask(k);
	}
	printf("%I64d\n",ans);
	return 0;
}

#include <bits/stdc++.h>

using namespace std;

const int MAXN = 59;

map <long long,int> cnt;
long long b[MAXN],a,t;
int n,m,k,k1,k0;
bool done;

long long Getv(long long a)
{
	/*
	long long b=0,t;
	while (a)
	{
		t=a&(-a);
		b+=t-1ll;
		a^=t;
	}*/
	long long b=0;
	for (long long i=m-1;~i;i--)
		b=(b<<1ll)+((a&(1ll<<i))?0:1);
	return b;
}

void print(long long a)
{
	for (int i=m-1;~i;i--)
		putchar((a&(1ll<<i))?'Y':'N');
	putchar('\n');
	return ;
}

bool _cmp(long long a,long long b) {return a<b;}

int main()
{
//	freopen("2615.in","r",stdin);
//	freopen("2615.out","w",stdout);
	int ttt;
	char ch;
	scanf("%d",&ttt);
	for (;ttt--;)
	{
		done=0,k=0;
		cnt.clear();
		scanf("%d%d%d%d",&n,&m,&k1,&k0);
		for (int i=1;i<=n;i++)
		{
			a=0;
			for (int j=0;j<m;j++)
			{
				do {ch=getchar();}
					while (ch!='Y' && ch!='N');
				a=(a<<1ll)+(ch=='Y'?1ll:0);
			}
			cnt[a]++;
			b[k++]=a;
		}
		sort(b,b+k,_cmp);
		for (int i=0;i<k;i++)
		{
			t=Getv(b[i]);
			cerr << t << endl;
			if (cnt[b[i]]==k1 && cnt[t]==k0)
			{
				print(b[i]);
				done=1;
				break;
			}
		}
		for (int i=0;i<k;i++)
			cnt[b[i]]=0;
		if (!done)
			printf("-1\n");
	}
	return 0;
}
#include <bits/stdc++.h>

using namespace std;

const int MAXN = 100000,
		  MOD1 = 19260817,
		  MOD2 = 49491001,
		  k1   = 30,
		  k2   = 32;

int _head[MOD1],_next[20000000],_val[20000000];
char s[MAXN];
int n,ans=0,fp=0;

inline bool iscorrect(char c)
{
	if (c==EOF)
	{
		printf("%d\n",ans);
		exit(0);
	}
	return (c>='a' && c<='z') || c=='.' || c=='@';}

inline bool Put(int v1,int v2)
{
	for (int i=_head[v1];~i;i=_next[i])
		if (v2==_val[i])
			return 0;
	_next[fp]=_head[v1];
	_val[fp]=v2;
	_head[v1]=fp++;
	return 1;
}

int main()
{
	memset(_head,-1,sizeof _head);
	freopen("2680.in","r",stdin);
	freopen("2680.out","w",stdout);
	bool ext;
	int v1,v2,i,j;
	while (1)
	{
		n=0;
		do {s[n]=getchar();}
			while (!iscorrect(s[n]));
		do {s[++n]=getchar();}
			while (iscorrect(s[n]));
		for (i=0;i<n;i++)
		{
			if (s[i]=='.' || s[i]=='@')
				continue;
			ext=0;
			v1=v2=0;
			for (j=i;j<n;j++)
			{
				if (ext)
				{
					if (s[j]=='@')
						break;
					if (s[j]=='.')
					{
						if (s[j+1]=='.')
							break;
						v1=((v1*k1)%MOD1+27)%MOD1;
						v2=((v2*k2)%MOD2+27)%MOD2;
						continue;
					}
					v1=((v1*k1)%MOD1+s[j]-'a'+1)%MOD1;
					v2=((v2*k2)%MOD2+s[j]-'a'+1)%MOD2;
					ans+=Put(v1,v2);
				}
				else
				{
					if (s[j]=='@')
					{
						ext=1;
						v1=((v1*k1)%MOD1+28)%MOD1;
						v2=((v2*k2)%MOD2+28)%MOD2;
						if (s[j+1]=='.' || s[j-1]=='.')
							break;
						continue;
					}
					if (s[j]=='.')
					{
						if (s[j+1]=='.')
							break;
						v1=((v1*k1)%MOD1+27)%MOD1;
						v2=((v2*k2)%MOD2+27)%MOD2;
						continue;
					}
					v1=((v1*k1)%MOD1+s[j]-'a'+1)%MOD1;
					v2=((v2*k2)%MOD2+s[j]-'a'+1)%MOD2;
				}
			}
		}
	}
	return 0;
}
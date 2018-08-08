#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <stdio.h>
#include <string.h>
#include <map>

using namespace std;

const int MAXN = 151,
		  MAXL = 41,
		  MOD1 = 23456789,
		  MOD2 = 19260817,
		  INF  = 250000;

int Hash1[MOD1],Hash2[MOD1],cnt[MOD1];
char tmp[MAXN][MAXL],c[MAXN][MAXL],s[MAXN][MAXL];
int n,len,ans;
bool flag;
map <int,int> used;

int main()
{
	freopen("key.in","r",stdin);
	freopen("key.out","w",stdout);
	int ttt,ha1,ha2,t,cost;
	scanf("%d",&ttt);
	for (int cas=1;cas<=ttt;cas++)
	{
		memset(Hash1,-1,sizeof Hash1);
		memset(cnt,0,sizeof cnt);
		ans=INF;
		scanf("%d%d",&n,&len);
		for (int i=0;i<n;i++)
		{
			scanf("%s",s[i]);
			if (i)
			{
				ha1=0,ha2=0;
				for (int j=0;j<len;j++)
					ha1=(ha1*17%MOD1+s[i][j]-'0'+1)%MOD1,
					ha2=(ha1*13%MOD2+s[i][j]-'0'+2)%MOD2;
				t=ha1;
				while (Hash1[t]!=-1 && Hash2[t]!=ha2)
					t++;
				Hash1[t]=ha1,Hash2[t]=ha2,cnt[t]++;
			}
		}
		for (int i=0;i<n;i++)
			scanf("%s",c[i]);
		for (int i=0;i<n;i++)
		{
			used.clear();
			cost=0;
			flag=1;
			memcpy(tmp,c,sizeof c);
			for (int j=0;j<len;j++)
			{
				if (s[0][j]==c[i][j])
					continue;
				cost++;
				for (int k=0;k<n;k++)
					tmp[k][j]=(tmp[k][j]=='0'?'1':'0');
			}
			for (int j=0;j<n;j++)
			{
				if (j==i)
					continue;
				ha1=ha2=0;
				for (int k=0;k<len;k++)
					ha1=(ha1*17%MOD1+tmp[j][k]-'0'+1)%MOD1,
					ha2=(ha1*13%MOD2+tmp[j][k]-'0'+2)%MOD2;
				t=ha1;
				while (Hash1[t]==ha1 && Hash2[t]!=ha2)
					t++;
				if (Hash1[t]!=ha1 || Hash2[t]!=ha2 || cnt[t]==used[t])
				{
					flag=0;
					break;
				}
				used[t]++;
			}
			if (flag)
				ans=min(ans,cost);
		}
		printf("Case #%d: ",cas);
		if (ans==INF)
			printf("NOT POSSIBLE\n");
		else
			printf("%d\n",ans);
	}
	return 0;
}

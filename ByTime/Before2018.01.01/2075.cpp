#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <fstream>

using namespace std;  
  
const int MOD = 1000003;  
  
char s[22][55];  
int f[57][34000];  
int n,m,k,ans,tmp,cnt,len;
  
int main()  
{  
	freopen("2075.in","r",stdin);
	freopen("2075.out","w",stdout);
	scanf("%d%d",&m,&k);  
	ans=0;
	memset(f,0,sizeof f);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",s[i]+1);
	}
	cnt = (1<<m);
	if (n!=strlen(s[1]+1)) n=strlen(s[1]+1);
	
	f[1][cnt-1]=1;  
	for(int i=1;i<=n;i++) 
	{
		for(int j=0;j<cnt;j++) 
		{
			if (f[i][j]) 
			{
				for(int ch=97;ch<123;ch++)  
				{  
					tmp=0;
					for(int p=1;p<=m;p++) 
						if (s[p][i]=='?' || s[p][i]==ch) 
							tmp+=(1<<(p-1));  
					f[i+1][j&tmp]=(f[i+1][j&tmp]+f[i][j])%MOD;  
				}
			}
		}
	}
	for(int i=0;i<cnt;i++)  
	{  
		tmp=0; 
		for(int j=0;j<m;j++) if (i&(1<<j)) tmp++;  
		if (tmp==k) ans=(ans+f[n+1][i])%MOD;  
	}  
	printf("%d\n",ans);  
	return 0;  
}  

#include<bits/stdc++.h>
using namespace std;

const int bas=27,mod=998244353;
const int N=55;
int T,n,m,a,b,cnt,ls,rs,hs[N];
string s[N],ans[N],tmp;
map<int,int>mp,id;
bool tflag;

int gethash(string s)
{
	int ret=0;
	for(int j=0;j<m;++j) ret=((long long)ret*bas+(s[j]-'A'))%mod;
	return ret;
}

void dfs(int x,string ret,string retf)
{
	if(tflag) return;
	if(x>m)
	{
		while(ls<=n && s[ls]<ret) ++ls;
		while(rs && s[rs]>retf) --rs;
		if(s[ls]!=ret && s[rs]!=retf) tflag=true,cout<<ret;
		return;
	}
	dfs(x+1,ret+'N',retf+'Y');dfs(x+1,ret+'Y',retf+'N');
}

int main()
{
//	freopen("2615.in","r",stdin);
//	freopen("2615.out","w",stdout);
	
	scanf("%d",&T);
	while(T--)
	{
		mp.clear();id.clear();cnt=0;
		scanf("%d%d%d%d",&n,&m,&a,&b);
		for(int i=1;i<=n;++i) cin>>s[i];//scanf("%s",s[i]+1);
		sort(s+1,s+n+1);
		for(int i=1;i<=n;++i)
		{
			hs[i]=gethash(s[i]);mp[hs[i]]++;
			if(hs[i]!=hs[i-1]) id[hs[i]]=i;
			ans[i]="";
		}
		if(!a && !b)
		{
			ls=1;rs=n;tflag=false;
			dfs(1,"","");
			if(!tflag) printf("-1");puts("");
		}
		else 
		if(!a && b)
		{
			for(map<int,int>::iterator it=id.begin();it!=id.end();++it)
			{
				int p=(*it).second;
				if(mp[hs[p]]!=b) continue;
				tmp="";for(int i=0;i<m;++i) tmp+=(s[p][i]=='N'?'Y':'N');
				if(mp[gethash(tmp)]!=a) continue;
				++cnt;ans[cnt]=tmp;
			}
			sort(ans+1,ans+cnt+1);
			if(cnt) cout<<ans[1];
				else printf("-1");
			puts("");
		}
		else
		{
			for(map<int,int>::iterator it=id.begin();it!=id.end();++it)
			{
				int p=(*it).second;
				if(mp[hs[p]]!=a) continue;
				tmp="";for(int i=0;i<m;++i) tmp+=(s[p][i]=='N'?'Y':'N');
				if(mp[gethash(tmp)]!=b) continue;
				++cnt;ans[cnt]=s[p];
			}
			sort(ans+1,ans+cnt+1);
			if(cnt) cout<<ans[1];
				else printf("-1");
			puts("");
		}
	}
	return 0;
}
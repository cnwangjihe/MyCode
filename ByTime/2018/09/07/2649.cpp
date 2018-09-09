#include<bits/stdc++.h>
using namespace std;

const int MOD  = 1000000007,
		  MAXN = 200050;

struct Data
{
	pair<long long,int> d[4];
	Data(){}
	Data(int x)
	{
		d[0]=make_pair(0,1);
		d[1]=d[2]=make_pair(0,0);
		d[3]=make_pair(x,1);
	}
	void clear() {d[0]=d[1]=d[2]=d[3]=make_pair(0,0);}
};

int T,n,m,change[5],d[MAXN];
map<int,Data> mp[MAXN];
priority_queue<pair<int,int> > q;
int x,y,z,id,pos,cnt;
long long best;
Data temp,newt,dat;
pair<int,int> pa;
pair<long long,int> newp;
map<int,Data>::iterator it,itx,ity;

void Add(int x,int y,int z)
{
	if (mp[x].find(y)!=mp[x].end())
	{
		if (mp[x][y].d[3].first<z)
			mp[x][y]=Data(z);
		else
			if (mp[x][y].d[3].first==z)
				mp[x][y].d[3].second++;
	}
	else
		d[x]++,mp[x][y]=Data(z);
	return ;
}

void Unique(int x,int y,Data t)
{
	Data temp;
	pair<long long,int> newp;
	if (mp[x].find(y)==mp[x].end())
	{
		mp[x][y]=t;
		return ;
	}
	temp.clear();
	for (int i=0;i<4;i++)
		if (mp[x][y].d[i].second)
			for (int j=0;j<4;j++)
				if ((t.d[j].second) && (!(i&j)))
				{
					newp=make_pair(mp[x][y].d[i].first+t.d[j].first,
						1ll*mp[x][y].d[i].second*t.d[j].second%MOD);
					if (newp.first>temp.d[i|j].first)
						temp.d[i|j]=newp;
					else
						if (newp.first==temp.d[i|j].first)
							(temp.d[i|j].second+=newp.second)%=MOD;
				}
	mp[x][y]=temp;
	return ;
}
int main()
{
	freopen("2649.in","r",stdin);
	freopen("2649.out","w",stdout);
	change[0]=0;
	change[1]=2;
	change[2]=1;
	change[3]=3;
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d%d",&n,&m);
		for (int i=1;i<=n;i++)
			d[i]=0,mp[i].clear();
		for (int i=1;i<=m;i++)
		{
			scanf("%d%d%d",&x,&y,&z);
			Add(x,y,z);
			Add(y,x,z);
		}
		for (;!q.empty();q.pop());
		for (int i=1;i<=n;i++)
			q.push(make_pair(-d[i],i));
		for (;!q.empty();)
		{
			pa=q.top();
			q.pop();
			id=pa.second;
			if (-pa.first!=d[id] || d[id]==0)
				continue;
			if (d[id]==1)
				break;
			itx=mp[id].begin();
			ity=itx;
			ity++;
			temp.clear();
			for (int i=0;i<4;i++)
				if (itx->second.d[i].second)
					for (int j=0;j<4;j++)
						if ((ity->second.d[j].second) && ((i&1)+(j&1)<=1))
						{
							newp=make_pair(itx->second.d[i].first+ity->second.d[j].first,
								1ll*itx->second.d[i].second*ity->second.d[j].second%MOD);
							pos=((i>>1)&1)+(j&2);
							if (newp.first>temp.d[pos].first)
								temp.d[pos]=newp;
							else
								if (newp.first==temp.d[pos].first)
									(temp.d[pos].second+=newp.second)%=MOD;
						}
			d[id]-=2;
			it=mp[itx->first].find(id);
			mp[itx->first].erase(it);
			Unique(itx->first,ity->first,temp);
			d[itx->first]=mp[itx->first].size();
			q.push(make_pair(-d[itx->first],itx->first));

			for (int i=0;i<4;i++)
				newt.d[i]=temp.d[change[i]];

			temp=newt;
			it=mp[ity->first].find(id);
			mp[ity->first].erase(it);
			Unique(ity->first,itx->first,temp);
			d[ity->first]=mp[ity->first].size();
			q.push(make_pair(-d[ity->first],ity->first));

			mp[id].erase(itx);
			mp[id].erase(ity);
		}
		best=cnt=0;
		dat=mp[id].begin()->second;
		for (int i=0;i<4;i++)
			if (dat.d[i].first>best)
				best=dat.d[i].first,cnt=dat.d[i].second;
			else
				if (dat.d[i].first==best)
					(cnt+=dat.d[i].second)%=MOD;
		printf("%lld %d\n",best,cnt);
	}
	return 0;
}

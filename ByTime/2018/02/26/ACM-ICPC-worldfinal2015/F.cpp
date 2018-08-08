#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
#include<cstdlib>
#include<cstring>
#define pii pair<int,int>
using namespace std;

const int N=51;
const int L=10005;
const int INF=1000000007;
const int dx[4]={-1,0,0,1};
const int dy[4]={0,1,-1,0};
int n,m,len,ans=INF;
pii next[N][N][4];
bool vis[N][N][L];
char s[N][N],T[L];
struct node
{
	int x,y,step,total;
};

inline bool in(int x,int y)
{
	return x>=1&&x<=n&&y>=1&&y<=m;
}

inline void pre()
{
	for (int i=1;i<=n;i++)
		for (int j=1;j<=m;j++)
			for (int k=0;k<4;k++)
			{
				int x=i+dx[k],y=j+dy[k];
				while (s[x][y]==s[i][j]&&in(x,y)) x=x+dx[k],y=y+dy[k];
				next[i][j][k]=make_pair(x,y);
			}
}

inline void BFS()
{
	queue<node> q;
	if (s[1][1]==T[1]) q.push((node){1,1,1,1}),vis[1][1][1]=true;
	else q.push((node){1,1,0,0}),vis[1][1][0]=true;
	while (!q.empty())
	{
		node now=q.front(); q.pop();
//	  cout << now.x << " " << now.y << " " << now.step << " " << now.total << endl;
//	  system("pause");
		if (s[now.x][now.y]==T[now.step+1]&&!vis[now.x][now.y][now.step+1])
		{
			vis[now.x][now.y][now.step+1]=true;
			q.push((node){now.x,now.y,now.step+1,now.total+1});
		}
		for (int k=0;k<4;k++)
		{
			pii nxt=next[now.x][now.y][k];
			if (!in(nxt.first,nxt.second)) continue;
			int x=nxt.first,y=nxt.second;
			if (T[now.step+1]==s[x][y]) 
			{
				if (vis[x][y][now.step+1]) continue;
				vis[x][y][now.step+1]=true;
				q.push((node){x,y,now.step+1,now.total+2});
				if (now.step+1==len) ans=min(ans,now.total+2);
			}
			else
			{
				if (vis[x][y][now.step]) continue;
				vis[x][y][now.step]=true;
				q.push((node){x,y,now.step,now.total+1});
			}
		}
	}
}		   

int main()
{
//  freopen("keyboard.in","r",stdin);
//  freopen("keyboard.out","w",stdout);

	scanf("%d%d",&n,&m);
	for (int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	scanf("%s",T+1);
	len=strlen(T+1)+1;
	T[len]='*';
	pre();
	BFS();
	printf("%d\n",ans);
	return 0;
}

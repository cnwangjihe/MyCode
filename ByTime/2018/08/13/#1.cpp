#include<cstdio>
#include<cstdlib>
#include<map>
using namespace std;
map<int,int> Go[400001];
int _next[400001],ed[400001],son[400001],val[400001],cnt;
int n,m,num[400001],f[400001],q[4000001],inq[400001];
int dis[400001];
int read(){
	int res=0;char ch;
	for (ch=getchar();ch<'0'||ch>'9';ch=getchar());
	for (;ch>='0'&&ch<='9';ch=getchar()) res=res*10+ch-'0';
	return res;
}
void link(){
	int x,y,z;
	x=read(); y=read(); z=read();
	_next[++cnt]=son[x]; son[x]=cnt; ed[cnt]=y; val[cnt]=z;
	_next[++cnt]=son[y]; son[y]=cnt; ed[cnt]=x; val[cnt]=z;
}
void SPFA(){
	int st,en,u,v;
	st=en=0; q[++en]=1; inq[1]=1;
	for (int i=1;i<=n;i++) dis[i]=0x7f7f7f7f;
	if(Go[1][0]) dis[1]=Go[1][0];
	else dis[1]=0;
	while (st<en){
		u=q[++st]; inq[u]=0;
		if(dis[u]>=dis[n]) continue;
		for (int i=son[u];i;i=_next[i]){
			v=ed[i];
			int tmp=dis[u]+val[i];

			if(Go[v][tmp]&&v!=n) tmp=Go[v][tmp];
		//	printf("v u %d %d %d %d %d\n",v,u,dis[v],dis[u],tmp);
			if(dis[v]>tmp){
				dis[v]=tmp;
				if(!inq[v]){
					++en; if(en==1000000) en=1;
					inq[v]=1; q[++en]=v;
				}
			}
		}
	}
}

int main(){
	scanf("%d%d",&n,&m);
	for (int i=1;i<=m;i++) link();
	for (int i=1;i<=n;i++){
		num[i]=read();
		for (int j=1;j<=num[i];j++) f[j]=read();
		int k=0;
		for (int j=1;j<=num[i];j=k){
			for (k=j;f[j]-f[k]==j-k&&k<=num[i];k++);
			int tmp=f[k-1]+1;
			for (k=j;f[j]-f[k]==j-k&&k<=num[i];k++){
				Go[i][f[k]]=tmp;
			//	printf("i %d k %d goto %d\n",i,f[i][k],tmp);
			}
		}
	}
	SPFA();
//	for (int i=1;i<=n;i++) printf("%d ",dis[i]); printf("dis\n");
	if(dis[n]==0x7f7f7f7f) dis[n]=-1;
	printf("%d\n",dis[n]);
	for (int i=1;i<=n;i++)
		printf("%d ",dis[i]);
return 0;
}

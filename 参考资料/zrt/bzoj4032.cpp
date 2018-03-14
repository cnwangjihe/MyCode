include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
char s1[2005],s2[2005];
int last[26];
struct zidongji{
	// 0 bad
	int l[4005];
	int to[4005][26];
	int fa[4005];
	int tot,root,last;
	void clear(){memset(to,0,sizeof to);tot=0;memset(l,0,sizeof l);memset(fa,0,sizeof fa);}
	void add(int w){
		//SAM
		int p=last,np=++tot;
		last=np;l[np]=l[p]+1;
		while(p&&!to[p][w]) to[p][w]=np,p=fa[p];
		if(!p) fa[np]=root;
		else{
			int q=to[p][w];
			if(l[q]==l[p]+1) fa[np]=q;
			else{
				int nq=++tot;
				l[nq]=l[p]+1;fa[nq]=fa[q];
				memcpy(to[nq],to[q],sizeof to[q]);
				fa[q]=fa[np]=nq;
				while(to[p][w]==q) to[p][w]=nq,p=fa[p];
			}
		}
	}
	void mkzichuan(char s[]){
		clear();
		root=last=++tot;
		int L=strlen(s+1);
		for(int i=1;i<=L;i++) add(s[i]-'a');
	}
	void mkzixulie(char s[]){// TODO change
		static int last[26];
		memset(last,0,sizeof last);
		root=2004;
		int L=strlen(s+1);
		clear();
		for(int i=0;i<26;i++) last[i]=0;
		for(int i=L;i>=1;i--){
			for(int j=0;j<26;j++) to[i][j]=last[j];
			last[s[i]-'a']=i;
		}
		for(int i=0;i<26;i++) to[root][i]=last[i];
	}
}A,B;
struct N{
	int a,b,l;
	N(int x=0,int y=0,int z=0){
		a=x,b=y,l=z;
	}
};
queue<N> q;
bool vis[4005][4005];
int ask(){
	memset(vis,0,sizeof vis);
	while(!q.empty()) q.pop();
	q.push(N(A.root,B.root,0));
	vis[A.root][B.root]=1;
	while(!q.empty()){
		N t=q.front();q.pop();
		for(int i=0;i<26;i++){
			if(A.to[t.a][i]&&!B.to[t.b][i]){
				return t.l+1;
			}else if(vis[A.to[t.a][i]][B.to[t.b][i]]){
				continue;
			}else{
				vis[A.to[t.a][i]][B.to[t.b][i]]=1;
				q.push(N(A.to[t.a][i],B.to[t.b][i],t.l+1));
			}
		}
	}
	return -1;
}
int main(){
//  freopen("sus.in","r",stdin);
//  freopen("sus.out","w",stdout);
	scanf("%s%s",s1+1,s2+1);
	A.clear();B.clear();
	A.mkzichuan(s1);
	B.mkzichuan(s2);
	printf("%d\n",ask());
	A.mkzichuan(s1);
	B.mkzixulie(s2);
	printf("%d\n",ask());
	A.mkzixulie(s1);
	B.mkzichuan(s2);
	printf("%d\n",ask());
	A.mkzixulie(s1);
	B.mkzixulie(s2);
	printf("%d\n",ask());
	fclose(stdin);fclose(stdout);
	return 0;
}

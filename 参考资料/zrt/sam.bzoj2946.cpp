#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int MAXN=9000;
char s[2005];
struct SAM{
	int last,l[MAXN],f[MAXN],go[MAXN][26],L;
	int mn[MAXN];
	int mx[MAXN];
	int x[MAXN];
	int root,tot;
	SAM(){
		root=last=tot=1;
	}
	void add(int w){// add last + char w
		L++;
		int p=last;
		int np=++tot;// xS
		l[np]=l[p]+1;
		while(p&&!go[p][w]){
			go[p][w]=np;
			p=f[p];
		}
		if(!p){
			f[np]=root;
		}else{
			int q=go[p][w];
			if(l[p]+1==l[q]){
				f[np]=q;
			}else{
				int nq=++tot;
				l[nq]=l[p]+1;
				memcpy(go[nq],go[q],sizeof go[q]);
				f[nq]=f[q];
				f[q]=f[np]=nq;
				while(p&&go[p][w]==q) go[p][w]=nq,p=f[p];
			}
		}
		last=np;
	}
	void sort(){
		for(int i=1;i<=tot;i++) mn[l[i]]++;
		for(int i=1;i<=L;i++) mn[i]+=mn[i-1];
		for(int i=1;i<=tot;i++) x[mn[l[i]]--]=i;
		for(int i=1;i<=tot;i++) mn[i]=l[i];
	}
	void work(){
		int p=root,L(0);
		for(int i=0;s[i];i++){
			if(go[p][s[i]-'a']){
				L++;
				p=go[p][s[i]-'a'];
				mx[p]=max(mx[p],L);
			}else{
				while(p&&!go[p][s[i]-'a']) p=f[p];
				if(!p){
					p=1;L=0;
				}else{
					L=l[p]+1;
					p=go[p][s[i]-'a'];
					mx[p]=max(mx[p],L);
				}
			}
		}
		for(int i=tot;i>0;i--){
			int t=x[i];
			mn[t]=min(mn[t],mx[t]);
			if(f[t]&&mx[t]) mx[f[t]]=mx[t];
			mx[t]=0;
		}
	}
	int ans(){
		int ret=0;
		for(int i=1;i<=tot;i++) ret=max(ret,mn[i]);
		return ret;
	}
}SAM;
int n;
int main(){
	scanf("%d",&n);
	scanf("%s",s);
	for(int i=0;s[i];i++){
		SAM.add(s[i]-'a');
	}
	SAM.sort();
	for(int i=1;i<n;i++){
		scanf("%s",s);
		SAM.work();
	}
	printf("%d\n",SAM.ans());
	return 0;
}

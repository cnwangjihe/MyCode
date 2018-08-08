#include<cmath>
#include<ctime>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<iostream>
#include<algorithm>
#define K 17
#define N 100001
struct section{
	int l,r;
}s[N];
int st[N][K],h[N],m[N],sq[N],log_2[N],n,ans;
double k;
inline int read(){
	int ret=0;char c=getchar();
	while(!(c>=бо0бо&&c<=бо9бо))
		c=getchar();
	while(c>=бо0бо&&c<=бо9бо){
		ret=ret*10+c-бо0бо;c=getchar();
	}
	return ret;
}
inline int sqr(int k){
	return k*k;
}
inline int max(int x,int y){
	return x>y?x:y;
} 
inline void ini_st(){
	log_2[1]=0;
	for(int i=2;i<=n;i++){
		log_2[i]=log_2[i-1];
		if((1<<log_2[i]+1)==i)/*pow(2,log_2[i]+1)==i*/
			log_2[i]++;
	}
	for(int i=n;i>=1;i--){
		st[i][0]=h[i];
		for(int j=1;(i+(1<<j)-1)<=n;j++)
			st[i][j]=max(st[i][j-1],st[i+(1<<j-1)][j-1]);
	}
}
inline int ask(int l,int r){
	if(l<1) l=1;
	if(r>n) r=n;
	int len=r-l+1,k=log_2[len];
	return max(st[l][k],st[r-(1<<k)+1][k]);
}
inline void init(){
	scanf("%d",&n);
	k=sqrt(n);
	int l=(int)(k);
	if(k>l) l++; 
	for(int i=1;i<=n;i++)
		scanf("%d",&h[i]);
	for(int i=1;i<=l;i++){
		s[i].l=sqr(i-1)+1;
		s[i].r=sqr(i);
		for(int j=s[i].l;j<=s[i].r;j++)
			sq[j]=i;
	}
	ini_st();
	for(int i=1;i<=n;i++,ans=0){
		for(int j=sq[i-1];j>=1;j--){
			ans=max(ans,ask(i-s[j].r,i-s[j].l)+j);
		}
		for(int j=sq[n-i];j>=1;j--){
			ans=max(ans,ask(i+s[j].l,i+s[j].r)+j);
		}
		printf("%d\n",max(0,ans-h[i]));
	}
}
int main(){
	freopen("light.in","r",stdin);
	freopen("light.out","w",stdout);
	init();
	fclose(stdin);
	fclose(stdout);
	return 0;
}

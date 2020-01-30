#include<cstdio>
#include<iostream>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cmath>
#include<vector>
#include<stack>
#include<map>
#include<set>
#define Run(i,l,r) for(int i=l;i<=r;i++)
#define Don(i,l,r) for(int i=l;i>=r;i--)
#define ll long long
#define inf 0x3f3f3f3f
using namespace std;
const int N=200010;
int n,m,sub[N],tot,fa[N];
struct data{
    int x,y,p;
    data(int _x=0,int _y=0,int _p=0):x(_x),y(_y),p(_p){};
}A[N];
set<int>s[N];
set<int>::iterator it;
char gc(){
    static char*p1,*p2,S[1000000];
    if(p1==p2)p2=(p1=S)+fread(S,1,1000000,stdin);
    return(p1==p2)?EOF:*p1++;
}
int rd(){
    int x=0,f=1; char c=gc();
    while(c<'0'||c>'9'){if(c=='-')f=-1;c=gc();}
    while(c>='0'&&c<='9')x=(x<<1)+(x<<3)+c-'0',c=gc();
    return x*f;
}
int find(int x){return fa[x]==x?x:fa[x]=find(fa[x]);}
bool check(int x,int y){
    if(x==y)return false;
    if(s[x].size()>s[y].size())swap(x,y);
    for(it=s[x].begin();it!=s[x].end();it++){
        if(find(*it)==y)return true; 
    }
    fa[x]=y;
    for(it=s[x].begin();it!=s[x].end();it++){
        s[y].insert(find(*it));
    }
    s[x].clear();
    return false;
}
int main(){
    int ttt;
    scanf("%d%d",&ttt,&n);
    // n=rd();
    Run(i,1,n){
        // A[i]=(data){rd(),rd(),rd()}; 
        scanf("%d%d%d",&A[i].p,&A[i].x,&A[i].y);
        // A[i].x=rd(); A[i].y=rd(); A[i].p=rd();
        sub[++tot]=A[i].x , sub[++tot]=A[i].y;
    }
    sort(sub+1,sub+tot+1);
    tot=unique(sub+1,sub+tot+1)-sub-1;
    Run(i,1,tot)fa[i]=i;
    for(int i=1,x,y;i<=n;i++){
        x=A[i].x=lower_bound(sub+1,sub+tot+1,A[i].x)-sub;
        y=A[i].y=lower_bound(sub+1,sub+tot+1,A[i].y)-sub;
        if(A[i].p==0){
            if(find(x)==find(y)){puts("No");continue;}
            puts("Yes");
            s[fa[x]].insert(fa[y]);
            s[fa[y]].insert(fa[x]);
        }else {
            int fx=find(x) , fy=find(y);
            if(check(fx,fy)){puts("No");continue;}
            else puts("Yes");
        }
    }
    return 0;
}
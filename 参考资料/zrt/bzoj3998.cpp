#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
#define int LL
int root,last,tot;
int l[1000005],fa[1000005],go[1000005][26];
char s[1000005];
int c[1000005];
int t[1000005];
int x[1000005];
int L;
void add(int w){
    int np=++tot,p=last;
    last=np;l[np]=l[p]+1;c[np]=1;
    while(p&&!go[p][w]) go[p][w]=np,p=fa[p];
    if(!p) fa[np]=root;
    else{
        int q=go[p][w];
        if(l[q]==l[p]+1){
            fa[np]=q;
        }else{
            int nq=++tot;
            l[nq]=l[p]+1;
            memcpy(go[nq],go[q],sizeof go[q]);
            fa[nq]=fa[q];
            fa[q]=fa[np]=nq;
            while(go[p][w]==q) go[p][w]=nq,p=fa[p];
        }
    }
}
int T,K;
#undef int
int main(){
    #define int LL
    root=last=++tot;
    scanf("%s%lld%lld",s,&T,&K);
    L=strlen(s);
    for(int i=0;i<L;i++) add(s[i]-'a');
    for(int i=1;i<=tot;i++) t[l[i]]++;
    for(int i=1;i<=L;i++) t[i]+=t[i-1];
    for(int i=1;i<=tot;i++) x[t[l[i]]--]=i;
    if(T==0){
        for(int i=2;i<=tot;i++) c[i]=1;
        for(int i=tot;i>=1;i--){
            for(int j=0;j<26;j++){
                if(go[x[i]][j]) c[x[i]]+=c[go[x[i]][j]];
            }
        }
        int o=root;
        K++;
        if(K>c[root]+1){
            puts("-1");
            return 0;
        }
        while(1){
            if(K==1){
                break;
            }
            K--;
            for(int i=0;i<26;i++){
                if(K<=c[go[o][i]]){
                    putchar(i+'a');
                    o=go[o][i];break;
                }else K-=c[go[o][i]];
            }
        }
    }else{
        for(int i=tot;i>=1;i--) if(fa[x[i]]) c[fa[x[i]]]+=c[x[i]];
        memcpy(t,c,sizeof t);
        for(int i=tot;i>=1;i--){
            for(int j=0;j<26;j++){
                if(go[x[i]][j]) t[x[i]]+=t[go[x[i]][j]];
            }
        }
        int o=root;
        c[1]=0;
        if(K>t[root]){
            puts("-1");
            return 0;
        }
        while(1){
            if(K<=c[o]) break;
            K-=c[o];
            for(int i=0;i<26;i++){
                if(K<=t[go[o][i]]){
                    putchar(i+'a');
                    o=go[o][i];break;
                }else K-=t[go[o][i]];
            }
        }
    }
    puts("");
    return 0;
}

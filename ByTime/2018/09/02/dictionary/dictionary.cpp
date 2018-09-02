#include <bits/stdc++.h>

#define N 200010
#define ll long long
using namespace std;
inline int read() 
{ 
    int x=0,f=1;char ch=getchar(); 
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();} 
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();} 
    return x*f; 
}
int ch[N][26];
bool tag[N],pd;
int tot,n,m,now,len,ans,vis[N],T;
char s[30];
void ins()
{
    len=strlen(s),now=0;
    for(int i=0;i<len;i++)
    {
        if(!ch[now][s[i]-'a'])ch[now][s[i]-'a']=++tot;
        now=ch[now][s[i]-'a'];
    }
    tag[now]=1;
}
void ask(int x,int deep,bool flag)
{
    if(deep==len&&tag[x]&&!flag){pd=1;return;}
    if(deep==len&&tag[x]&&flag){if(vis[x]!=T)ans++,vis[x]=T;return;} 
    if(deep<len&&!flag)ask(x,deep+1,1);  
    if(!flag)
    for(int i=0;i<26;i++)
    if(ch[x][i])
    {
        ask(ch[x][i],deep,1);
        if(i!=s[deep+1]-'a')
        ask(ch[x][i],deep+1,1);
    }
    if(deep==len)return;  
    if(ch[x][s[deep+1]-'a'])ask(ch[x][s[deep+1]-'a'],deep+1,flag);  
}
int main()
{
    n=read(),m=read();
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        ins();
    }
    for(int i=1;i<=m;i++)
    {
        T++;
        pd=0,ans=0;
        scanf("%s",s+1);
        len=strlen(s+1);
        ask(0,0,0);  
        if(pd)printf("-1\n"); 
        else printf("%d\n",ans);  
    }
}
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <cmath>
#include <cctype>

using namespace std;

const int MAXN = 500008;

int add[MAXN*4],v[MAXN];
int n,m;

inline int read()
{
    int X=0,w=0; char ch=0;
    while(!isdigit(ch)) {w|=ch=='-';ch=getchar();}
    while(isdigit(ch)) X=(X<<3)+(X<<1)+(ch^48),ch=getchar();
    return w?-X:X;
}
inline void write(int x)
{
     if(x<0) putchar('-'),x=-x;
     if(x>9) write(x/10);
     putchar(x%10+'0');
}

void _down(int u)
{
    if (add[u]==0)
        return ;
    add[u*2]+=add[u];
    add[u*2+1]+=add[u];
    add[u]=0;
    return ;
}

int _ask(int u,int l,int r,int p)
{
    if (l==r)
        return v[l]+add[u];
    int mid=(l+r)/2;
    _down(u);
    if (p<=mid)
        return _ask(u*2,l,mid,p);
    else
        return _ask(u*2+1,mid+1,r,p);
}

void _add(int u,int l,int r,int al,int ar,int ad)
{
    if (al<=l && ar>=r)
    {
        add[u]+=ad;
        return ;
    }
    int mid=(l+r)/2;
    if (al<=mid)
        _add(u*2,l,mid,al,ar,ad);
    if (ar>mid)
        _add(u*2+1,mid+1,r,al,ar,ad);
    return ;
}

int main()
{
    int x,y,k,t;
    n=read();m=read();
    for (register int i=1;i<=n;i++)
        v[i]=read();
    for (register int i=0;i<m;i++)
    {
        t=read();
        if (t==1)
        {
            x=read(),y=read(),k=read();
            _add(1,1,n,x,y,k);
        }
        else
        {
            x=read();
            printf("%d\n",_ask(1,1,n,x));
        }
    }
    return 0;
}
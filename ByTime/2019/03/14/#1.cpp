#include <bits/stdc++.h>

using namespace std;

namespace IOspace
{
    inline char getch()
    {
        register char ch;
        do ch=getchar(); while (ch!='A' && ch!='I' && ch!='D' && ch!='Q');
        return ch;
    }
    inline int getint()
    {
        register int num=0;
        register char ch;
        do ch=getchar(); while (ch<'0' || ch>'9');
        do num=num*10+ch-'0', ch=getchar(); while (ch>='0' && ch<='9');
        return num;
    }
    inline void putint(int num, char ch='\n')
    {
        char stack[15];
        register int top=0;
        if (num==0) stack[top=1]='0';
        for ( ;num;num/=10) stack[++top]=num%10+'0';
        for ( ;top;top--) putchar(stack[top]);
        if (ch) putchar(ch);
    }
}

int N;
int add;
std::map<int, int> s;
int sum[17][65537];
inline int lim(int x) {return (1<<x+1)-1;}
inline int min(int x, int y) {return x<y?x:y;}
inline int max(int x, int y) {return x>y?x:y;}
inline int lowbit(int x) {return x & -x;}
inline void update(int, int, int);
inline int query(int, int);

int main()
{
    freopen("bitcoin.in","r",stdin);
    freopen("bitcoin.out","w",stdout);
    N=IOspace::getint();
    for ( ;N;N--)
    {
        int ch=IOspace::getint(); int x=IOspace::getint();
        if (ch==2) add+=x;
        if (ch==0)
        {
            x-=add;
            s[x]++;
            for (int i=0;i<16;i++)
            {
                update(i, (x & lim(i))+1, 1);
            }
        }
        if (ch==1)
        {
            x-=add;
            int t=s[x];
            s[x]=0;
            for (int i=0;i<16;i++) update(i, (x & lim(i))+1, -t);
        }
        if (ch==3)
        {
            int l=1<<x, r=lim(x);
            int ans=0;
            ans+=query(x, min(max(r-(add & lim(x))+1, 0), 1<<16));
            ans-=query(x, min(max(l-(add & lim(x)), 0), 1<<16));
            l+=1<<x+1, r+=1<<x+1;
            ans+=query(x, min(max(r-(add & lim(x))+1, 0), 1<<16));
            ans-=query(x, min(max(l-(add & lim(x)), 0), 1<<16));
            IOspace::putint((add & lim(x)));
        }
    }

    return 0;
}
inline void update(int k, int i, int v)
{
    for ( ;i<=1<<16;i+=lowbit(i)) sum[k][i]+=v;
}
inline int query(int k, int i)
{
    int ret=0;
    for ( ;i;i-=lowbit(i)) ret+=sum[k][i];
    return ret;
}
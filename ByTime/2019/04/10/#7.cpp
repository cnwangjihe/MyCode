#include <iostream>
#include <cstdio>
using namespace std;

typedef long long ll;
int k;
ll a,p,w;
struct T{ll x,y;};

T mul_two(T a,T b,ll p)
{
    T ans;
    ans.x=(a.x*b.x%p+a.y*b.y%p*w%p)%p;
    ans.y=(a.x*b.y%p+a.y*b.x%p)%p;
    return ans;
}

T qpow_two(T a,ll n,ll p)
{
    T ans;
    ans.x=1;
    ans.y=0;
    while(n)
    {
        if(n&1) ans=mul_two(ans,a,p);
        n>>=1;
        a=mul_two(a,a,p);
    }
    return ans;
}

ll qpow(ll a,ll n,ll p)
{
    ll ans=1;
    a%=p;
    while(n)
    {
        if(n&1) ans=ans*a%p;
        n>>=1;
        a=a*a%p;
    }
    return ans%p;
}

ll Legendre(ll a,ll p)
{
    return qpow(a,(p-1)>>1,p);
}

int solve(ll n,ll p)
{
    if(p==2) return 1;
    if(Legendre(n,p)+1==p) return -1;
    ll a,t;
    while(1)
    {
        a=rand()%p;
        t=a*a-n;
        w=(t%p+p)%p;
        if(Legendre(w,p)+1==p) break;
    }
    T tmp;
    tmp.x=a;
    tmp.y=1;
    T ans=qpow_two(tmp,(p+1)>>1,p);
    return ans.x;
}

int main()
{
    scanf("%d",&k);
    while(k--)
    {
        scanf("%lld%lld",&a,&p);
        int d=solve(a,p);
        if(d==-1)
        {
            printf("No root\n");
            continue;
        }
        int f=p-d;
        if(d>f) swap(d,f);
        if(d==f) printf("%d\n",d);
        else printf("%d %d\n",d,f);
    }

    return 0;
}
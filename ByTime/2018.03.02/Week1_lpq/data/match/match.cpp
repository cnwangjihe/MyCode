//bzoj 4481 [Jsoi2015]·Ç³ÏÎðÈÅ
#includecstdio
#includecstring
#includeiostream
#includealgorithm
#define ll long long
#define double long double
#define M(a) memset(a,0,sizeof a)
#define fo(i,j,k) for(i=j;i=k;i++)
using namespace std;
const int mxn=500005;
int n,m;
double p,ans;
double c[mxn];
struct node {int x,y;} a[mxn];
inline bool comp(node u,node v)
{
    return u.x==v.xu.yv.yu.xv.x;
}
inline int lowbit(int x)
{
    return x&-x;
}
inline void add(int x,double v)
{
    for(int i=x;i=n;i+=lowbit(i))
      c[i]+=v;
}
inline double getsum(int x)
{
    double sum=0;
    for(int i=x;i;i-=lowbit(i))
      sum+=c[i];
    return sum;
}
int main()
{
    int i,j,last;
    scanf(%d%d%Lf,&n,&m,&p);
    fo(i,1,m) scanf(%d%d,&a[i].x,&a[i].y);
    sort(a+1,a+m+1,comp);
    for(i=1;i=m;i=last+1)
    {
        double q=1;last=i;
        while(a[last+1].x==a[last].x) last++;
        fo(j,1,last-i+1) q=q(1-p);q=1-q;
        double up=p;
        fo(j,i,last)
        {
            if(ji) up=up(1-p);
            double now=upq;
            add(n-a[j].y+1,now);
            ans+=nowgetsum(n-a[j].y);
        }
    }
    printf(%.2Lfn,ans);
    return 0;
}

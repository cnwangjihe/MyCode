#include<cstdio>
#include<algorithm>
using namespace std;const int N=80;typedef unsigned int uit;
int n;int m;int p;int k;uit t[N][N];int up;int bk[N][N];uit ans;
int at[3];int att[3][N];int zt[N];int ct;bool book[N];int lg[N];
struct mar
{
    uit mp[N][N];
    void operator *=(const mar& b)
    {
        for(int i=1;i<=ct;i++)for(int j=1;j<=ct;j++)t[i][j]=0;
        for(int i=1;i<=ct;i++)
            for(int k=0;k<=ct;k++)
                for(int j=1;j<=ct;j++)
                    t[i][j]+=mp[i][k]*b.mp[k][j];
        for(int i=1;i<=ct;i++)for(int j=1;j<=ct;j++)mp[i][j]=t[i][j];
    }
}tr,res,st;
int main()
{
    scanf("%d%d%d%d",&n,&m,&p,&k);
    for(int i=0;i<3;i++)
    {for(int j=0,t;j<p;j++){scanf("%u",&t);at[i]+=(1<<j)*t;}}at[1]-=(1<<k);
    up=(1<<m);zt[++ct]=0;book[0]=true;
    for(int i=1;i<up;i++)
    {
        for(int j=0,p=i;p;p>>=1,j++)
        {
            if((p&1)==0){continue;}
            att[0][i]|=(j<k)?at[0]>>(k-j):at[0]<<(j-k);
            att[1][i]|=(j<k)?at[1]>>(k-j):at[1]<<(j-k);
            att[2][i]|=(j<k)?at[2]>>(k-j):at[2]<<(j-k);
        }
    }
    for(int i=1;i<up;i++){if((i&att[1][i])==0){zt[++ct]=i;}}
    for(int p1=1;p1<=ct;p1++)
    {
        for(int p2=1;p2<=ct;p2++)
        {if((att[2][zt[p1]]&zt[p2])==0&&(att[0][zt[p2]]&zt[p1])==0){tr.mp[p1][p2]++;}}
    }
    for(int i=1;i<=ct;i++){res.mp[i][i]=1;}st.mp[1][1]=1;
    for(;n;n>>=1,tr*=tr){if(n&1){res*=tr;}}st*=res;
    for(int i=1;i<=ct;i++){ans+=st.mp[1][i];}printf("%u",ans);return 0;
}
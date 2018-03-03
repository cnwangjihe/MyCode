/*
  ת�Ʒ��̺ܺ��룬f[i][j]��ʾȡ��i��ǡ����j���������ϵĸ���
  f[i][j]=f[i-1][j+1]*(j+1)/c+f[i-1][j-1]*(j+1)/c
  ����������n�ر�����Կ���һ������ķ�����
  ���ڱ���Ծ��ȵ�Ҫ�󲻸ߣ�����Խ�����棬����ǰ����������������ǿ���ֻ��һ���֡�
  ��Ҫע����ǣ���n+m������ʱ������һ����0������Ҫ��ż���֡� 
*/
#include<cstdio>
#include<iostream>
#include<cstring>
#define N 1010
using namespace std;
double dp[N][N];int c,n,m;
int main(){
    freopen("10.in","r",stdin);
    freopen("10.out","w",stdout);
    while(scanf("%d",&c)&&c){
        memset(dp,0,sizeof(dp));
        scanf("%d%d",&n,&m);
        if(!n&&!m){
            printf("1.000\n");
            continue;
        }
        if(m>c||m>n||(m+n&1)){
            printf("0.000\n");
            continue;
        }
        if(n>1000){
            if(n&1) n=1001;
            else n=1000;
        }
        dp[1][1]=1;
        for(int i=2;i<=n;i++)
            for(int j=0;j<=min(i,c);j++){
                if(i+j&1) {dp[i][j]=0;continue;}
                if(j>0) dp[i][j]+=dp[i-1][j-1]*double(c-j+1)/double(c);
                if(j+1<i) dp[i][j]+=dp[i-1][j+1]*double(j+1)/double(c);
            }
        printf("%.3lf\n",dp[n][m]);
    }
    return 0;
}

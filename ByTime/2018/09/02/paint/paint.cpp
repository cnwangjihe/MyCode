#include<bits/stdc++.h>

using namespace std;
const int MAXN = 55;

int n,m,t,dp[3][MAXN][2505][3]; 
bool col[MAXN][MAXN];

int main(){
    scanf("%d%d%d",&n,&m,&t);
    for(register int i=1;i<=n;i++){
        char c[MAXN];
        scanf("%s",c+1);
        for(register int j=1;j<=m;j++)
            col[i][j]=c[j]-'0';
    }
    for(register int i=1;i<=n;i++)
    for(register int j=1;j<=m;j++)
    for(register int k=1;k<=t;k++){
        if(j==1){
            dp[i&1][j][k][0]=max(dp[(i-1)&1][m][k][1],dp[(i-1)&1][m][k][0]);
            dp[i&1][j][k][0]=max(dp[i&1][j][k][0],dp[(i-1)&1][m][k][2]);
            dp[i&1][j][k][1]=max(dp[(i-1)&1][m][k-1][1],dp[(i-1)&1][m][k-1][0]);
            dp[i&1][j][k][1]=max(dp[i&1][j][k][1],dp[(i-1)&1][m][k-1][2]);
            dp[i&1][j][k][2]=max(dp[(i-1)&1][m][k-1][1],dp[(i-1)&1][m][k-1][0])+1;
            dp[i&1][j][k][2]=max(dp[i&1][j][k][2],dp[(i-1)&1][m][k-1][2]+1);
        } 
        else{
            if(col[i][j]==col[i][j-1]){
                dp[i&1][j][k][2]=dp[i&1][j-1][k][2]+1;
                dp[i&1][j][k][1]=max(dp[i&1][j-1][k][1],dp[i&1][j-1][k-1][0]);
                dp[i&1][j][k][0]=max(dp[i&1][j-1][k][0],dp[i&1][j-1][k][1]);
            }
            else{
                dp[i&1][j][k][2]=max(dp[i&1][j-1][k][1],dp[i&1][j-1][k-1][0])+1;
                dp[i&1][j][k][2]=max(dp[i&1][j-1][k-1][2]+1,dp[i&1][j][k][2]);
                dp[i&1][j][k][1]=max(dp[i&1][j-1][k][2],dp[i&1][j-1][k-1][0]);
                dp[i&1][j][k][0]=max(dp[i&1][j-1][k][0],dp[i&1][j-1][k][2]);
            }   
        }       
//      cout<<dp[i][j][k][0]<<" "<<dp[i][j][k][1]<<" ";
//      cout<<dp[i][j][k][2]<<endl;
    }
    printf("%d",max(max(dp[n&1][m][t][0],dp[n&1][m][t][1]),dp[n&1][m][t][2]));
    return 0;
}
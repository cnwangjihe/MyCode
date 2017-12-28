#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
using namespace std;
const int MOD = 100000000;
const int MAXN = 13;
const int MAXSTATE = 8193;
int dp[MAXN][MAXSTATE];
int matrix[MAXN][MAXN];
int vst[MAXSTATE];
int vnum = 0, row = 0, col = 0;
//get valid state num
void getvalidstate()
{
    for(int i = 0; i < (1<<col); ++i)
    {
        if(0 == (i&(i<<1)))
            vst[vnum++] = i;
    }
}
bool valid(int state, int r)
{
    int rstate = 0;
    for(int i = 1; i <= col; ++i)
    {
        if(matrix[r][i])
            rstate += (1<<(col - i));
    }
//    printf("r state : %d %d\n", r, rstate);
    if(!(state&(~rstate)))
        return true;
    return false;
}
int main()
{
    int m, n, i, j;
    while(EOF != scanf("%d%d", &m, &n)){
    for(i = 1; i <= m; ++i)
        for(j = 1; j <= n; ++j)
            scanf("%d", &matrix[i][j]);
    row = m;
    col = n;
    vnum = 0;
    getvalidstate();
    memset(dp, 0, sizeof(int)*MAXN*MAXSTATE);
    dp[0][0] = 1;
    for(i = 1; i <= row; ++i)
    {
        for(int st = 0; st < vnum; ++st)
        {
            if(valid(vst[st], i))
            {
                for(int pst = 0; pst < vnum; ++pst)
                {
                    if(valid(vst[pst], i - 1) && !(vst[st]&vst[pst]))
                        dp[i][vst[st]] += dp[i - 1][vst[pst]];
                }
            }
        }
    }
    int ret = 0;
    for(i = 0; i < vnum; ++i)
    {
        ret = (ret + dp[row][vst[i]])%MOD;
    }
    printf("%d\n", ret);
  }
}
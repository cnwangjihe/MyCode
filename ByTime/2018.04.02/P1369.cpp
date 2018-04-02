#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <algorithm>

using namespace std;

const int MAXN = 109;

int mp[MAXN][MAXN],a[MAXN][MAXN],b[MAXN][MAXN];
int ans=0,n;

int main()
{
    int x,y,D,sum;
    scanf("%d",&n);
    for (int i=0;i<n;i++)
        scanf("%d%d",&x,&y),mp[x][y]=1;
    for (int i=1;i<=100;i++)
        for (int j=1;j<=100;j++)
            a[i][j]=a[i][j-1]+mp[i][j],
            b[i][j]=b[i-1][j]+mp[i][j];
    for (int L=1;L<=100;L++)
    {
        for (int R=L+1;R<=100;R++)
        {
            D=1;
            for (int U=2;U<=100;U++)
            {
                sum=a[U][R]-a[U][L-1]+a[D][R]-a[D][L-1];
                sum+=b[U-1][L]-b[D][L]+b[U-1][R]-b[D][R];
                ans=max(ans,sum);
                if (a[U][R]-a[U][L-1]-(b[U-1][L]-b[D-1][L]+b[U-1][R]-b[D-1][R])>a[D][R]-a[D][L-1])
                    D=U;
            }
        }
    }
    printf("%d\n",ans);
}
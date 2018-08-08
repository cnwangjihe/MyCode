#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

using namespace std;
  
const int MAXN = 100005; 
int n,a[MAXN],c[MAXN];
vector<int> ans;
  
int main() 
{
 
    scanf("%d", &n);
    int mx=0;
    for(int i=1;i<=n;++i) 
    {
        scanf("%d",&a[i]);c[a[i]]++;
        mx=max(mx,a[i]);
    }
    if(c[mx]==1) 
    {
        puts("NO");
        return 0;
    }
    bool flag=false;
     
    for(int i=mx;i;--i) 
    {
        int cur=c[i]%10,go=c[i]/10;
        c[i-1]+=go;
        if(cur == 0) 
            ans.push_back((i==mx?1:0));
        else
        {
            int add=10-cur;
            if (i==mx) 
            {
                ++add;
                if(add==10) 
                {
                    flag=true;
                    --add;
                }
            }
            ans.push_back(add);c[i-1]++;
        }
    }
     
    if(c[0]==1) 
    {
        puts("YES");
        reverse(ans.begin(), ans.end());
        for(int i=1;i<=n;++i) 
        {
            printf("0.");
            if(a[i]==mx) 
            {
                if (flag) 
                {
                    for(int j=1;j<a[i];++j) 
                        printf("0");
                    puts("2");
                    flag=false;
                    continue;
                }
                for(int j=0;j<ans.size();++j)
                    printf("%d",ans[j]);
                puts("");mx=-1;
            } 
            else
            {
                for(int j=1;j<a[i];++j)
                    printf("0");
                puts("1");
            }
        }
    } 
    else
        puts("NO");
 
    return 0;
}
#include <bits/stdc++.h>
using namespace std;
int ans[200005],vis[200005];
int main() {
    memset(vis,0,sizeof(vis));
    int n,num=0;
    cin>>n;
    for(int i=1;i<=n;++i) {
        scanf("%d",&ans[i]);
    }
    for(int i=n;i>=1;i--) {
        if(vis[i]) continue;
        num++;vis[i]=1;
        int j=i;
        while(ans[j]!=0||vis[ans[j]]==0) {
            vis[ans[j]]=1;
            j=ans[j];
        }
    }
    cout<<num<<endl;
    return 0;
}

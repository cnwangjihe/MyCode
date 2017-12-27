#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
typedef long long LL;
int n,m;
const int maxn = 1e5+7;
int a[maxn];pii ps[maxn];
int main(){
	a[0] = 1e9+7;
	scanf("%d%d",&n,&m);
	for(int i = 1;i <= n;++i) scanf("%d",&a[i]);
	for(int i = 1;i <= m;++i) scanf("%d",&ps[i].first);
	for(int i = 1;i <= m;++i) scanf("%d",&ps[i].second);
	sort(ps+1,ps+1+m);
	priority_queue<int,vector<int>,greater<int> >Q;
	int j = 0,k,pre = 1;
	LL tot;
	int ans = 0;
	for(int i = n;i >= 1;i = j){
		tot = 0;
		for(j = i;a[j] <= a[i];j--) tot += a[j];
		
		for(k = pre;k <= m && ps[k].first <= a[i];++k) Q.push(ps[k].second);
		pre = k;
		while(!Q.empty()){
			if(tot >= Q.top()) ans++,tot -= Q.top(),Q.pop();
			else{
				tot = Q.top()-tot;
				Q.pop();
				Q.push(tot);
				break;
			}
		}
	}
	cout<<ans<<endl;
	return 0;
} 

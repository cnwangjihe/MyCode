#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<algorithm>
#define LL long long int
#define Redge(u) for (int k = h[u],to; k; k = ed[k].nxt)
#define REP(i,n) for (int i = 1; i <= (n); i++)
#define BUG(s,n) for (int i = 1; i <= (n); i++) cout<<s[i]<<' '; puts("");
using std::max;using std::min;using std::swap;
const int maxn = 300005,maxm = 100005;
const LL INF = 1000000000000000000ll;
inline int read(){
    int out = 0,flag = 1; char c = getchar();
    while (c < 48 || c > 57){if (c == '-') flag = -1; c = getchar();}
    while (c >= 48 && c <= 57){out = (out << 3) + (out << 1) + c - 48; c = getchar();}
    return out * flag;
}
char s[maxn];
int sa[maxn],rank[maxn],height[maxn],t1[maxn],t2[maxn],bac[maxn],n,m;
void getsa(){
    int *x = t1,*y = t2; m = 256;
    for (int i = 0; i <= m; i++) bac[i] = 0;
    for (int i = 1; i <= n; i++) bac[x[i] = s[i]]++;
    for (int i = 1; i <= m; i++) bac[i] += bac[i - 1];
    for (int i = n; i; i--) sa[bac[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1){
        int p = 0;
        for (int i = n - k + 1; i <= n; i++) y[++p] = i;
        for (int i = 1; i <= n; i++) if (sa[i] - k > 0) y[++p] = sa[i] - k;
        for (int i = 0; i <= m; i++) bac[i] = 0;
        for (int i = 1; i <= n; i++) bac[x[y[i]]]++;
        for (int i = 1; i <= m; i++) bac[i] += bac[i - 1];
        for (int i = n; i; i--) sa[bac[x[y[i]]]--] = y[i];
        swap(x,y);
        p = x[sa[1]] = 1;
        for (int i = 2; i <= n; i++)
            x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k] ? p : ++p);
        if (p >= n) break;
        m = p;
    }
    for (int i = 1; i <= n; i++) rank[sa[i]] = i;
    for (int i = 1,k = 0; i <= n; i++){
        if (k) k--;
        int j = sa[rank[i] - 1];
        while (s[i + k] == s[j + k]) k++;
        height[rank[i]] = k;
    }
}
LL lcp[maxn],cnt[maxn],last[maxn],tmx[maxn],tmn[maxn],top;
LL mx[maxn],sum[maxn],val[maxn];
LL rmx[maxn][20],rmn[maxn][20],Log[maxn];
void init(){
    Log[0] = -1; mx[0] = -INF;
    for (int i = 1; i <= n; i++){
        Log[i] = Log[i >> 1] + 1;
        rmx[i][0] = rmn[i][0] = val[sa[i]];
        mx[i] = -INF;
    }
    for (int j = 1; j <= 19; j++){
        for (int i = 1; i + (1 << j) - 1 <= n; i++){
            rmx[i][j] = max(rmx[i][j - 1],rmx[i + (1 << j - 1)][j - 1]);
            rmn[i][j] = min(rmn[i][j - 1],rmn[i + (1 << j - 1)][j - 1]);
        }
    }
}
LL getmx(int l,int r){
    int t = Log[r - l + 1];
    return max(rmx[l][t],rmx[r - (1 << t) + 1][t]);
}
LL getmn(int l,int r){
    int t = Log[r - l + 1];
    return min(rmn[l][t],rmn[r - (1 << t) + 1][t]);
}
void solve(){
    for (int i = 2; i <= n+1; i++){
        int tot = 1;
        LL gmax = val[sa[i - 1]],gmin = val[sa[i - 1]];
        while (top && lcp[top] >= height[i]){
            sum[lcp[top]] += (LL)cnt[top] * (i - last[top]);
            mx[lcp[top]] = max(mx[lcp[top]],max(getmx(last[top],i - 1) * tmx[top],getmn(last[top],i - 1) * tmn[top]));
            std::cerr << lcp[top] << ':' << i-1 << '\n';
            gmax = max(gmax,tmx[top]);
            gmin = min(gmin,tmn[top]);
            tot += cnt[top--];
        }
        lcp[++top] = height[i]; cnt[top] = tot; last[top] = i;
        tmx[top] = gmax; tmn[top] = gmin;
        std::cerr << cnt[top] << '\n';
    }
}
void print(){
    for (int i = n - 1; i >= 0; i--)
        sum[i] += sum[i + 1],mx[i] = max(mx[i],mx[i + 1]);
    for (int i = 0; i < n; i++)
        printf("%lld %lld\n",sum[i],mx[i] == -INF ? 0 :mx[i]);
}
int main(){
    n = read();
    scanf("%s",s + 1);
    for (int i = 1; i <= n; i++) val[i] = read();
    getsa();
    init();
    solve();
    print();
    for (int i=1;i<=n;i++)
        std::cerr << getmx(i,i) << ' ';
    return 0;
}
#include<cstdio>
#include<cctype>
#include<ext/pb_ds/assoc_container.hpp>
inline int getint() {
    register char ch;
    while(!isdigit(ch=getchar()));
    register int x=ch^'0';
    while(isdigit(ch=getchar())) x=(((x<<2)+x)<<1)+(ch^'0');
    return x;
}
inline int getval() {
    register char ch;
    while(!isalpha(ch=getchar()));
    return ch=='W';
}
typedef long long int64;
int n,m;
long long CCC=0;
__gnu_pbds::cc_hash_table<int64,double> map;
inline int del(const int &s,const int &i) {
    return (s>>(i+1)<<i)+(s&((1<<i)-1));
}
inline int bit(const int &s,const int &i) {
    return (s>>i)&1;
}
double dfs(const int &s,const int &cnt) {
    if(cnt<=n-m) return 0;
    const int64 p=(1ll<<cnt)|s;
    if(map.find(p)!=map.end()) return map[p];
    CCC++;
    double ret=0;
    for(register int i=0;i<cnt;i++) {
        double tmp=0;
        const int j=cnt-i-1;
        tmp=std::max(tmp,dfs(del(s,i),cnt-1)+bit(s,i));
        tmp=std::max(tmp,dfs(del(s,j),cnt-1)+bit(s,j));
        ret+=tmp;
    }
    ret/=cnt;
    return map[p]=ret;
}
int main() {
    n=getint(),m=getint();
    int all=0;
    for(register int i=0;i<n;i++) {
        all=all<<1|getval();
    }
    printf("%.8f\n",dfs(all,n));
    printf("%lld\n",CCC);
    return 0;
}
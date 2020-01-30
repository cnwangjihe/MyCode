#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#define N 1020
using namespace std;

long long a[N];
pair<long long, pair<int, int> > e[N * N];
int p[N];

inline int find(const int &x)
{
    return p[x] == x ? x : p[x] = find(p[x]);
}

int main(void)
{
    int n, m;
    int i, j;
    long long o;

    // freopen("2865.in" , "r", stdin );
    // freopen("2865.out", "w", stdout);

    scanf("%d", &n);
    for(i = 1; i <= n; i ++)
    {
        scanf("%lld", &a[i]);
        a[i] ^= a[i - 1];
    }

    for(i = 0; i <= n; i ++)
        p[i] = i;
    for(i = 1, m = 0; i <= n; i ++)
        for(j = i; j <= n; j ++)
            e[m ++] = make_pair(a[j] ^ a[i - 1], make_pair(i - 1, j));

    sort(e, e + m);
    for(i = o = 0; i < m; i ++)
        if(find(e[i].second.first) != find(e[i].second.second))
        {
             o += e[i].first;
             p[find(e[i].second.first)] = find(e[i].second.second);
        }

    printf("%lld\n", o);

    return 0;
}
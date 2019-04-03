#include <iostream>
#include <algorithm>
#include <cstdio>
#define N 2000020
#pragma GCC optimize("O3")
using namespace std;

__int128 Ceil(__int128 a, __int128 b)
{
    return a <= 0 ? 0 : a / b + (a % b ? 1 : 0);
}

__int128 Scan(void)
{
    __int128 s;
    int c;

    for(s = 0; (c = getchar()) < '0' || c > '9'; )
        ;
    do
        s = s * 10 + c - 48;
    while((c = getchar()) >= '0' && c <= '9');

    return s;
}

void Print(__int128 x)
{
    static int b[20], c;

    if(!x)
        printf("0");
    else
    {
        for(c = 0; x; x /= 10)
            b[c ++] = x % 10;
        while(c --)
            printf("%d", b[c]);
    }
    printf("\n");

    return;
}

int main(void) // 2844.cpp
{
    int t;
    __int128 n, m, k, v;
    __int128 o, s, r;
    int i;

    // freopen("2844.in" , "r", stdin );
    // freopen("2844.out", "w", stdout);

    cin >> t;
    while(t --)
    {
        n = Scan();
        m = Scan();
        k = Scan();
        v = Scan();

        o = Ceil(v, n * m);
        s = Ceil(k, n * m);
        r = n * m * s - k;
         cout<<(long long)r<<endl;
        for(i = 1; i <= N; i ++)
        {
            if(n > m)
                m ++;
            else
                n ++;

            // printf("at inc %d\n", i);
            // Print(n);
            // Print(m);
            // // puts("");
            // Print(o);
            // Print(s);
            // Print(r);
            // puts("-----");
            // if(i>10)break;

            o = min(o, s + Ceil(v - r, n * m));
            s += Ceil(k - r, n * m);
            // if(k <= r)
            //     r -= k;
            // else
                r = n * m * Ceil(k - r, n * m) - (k - r);
        }
        Print(o);
    }

    return 0;
}

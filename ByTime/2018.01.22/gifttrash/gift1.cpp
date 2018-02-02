#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std ;

#define N 1000 + 10
const int MAXN = 1000 ;
struct Object {
    int a , b , c ;
} P[N] ;

int Qv[N] , Qx[N] ;
int f[15][N] , ans[N][N] ;
int n , m , Cnt ;

void Calc( int l , int r ) {
    for (int i = 0 ; i <= MAXN ; i ++ ) f[Cnt][i] = f[Cnt-1][i] ;
    for (int i = l ; i <= r ; i ++ ) {
        int v = P[i].a , w = P[i].b , c = P[i].c ;
        for (int b = 0 ; b < v ; b ++ ) {
            int head = 1 , tail = 0 ;
            for (int a = 0 ; a * v + b <= MAXN ; a ++ ) {
                int last = f[Cnt][a*v+b] - a * w ;
                while ( tail >= head && Qv[tail] < last ) tail -- ;
                ++ tail ;
                Qv[tail] = last ;
                Qx[tail] = a ;
                while ( head <= tail && a - Qx[head] > c ) head ++ ;
                f[Cnt][a*v+b] = Qv[head] + a * w ;
            }
        }
    }
}

void DIV( int l , int r ) {
    if ( l == r ) {
        for (int i = 0 ; i <= MAXN ; i ++ ) ans[l][i] = f[Cnt][i] ;
        return ;
    }
    ++ Cnt ;
    int mid = (l + r) / 2 ;
    Calc( mid + 1 , r ) ;
    DIV( l , mid ) ;
    Calc( l , mid ) ;
    DIV( mid + 1 , r ) ;
    Cnt -- ;
}

int main() {
	freopen("gift.in" , "r" , stdin);
	freopen("gift1.out" , "w" , stdout);
    scanf( "%d" , &n ) ;
    for (int i = 1 ; i <= n ; i ++ ) scanf( "%d%d%d" , &P[i].a , &P[i].b , &P[i].c ) ;
    DIV( 1 , n ) ;
    scanf( "%d" , &m ) ;
    for (int i = 1 ; i <= m ; i ++ ) {
        int d , e ;
        scanf( "%d%d" , &d , &e ) ;
        d ++ ;
        printf( "%d\n" , ans[d][e] ) ;
    }
    return 0 ;
}


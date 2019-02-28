// Date      : 2019-02-18 08:50:59
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : Test

#include <bits/stdc++.h>

using std::swap;using std::max;using std::copy;
using std::cerr;using std::min;using std::fill;

int n;
int cnt[100];

int main()
{
//	freopen("#1.in","r",stdin);
//	freopen("#1.out","w",stdout);
	cnt[0]=5;
	cnt[++n]=cnt[n]+7;
	cerr << cnt[n] << ' ' << cnt[0] << '\n';
	return 0;
}
#include <bits/stdc++.h>
using namespace std;
int x[114514], y[114514], n;
int used[114514];
int cover;
#define place(xm, ym) {\
	for(register int l=0; l<n; ++l) if (xm <= x[l] && (xm+M) >= x[l] && ym <= y[l] && (ym+M) >= y[l]) {\
		++used[l]; if (used[l]==1) ++cover;\
	}\
}
#define unplace(xm, ym) {\
	for(register int l=0; l<n; ++l) if (xm <= x[l] && (xm+M) >= x[l] && ym <= y[l] && (ym+M) >= y[l]) {\
		--used[l]; if (used[l]==0) --cover;\
	}\
}
#define test \
	if ((cover == n) || dfs(M, bk-1)) return 1;

int UX0=2e9, UY0=2e9, DX0=-1e9, DY0=-1e9;
inline bool dfs(int M, int bk) {
	int UX=2e9, UY=2e9, DX=-1e9, DY=-1e9;
	if (bk == 3) {UX=UX0, UY=UY0, DX=DX0-M, DY=DY0-M;}
	else { for(register int i=0; i<n; ++i) {
		if (!used[i]) {
			if (x[i] < UX) UX = x[i]; 
			if (y[i] < UY) UY = y[i];
			if (x[i]-M > DX) DX = x[i]-M; 
			if (y[i]-M > DY) DY = y[i]-M;
		}
	} }
	if (bk == 1) return DX <= UX && DY <= UY;
	place(UX, UY); test; unplace(UX, UY);
	place(DX, DY); test; unplace(DX, DY);
	place(UX, DY); test; unplace(UX, DY);
	place(DX, UY); test; unplace(DX, UY);
	return 0;
}
inline bool teszt(int M) {
	memset(used, 0, sizeof used);
	cover = 0;
	return dfs(M, 3);
}
int main() {
//	freopen("2585.in","r",stdin);
//	freopen("2585.out","w",stdout);
	scanf("%d", &n);
	if (n<=3) {puts("0"); return 0;}
	for(register int i=0; i<n; i++) { scanf("%d%d", x+i, y+i);
		if (x[i] < UX0) UX0 = x[i]; 
		if (y[i] < UY0) UY0 = y[i];
		if (x[i] > DX0) DX0 = x[i]; 
		if (y[i] > DY0) DY0 = y[i];
	}
	register int L=-1, R=1e9+3, M;
	while(L+1 < R) {
		M = (L+R)>>1;
		if (teszt(M)) R=M; else L=M;
	}
	printf("%d\n", R);
}
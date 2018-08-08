#include <bits/stdc++.h>

using namespace std;

const int MAXN = 120009;

int x[MAXN], y[MAXN];
int used[MAXN];
int n,cover;
void place(int xm,int ym,int M)
{
	for (int l=0; l<n; l++)
		if (xm <= x[l] && (xm+M) >= x[l] && ym <= y[l] && (ym+M) >= y[l])
		{
			cover+=(!used[l]);
			used[l]++;
		}
	return ;
}
void unplace(int xm,int ym,int M)
{
	for(int l=0; l<n; l++)
		if (xm <= x[l] && (xm+M) >= x[l] && ym <= y[l] && (ym+M) >= y[l]) 
		{
			used[l]--;
			cover-=(!used[l]);
		}
	return ;
}
#define test \
	if ((cover == n) || dfs(M, bk-1)) return 1;

int UX0=2e9, UY0=2e9, DX0=-1e9, DY0=-1e9;
bool dfs(int M, int bk)
{
	int UX=2e9, UY=2e9, DX=-1e9, DY=-1e9;
	if (bk == 3){UX=UX0, UY=UY0, DX=DX0-M, DY=DY0-M;}
	else
		for (int i=0; i<n; ++i)
			if (!used[i])
			{
				if (x[i] < UX) UX = x[i]; 
				if (y[i] < UY) UY = y[i];
				if (x[i]-M > DX) DX = x[i]-M; 
				if (y[i]-M > DY) DY = y[i]-M;
			}
	if (bk == 1)
		return DX <= UX && DY <= UY;
	place(UX, UY, M); test; unplace(UX, UY, M);
	place(DX, DY, M); test; unplace(DX, DY, M);
	place(UX, DY, M); test; unplace(UX, DY, M);
	place(DX, UY, M); test; unplace(DX, UY, M);
	return 0;
}
bool teszt(int M)
{
	memset(used, 0, sizeof used);
	cover = 0;
	return dfs(M, 3);
}
int main()
{
	freopen("2585.in","r",stdin);
	freopen("2585.out","w",stdout);
	scanf("%d",&n);
	if (n<=3) 
		return printf("0\n"),0;
	for (int i=0; i<n; i++)
	{
		scanf("%d%d", x+i, y+i);
		if (x[i] < UX0) UX0 = x[i]; 
		if (y[i] < UY0) UY0 = y[i];
		if (x[i] > DX0) DX0 = x[i]; 
		if (y[i] > DY0) DY0 = y[i];
	}
	int L=-1, R=1e9+3, M;
	while(L+1 < R)
	{
		M = (L+R)/2;
		if (teszt(M))
			R=M;
		else
			L=M;
	}
	printf("%d\n",R);
	return 0;
}
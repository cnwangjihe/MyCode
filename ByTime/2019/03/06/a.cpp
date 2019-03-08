// Date      : 2019-03-06 10:56:26
// Author    : Wangjihe (wangjihe.mail@gmail.com)
// Link      : wangjihe.cf
// Algorithm : 
// Notice    : None

#include <bits/stdc++.h>

using namespace std;

const bool BLACK = 1,
		   WHITE = 0;

inline bool Check(char c){return c=='.' || c=='W' || c=='B';}

const int MAXN = 100009;

char s[MAXN],t[MAXN];
int n,l,r;

bool Solve(int l,int r,int fst)
{
	int lcnt=0,rcnt=0,c,mcnt;
	while (t[l]!='W' && l>=0)
		l--;
	while (t[r]!='B' && r<n)
		r++;
//	cerr << l << ' ' << r << endl;
	if (l<0)
		return 1;
	if (r>=n)
		return 0;
	mcnt=r-l-2;
	t[l]=t[r]='.';
	l+=(mcnt)/2,r-=(mcnt)/2;
//	cerr << l << ' ' << r << ' ' << mcnt << endl;
	if (mcnt&1)
	{
		if (fst==BLACK)
			r--,fst=WHITE;
		else
			l++,fst=BLACK;
	}
//	cerr << l << ' ' << r << endl;
	t[l]='W',t[r]='B';
	c=0;
	for (int i=0;i<=l;i++)
		if (t[i]=='.')
			lcnt+=c;
		else
			c++;
	c=0;
	for (int i=n-1;i>=r;i--)
		if (t[i]=='.')
			rcnt+=c;
		else
			c++;
//	cerr << lcnt << ' ' << rcnt << '\n';
	if (lcnt==rcnt)
		return fst==WHITE;
	if (lcnt>rcnt)
		return 0;
	if (lcnt<rcnt)
		return 1;
	return 0;
}

int main()
{
	freopen("a.in","r",stdin);
	freopen("a.out","w",stdout);
	int T;
	scanf("%d",&T);
	for (int cn=1;cn<=T;cn++)
	{
		n=0;
		int ans=1;
		do {s[0]=getchar();}
			while (!Check(s[0]));
		do {s[++n]=getchar();}
			while (Check(s[n]));
		s[n]='\0';
		r=0,l=n-1; 
		while (s[r]!='B' && r<n)
			r++;
		while (s[l]!='W' && l>=0)
			l--;

		if (l+1==r)
		{
			if (r+1<n && s[r+1]=='B')
			{
				strcpy(t,s);
				t[l]=t[r+1]='.';
				ans&=Solve(l,r,WHITE);
			}
			else
			{
				strcpy(t,s);
				t[l]='.',t[r]='W';
				ans&=Solve(r,r,BLACK);
			}
			strcpy(t,s);
			t[l]='.';
			ans&=Solve(l,r,WHITE);
		}
		else
		{
			strcpy(t,s);
			ans&=Solve(l,r,WHITE);
		}
		putchar(ans?'B':'W');
		putchar('\n');
	}
	return 0;
}
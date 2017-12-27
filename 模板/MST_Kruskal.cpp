#include<iostream>
#include<fstream>
#include<algorithm>

using namespace std;

struct Tline{
	int a,b,len;
}Line[10005];

int fa[10005];
int n,m,ans=0;

bool _cmp(Tline a,Tline b)
{
	return a.len<b.len;
}

int u_f(int x)
{
	int root = x;
	while (fa[root]!=root) root=fa[root];
	while (fa[x]!=x) { int y = fa[x]; fa[x] = root; x = y;}
	return root;
}

int main()
{
	cin >> n >> m;
	for (int i=0;i<n;i++) fa[i]=i;
	for (int i=0;i<m;i++) 
		cin >> Line[i].a >> Line[i].b >> Line[i].len;
	sort(Line,Line+m,_cmp);
	for (int i=0;i<m&&n>0;i++)
	{
		int f_a=u_f(Line[i].a),f_b=u_f(Line[i].b);
		if (f_a!=f_b)
		{
			n--;
			fa[f_a]=f_b;
			ans+=Line[i].len;
		}
	}
	if (n>0) cout << "No Answer!!\n";
	else cout << ans;
}
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <vector>
#include <string>

using namespace std;

struct Tnode
{
	int r,c;
	Tnode *L,*R,*UL,*UR,*LL,*LR;
	Tnode() 
	{
		r = c = 0;
		L = R = UL = UR = LL = LR = NULL;
	}
}map[402],*row[22],*loc=map;


Tnode *goRight(Tnode*x, int d) 
{
	for (int i = 0; i < d; i++)
		x = x->R;
	return x;
}

int num[] = {0, 1, 2, 3, 4, 13, 12, 11, 10, 9, 10, 11, 12, 13, 4, 3, 2, 1};
int sp[] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 5, 1, 1, 1};
int sc[] = {0, 0, 1, 1, 1, 5, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0};

void build()
{
	Tnode *p, *c;

	for (int i = 1; i <= 17;i++)
		row[i] = loc++;

	for (int i = 1; i <= 17;i++)
	{
		p = row[i];
		for (int j = 1; j <= num[i]; j++) 
		{
			p->R = loc++;
			if (j != 1) p->R->L = p;
			p = p->R;
		}
	}

	for (int i = 2; i <= 17; i++) 
	{
		p = goRight(row[i - 1]->R, sp[i - 1]);
		c = i == 5 ? goRight(row[i]->R, 4) : row[i]->R;
		while (p && c) 
		{
			c->UR = p;
			p->LL = c;
			p = p->R;
			c = c->R;
		}
	}

	for (int i = 2; i <= 17; i++) 
	{
		c = goRight(row[i]->R, sc[i]);
		p = i == 14 ? goRight(row[i - 1]->R, 4) : row[i - 1]->R;
		while (p && c) 
		{
			c->UL = p;
			p->LR = c;
			p = p->R;
			c = c->R;
		}
	}

}


void recolor() 
{
	Tnode*p;
	for (int i = 1; i <= 17; i++) 
	{
		p = row[i]->R;
		while (p) 
		{
			p->c = 0;
			p = p->R;
		}
	}

	for (int i = 1; i <= 4; i++) 
	{
		p = row[i]->R;
		for (int j = 1; j <= i; j++)
			p->c = p->r = 1,
			p = p->R;
	}

	for (int i = 5; i <= 8; i++)
	{
		p = row[i]->R;
		for (int j = 4; i - 5 < j; --j)
			p->c = p->r = 6,
			p = p->R;
		p = goRight(row[i]->R, 9);
		for (int j = 4; i - 5 < j;j--)
			p->c = p->r = 4,
			p = p->R;
	}

	for (int i = 10; i <= 13; i++) 
	{
		p = row[i]->R;
		for (int j = 0; j < i - 9; j++)
			p->c = p->r = 3,
			p = p->R;
		p = goRight(row[i]->R, 9);
		for (int j = 0; j < i - 9; j++) 
			p->c = p->r = 5,
			p = p->R;
	}

	for (int i = 14; i <= 17; i++) 
	{
		p = row[i]->R;
		for (int j = 4; i - 14 < j; --j) 
			p->c = p->r = 2,
			p = p->R;
	}
}

Tnode*go(Tnode*c, string dir) 
{
	if (dir == "L")
		return c->L;
	if (dir == "R")
		return c->R;
	if (dir == "UL")
		return c->UL;
	if (dir == "UR")
		return c->UR;
	if (dir == "LL")
		return c->LL;
	return c->LR;
}

vector<pair<bool, Tnode*> > path;
int ok_col[7] = {0, 2, 1, 4, 3, 6, 5};

bool sym(int l, int r) 
{
	for (int i = l, j = r; i < j; i++,j--)
		if (path[i].first != path[j].first)
			return false;
	if (r < l) return true;
	int cnt = 0;
	for (int i = l; i <= r; i++)
		if (!path[i].first) ++cnt;
	return cnt > 0;
}

bool ok(int p, int c) 
{
	if (path[p].second->r == 0 || path[p].second->r == c || ok_col[path[p].second->r] == c)
		return path[p].first;
	return false;
}

vector<pair<int, int> > pos[7];

int go(Tnode*c, string dir, int t) 
{
	if (!c) return t;
	return go(go(c, dir), dir, t + 1);
}

int main() 
{
	build();
	int r, c, n;
	string dir;
	while (cin>>n) 
	{
		int ttn=n;
		recolor();
		int player = 1;
		while (n--)
		{
			cin >> r >> c >> dir;
			Tnode*p = row[r], *t;
			for (int i = 0; i < c; i++) if (p) p = p->R;
			if (p && p->c == player) 
			{
				path.clear();
				t = p;
				while (t)
				{
					path.push_back(make_pair(t->c == 0, t));
					t = go(t, dir);
				}
			//	printf("%d\n", (int)path.size());
				t = NULL;
				for (int i = 1; i < (int)path.size(); i++) 
					if (sym(1, i - 1) && ok(i, p->c))
						t = path[i].second;
				if (t != NULL) 
					swap(t->c, p->c);
			}
			for (int i = 1; i <= 6; i++)
				pos[i].clear();
			for (int i = 1; i <= 17; i++) 
			{
				p = row[i]->R;
				for (int j = 1; p; p = p->R, j++)
					if (p->c) pos[p->c].push_back(make_pair(i, j));
			}
			player %= 6;
			player++;
		}
		for (int i = 1; i <= 6; i++) 
		{
			sort(pos[i].begin(), pos[i].end());
		//	if (pos[i][0]=='R') 
		//	{
		//		int j=0;
		//		while (pos[i][++j]-'0')
		//		{
		//			printf("%c*",pos[i][j]);
		//			pos[i][j+1]+=pos[i][0]*(i-j);
		//		}
		//	}
			for (int j = 0; j < (int)pos[i].size(); j++)
			{
				if (ttn>=10000)
				printf("%d %d ", pos[i][j].first-1, pos[i][j].second);
				else
				printf("%d %d ", pos[i][j].first, pos[i][j].second);
			}
			printf("\n");
			
		}
	}
	return 0;
}

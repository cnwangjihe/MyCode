#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <string.h>
#include <cmath>

using namespace std;

const int MAXN = 300500,
		  MAXM = 10000000;
int n,m,now,o[MAXN],q,root[N],fp,sz[MAXM],ls[MAXM],rs[MAXM];
long long val[MAXM];

int get_sz(int l,int r)
{
	if(now == n + 1)
	{
		if(r <= n) return r - l + 1;
		if(l <= n) return n - l + 1;
		return 0;
	}
	if(r < m) return r - l + 1;
	if(l < m) return m - l ;
	return 0;
}

long long query(int &root,int l,int r,int x)
{
	if(!root)
	{
		root = ++fp;
		sz[root] = get_sz(l,r);
		if(l == r)
		{
			if(now <= n) val[root] = (long long)(now - 1) * m + l;
				else val[root] = (long long)l * m;
		}
	}
	sz[root]--;
	if(l == r) return val[root];
	int mid = (l + r) >> 1;
	if((!ls[root] && x <= (mid - l + 1)) || x <= sz[ls[root]]) 
		return query(ls[root],l,mid,x);
	if(!ls[root]) x -= (mid - l + 1); 
		else x -= sz[ls[root]];
	return query(rs[root],m,r,x);
}

void update(int &root,int x,ll w,int l,int r)
{
	if(!root)
	{
		root = ++fp;
		sz[root] = get_sz(l,r);
		if(l == r) val[root] = w;
	}
	sz[root]++;
	if(l == r) return ;
	int mid = (l + r) >> 1;
	if(x <= mid) update(ls[root],x,w,l,mid);
		else update(rs[root],x,w,mid + 1,r);
	return ;
}

int main()
{
	
}

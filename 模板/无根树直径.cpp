#include<iostream>
#include<fstream>
#include<math.h>
#include<algorithm>

using namespace std;

struct Tnode{
	int num,next;
};

int Head[10005],sx[10005],xh[10005],Max[10005],nd_Max[10005];
int fp=0,ans=0;
Tnode D[10005];
bool f[10005];

void _add(int h,int num)
{
	fp++;
	D[fp].num=num;
	D[fp].next=D[Head[h]].next;
	D[Head[h]].next=fp;
}


void _bfs(int root)
{
	int head=1,tail=1,line[10005],_next,_fa;
	line[tail] = Head[root];
	f[root]=1;
	while (head<=tail)
	{
		_next=D[line[head]].next;
		_fa=line[head];
		for (;_next!=0;_next = D[_next].next)
			if (!f[D[_next].num])
			{
				tail++;
				line[tail] = Head[D[_next].num];
				f[D[_next].num]=1;
				_fa=_next;
			}
			else D[_fa].next=D[_next].next;
		xh[D[line[head]].num]=head;
		head++;
	}
}

bool _cmp(int a,int b)
{
	return xh[a]>xh[b];
}

int main()
{
	int n,root=1,m,node;
	cin >> n;
	for (int i=1;i<=n;i++)
	{
		cin >> m;
		fp++;
		D[fp].num=i;
		Head[i]=fp;
		for (int j=1;j<=m;j++)
		{
			cin >> node;
			_add(i,node);
		}
	}
	_bfs(root);
	for (int i=1;i<=n;i++) sx[i]=i;
	sort(sx+1,sx+n+1,_cmp);
	int _next;
	for (int i=1;i<=n;i++)
	{
		_next=D[Head[sx[i]]].next;
		for (;_next!=0;_next = D[_next].next)
		{
			if (Max[D[_next].num]+1>Max[Head[sx[i]]])
			{
				nd_Max[Head[sx[i]]]=Max[Head[sx[i]]];
				Max[Head[sx[i]]]=Max[D[_next].num]+1;
			}
			else 
			{
				if (Max[D[_next].num]+1>nd_Max[Head[sx[i]]]) nd_Max[Head[sx[i]]]=Max[D[_next].num]+1;
				else if (nd_Max[D[_next].num]+1>nd_Max[Head[sx[i]]]) nd_Max[Head[sx[i]]]=nd_Max[D[_next].num]+1;	
			}
			
		}
		if (Max[Head[sx[i]]]+nd_Max[Head[sx[i]]]>ans)
			ans=Max[Head[sx[i]]]+nd_Max[Head[sx[i]]];
		cout << Max[Head[sx[i]]] << ' ' << nd_Max[Head[sx[i]]] << endl;
	}
	cout << ans;
}
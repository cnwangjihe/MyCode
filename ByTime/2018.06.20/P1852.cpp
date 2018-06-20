#include <bits/stdc++.h>

using namespace std;

const int INF = 1000000009;

struct Tnode
{
	int x, y, z;
	bool operator ==(Tnode a)
	{
		return a.x == x && a.y == y && a.z == z;
	}
	bool operator !=(Tnode a)
	{
		return !(*this == a);
	}
	void Reset()
	{
		if (x > y)
			swap(x, y);
		if (x > z)
			swap(x, z);
		if (y > z)
			swap(y, z);
		return ;
	}
};

Tnode a, b, r1, r2;
int used;

Tnode _getfa(Tnode p, int step)
{
	int a, b, tmp = step, k;
	while (step)
	{
		a = p.y - p.x, b = p.z - p.y;
		if (a == b)
			break;
		if (a <= b)
		{
			k = min((b - 1) / a, step);
			p.x += k * a, p.y += k * a, step -= k;
		}
		else
		{
			k = min((a - 1) / b, step);
			p.y -= k * b, p.z -= k * b, step -= k;
		}
	}
	used = tmp - step;
	return p;
}

int main()
{
	scanf("%d%d%d", &a.x, &a.y, &a.z);
	scanf("%d%d%d", &b.x, &b.y, &b.z);
	a.Reset(), b.Reset();

	int d1 = INF, d2 = INF;
	r1 = _getfa(a, d1), d1 = used;
	r2 = _getfa(b, d2), d2 = used;
	if (r1 != r2)
		return printf("NO\n"), 0;
	if (d1 > d2)
		a = _getfa(a, d1 - d2);
	else
		b = _getfa(b, d2 - d1);
	int l = -1, r = max(d1, d2), mid;
	while (l + 1 < r)
	{
		mid = (l + r) / 2;
		if (_getfa(a, mid) == _getfa(b, mid))
			r = mid;
		else
			l = mid;
	}
	printf("YES\n%d\n", 2 * r + abs(d1 - d2));
	return 0;
}
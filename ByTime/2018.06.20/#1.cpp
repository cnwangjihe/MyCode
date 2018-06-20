using namespace std;
int l, k;
il ll gi()
{
	re ll x = 0, t = 1;
	re char ch = getchar();
	while ((ch < '0' || ch > '9') && ch != '-')
		ch = getchar();
	if (ch == '-')
		t = -1, ch = getchar();
	while (ch >= '0' && ch <= '9') x = x * 10 + ch - 48, ch = getchar();
	return x * t;
}
struct node
{
	int x, y, z;
	il void init()
	{
		x = gi(), y = gi(), z = gi();
		if (x > y) swap(x, y);
		if (x > z) swap(x, z);
		if (y > z) swap(y, z);
	}
} a, b, p, q;
il bool eql(node u, node v)
{
	return u.x == v.x && u.y == v.y && u.z == v.z;
}
node getfa(node t, int s)
{
	for (l = 0; s; l += k)
	{
		re int u = t.y - t.x, v = t.z - t.y;
		if (u == v) return t;
		if (u < v)
		{
			k = min((v - 1) / u, s);
			t.x += k * u;
			t.y += k * u;
			s -= k;
		}
		else
		{
			k = min((u - 1) / v, s);
			t.y -= k * v, t.z -= k * v, s -= k;
		}
	}
	return t;
}
int main()
{
	a.init();
	b.init();
	p = getfa(a, inf);
	re int l1 = l;
	q = getfa(b, inf);
	re int l2 = l;
	if (!eql(p, q))
	{
		puts("NO");
		return 0;
	}
	if (l1 < l2) swap(a, b), swap(l1, l2);
	a = getfa(a, l1 - l2);
	re int l = 0, r = l2, mid;
	while (l < r)
	{
		mid = l + r >> 1;
		if (eql(getfa(a, mid), getfa(b, mid))) r = mid;
		else l = mid + 1;
	}
	printf("YES\n%d\n", (l << 1) + l1 - l2);
	return 0;
}
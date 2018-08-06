#include <bits/stdc++.h>

using namespace std;

int s[10], f[205][205], cnt[205], type[205];
bool have[2][205][205];
char st[205];

int main()
{
	int cas, dt, n, i, j, k, t, tot, le, ri;
//	freopen("2584.in", "r", stdin);
//	freopen("2584.out", "w", stdout);

	scanf("%d", &cas);
	for (dt = 1; dt <= cas; dt++)
	{
		scanf("%s", st + 1);
		n = strlen(st + 1);
		tot = 0;
		memset(cnt, 0, sizeof(cnt));
		for (i = 1; i <= n; i++)
			if (st[i] != st[i - 1])
			{
				type[++tot] = st[i] - '0';
				cnt[tot]++;
			}
			else
				cnt[tot]++;
		memset(f, 127, sizeof(f));
		n = tot;
		for (i = 1; i <= n; i++)
			f[i][i] = max(0, 3 - cnt[i]);
		for (i = 0; i <= n + 2; i++)
			for (j = 0; j <= n + 2; j++)
				if (i > j)
					f[i][j] = 0;
		for (i = 2; i <= n; i++)
			for (j = 1; j + i - 1 <= n; j++)
			{
				t = j + i - 1;
				for (k = j; k < t; ++k)
				{
					if (f[j][k] + f[k + 1][j + i - 1] < f[j][j + i - 1])
						f[j][j + i - 1] = f[j][k] + f[k + 1][j + i - 1];
					if (k > j && type[j] == type[j + i - 1] && type[k] == type[j])
					{
						if (cnt[j] + cnt[k] <= 2 || cnt[k] + cnt[j + i - 1] <= 2)
							f[j][j + i - 1] = min(f[j][j + i - 1], f[j + 1][k - 1] + f[k + 1][t - 1]);
					}
				}
				if (type[j] == type[j + i - 1])
					f[j][j + i - 1] = min(f[j][j + i - 1], max(0, 3 - cnt[j] - cnt[j + i - 1]) + f[j + 1][j + i - 2]);
			}
		printf("Case #%d: %d\n", dt, f[1][n]);
	}
	return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdio.h>
#include <cmath>
#include <string.h>

using namespace std;

int ans=0,n;
int a[200005];

int main()
{
	freopen("2327.in","r",stdin);
	freopen("2327.out","w",stdout);
	scanf("%d",&n);
	for (int i=0;i<n;i++) scanf("%d",&a[i]);
	sort(a,a+n);
	for (int i=1;i<n;i++)
		if (a[i]==a[i-1]) ans++;
	printf("%d\n",ans+1);
	return 0;
}

#include<bits/stdc++.h>
using namespace std;
int n,m,k,cnt;
struct ku{
	int l,r,a[2010],s[2010],num;
}b[210];
int bg,ed;
int ans;
void split(int q)
{
	++cnt;
	b[cnt].l = q;
	b[cnt].r = b[q].r;
	b[b[q].r].l = cnt;
	b[q].r = cnt;
	for(int i = k + 1;i <= b[q].num;++i) b[cnt].a[i - k] = b[cnt].s[i - k] = b[q].a[i];
	for(int i = 1;i <= k;++i) b[q].s[i] = b[q].a[i];
	b[cnt].num = b[q].num - k;
	b[q].num = k;
	sort(b[q].s + 1,b[q].s + k + 1);
	sort(b[cnt].s + 1,b[cnt].s + b[cnt].num + 1);
	if(ed == q) ed = cnt; 
}
void insert(int q,int w)
{
	int i,j;
	for(i = bg;i != ed;i = b[i].r)
	{
		if(b[i].num >= q) break;
		q -= b[i].num;
	}
	for(j = b[i].num;j >= q;--j) b[i].a[j + 1] = b[i].a[j];
	b[i].a[q] = w;
	++b[i].num;
	if(b[i].num >= k * 2)
		split(i);
	else
	{
		for(j = b[i].num - 1;j;--j)
		{
			if(b[i].s[j] <= w) break;
			b[i].s[j + 1] = b[i].s[j];
		}
		b[i].s[j + 1] = w;
	} 
}
void modify(int q,int w)
{
	int i,j;
	for(i = bg;i != ed;i = b[i].r) {
		if(b[i].num >= q) break;
		q -= b[i].num;
	}
	for(j = 1;j <= b[i].num;++j)
		if(b[i].s[j] == b[i].a[q]) break;
	for(;j < b[i].num;++j) b[i].s[j] = b[i].s[j + 1];
	b[i].a[q] = w;
	for(j = b[i].num - 1;j;--j)
	{
		if(b[i].s[j] <= w) break;
		b[i].s[j + 1] = b[i].s[j];
	}
	b[i].s[j + 1] = w;
}
int query(int al,int ar,int q)
{
	int as = 0,l,r,mid,i,j,g,sa;
	for(i = bg;i != ed;i = b[i].r)
	{
		if(b[i].num >= al) break;
		al -= b[i].num;
	}
	for(g = bg;g != ed;g = b[g].r)
	{
		if(b[g].num >= ar) break;
		ar -= b[g].num;
	}
	if(i == g)
	{
		for(j = al;j <= ar;++j) as += (b[i].a[j] < q);
		return as;
	}
	for(j = al;j <= b[i].num;++j) as += (b[i].a[j] < q);
	//cout<<q<<":"<<i<<" "<<al<<" "<<as<<" ";
	for(i = b[i].r;i != g;i = b[i].r)
	{
		sa = 0;
		l = 1,r = b[i].num;
		while(l<=r)
		{
			mid = (l + r) >> 1;
			if(b[i].s[mid] < q)
				sa=mid,l = mid+1;
			else 
				r = mid-1; 
		}
		as += sa;
		//cout<<as<<" ";
	}
	for(j = 1;j <= ar;++j) as += (b[g].a[j] < q);
	//cout<<g<<" "<<ar<<" "<<as<<endl; 
	return as;
}
int main()
{
	int i,j,l,r,u,v,al,ar,mid;
	char c;
	scanf("%d",&n);
	k = 800;
	j = k;
	for(i = 1;i <= n;++i)
{
		if(j == k)
		{
			b[cnt].num = k;
			b[cnt].r = cnt + 1;
			++cnt;
			b[cnt].l = cnt - 1;
			j = 0;
		}
		scanf("%d",&b[cnt].a[++j] );
		b[cnt].s[j] = b[cnt].a[j];
	}
	b[cnt].num = j;
	bg = 1;
	ed = cnt;
	for(i = 1;i <= cnt;++i) sort(b[i].s + 1,b[i].s + b[i].num + 1);
	scanf("%d",&m);
	for(i = 1;i <= m;++i)
	{
		do {c=getchar();}
			while(c != 'I' && c != 'M' && c != 'Q');
		if(c == 'I')
		{
			scanf("%d%d",&u,&v);
			u ^= ans;
			v ^= ans;
			//cout<<u<<" "<<v<<endl;
			insert(u,v);
		}
		else if(c == 'M')
		{
			scanf("%d%d",&u,&v);
			u ^= ans;
			v ^= ans;
			//cout<<u<<" "<<v<<endl;
			modify(u,v);
		}
		else
		{
			scanf("%d%d%d",&al,&ar,&u);
			al ^= ans;
			ar ^= ans;
			u ^= ans;
			//cout<<al<<" "<<ar<<" "<<u<<endl;
			l = 0,r = 70000;
			while(l<=r)
			{
				mid = (l + r) >> 1;
				if(query(al,ar,mid) < u)
					ans=mid,l = mid+1;
				else
					r = mid-1;
			} 
			printf("%d\n",ans);
		}
		/*for(j = bg;j;j = b[j].r)
			for(v = 1;v <= b[j].num;++v) cout<<b[j].a[v]<<" ";
		cout<<endl;
		for(j = bg;j;j = b[j].r)
			for(v = 1;v <= b[j].num;++v) cout<<b[j].s[v]<<" ";cout<<endl;
		*/
	}
	return 0;
} 

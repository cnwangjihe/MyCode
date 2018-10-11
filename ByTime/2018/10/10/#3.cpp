#include <bits/stdc++.h>

using namespace std;
const int maxn=100005;
int T,a,b,c,d,p,p1,p2,p3,p4,pp1,pp2,la[maxn],lb[maxn],lc[maxn],ld[maxn],mod,las,lp1,lp2;
struct data
{int l,r;};
data asd1[maxn],asd2[maxn];
void zuo(int p1,int p2)
{
	int ma=0,t=1;
	for (int i=1;i<=p1;i++)
	{
		while (t<p2 && asd2[t].r<asd1[i].r) t++;
		if (asd2[t].r>=asd1[i].r && asd2[t].l<=asd1[i].r)
			ma=max(ma,asd1[i].r);
	}
	t=0;
	for (int i=1;i<=p2;i++)
	{
		while (t<p1 && asd1[t].r<asd2[i].r) t++;
		if (asd1[t].r>=asd2[i].r && asd1[t].l<=asd2[i].r)
			ma=max(ma,asd2[i].r);
	}
	printf("%d\n",ma);
}
int main()
{
	cin>>T;mod=1000000007;
	for (int o=1;o<=T;o++)
	{
		cin>>a>>b>>c>>d;a--;c--;
		if (a>b || c>d) printf("0\n");
		else
		{
			p=0;
			for (int i=1;i<=a;i=a/(a/i)+1)
				{p++;la[p]=a/(a/i);}
			p1=p;p=0;
			for (int i=1;i<=b;i=b/(b/i)+1)
				{p++;lb[p]=b/(b/i);}
			p2=p;p=0;
			for (int i=1;i<=c;i=c/(c/i)+1)
				{p++;lc[p]=c/(c/i);}
			p3=p;p=0;
			for (int i=1;i<=d;i=d/(d/i)+1)
				{p++;ld[p]=d/(d/i);}
			p4=p;p=0;
			la[p1+1]=lb[p2+1]=lc[p3+1]=ld[p4+1]=mod;
			pp1=0;pp2=0;las=1;
			while (pp1<p1 || pp2<p2)
			{
				if (la[pp1+1]<lb[pp2+1])
				{
					pp1++;
					if (las<=la[pp1] && a/la[pp1]!=b/la[pp1])
					{
						p++;asd1[p].l=las;asd1[p].r=la[pp1];
					}
					las=la[pp1]+1;
				}
				else
				{
					pp2++;
					if (las<=lb[pp2] && a/lb[pp2]!=b/lb[pp2])
					{
						p++;asd1[p].l=las;asd1[p].r=lb[pp2];
					}
					las=lb[pp2]+1;
				}
			}
			for (int i=1;i<=p;i++)
				cerr << asd1[i].l << ' ' << asd1[i].r << '\n';
			lp1=p;
			pp1=0;pp2=0;las=1;p=0;
			while (pp1<p3 || pp2<p4)
			{
				if (lc[pp1+1]<ld[pp2+1])
				{
					pp1++;
					if (las<=lc[pp1] && c/lc[pp1]!=d/lc[pp1])
					{
						p++;asd2[p].l=las;asd2[p].r=lc[pp1];
					}
					las=lc[pp1]+1;
				}
				else
				{
					pp2++;
					if (las<=ld[pp2] && c/ld[pp2]!=d/ld[pp2])
					{
						p++;asd2[p].l=las;asd2[p].r=ld[pp2];
					}
					las=ld[pp2]+1;
				}
			}
			lp2=p;
			zuo(lp1,lp2);
		}
	}
	return 0;
}

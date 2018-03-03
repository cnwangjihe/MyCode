#include <iostream>
#include <fstream>
#include <stdio.h>
#include <algorithm>
#include <cmath>
#include <string.h>
#include <vector>
#include <queue>

using namespace std;

const double LFINF = 1000000000000009;
const int MAXC = 1000009; 

int n,w,u,v,t1,t2;
int m,len,pos,cnt=0;
double ans;
char c;
pair <double,int> vc[MAXC];

bool check(char c) {return (c=='E')||(c=='W');}

char _getch()
{
	char c;
	do {c=getchar();}
		while (!check(c));
	return c;
}

int main()
{
    scanf("%d%d%d%d%d%d",&n,&w,&u,&v,&t1,&t2);
    cnt=0;
    for (int i=1;i<=n;i++)
    {
    	c=_getch();
        scanf("%d",&m);
        for (int j=0;j<m;j++)
        {
            scanf("%d%d",&len,&pos);
            if (c=='E')
                pos=-pos;
            vc[cnt++]=(make_pair((double)pos/u-(double)w*i/v,1));
            vc[cnt++]=(make_pair((double)(pos+len)/u-(double)w*(i-1)/v,-1));
        }
    }
    vc[cnt++]=(make_pair(LFINF,1));
    vc[cnt++]=(make_pair(t1,0));
    sort(vc,vc+cnt);
    int tmp=0;
    for (int i=0;i<cnt-1;i++)
    {
        tmp+=vc[i].second;
        if (tmp==0 && vc[i].first>=t1)
            ans=max(ans,min((double)t2,vc[i+1].first)-vc[i].first);
    }
    printf("%0.8f\n",ans);
    return 0;
}

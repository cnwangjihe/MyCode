#include<bits/stdc++.h>
using namespace std;
struct tree{int l,r,sl,sr;} t[15000005];
int n,a[500005],tn,rt;
long long s0[31],s1[31];

void insl(int p,int x,int h,int v){
	t[p].sl+=v;
	cerr << t[p].sl;
	if (h==1) return;
	if (x&(1<<(h-2))){
		if (!t[p].r){
			t[p].r=++tn;
			t[tn].l=t[tn].r=t[tn].sl=t[tn].sr=0;
		}
		s1[h-1]-=(long long)t[t[p].l].sr*t[t[p].r].sl;
		insl(t[p].r,x,h-1,v);
		s1[h-1]+=(long long)t[t[p].l].sr*t[t[p].r].sl;
		
	}
	else{
		if (!t[p].l){
			t[p].l=++tn;
			t[tn].l=t[tn].r=t[tn].sl=t[tn].sr=0;
		}
		s0[h-1]-=(long long)t[t[p].l].sl*t[t[p].r].sr;
		insl(t[p].l,x,h-1,v);
		s0[h-1]+=(long long)t[t[p].l].sl*t[t[p].r].sr;
	}
}
void insr(int p,int x,int h,int v){
	t[p].sr+=v;
	cerr << t[p].sr;
	if (h==1) return;
	if (x&(1<<(h-2))){
		if (!t[p].r){
			t[p].r=++tn;
			t[tn].l=t[tn].r=t[tn].sl=t[tn].sr=0;
		}
		s0[h-1]-=(long long)t[t[p].l].sl*t[t[p].r].sr;
		insr(t[p].r,x,h-1,v);
		s0[h-1]+=(long long)t[t[p].l].sl*t[t[p].r].sr;
	}
	else{
		if (!t[p].l){
			t[p].l=++tn;
			t[tn].l=t[tn].r=t[tn].sl=t[tn].sr=0;
		}
		s1[h-1]-=(long long)t[t[p].l].sr*t[t[p].r].sl;
		insr(t[p].l,x,h-1,v);
		s1[h-1]+=(long long)t[t[p].l].sr*t[t[p].r].sl;
	}
}
int main(){
//	freopen("2582.in","r",stdin);
//	freopen("2582.out","w",stdout);
	int ttt;scanf("%d",&ttt);
	for (;ttt--;){
		scanf("%d",&n);
		for (int i=1;i<=n;i++) scanf("%d",&a[i]);
		
		rt=1;tn=1;long long ans=0;t[1].l=t[1].r=t[1].sl=t[1].sr=0;
		for (int i=0;i<=30;i++) s0[i]=s1[i]=0;
		for (int i=2;i<=n;i++) insr(rt,a[i],31,1),cerr << '\n';
		for (int i=1;i<=n;i++){
			for (int j=1;j<=30;j++){
				if (a[i]&(1<<(j-1))) ans+=s1[j];
				else ans+=s0[j];
			}
			insl(rt,a[i],31,1);
			cerr << '\n';
			insr(rt,a[i+1],31,-1);
			cerr << '\n';
		}
		
		cout<<ans<<endl;
	}
}
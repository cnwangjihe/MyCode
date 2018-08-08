#include<algorithm>
#include<iostream>
#include<iomanip>
#include<cstring>
#include<cstdlib>
#include<vector>
#include<cstdio>
#include<cmath>
#include<queue>
using namespace std;
inline const int Get_Int() {
	int num=0,bj=1;
	char x=getchar();
	while(x<'0'||x>'9') {
		if(x=='-')bj=-1;
		x=getchar();
	}
	while(x>='0'&&x<='9') {
		num=num*10+x-'0';
		x=getchar();
	}
	return num*bj;
}
#define pii pair<int,int>
#define mp make_pair
mt19937 g(rand());
int max(int a,int b) {
	return a>b?a:b;
}
const int maxn=200005;
struct Tree {
	int l,r,size;
	int val,max;
	Tree() {} 
	Tree(int _l,int _r,int s,int v,int m):l(_l),r(_r),size(s),val(v),max(m) {}
};
struct Treap { //以根作为接口
	Tree tree[maxn*100];
	int size;
#define val(x) tree[x].val
#define size(x) tree[x].size
	int newnode(int v) {
		tree[++size]=Tree(0,0,1,v,v);
		return size;
	}
	void push_up(int index) {
		int l=tree[index].l,r=tree[index].r;
		size(index)=size(l)+size(r)+1;
		tree[index].max=max(val(index),max(tree[l].max,tree[r].max));
	}
	pii split(int index,int num) {
		if(!index)return mp(0,0);
		int l=tree[index].l,r=tree[index].r;
		int now=++size;
		tree[now]=tree[index];
		if(num<=size(l)) {
			pii lt=split(l,num);
			tree[now].l=lt.second;
			push_up(now);
			return mp(lt.first,now);
		} else {
			pii rt=split(r,num-size(l)-1);
			tree[now].r=rt.first;
			push_up(now);
			return mp(now,rt.second);
		}
	}
	int merge(int a,int b) {
		if(!a||!b)return a+b;
		int now=++size;
		if(g()%(size(a)+size(b))<size(a)) {
			tree[now]=tree[a];
			tree[now].r=merge(tree[a].r,b);
		} else {
			tree[now]=tree[b];
			tree[now].l=merge(a,tree[b].l);
		}
		push_up(now);
		return now;
	}
} bbt;
int n,q,root[maxn],lastans;
int main() {
	srand(time(NULL));
	n=Get_Int();
	q=Get_Int();
	for(int i=1; i<=n; i++)root[0]=bbt.merge(root[0],bbt.newnode(Get_Int()));
	for(int i=1; i<=q; i++) {
		int opt=Get_Int(),x=Get_Int();
		n=bbt.tree[root[i-1]].size;
		if(opt==1) {
			x=(x+lastans)%(n+1);
			pii tmp=bbt.split(root[i-1],x);
			root[i]=bbt.merge(bbt.merge(tmp.first,bbt.newnode(Get_Int()^lastans)),tmp.second);
		} else if(opt==2) {
			x=(x+lastans)%n+1;
			root[i]=bbt.merge(bbt.split(root[i-1],x-1).first,bbt.split(root[i-1],x).second);
		} else if(opt==3) {
			x=(x+lastans)%n+1;
			int y=(Get_Int()+lastans*2)%n+1;
			if(x>y)swap(x,y);
			root[i]=root[i-1];
			lastans=bbt.tree[bbt.split(bbt.split(root[i],y).first,x-1).second].max;
			printf("%d\n",lastans);
		} else if(opt==4) {
			x=(x+lastans)%i;
			root[i]=root[x];
		}
	}
	return 0;
}
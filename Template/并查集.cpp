#include<iostream>
#include<fstream>
#include<algorithm>
 
using namespace std;
ifstream fin("tree.in");
ofstream fout("tree.out");
#define cin fin
#define cout fout
int n,m,fa[1000001],ans=0;
 
int u_f(int x)
{
   int root = x;
   while (fa[root]!=root && fa[root]!=-1) root=fa[root]; //找root
   while (fa[x]!=x && fa[x]!=-1) { int y = fa[x]; fa[x] = root; x = y;} //压缩路径
   return root;
}
 
int main()
{
   cin >> n >> m;
   for (int i=1;i<=n;i++) fa[i]=i;
   for (int i=0;i<m;i++)
   {
	 int x,y;
	 cin >> x >> y;
	 int xfa=u_f(x);int yfa=u_f(y);
	 if (xfa!=yfa) fa[yfa]=xfa;
	   else fa[xfa]=-1;  // 如果x和y已在同一个连通块上，再将它们连接就说明它已不是树，将它修改为-1（将这个连通块的root废掉）
   }
   for (int i=1;i<=n;i++) if (fa[i]==i) ans++; //如果它的祖先是自己，就说明他是一个祖先（root）。（非树的root为-1，已排除）
   cout << ans << endl;
   return 0;
}
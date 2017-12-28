#include <iostream>
#include <fstream>
#include <algorithm>
#include <string.h>
#include <cmath>
#include <math.h>

using namespace std;

ifstream fin("teacher.in");
ofstream fout("teacher.out");
#define cin fin
#define cout fout

int n,m;
bool f[200006];
int x[100006],y[100006];

void work() //处理 
{
    for (int i=0;i<n;i++)
        for (int j=i+1;j<n;j++)//不要重复
        {
            if (f[abs(x[i]-x[j])+abs(y[i]-y[j])]) //判断是否已有相同曼哈顿距离 
            {
                cout << "YES\n";
                return ;  //省去不必要的计算，节省时间 
            }
            f[abs(x[i]-x[j])+abs(y[i]-y[j])]=true; //标记 
        }
    cout << "NO\n";
}

int main()
{
    int q;
    cin >> q;
    for (;q>0;q--)
    {
        memset(f,false,sizeof f);
        cin >> n >> m;
        for (int i=0;i<n;i++) cin >> x[i] >> y[i];
        work();
    }
}
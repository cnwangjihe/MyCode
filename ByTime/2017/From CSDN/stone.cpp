#include<iostream>
#include<fstream>
#include<algorithm>
#include<stdio.h>

using namespace std;

ifstream fin("stone.in");
ofstream fout("stone.out");
#define cin fin
#define cout fout

int Sstone[50005],Nstone[50005];
int N,M,L,l,r;

bool pass(int Min)
{
	int _use=0;
	for (int i=1;i<=N;i++) Nstone[i]=Sstone[i];  //将原来的一组距离复制一遍
	for (int i=1;i<=N;i++)
		if (Nstone[i]<Min)  //如果距离小于二分的最小值，就移走一块石头。
		{
			if (_use>=M) return false;//如果经费不够，方案就不通过
			else{
				_use++;
				Nstone[i+1]+=Nstone[i]; //与后面的合并
			}
		}
	return true;
}

int main()
{
	int now,last=0;
	cin >> L >> N >> M;
	r=L;
	for (int i=1;i<=N;i++)
	{
		cin >> now;
		Sstone[i]=now-last;
		last=now;
	}
	N++;
	Sstone[N]=L-last;
	while (l<=r)
	{
		if (pass((l+r)/2)) l=(l+r)/2+1;  //二分，如果成立，放入左值，否则放入右值
			else r=(l+r)/2-1;
	}
	cout << l-1;
}
#include <bits/stdc++.h>

using namespace std;
int ss,sum[10005],su[20],run[10005],T,num,nian,yue,ri,p,nn;
bool boo;
string st;
int suan(int nian,int yue,int ri)
{
	int ss=0;
	ss+=sum[nian-1];
	ss+=su[yue-1]+ri;
	if (run[nian])
	{
		if (yue>2 || (yue==2 && ri==29)) ss++;
	}
	return ss;
}
void pan(int u)
{
	if (u==0) {printf("Niubi\n"); return;}
	boo=true;
	if (u==1) {printf("Haixing\n"); return;}
	for (int i=2;i*i<=u;i++)
	if (u%i==0) {boo=false;break;}
	if (boo) {printf("Niubi\n"); return;}
	else  {printf("Haixing\n"); return;}
}
int main()
{
	cin>>T;
	su[1]=31;su[2]=28;su[3]=31;su[4]=30;su[5]=31;su[6]=30;
	su[7]=31;su[8]=31;su[9]=30;su[10]=31;su[11]=30;su[12]=31;
	for (int i=1;i<=12;i++) su[i]+=su[i-1];
	for (int i=1;i<=10000;i++)
	{
		if (((i%100!=0) && (i%4==0)) || (i%400==0)) run[i]=true;
		else run[i]=false;
		if (run[i]) sum[i]=sum[i-1]+366;
		else sum[i]=sum[i-1]+365;
	}
	num=suan(1926,8,17);
	for (int o=1;o<=T;o++)
	{
		cin>>st;
		p=st.size();
		nian=(st[0]-'0')*1000+(st[1]-'0')*100+(st[2]-'0')*10+(st[3]-'0');
		yue=(st[5]-'0')*10+(st[6]-'0');
		ri=(st[8]-'0')*10+(st[9]-'0');
		nn=suan(nian,yue,ri);
	cerr << sum[nian] << endl;
		pan(abs(nn-num));
	}
	return 0;
}

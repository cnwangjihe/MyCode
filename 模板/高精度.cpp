#include <iostream>
#include <string>
#include <cstring>

using namespace std;

struct Tb_num{
	friend istream& operator >> (istream&,Tb_num&);
	friend ostream& operator << (ostream&,Tb_num&);
	int len;
	int num[5006];
	bool minus;
	
	Tb_num change(long long d)
	{
		Tb_num a;
		if (d<0) a.minus=1,d*=-1;
		if (d==0) 
		{
			a.len=1;
			a.num[1]=0;
			a.minus=0;
			return a;
		}
		while (d!=0)
		{
			a.len++;
			a.num[a.len]=d%10;
			d/=10;
		}
		return a;
	}
	
	void read()
	{
		string st;
		cin >> st;
		if (st[0]=='-') 
		{
			minus=1;
			len=st.size();
			for (int i=len-1;i>0;i--) num[i]=st[len-i]-'0';
			len--;
		}
		else
		{
			len=st.size();
			for (int i=len;i>0;i--) num[i]=st[len-i]-'0';
		}
		while (num[len]==0) len--;
		if (len==0) 
		{
			len=1;
			num[len]=0;
			minus=0;
		}
		return ;
	}
	
	void write(){
		if (minus) cout << '-';
		for (int i=len;i>0;i--) cout << num[i];
		cout << endl;
		return ;
	}
	void clear(){
		memset(num,0,sizeof num);
		len=0;minus=0;
		num[0]=10;
		return ;
	}
	Tb_num(){clear();}
	
	Tb_num half()
	{
		int d=0;
		for (int i=len;i>0;i--) num[i]=num[i]+d,d=(num[i]%2)*10,num[i]/=2;
		while (num[len]==0) len--;
		return *this;
	}
	
	bool operator > (Tb_num a)
	{
		if (minus==a.minus)
		{
			if (len==a.len) 
			{
				for (int i=len;i>0;i--)
					if (num[i]!=a.num[i]) 
					{
						if (minus) return !(num[i]>a.num[i]);
						else return num[i]>a.num[i];
					}
			}
			if (minus) return !(len>a.len);
			else return len>a.len;
		}
		if (minus) return 0;
		return 1;
	}
	bool operator == (Tb_num a)
	{
		if (minus!=a.minus) return 0;
		if (len!=a.len) return 0;
		for (int i=1;i<=len;i++) if (num[i]!=a.num[i]) return 0;
		return 1;
	}
	bool operator < (Tb_num a){return !(*this>a || *this==a);}
	bool operator != (Tb_num a){return !(*this==a);}
	bool operator >= (Tb_num a){return ((*this>a)||(*this==a));}
	bool operator <= (Tb_num a){return ((*this<a)||(*this==a));}
	bool operator > (long long d){return *this>change(d);}
	bool operator < (long long d){return *this<change(d);}
	bool operator == (long long d){return *this==change(d);}
	bool operator != (long long d){return *this!=change(d);}
	bool operator >= (long long d){return *this>=change(d);}
	bool operator <= (long long d){return *this<=change(d);}
	Tb_num operator = (long long d){*this=change(d);return *this;}
	
	Tb_num operator + (Tb_num a)
	{
		if (minus!=a.minus)
		{
			bool tmp = minus;
			a.minus=minus=0;
			if (a>*this)
			{
				a.minus=minus=!tmp;
				return a-*this;
			}
			a.minus=minus=tmp;
			return *this-a;
		}
		short d=0;
		Tb_num ans;
		ans.minus=minus;
		ans.len=max(a.len,len);
		for (int i=1;i<=ans.len;i++)
		{
			ans.num[i]=d+a.num[i]+num[i];
			d=ans.num[i]/10;
			ans.num[i]%=10;
		}
		if (d!=0) ans.len++,ans.num[ans.len]=d;
		return ans;
	}
	
	Tb_num operator - (Tb_num a)
	{
		if (minus!=a.minus)
		{
			a.minus=minus;
			return *this-a;
		}
		int d=0;
		Tb_num ans;
		if (*this==a)
		{
			ans.minus=0;
			ans.len=1;
			ans.num[1]=0;
			return ans;
		}
		Tb_num t1=*this;
		Tb_num t2=a;
		t1.minus=t2.minus=0;
		if (t1<t2)
		{
			ans.minus=!minus;
			ans.len=a.len;
			d=0;
			for (int i=1;i<=a.len;i++)
				if ((a.num[i]-num[i]-d)<0) ans.num[i]=a.num[i]-num[i]-d+10,d=1;
					else ans.num[i]=a.num[i]-num[i]-d,d=0;
			while (ans.num[ans.len]==0) ans.len--;
		}
		else
		{
			ans.minus=minus;
			ans.len=len;
			d=0;
			for (int i=1;i<=len;i++)
				if ((num[i]-a.num[i]-d)<0) ans.num[i]=num[i]-a.num[i]-d+10,d=1;
					else ans.num[i]=num[i]-a.num[i]-d,d=0;
			while (ans.num[ans.len]==0) ans.len--;
		}
		return ans;
	}
	
	Tb_num operator * (Tb_num a)
	{
		int d=0;
		Tb_num ans;
		if ( (a.len==1 && a.num[1]==0) || (len==1 && num[1]==0) )
		{
			ans.len=1;ans.num[1]=0;ans.minus=0;
			return ans;
		}
		ans.minus=minus^a.minus;
		ans.len=len+a.len-1;
		for (int i=1;i<=len;i++)
		{
			int j;
			for (j=1;j<=a.len;j++)
			{
				ans.num[i+j-1]+=num[i]*a.num[j]+d;
				d=ans.num[i+j-1]/10;
				ans.num[i+j-1]%=10;
			}
			while (d!=0) 
			{
				ans.len=max(ans.len,i+j-1);
				ans.num[i+j-1]=d%10;
				d/=10;
				j++;
			}
		}
		return ans;
	}
	
	
	Tb_num operator + (long long d){return *this+change(d);}
	Tb_num operator - (long long d){return *this-change(d);}
	Tb_num operator * (long long d){return *this*change(d);}
	Tb_num& operator += (Tb_num a){*this=*this+a;return *this;}
	Tb_num& operator -= (Tb_num a){*this=*this-a;return *this;}
	Tb_num& operator *= (Tb_num a){*this=*this*a;return *this;}
	Tb_num& operator += (long long d) {*this=*this+d;return *this;}
	Tb_num& operator -= (long long d) {*this=*this-d;return *this;}
	Tb_num& operator *= (long long d) {*this=*this*d;return *this;}
	
	Tb_num operator / (Tb_num a)
	{
		Tb_num l,r,mid;
		if (a==0) {
			cerr << "ERROR!!!\n";
			int xxx=0;
			cout << (0/xxx);
			return r;
		}
		int m=minus^a.minus,t1=minus,t2=a.minus;
		minus=a.minus=0;
		l=0;r=*this;
		while (l+1<r)
		{
			mid=(l+r).half();
			if (mid*a>*this) r=mid;
			else l=mid;
		}
		minus=t1;a.minus=t2;
		l.minus=m;
		if (l.len==1 && l.num[1]==0) l.minus=0;
		return l;
	}
	Tb_num operator / (long long d){return *this/change(d);}
	Tb_num& operator /= (Tb_num a){*this=*this/a;return *this;}
	Tb_num& operator /= (long long d) {*this=*this/d;return *this;}
	
	
	Tb_num operator % (Tb_num a)
	{
		Tb_num l;
		l=*this/a;
		Tb_num ans;
		ans=*this-(l*a);
		if (ans.minus) 
		{
			a.minus=0;
			ans+=a;
		}
		return ans;
	}
	Tb_num operator % (long long d){return *this%change(d);}
	Tb_num& operator %= (Tb_num a){*this=*this%a;return *this;}
	Tb_num& operator %= (long long d) {*this=*this%d;return *this;}
	
	Tb_num operator ++ ()
	{
		Tb_num a;
		a.len=1;a.minus=0;a.num[1]=1;
		*this+=a;
		return *this;
	}
	Tb_num operator -- ()
	{
		Tb_num a;
		a.len=1;a.minus=0;a.num[1]=1;
		*this-=a;
		return *this;
	}
	Tb_num operator ++ (int)
	{
		Tb_num tmp=*this;
		Tb_num a;
		a.len=1;a.minus=0;a.num[1]=1;
		*this+=a;
		return tmp;
	}
	Tb_num operator -- (int)
	{
		Tb_num tmp=*this;
		Tb_num a;
		a.len=1;a.minus=0;a.num[1]=1;
		*this-=a;
		return tmp;
	}
};

istream& operator >> (istream& in,Tb_num& c){
	string st;
	in >> st;
	if (st[0]=='-') 
	{
		c.minus=1;
		c.len=st.size();
		for (int i=c.len-1;i>0;i--) c.num[i]=st[c.len-i]-'0';
		c.len--;
	}
	else
	{
		c.len=st.size();
		for (int i=c.len;i>0;i--) c.num[i]=st[c.len-i]-'0';
	}
	while (c.num[c.len]==0) c.len--;
	if (c.len==0) 
	{
		c.len=1;
		c.num[c.len]=0;
		c.minus=0;
	}
	return in;
}

ostream& operator << (ostream& out,Tb_num& c){
	if (c.minus) out << '-';
	for (int i=c.len;i>0;i--) out << c.num[i];
	return out;
}

Tb_num a,b,ans;

int main()
{
	cin >> a >> b;
	ans=a-b;
	cout << ans;
}

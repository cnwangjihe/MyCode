template<int n,int m>
struct Matrix
{
	int v[n][m];
	int * operator[](int i) {return v[i];}
	const int * operator[](int i) const{return v[i];}
	inline void Clear()
	{
		for (int i=0;i<n;i++)
			for (int j=0;j<m;j++)
				v[i][j]=-INF;
		return ;
	}
	Matrix(){Clear();}
	#if __cplusplus >= 201103L
		Matrix(initializer_list<int> l)
		{
			assert(l.size()<=n*m);
			auto t=l.begin();
			for (int i=0;i<n;i++)
				for (int j=0;j<m;j++,t++)
					v[i][j]=*t;
		}
	#else
		#warning Please use c++11 to enable all features of Matrix
	#endif
	void Out()
	{
		for (int i=0;i<n;i++,cerr<<'\n')
			for (int j=0;j<m;j++)
				cerr << v[i][j] << ' ';
		cerr << '\n';
	}
};

template<int n,int m,int k>
Matrix<n,k> operator *(const Matrix<n,m> &a,const Matrix<m,k> &b)
{
	Matrix<n,k> ans;
	for (int i=0;i<n;i++)
		for (int j=0;j<k;j++)
			for (int p=0;p<m;p++)
				ans[i][j]=max(ans[i][j],a[i][p]+b[p][j]);
	return ans;
}
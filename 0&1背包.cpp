

// µÝ¹é
int Knapsack(int *W,int *V,int i,int n,int j,int **m)
{
	if(i == n)
	{
		m[i][j] = j >= W[n] ? V[n]: 0;
	}else
	{
		if(j < W[i])
		{
			m[i][j] = Knapsack(W,V,i+1,n,j,m);
		}
		else
		{
			int max1 = Knapsack(W,V,i+1,n,j,m);
			int max2 = Knapsack(W,V,i+1,n,j-W[i],m) + V[i];
			m[i][j] = max1 > max2? max1:max2;
		}
	}
	return m[i][j];
}


void BackPrint(int *W,int **m,int n,int c,int *X)
{
	int i = 1;
	for(;i<n;++i)
	{
		if(m[i][c] != m[i+1][c])
		{
			X[i] = true;
			c-=W[i];
		}
	}
	if(m[i][c] != 0)
	{
		X[i]=true;
	}
}
// ·ÇµÝ¹é
int Knapsack2(int *W,int *V, int n,int c,int **m)
{
	int i = n;
	int j ;
	for(j = 1;j<=c;++j)
	{
		if(j>=W[n])
		{
			m[n][j] = V[n];
		}
		else
		{
			m[n][j] = 0;
		}
	}
	//Print2Array(m,n+1,c+1);
	for(i = n-1;i>=1;--i)
	{
		for(int j = 1;j<=c;++j)
		{
			if(j < W[i])
			{
				m[i][j] = m[i+1][j];
			}else
			{
				m[i][j] = Max(m[i+1][j], m[i+1][j-W[i]] + V[i]);
			}
		}
		Print2Array(m,n+1,c+1);
	}
	return m[1][c];

}
void main()
{
	const int n = 5;
	const int c = 10;
	int W[n+1]={0,2,2,6,5,4};
	int V[n+1]={0,6,3,5,4,6};
	int X[n+1]={0,0,0,0,0,0};
	int **m = Get2Array(n+1,c+1);
	int maxv = Knapsack2(W,V,n,c,m);

	Print2Array(m,n+1,c+1);
	cout<<maxv<<endl;
	BackPrint(W,m,n,c,X);
	for(int i = 1;i<=n;++i)
	{
		if(X[i])
		{
			cout<<i<<" ";
		}
	}
	cout<<endl;
}
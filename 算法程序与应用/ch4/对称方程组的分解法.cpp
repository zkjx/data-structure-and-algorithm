//对称方程组的分解法.cpp
  #include <iostream>
  #include <cmath>
  using namespace  std;
//a[n][n]        存放系数矩阵，返回时将被破坏。
//n              方程组的阶数。
//m              方程组右端常数向量的组数。
//c[n][m]        存放方程组右端m组常数向量。返回m组解向量。
  //函数返回标志值。若<0则表示系数矩阵非对称；若=0则表示失败；若>0则表示正常。
  int ldle(double a[], int n, int m, double c[])
  { 
	  int i,j,l,k,u,v,w,k1,k2,k3;
      double p;
	  for (i=0; i<n; i++)
		  for (j=0; j<i-1; j++)
			  if (a[i*n+j]!=a[j*n+i]) 
			  {
				  cout <<"矩阵不对称！" <<endl;  return -2;
			  }
      if (fabs(a[0])+1.0==1.0)  return 0;
      for (i=1; i<=n-1; i++)
	  {
		  u=i*n; a[u]=a[u]/a[0];
	  }
      for (i=1; i<=n-2; i++)
      { 
		  u=i*n+i;
          for (j=1; j<=i; j++)
          { 
			  v=i*n+j-1; l=(j-1)*n+j-1;
              a[u]=a[u]-a[v]*a[v]*a[l];
          }
          p=a[u];
          if (fabs(p)+1.0==1.0) return 0;
          for (k=i+1; k<=n-1; k++)
          { 
			  u=k*n+i;
              for (j=1; j<=i; j++)
              { 
				  v=k*n+j-1; l=i*n+j-1; w=(j-1)*n+j-1;
		          a[u]=a[u]-a[v]*a[l]*a[w];
              }
            a[u]=a[u]/p;
          }
      }
      u=n*n-1;
      for (j=1; j<=n-1; j++)
      {
		  v=(n-1)*n+j-1; w=(j-1)*n+j-1;
          a[u]=a[u]-a[v]*a[v]*a[w];
      }
      p=a[u];
      if (fabs(p)+1.0==1.0)  return 0;
      for (j=0; j<=m-1; j++)
      for (i=1; i<=n-1; i++)
      { 
		  u=i*m+j;
          for (k=1; k<=i; k++)
          { 
			  v=i*n+k-1; w=(k-1)*m+j;
              c[u]=c[u]-a[v]*c[w];
          }
      }
      for (i=1; i<=n-1; i++)
      { 
		  u=(i-1)*n+i-1;
          for (j=i; j<=n-1; j++)
          { 
			  v=(i-1)*n+j; w=j*n+i-1;
              a[v]=a[u]*a[w];
          }
      }
      for (j=0; j<=m-1; j++)
      {
		  u=(n-1)*m+j;
          c[u]=c[u]/p;
          for (k=1; k<=n-1; k++)
          { 
			  k1=n-k; k3=k1-1; u=k3*m+j;
              for (k2=k1; k2<=n-1; k2++)
              { 
				  v=k3*n+k2; w=k2*m+j;
                  c[u]=c[u]-a[v]*c[w];
              }
              c[u]=c[u]/a[k3*n+k3];
          }
      }
      return(2);
  }

/*
  #include <iostream>
  #include <iomanip>
  #include <cmath>
//  #include "对称方程组的分解法.cpp"
  using namespace  std;
  int main()
  { 
	  int i;
      double a[5][5]={ {5.0,7.0,6.0,5.0,1.0},
           {7.0,10.0,8.0,7.0,2.0},{6.0,8.0,10.0,9.0,3.0},
           {5.0,7.0,9.0,10.0,4.0},{1.0,2.0,3.0,4.0,5.0}};
      double c[5][2]={ {24.0,96.0},{34.0,136.0},
           {36.0,144.0},{35.0,140.0},{15.0,60.0}};
	  i = ldle(&a[0][0],5,2,&c[0][0]);
	  if (i <= 0)  return 0;
      for (i=0; i<=4; i++)
        cout <<"x(" <<i <<") = " <<setw(15) <<c[i][0] <<setw(15) <<c[i][1] <<endl;
	  return 0;
  }
*/

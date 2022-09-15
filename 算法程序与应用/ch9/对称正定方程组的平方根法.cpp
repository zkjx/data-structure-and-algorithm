//对称正定方程组的平方根法.cpp
  #include <iostream>
  #include <cmath>
  using namespace  std;
//a[n][n]        存放对称正定的系数矩阵，返回时上三角部分存放U矩阵。。
//n              方程组的阶数。
//m              方程组右端常数向量的组数。
//d[n][m]        存放方程组右端m组常数向量。返回m组解向量。
  //函数返回标志值。若=0则表示失败；若>0则表示正常。
  int chlk(double a[], int n, int m, double d[])
  { 
	  int i,j,k,u,v;
      if ((a[0]+1.0==1.0)||(a[0]<0.0))  return(0);
      a[0]=sqrt(a[0]);
      for (j=1; j<=n-1; j++) a[j]=a[j]/a[0];
      for (i=1; i<=n-1; i++)
      { 
		  u=i*n+i;
          for (j=1; j<=i; j++)
          {
			  v=(j-1)*n+i; a[u]=a[u]-a[v]*a[v];
          }
          if ((a[u]+1.0==1.0)||(a[u]<0.0)) return(0);
          a[u]=sqrt(a[u]);
          if (i!=(n-1))
          { 
			  for (j=i+1; j<=n-1; j++)
              { 
				  v=i*n+j;
                  for (k=1; k<=i; k++)
                        a[v]=a[v]-a[(k-1)*n+i]*a[(k-1)*n+j];
                  a[v]=a[v]/a[u];
              }
          }
      }
      for (j=0; j<=m-1; j++)
      { 
		  d[j]=d[j]/a[0];
          for (i=1; i<=n-1; i++)
          {
			  u=i*n+i; v=i*m+j;
              for (k=1; k<=i; k++)
                  d[v]=d[v]-a[(k-1)*n+i]*d[(k-1)*m+j];
              d[v]=d[v]/a[u];
          }
      }
      for (j=0; j<=m-1; j++)
      {
		  u=(n-1)*m+j;
          d[u]=d[u]/a[n*n-1];
          for (k=n-1; k>=1; k--)
          { 
			  u=(k-1)*m+j;
              for (i=k; i<=n-1; i++)
              {
				  v=(k-1)*n+i; d[u]=d[u]-a[v]*d[i*m+j];
              }
              v=(k-1)*n+k-1;
              d[u]=d[u]/a[v];
          }
      }
      return(2);
  }

  /*
  #include <iostream>
  #include <iomanip>
  #include <cmath>
//  #include "对称正定方程组的平方根法.cpp"
  using namespace  std;
  int main()
  { 
	  int i;
      double a[4][4]={ {5.0,7.0,6.0,5.0},
	  {7.0,10.0,8.0,7.0},{6.0,8.0,10.0,9.0},{5.0,7.0,9.0,10.0}};
      double d[4][2]={ {23.0,92.0},{32.0,128.0},
                            {33.0,132.0},{31.0,124.0}};
      i = chlk(&a[0][0], 4, 2, &d[0][0]);
	  if (i<=0) return 0;
      for (i=0; i<=3; i++)
        cout <<"x(" <<i <<") = " <<setw(15) <<d[i][0] <<setw(15) <<d[i][1] <<endl;
	  return 0;
  }
*/
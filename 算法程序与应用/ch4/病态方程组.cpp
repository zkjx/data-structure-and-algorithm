//病态方程组.cpp
  #include <cmath>
  #include <iostream>
  #include "gauss消去法.cpp"
  using namespace std;
//a[n][n]     系数矩阵
//n           方程组阶数
//b[n]        常数向量
//eps         精度要求
//x[n]        返回解向量。若系数矩阵奇异，返回0向量。
  //若系数矩阵奇异或校正达到10次还不满足精度要求，则显示错误信息，并返回0标志值。
  //正常则返回非0标志值。
  int bingt(double a[], int n, double b[], double eps, double x[])
  { 
	  int i,j,k;
      double q, qq;
      double *p,*r,*e;
      p=new double[n*n];
      r=new double[n];
      e=new double[n];
      k=0;
      for (i=0; i<=n-1; i++)
      for (j=0; j<=n-1; j++)  p[i*n+j]=a[i*n+j];
      for (i=0; i<=n-1; i++)  x[i]=b[i];
      i=gauss(p,x,n);
	  if (i==0)  
	  {
		  delete[] p; delete[] r; delete[] e; return 0;
	  }
      q=1.0+eps;
      while (q>=eps)
      { 
		  if (k==10)
          { 
			  cout <<"校正达到10次！\n";
			  delete[] p; delete[] r; delete[] e; return 0; 
		  }
          k=k+1;       
          for (i=0; i<=n-1; i++)
		  {  
			  e[i]=0;
		      for (j=0; j<=n-1; j++) e[i]=e[i]+a[i*n+j]*x[j];
		  }
		  for ( i=0; i<=n-1; i++)   r[i]=b[i]-e[i];
		  for ( i=0; i<=n-1; i++)
          for ( j=0; j<=n-1; j++)   p[i*n+j]=a[i*n+j];
          i = gauss(p,r,n);
		  if ( i == 0 )
		  {
			  delete[] p; delete[] r; delete[] e;   return 0;
		  }
          q=0.0;
          for ( i=0; i<=n-1; i++)
          {
			  qq=fabs(r[i])/(1.0+fabs(x[i]+r[i]));
              if (qq>q) q=qq;
          }
          for ( i=0; i<=n-1; i++) x[i]=x[i]+r[i];
      }
	  cout <<"校正次数为"  <<k <<endl;
      delete[] p; delete[] r; delete[] e; return 1;
  }


/*
  #define N  5
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "病态方程组.cpp"
  using namespace std;
  int main()
  { 
	  int i, j;
      double a[N][N];
      double r[N], x[N], b[N]={1.0, 0.0, 0.0, 0.0, 1.0};
      for (i=0; i<N; i++)
		  for (j=0; j<N; j++)  a[i][j] = 1.0/(1.0+i+j);
	  cout <<"系数矩阵:\n";
	  for (i=0; i<N; i++)
	  {
		  for (j=0; j<N; j++)  cout <<setw(10) <<a[i][j];
		  cout <<endl;
	  }
	  cout <<"常数向量:\n";
	  for (i=0; i<N; i++)  cout <<b[i] <<"    ";
	  cout <<endl;
	  cout <<"解向量:\n";
      bingt(&a[0][0],N,b,0.00000001 ,x);
      for (i=0; i<N; i++)
             cout <<"x(" <<i <<")=" <<x[i] <<endl;
	  cout <<"残向量:\n";
	  for (i=0; i<N; i++)
	  { 
		  r[i]=0;
	      for (j=0; j<N; j++)  r[i]=r[i]+a[i][j]*x[j];
	      r[i]=b[i]-r[i];
	      cout <<"r(" <<i <<")=" <<r[i] <<endl;
	  }
	  return 0;
  }
*/
//Kalman滤波.cpp
  #include <cmath>
  #include <iostream>
  #include "实矩阵求逆.cpp"
  using namespace std;
//n          动态系统的维数。
//m          观测系统的维数
//k          观测序列长度。
//f[n][n]    系统状态转移矩阵
//q[n][n]    模型噪声W的协方差阵。
//r[m][m]    观测噪声V的协方差阵。
//h[m][n]    观测矩阵
//y[k][m]    观测向量序列。
//x[k][n]    x[0][j]存放初值。其余各行返回状态向量估值序列。
//p[n][n]    存放初值。返回最后时刻的估计误差协方差阵。
//g[n][m]    返回最后时刻的稳定增益矩阵。
  //函数返回标志值。若=0表示求逆失败，若不为0表示正常。
  int kalman(int n, int m, int k, double f[], double q[], double r[],
	         double h[], double y[], double x[], double p[], double g[])
  { 
	  int i,j,kk,ii,l,jj,js;
      double *e,*a,*b;
      e=new double[m*m];
      l=m;
      if (l<n) l=n;
      a=new double[l*l];
      b=new double[l*l];
      for (i=0; i<=n-1; i++)
      for (j=0; j<=n-1; j++)
      { 
		  ii=i*l+j; a[ii]=0.0;
          for (kk=0; kk<=n-1; kk++)
            a[ii]=a[ii]+p[i*n+kk]*f[j*n+kk];
      }
      for (i=0; i<=n-1; i++)
      for (j=0; j<=n-1; j++)
      { 
		  ii=i*n+j; p[ii]=q[ii];
          for (kk=0; kk<=n-1; kk++)
            p[ii]=p[ii]+f[i*n+kk]*a[kk*l+j];
      }
      for (ii=2; ii<=k; ii++)
      { 
		  for (i=0; i<=n-1; i++)
          for (j=0; j<=m-1; j++)
          { 
			  jj=i*l+j; a[jj]=0.0;
              for (kk=0; kk<=n-1; kk++)
                  a[jj]=a[jj]+p[i*n+kk]*h[j*n+kk];
          }
          for (i=0; i<=m-1; i++)
          for (j=0; j<=m-1; j++)
          { 
			  jj=i*m+j; e[jj]=r[jj];
              for (kk=0; kk<=n-1; kk++)
                 e[jj]=e[jj]+h[i*n+kk]*a[kk*l+j];
          }
          js=inv(e,m);
          if (js==0) 
          {
			  delete[] e; delete[] a; delete[] b; return(js);
		  }
          for (i=0; i<=n-1; i++)
          for (j=0; j<=m-1; j++)
          { 
			  jj=i*m+j; g[jj]=0.0;
              for (kk=0; kk<=m-1; kk++)
                  g[jj]=g[jj]+a[i*l+kk]*e[j*m+kk];
          }
          for (i=0; i<=n-1; i++)
          { 
			  jj=(ii-1)*n+i; x[jj]=0.0;
              for (j=0; j<=n-1; j++)
                 x[jj]=x[jj]+f[i*n+j]*x[(ii-2)*n+j];
          }
          for (i=0; i<=m-1; i++)
          { 
			  jj=i*l; b[jj]=y[(ii-1)*m+i];
              for (j=0; j<=n-1; j++)
                 b[jj]=b[jj]-h[i*n+j]*x[(ii-1)*n+j];
          }
          for (i=0; i<=n-1; i++)
          { 
			  jj=(ii-1)*n+i;
              for (j=0; j<=m-1; j++)
                 x[jj]=x[jj]+g[i*m+j]*b[j*l];
          }
          if (ii<k)
          {
			  for (i=0; i<=n-1; i++)
              for (j=0; j<=n-1; j++)
              { 
				  jj=i*l+j; a[jj]=0.0;
                  for (kk=0; kk<=m-1; kk++)
                     a[jj]=a[jj]-g[i*m+kk]*h[kk*n+j];
                  if (i==j) a[jj]=1.0+a[jj];
              }
              for (i=0; i<=n-1; i++)
              for (j=0; j<=n-1; j++)
              {
				  jj=i*l+j; b[jj]=0.0;
                  for (kk=0; kk<=n-1; kk++)
                     b[jj]=b[jj]+a[i*l+kk]*p[kk*n+j];
              }
              for (i=0; i<=n-1; i++)
              for (j=0; j<=n-1; j++)
              { 
				  jj=i*l+j; a[jj]=0.0;
                  for (kk=0; kk<=n-1; kk++)
                     a[jj]=a[jj]+b[i*l+kk]*f[j*n+kk];
              }
              for (i=0; i<=n-1; i++)
              for (j=0; j<=n-1; j++)
              { 
				  jj=i*n+j; p[jj]=q[jj];
                  for (kk=0; kk<=n-1; kk++)
                     p[jj]=p[jj]+f[i*n+kk]*a[j*l+kk];
              }
          }
      }
      delete[] e; delete[] a; delete[] b;
      return(js);
  }
/*
//Kalman滤波例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
  #include "产生随机数类.h"
//  #include "Kalman滤波.cpp"
  using namespace std;
  int main()
  { 
	  int i,j,js;
	  RND pp;
      double p[3][3],x[150][3],y[150][1],g[3][1],t,s;
      double f[3][3]={{1.0,0.05,0.00125},
                 {0.0,1.0,0.05},{0.0,0.0,1.0}};
      double q[3][3]={{0.25,0.0,0.0},
                 {0.0,0.25,0.0},{0.0,0.0,0.25}};
      double r[1][1]={0.25};
      double h[1][3]={1.0,0.0,0.0};
      for (i=0; i<=2; i++)
      for (j=0; j<=2; j++) p[i][j]=0.0;
      for (i=0; i<=149; i++)
      for (j=0; j<=2; j++) x[i][j]=0.0;
	  pp = RND(0);
	  for (i=0; i<149; i++) //产生150个均值为0，方差为0.25的高斯白噪声
		  y[i][0] = pp.rndg(0.0,0.5);
      for (i=0; i<=149; i++)
      { t=0.05*i;
        y[i][0]=5.0-2.0*t+3.0*t*t+y[i][0];
      }
      js=kalman(3,1,150,&f[0][0],&q[0][0],&r[0][0],&h[0][0],&y[0][0],
		                                &x[0][0],&p[0][0],&g[0][0]);
      if (js==0) return 0;
	  cout <<setw(5) <<"t" <<setw(10) <<"s"  <<setw(10) <<"y" 
		   <<setw(10) <<"x(0)" <<setw(10) <<"x(1)" 
		   <<setw(10) <<"x(2)" <<endl;
      for (i=0; i<=149; i=i+5)
      { 
		  t=0.05*i; s=5.0-2.0*t+3.0*t*t;
		  cout <<setw(5) <<t <<setw(10) <<s 
		   <<setw(10) <<y[i][0] <<setw(10) <<x[i][0] 
		   <<setw(10) <<x[i][1]  <<setw(10) <<x[i][2] <<endl;
          }
     return 0;
  }
*/
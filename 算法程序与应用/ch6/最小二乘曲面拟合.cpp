//最小二乘曲面拟合.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//x[n]       存放给定数据点的X坐标。
//y[n]       存放给定数据点的Y坐标。
//z[n][m]    存放给定n*m个网点上函数值。
//n          X坐标个数。
//m          Y坐标个数。
//a[p][q]    返回二元拟合多项式的系数。
//p          拟合多项式中x的最高次为p-1。要求p<=min(n,20)。
//q          拟合多项式中y的最高次为q-1。要求q<=min(n,20)。
//dt[3]      分别返回误差平方和，误差绝对值之和与误差绝对值的最大值。
  void pir2(double x[], double y[], double z[], int n, int m, 
	        double a[], int p, int q, double dt[])
  { 
	  int i,j,k,l,kk;
      double apx[20],apy[20],bx[20],by[20],u[20][20];
      double t[20],t1[20],t2[20],d1,d2,g,g1,g2;
      double x2,dd,y1,x1,*v;
      v = new double[20*m];
      for (i=0; i<=p-1; i++)
      { 
		  l=i*q;
          for (j=0; j<=q-1; j++) a[l+j]=0.0;
      }
      if (p>n) p=n;
      if (p>20) p=20;
      if (q>m) q=m;
      if (q>20) q=20;
      d1=1.0*n; apx[0]=0.0;
      for (i=0; i<=n-1; i++)  apx[0]=apx[0]+x[i];
      apx[0]=apx[0]/d1;
      for (j=0; j<=m-1; j++)
      { 
		  v[j]=0.0;
          for (i=0; i<=n-1; i++)  v[j]=v[j]+z[i*m+j];
          v[j]=v[j]/d1;
      }
      if (p>1)
      { 
		  d2=0.0; apx[1]=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  g=x[i]-apx[0];
              d2=d2+g*g;
              apx[1]=apx[1]+x[i]*g*g;
          }
          apx[1]=apx[1]/d2;
          bx[1]=d2/d1;
          for (j=0; j<=m-1; j++)
          { 
			  v[m+j]=0.0;
              for (i=0; i<=n-1; i++)
              { 
				  g=x[i]-apx[0];
                  v[m+j]=v[m+j]+z[i*m+j]*g;
              }
              v[m+j]=v[m+j]/d2;
          }
          d1=d2;
      }
      for (k=2; k<=p-1; k++)
      { 
		  d2=0.0; apx[k]=0.0;
          for (j=0; j<=m-1; j++) v[k*m+j]=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  g1=1.0; g2=x[i]-apx[0];
              for (j=2; j<=k; j++)
              { 
				  g=(x[i]-apx[j-1])*g2-bx[j-1]*g1;
                  g1=g2; g2=g;
              }
              d2=d2+g*g;
              apx[k]=apx[k]+x[i]*g*g;
              for (j=0; j<=m-1; j++) v[k*m+j]=v[k*m+j]+z[i*m+j]*g;
          }
          for (j=0; j<=m-1; j++) v[k*m+j]=v[k*m+j]/d2;
          apx[k]=apx[k]/d2;
          bx[k]=d2/d1;
          d1=d2;
      }
      d1=m; apy[0]=0.0;
      for (i=0; i<=m-1; i++) apy[0]=apy[0]+y[i];
      apy[0]=apy[0]/d1;
      for (j=0; j<=p-1; j++)
      { 
		  u[j][0]=0.0;
          for (i=0; i<=m-1; i++)  u[j][0]=u[j][0]+v[j*m+i];
	      u[j][0]=u[j][0]/d1;
      }
      if (q>1)
      { 
		  d2=0.0; apy[1]=0.0;
          for (i=0; i<=m-1; i++)
          { 
			  g=y[i]-apy[0];
              d2=d2+g*g;
              apy[1]=apy[1]+y[i]*g*g;
          }
          apy[1]=apy[1]/d2;
          by[1]=d2/d1;
          for (j=0; j<=p-1; j++)
		  { 
			  u[j][1]=0.0;
              for (i=0; i<=m-1; i++)
              { 
				  g=y[i]-apy[0];
		          u[j][1]=u[j][1]+v[j*m+i]*g;
              }
	          u[j][1]=u[j][1]/d2;
          }
          d1=d2;
      }
      for (k=2; k<=q-1; k++)
      { 
		  d2=0.0; apy[k]=0.0;
	      for (j=0; j<=p-1; j++) u[j][k]=0.0;
          for (i=0; i<=m-1; i++)
          { 
			  g1=1.0;
              g2=y[i]-apy[0];
              for (j=2; j<=k; j++)
              { 
				  g=(y[i]-apy[j-1])*g2-by[j-1]*g1;
                  g1=g2; g2=g;
              }
              d2=d2+g*g;
              apy[k]=apy[k]+y[i]*g*g;
              for (j=0; j<=p-1; j++) u[j][k]=u[j][k]+v[j*m+i]*g;
          }
          for (j=0; j<=p-1; j++) u[j][k]=u[j][k]/d2;
          apy[k]=apy[k]/d2;
          by[k]=d2/d1;
          d1=d2;
      }
      v[0]=1.0; v[m]=-apy[0]; v[m+1]=1.0;
      for (i=0; i<=p-1; i++)
      for (j=0; j<=q-1; j++) a[i*q+j]=0.0;
      for (i=2; i<=q-1; i++)
      { 
		  v[i*m+i]=v[(i-1)*m+(i-1)];
          v[i*m+i-1]=-apy[i-1]*v[(i-1)*m+i-1]+v[(i-1)*m+i-2];
          if (i>=3)
          for (k=i-2; k>=1; k--)
            v[i*m+k]=-apy[i-1]*v[(i-1)*m+k]+
                     v[(i-1)*m+k-1]-by[i-1]*v[(i-2)*m+k];
          v[i*m]=-apy[i-1]*v[(i-1)*m]-by[i-1]*v[(i-2)*m];
      }
      for (i=0; i<=p-1; i++)
      { 
		  if (i==0) { t[0]=1.0; t1[0]=1.0;}
          else
          { 
			  if (i==1)
              { 
				  t[0]=-apx[0]; t[1]=1.0;
                  t2[0]=t[0]; t2[1]=t[1];
              }
              else
              { 
				  t[i]=t2[i-1];
                  t[i-1]=-apx[i-1]*t2[i-1]+t2[i-2];
                  if (i>=3)
                  for (k=i-2; k>=1; k--)
                    t[k]=-apx[i-1]*t2[k]+t2[k-1]
                         -bx[i-1]*t1[k];
                  t[0]=-apx[i-1]*t2[0]-bx[i-1]*t1[0];
                  t2[i]=t[i];
                  for (k=i-1; k>=0; k--)
                  { t1[k]=t2[k]; t2[k]=t[k];}
              }
          }
          for (j=0; j<=q-1; j++)
          for (k=i; k>=0; k--)
          for (l=j; l>=0; l--)
	         a[k*q+l]=a[k*q+l]+u[i][j]*t[k]*v[j*m+l];
      }
      dt[0]=0.0; dt[1]=0.0; dt[2]=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  x1=x[i];
          for (j=0; j<=m-1; j++)
          { 
			  y1=y[j];
              x2=1.0; dd=0.0;
              for (k=0; k<=p-1; k++)
              { 
				  g=a[k*q+q-1];
                  for (kk=q-2; kk>=0; kk--) g=g*y1+a[k*q+kk];
                  g=g*x2; dd=dd+g; x2=x2*x1;
              }
              dd=dd-z[i*m+j];
              if (fabs(dd)>dt[2]) dt[2]=fabs(dd);
              dt[0]=dt[0]+dd*dd;
              dt[1]=dt[1]+fabs(dd);
          }
      }
      delete[] v;
      return;
  }
/*
//最小二乘曲面拟合例
  #include <iostream>
  #include <iomanip>
  #include <cmath>
//  #include "最小二乘曲面拟合.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double x[11],y[21],z[11][21],a[6][5],dt[3];
      for (i=0; i<=10; i++) x[i]=0.2*i;
      for (i=0; i<=20; i++) y[i]=0.1*i;
      for (i=0; i<=10; i++)
      for (j=0; j<=20; j++)
          z[i][j]=exp(x[i]*x[i]-y[j]*y[j]);
      pir2(x,y,&z[0][0],11,21,&a[0][0],6,5,dt);
      cout <<"二元拟合多项式系数矩阵 : " <<endl;
      for (i=0; i<=5; i++)
      { 
		  for (j=0; j<=4; j++)
              cout <<setw(14) <<a[i][j];
          cout <<endl;
      }
      cout <<"误差平方和 = " <<dt[0] <<endl;
	  cout <<"误差绝对值和 = " <<dt[1] <<endl;
	  cout <<"误差绝对值最大值 = " <<dt[2] <<endl;
      return 0;
  }
*/
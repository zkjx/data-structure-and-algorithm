//最小二乘曲线拟合.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//x[n]       存放给定数据点的X坐标。
//y[n]       存放给定数据点的Y坐标。
//n          给定数据点的个数。
//a[m]       返回m - 1次拟合多项式的系数。
//m          拟合多项式的项数。要求m<=min(n,20)。
//dt[3]      分别返回误差平方和，误差绝对值之和与误差绝对值的最大值。
  void pir1(double x[], double y[], int n, double a[], int m, double dt[])
  { 
	  int i,j,k;
      double p,c,g,q,d1,d2,s[20],t[20],b[20];
      for (i=0; i<=m-1; i++) a[i]=0.0;
      if (m>n) m=n;
      if (m>20) m=20;
      b[0]=1.0; d1=1.0*n; p=0.0; c=0.0;
      for (i=0; i<=n-1; i++)
      { p=p+x[i]; c=c+y[i];}
      c=c/d1; p=p/d1;
      a[0]=c*b[0];
      if (m>1)
      { 
		  t[1]=1.0; t[0]=-p;
          d2=0.0; c=0.0; g=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  q=x[i]-p; d2=d2+q*q;
              c=c+y[i]*q;
              g=g+x[i]*q*q;
          }
          c=c/d2; p=g/d2; q=d2/d1;
          d1=d2;
          a[1]=c*t[1]; a[0]=c*t[0]+a[0];
      }
      for (j=2; j<=m-1; j++)
      { 
		  s[j]=t[j-1];
          s[j-1]=-p*t[j-1]+t[j-2];
          if (j>=3)
            for (k=j-2; k>=1; k--)
              s[k]=-p*t[k]+t[k-1]-q*b[k];
          s[0]=-p*t[0]-q*b[0];
          d2=0.0; c=0.0; g=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  q=s[j];
              for (k=j-1; k>=0; k--)  q=q*x[i]+s[k];
              d2=d2+q*q; c=c+y[i]*q;
              g=g+x[i]*q*q;
          }
          c=c/d2; p=g/d2; q=d2/d1;
          d1=d2;
          a[j]=c*s[j]; t[j]=s[j];
          for (k=j-1; k>=0; k--)
          { 
			  a[k]=c*s[k]+a[k];
              b[k]=t[k]; t[k]=s[k];
          }
      }
      dt[0]=0.0; dt[1]=0.0; dt[2]=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  q=a[m-1];
          for (k=m-2; k>=0; k--) q=a[k]+q*x[i];
          p=q-y[i];
          if (fabs(p)>dt[2]) dt[2]=fabs(p);
          dt[0]=dt[0]+p*p;
          dt[1]=dt[1]+fabs(p);
      }
      return;
  }

/*
//最小二乘曲线拟合例
  #include <iostream>
  #include <cmath>
//  #include "最小二乘曲线拟合.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double x[20],y[20],a[6],dt[3];
      for (i=0; i<=19; i++)
      { 
		  x[i]=0.1*i; y[i]=x[i]-exp(-x[i]);
      }
      pir1(x,y,20,a,6,dt);
      cout <<"拟合多项式系数: " <<endl;
      for (i=0; i<=5; i++)
        cout <<"a(" <<i <<") = " <<a[i] <<endl;
      cout <<"误差平方和 = " <<dt[0] <<endl;
	  cout <<"误差绝对值和 = " <<dt[1] <<endl;
	  cout <<"误差绝对值最大值 = " <<dt[2] <<endl;
	  return 0;
  }
*/
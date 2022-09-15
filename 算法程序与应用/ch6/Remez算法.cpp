//Remez算法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//a         区间左端点值。
//b         区间右端点值。
//p[n]      返回n - 1次最佳一致逼近多项式的系数。
//n         n - 1次最佳一致逼近多项式的项数。
//eps       控制精度要求。
//f         计算f(x)函数值的函数名。
  //函数返回偏差绝对值。
  double remz(double a, double b, double p[], int n, double eps, double (*f)(double))
  { 
	  int i,j,k,m;
      double x[21],g[21],pp[21],d,t,u,s,xx,x0,h,yy;
      if (n>20) n=20;
      m = n+1; d=1.0e+35;
      for (k=0; k<=n; k++)      //初始点集
      { 
		  t=cos((n-k)*3.1415926/(1.0*n));
          x[k]=(b+a+(b-a)*t)/2.0;
      }
      while (1==1)
      { 
		  u=1.0;
          for (i=0; i<=m-1; i++)
          { 
			  pp[i]=(*f)(x[i]);  g[i]=-u; u=-u;
          }
          for (j=0; j<=n-1; j++)
          { 
			  k=m; s=pp[k-1]; xx=g[k-1];
              for (i=j; i<=n-1; i++)
              { 
				  t=pp[n-i+j-1]; x0=g[n-i+j-1];
                  pp[k-1]=(s-t)/(x[k-1]-x[m-i-2]);
                  g[k-1]=(xx-x0)/(x[k-1]-x[m-i-2]);
                  k=n-i+j; s=t; xx=x0;
              }
          }
          u=-pp[m-1]/g[m-1];
          for (i=0; i<=m-1; i++) pp[i]=pp[i]+g[i]*u;
          for (j=1; j<=n-1; j++)
          { 
			  k=n-j; h=x[k-1]; s=pp[k-1];
              for (i=m-j; i<=n; i++)
              { 
				  t=pp[i-1]; pp[k-1]=s-h*t;  s=t; k=i;
              }
          }
          pp[m-1]=fabs(u); u=pp[m-1];
          if (fabs(u-d)<=eps)
		  {
			  for (i=0; i<n; i++)  p[i] = pp[i];
			  return(u);
		  }
          d=u; h=0.1*(b-a)/(1.0*n);
          xx=a; x0=a;
          while (x0<=b)
          { 
			  s=(*f)(x0); t=pp[n-1];
              for (i=n-2; i>=0; i--)  t=t*x0+pp[i];
              s=fabs(s-t);
              if (s>u) { u=s; xx=x0;}
              x0=x0+h;
          }
          s=(*f)(xx); t=pp[n-1];
          for (i=n-2; i>=0; i--) t=t*xx+pp[i];
          yy=s-t; i=1; j=n+1;
          while ((j-i)!=1)
          { 
			  k=(i+j)/2;
              if (xx<x[k-1]) j=k;
              else i=k;
          }
          if (xx<x[0])
          { 
			  s=(*f)(x[0]); t=pp[n-1];
              for (k=n-2; k>=0; k--) t=t*x[0]+pp[k];
              s=s-t;
              if (s*yy>0.0) x[0]=xx;
              else
              { 
				  for (k=n-1; k>=0; k--)  x[k+1]=x[k];
                  x[0]=xx;
              }
          }
          else
          { 
			  if (xx>x[n])
              { 
				  s=(*f)(x[n]); t=pp[n-1];
                  for (k=n-2; k>=0; k--)  t=t*x[n]+pp[k];
                  s=s-t;
                  if (s*yy>0.0) x[n]=xx;
                  else
                  {
					  for (k=0; k<=n-1; k++) x[k]=x[k+1];
                      x[n]=xx;
                  }
              }
              else
              { 
				  i=i-1; j=j-1;
                  s=(*f)(x[i]); t=pp[n-1];
                  for (k=n-2; k>=0; k--) t=t*x[i]+pp[k];
                  s=s-t;
                  if (s*yy>0.0) x[i]=xx;
                  else x[j]=xx;
              }
          }
      }
  }

/*
//Remez算法例
  #include <cmath>
  #include <iostream>
//  #include "Remez算法.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double a,b,eps,p[4], u;
      double remzf(double);
      a=-1.0; b=1.0; eps=1.0e-10;
      u = remz(a,b,p,4,eps,remzf);
	  cout <<"最佳一致逼近多项式系数 :" <<endl;
      for (i=0; i<=3; i++)
         cout <<"p(" <<i <<") = " <<p[i] <<endl;
      cout <<"偏差绝对值 = " <<u <<endl;
      return 0;
  }

  double remzf(double x)
  { 
	  return(exp(x));
  }
*/
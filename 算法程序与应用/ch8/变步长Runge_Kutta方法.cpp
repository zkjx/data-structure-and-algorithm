//变步长Runge_Kutta方法.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//t           积分起始点。
//h           积分步长。
//n           一阶微分方程组中方程个数，也是未知函数个数。
//y[n]        存放n个未知函数在起始点t处的函数值。
//            返回n个未知函数在t+h处的函数值。
//eps         控制精度要求。
//f           计算微分方程组中各方程右端函数值的函数名。
  void runge_kutta(double t, double h, int n, double y[], double eps, 
	               void (*f)(double, double [], int, double []))
  { 
	  int m,i,j,k;
      double hh,p,dt,x,tt,q,a[4],*g,*b,*c,*d,*e;
      g=new double[n];
      b=new double[n];
      c=new double[n];
      d=new double[n];
      e=new double[n];
      hh=h; m=1; p=1.0+eps; x=t;
      for (i=0; i<=n-1; i++) c[i]=y[i];
      while (p>=eps)
      { 
		  a[0]=hh/2.0; a[1]=a[0]; a[2]=hh; a[3]=hh;
          for (i=0; i<=n-1; i++)
          { 
			  g[i]=y[i]; y[i]=c[i];
		  }
          dt=h/m; t=x;
          for (j=0; j<=m-1; j++)
          { 
			  (*f)(t,y,n,d);
              for (i=0; i<=n-1; i++) 
              { 
				  b[i]=y[i]; e[i]=y[i];
			  }
              for (k=0; k<=2; k++)
              { 
				  for (i=0; i<=n-1; i++)
                  { 
					  y[i]=e[i]+a[k]*d[i];
                      b[i]=b[i]+a[k+1]*d[i]/3.0;
                  }
                  tt=t+a[k];
                  (*f)(tt,y,n,d);
              }
              for (i=0; i<=n-1; i++) y[i]=b[i]+hh*d[i]/6.0;
              t=t+dt;
          }
          p=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  q=fabs(y[i]-g[i]);
              if (q>p) p=q;
          }
          hh=hh/2.0; m=m+m;
      }
      delete[] g; delete[] b; delete[] c; delete[] d; delete[] e;
      return;
  }

/*
//变步长Runge_Kutta方法例
  #include <iostream>
  #include <cmath>
  #include <iomanip>
//  #include "变步长Runge_Kutta方法.cpp"
  using namespace std;
  int main()
  { 
	  int i, j;
      void  rktf(double,double [],int,double []);
      double t,h,eps,y[2];
      y[0]=0.0; y[1]=1.0;
      t=0.0; h=0.1; eps=0.0000001;
      cout <<"t = " <<t;
      for (i=0; i<=1; i++)
		  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
      cout <<endl;
      for (j=1; j<=10; j++)
      { 
		  runge_kutta(t,h,2,y,eps,rktf);
          t=t+h;
          cout <<"t = " <<t;
          for (i=0; i<=1; i++)
			  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
          cout <<endl;
      }
	  return 0;
  }
//计算微分方程组中各方程右端函数值
  void rktf(double t, double y[], int n, double d[])
  { 
	  t=t; n=n;
      d[0]=y[1]; d[1]=-y[0];
      return;
  }
*/
//变步长Merson方法.cpp
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
  void merson(double t, double h, int n, double y[], double eps, 
	                   void (*f)(double,double [],int,double []))
  { 
	  int j,m,nn;
      double x,hh,p,dt,t0,q,*a,*b,*c,*d,*u,*v;
      a=new double[n];
      b=new double[n];
      c=new double[n];
      d=new double[n];
      u=new double[n];
      v=new double[n];
	  x=t; nn=1; hh=h;
      for (j=0; j<=n-1; j++) u[j]=y[j];
      p=1.0+eps;
      while (p>=eps)
      { 
		  for (j=0; j<=n-1; j++)
          { 
			  v[j]=y[j]; y[j]=u[j];
		  }
          dt=h/nn; t=x;
          for (m=0; m<=nn-1; m++)
          { 
			  (*f)(t,y,n,d);
              for (j=0; j<=n-1; j++)
              { 
				  a[j]=d[j]; y[j]=y[j]+hh*d[j]/3.0;
			  }
              t0=t+hh/3.0;
              (*f)(t0,y,n,d);
              for (j=0; j<=n-1; j++)
              { 
				  b[j]=d[j]; y[j]=y[j]+hh*(d[j]-a[j])/6.0;
			  }
              (*f)(t0,y,n,d);
              for (j=0; j<=n-1; j++)
              { 
				  b[j]=d[j];
                  q=(d[j]-4.0*(b[j]+a[j]/4.0)/9.0)/8.0;
                  y[j]=y[j]+3.0*hh*q;
              }
              t0=t+hh/2.0;
              (*f)(t0,y,n,d);
              for (j=0; j<=n-1; j++)
              { 
				  c[j]=d[j];
                  q=d[j]-15.0*(b[j]-a[j]/5.0)/16.0;
                  y[j]=y[j]+2.0*hh*q;
              }
              t0=t+hh;
              (*f)(t0,y,n,d);
              for (j=0; j<=n-1; j++)
              { 
				  q=c[j]-9.0*(b[j]-2.0*a[j]/9.0)/8.0;
                  q=d[j]-8.0*q;
                  y[j]=y[j]+hh*q/6.0;
              }
              t=t+dt;
		  }
          p=0.0;
          for (j=0; j<=n-1; j++)
          { 
			  q=fabs(y[j]-v[j]);
              if (q>p) p=q;
          }
          hh=hh/2.0; nn=nn+nn;
	  }
      delete[] a; delete[] b; delete[] c; delete[] d; delete[] u; delete[] v;
      return;
  }

/*
//变步长Merson方法例
  #include <iostream>
  #include <cmath>
  #include <iomanip>
//  #include "变步长Merson方法.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      void mrsnf(double,double [],int,double []);
      double t,h,eps,y[2];
      y[0]=0.0; y[1]=1.0; 
      t=0.0; h=0.01; eps=0.0000001;
      cout <<"t = " <<t;
      for (i=0; i<=1; i++)
		  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
      cout <<endl;
      for (j=1; j<=30; j++)
      { 
		  merson(t,h,2,y,eps,mrsnf);
          t=t+h;
          cout <<"t = " <<t;
          for (i=0; i<=1; i++)
			  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
          cout <<endl;
      }
	  return 0;
  }
//计算微分方程组中各方程右端函数值
  void mrsnf(double t, double y[], int n, double d[])
  { 
	  double q;
      n=n;
      q=60.0*(0.06+t*(t-0.6));
      d[0]=q*y[1]; d[1]=-q*y[0];
      return;
  }
*/
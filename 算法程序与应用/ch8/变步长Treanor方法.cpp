//变步长Treanor方法.cpp
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
  void treanor(double t, double h, int n, double y[], double eps, 
	                   void (*f)(double,double [],int,double []))
  { 
	  int i, j, m;
      double x,dt,hh,pp,s,aa,bb,dd,g,dy,dy1,*d,*p,*w,*q,*r,*u,*v;
      w=new double[4*n];
      q=new double[4*n];
      r=new double[4*n];
      d=new double[n];
      p=new double[n];
      u=new double[n];
	  v=new double[n];
      hh = h; m = 1; pp = 1.0 + eps; x = t;
	  for (j=0; j<=n-1; j++)  u[j] = y[j];
	  while (pp>=eps)
	  {
		  for (j=0; j<=n-1; j++)
		  {
			  v[j] = y[j]; y[j] = u[j];
		  }
		  t = x; dt = hh/m;
		  for (i=0; i<=m-1; i++)
		  {
			  for (j=0; j<=n-1; j++) w[j]=y[j];
              (*f)(t,y,n,d);
              for (j=0; j<=n-1; j++)
			  { 
				  q[j]=d[j]; y[j]=w[j]+h*d[j]/2.0;
                  w[n+j]=y[j];
			  }
              s=t+h/2.0;
              (*f)(s,y,n,d);
              for (j=0; j<=n-1; j++)
			  { 
				  q[n+j]=d[j];
                  y[j]=w[j]+h*d[j]/2.0;
                  w[n+n+j]=y[j];
			  }
              (*f)(s,y,n,d);
              for (j=0; j<=n-1; j++) q[n+n+j]=d[j];
              for (j=0; j<=n-1; j++)
			  { 
				  aa=q[n+n+j]-q[n+j];
                  bb=w[n+n+j]-w[n+j];
                  if (-aa*bb*h>0.0)
				  { 
					  p[j]=-aa/bb; dd=-p[j]*h;
                      r[j]=exp(dd);
                      r[n+j]=(r[j]-1.0)/dd;
                      r[n+n+j]=(r[n+j]-1.0)/dd;
                      r[3*n+j]=(r[n+n+j]-1.0)/dd;
				  }
                  else p[j]=0.0;
                  if (p[j]<=0.0) g=q[n+n+j];
                  else
				  { 
					  g=2.0*(q[n+n+j]-q[j])*r[n+n+j];
                      g=g+(q[j]-q[n+j])*r[n+j]+q[n+j];
				  }
                  w[3*n+j]=w[j]+g*h;
                  y[j]=w[3*n+j];
			  }
              s=t+h;
              (*f)(s,y,n,d);
              for (j=0; j<=n-1; j++) q[3*n+j]=d[j];
              for (j=0; j<=n-1; j++)
			  { 
				  if (p[j]<=0.0)
				  { 
					  dy=q[j]+2.0*(q[n+j]+q[n+n+j]);
                      dy=(dy+q[n+n+n+j])*h/6.0;
				  }
                  else
				  { 
					  dy=-3.0*(q[j]+p[j]*w[j])+2.0*(q[n+j]
                          +p[j]*w[n+j]);
                      dy=dy+2.0*(q[n+n+j]+p[j]*w[n+n+j]);
                      dy=dy-(q[n+n+n+j]+p[j]*w[n+n+n+j]);
                      dy=dy*r[n+n+j]+q[j]*r[n+j];
                      dy1=q[j]-q[n+j]-q[n+n+j]+q[n+n+n+j];
                      dy1=dy1+(w[j]-w[n+j]-w[n+n+j]+w[n+n+n+j])*p[j];
                      dy=(dy+4.0*dy1*r[n+n+n+j])*h;
				  }
                  y[j]=w[j]+dy;
			  }
	          t = t + dt;
		  }
          pp = 0.0;
	      for (j=0; j<=n-1; j++)
		  {
			  dd = fabs(y[j]-v[j]);
		      if (dd>pp) pp = dd;
		  }
	      h = h/2.0; m = m + m;
	  }
      delete[] d; delete[] p; delete[] w; delete[] q; delete[] r;
	  delete[] u; delete[] v;
      return;
  }

/*
//变步长Treanor方法例
  #include <iostream>
  #include <cmath>
  #include <iomanip>
//  #include "变步长Treanor方法.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      void tnrf(double,double [],int,double []);
      double t,h,eps,y[3];
      y[0]=1.0; y[1]=0.0; y[2]=-1.0;
      t=0.0; h=0.001; eps=0.0000001;
      cout <<"t = " <<t;
      for (i=0; i<=2; i++)
		  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
      cout <<endl;
      for (j=1; j<=10; j++)
      { 
		  treanor(t,h,3,y,eps,tnrf);
          t=t+h;
          cout <<"t = " <<t;
          for (i=0; i<=2; i++)
			  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
          cout <<endl;
      }
	  return 0;
  }
//计算微分方程组中各方程右端函数值	  
  void tnrf(double t, double y[], int n, double d[])
  { 
	  t=t; n=n;
      d[0]=-21.0*y[0]+19.0*y[1]-20.0*y[2];
      d[1]=19.0*y[0]-21.0*y[1]+20.0*y[2];
      d[2]=40.0*y[0]-40.0*y[1]-40.0*y[2];
      return;
  }
*/
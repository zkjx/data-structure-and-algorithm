//全区间积分双边法.cpp
  #include <iostream>
  #include <cmath>
  #include "变步长Runge_Kutta方法.cpp"
  using namespace std;
//t           积分起始点。
//h           积分步长。
//n           一阶微分方程组中方程个数，也是未知函数个数。
//y[n]        存放n个未知函数在起始点t处的函数值。
//eps         变步长Runge_Kutta法的控制精度要求。
//k           积分步数（包括起始点这一步）。
//z[n][k]     返回k个积分点（包括起始点）上的未知函数值。
//f           计算微分方程组中各方程右端函数值的函数名。
  void gjfq(double t, double h, int n, double y[], double eps, int k, 
	           double z[], void (*f)(double,double [],int,double []))
  { 
      int i,j;
      double a,qq,*d,*p,*u,*v,*w;
      d=new double[n];
      p=new double[n];
      u=new double[n];
      v=new double[n];
      w=new double[n];
      for (i=0; i<=n-1; i++) 
	  {
		  p[i]=0.0; z[i*k]=y[i];
	  }
      a=t;
      (*f)(t,y,n,d);
      for (j=0; j<=n-1; j++) u[j]=d[j];
      runge_kutta(t,h,n,y,eps,f);
      t=a+h;
      (*f)(t,y,n,d);
      for (j=0; j<=n-1; j++)
      { 
		  z[j*k+1]=y[j]; v[j]=d[j];
	  }
      for (j=0; j<=n-1; j++)
      { 
		  p[j]=-4.0*z[j*k+1]+5.0*z[j*k]+2.0*h*(2.0*v[j]+u[j]);
        y[j]=p[j];
      }
      t=a+2.0*h;
      (*f)(t,y,n,d);
      for (j=0; j<=n-1; j++)
      { 
		  qq=2.0*h*(d[j]-2.0*v[j]-2.0*u[j])/3.0;
          qq=qq+4.0*z[j*k+1]-3.0*z[j*k];
          z[j*k+2]=(p[j]+qq)/2.0;
          y[j]=z[j*k+2];
      }
      for (i=3; i<=k-1; i++)
      { 
		  t=a+(i-1)*h;
          (*f)(t,y,n,d);
          for (j=0; j<=n-1; j++)
          { 
			  u[j]=v[j]; v[j]=d[j];
		  }
          for (j=0; j<=n-1; j++)
          { 
			  qq=-4.0*z[j*k+i-1]+5.0*z[j*k+i-2];
              p[j]=qq+2.0*h*(2.0*v[j]+u[j]);
              y[j]=p[j];
          }
          t=t+h;
          (*f)(t,y,n,d);
          for (j=0; j<=n-1; j++)
          { 
			  qq=2.0*h*(d[j]-2.0*v[j]-2.0*u[j])/3.0;
              qq=qq+4.0*z[j*k+i-1]-3.0*z[j*k+i-2];
              y[j]=(p[j]+qq)/2.0;
              z[j*k+i]=y[j];
          }
      }
      delete[] d; delete[] p; delete[] u; delete[] v; delete[] w;
      return;
  }
/*
//全区间积分双边法例
  #include <iostream>
  #include <cmath>
  #include <iomanip>
//  #include "全区间积分双边法.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      void  gjfqf(double,double [],int,double []);
      double y[2],z[2][11];
      double t,h,eps;
      t=0.0; h=0.1; eps=0.0000001;
      y[0]=1.0; y[1]=0.0;
      gjfq(t,h,2,y,eps,11,&z[0][0],gjfqf);
      for (i=0; i<=10; i++)
      { 
		  t=i*h;
          cout <<"t = " <<t;
          for (j=0; j<=1; j++)
			  cout <<"  y(" <<j <<") = " <<setw(10) <<z[j][i];
          cout <<endl;
      }
      return 0;
  }
//计算微分方程组中各方程右端函数值
  void gjfqf(double t, double y[], int n, double d[])
  { 
	  t=t; n=n;
      d[0]=-y[1]; d[1]=y[0];
      return;
  }
*/
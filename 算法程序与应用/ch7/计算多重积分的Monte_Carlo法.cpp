//计算多重积分的Monte_Carlo法.cpp
  #include <cmath>
  #include <iostream>
  #include "产生随机数类.h"
  using namespace std;
//n          积分重数。
//a[n]       各层积分的下限。
//b[n]       各层积分的上限。
//f          计算被积函数值f(X)的函数名。
  //函数返回积分值。
  double mtml(int n, double a[], double b[], double (*f)(int,double []))
  { 
	  int m,i;
      double s,d,*x;
	  RND r(1.0);
      x=new double[n];
      d=65536.0; s=0.0;
      for (m=0; m<=65535; m++)
      { 
		  for (i=0; i<=n-1; i++)
              x[i]=a[i]+(b[i]-a[i])*r.rnd1();
          s=s+(*f)(n,x)/d;
      }
      for (i=0; i<=n-1; i++) s=s*(b[i]-a[i]);
      delete[] x; return(s);
  }

/*
//计算多重积分的Monte_Carlo法例
  #include <cmath>
  #include <iostream>
//  #include "计算多重积分的Monte_Carlo法.cpp"
  using namespace std;
  int main()
  { 
	  double a[3]={ 1.0,1.0,1.0};
      double b[3]={ 2.0,2.0,2.0};
      double  mtmlf(int,double []);
      cout <<"s = " <<mtml(3,a,b,mtmlf) <<endl;
      return 0;
  }
//计算被积函数值
  double mtmlf(int n, double x[])
  { 
	  int i;
      double f;
      f=0.0;
      for (i=0; i<=n-1; i++) f=f+x[i]*x[i];
      return(f);
  }
*/
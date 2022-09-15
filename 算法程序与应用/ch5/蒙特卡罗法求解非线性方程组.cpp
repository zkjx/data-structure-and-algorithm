//蒙特卡罗法求解非线性方程组.cpp
  #include <iostream>
  #include <cmath>
  #include "产生随机数类.h"
  using namespace std;
//x[n]       存放实数解初值。
//n          方程组阶数
//b          均匀分布随机数的端点初值。
//m          控制调节b的参数。
//eps        控制精度要求。
//f          计算方程组模函数值的函数名。
  //若程序显示“b调整了100次！迭代不收敛！”，则需调整b和m的值再试。
  void nmtc(double x[], int n, double b, int m, double eps, double (*f)(double [], int))
  { 
	  int k,i,flag;
      double *y,z,z1;
	  RND  r(1.0);
      y = new double[n];
      k=0;   flag = 0;
	  z=(*f)(x,n);
      while (flag <= 100)
      {
		  k = k + 1;
		  for (i=0; i<=n-1; i++)    //产生一组随机数
              y[i]=-b+2.0*b*(r.rnd1()) + x[i];
          z1=(*f)(y,n);
          if (z1>=z)
		  { 
			  if (k == m)  
			  { 
				  flag = flag + 1; k = 0; b = b/2.0;
			  }
		  }
          else
          { 
			  k = 0;
              for (i=0; i<=n-1; i++) x[i]=y[i];
              z=z1;
              if (z<eps)  {delete[] y; return;}
          }
      }
	  cout <<"b调整了100次！迭代不收敛！" <<endl;
      delete[] y; return;
  }

/*
//蒙特卡罗法求解非线性方程组例
  #include <iostream>
  #include <cmath>
//  #include "蒙特卡罗法求解非线性方程组.cpp"
  using namespace std;
  int main()
  { 
	  int i,n,m;
      double nmtcf(double [],int);
      double b,eps,x[3]={0.0,0.0,0.0};
      b=2.0; m=50; n=3; eps=0.000001;
      nmtc(x,n,b,m,eps,nmtcf);
      for (i=0; i<=2; i++)  
		  cout <<"x(" <<i <<") = " <<x[i] <<endl;
	  cout <<"验证: |F| = " <<nmtcf(x,n) <<endl;
      return 0;
  }
//计算方程组模
  double nmtcf(double x[], int n)
  { 
	  double f,f1,f2,f3;
      n=n;
      f1=3.0*x[0]+x[1]+2.0*x[2]*x[2]-3.0;
      f2=-3.0*x[0]+5.0*x[1]*x[1]+2.0*x[0]*x[2]-1.0;
      f3=25.0*x[0]*x[1]+20.0*x[2]+12.0;
      f=sqrt(f1*f1+f2*f2+f3*f3);
      return(f);
  }
*/
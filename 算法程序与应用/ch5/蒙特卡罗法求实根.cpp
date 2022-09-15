//蒙特卡罗法求实根.cpp
  #include <cmath>
  #include <iostream>
  #include "产生随机数类.h"
  using namespace std;
//z          根的初值。
//b          均匀分布随机数的端点初值。
//m          控制调节b的参数。
//eps        控制精度要求。
//f          计算方程左端函数值的函数名。
  //函数返回根的终值。
  //若程序显示“b调整了100次！ 迭代不收敛！”，则需调整b和m的值再试。
  double metcalo(double z, double b,int m, double eps, double (*f)(double))
  { 
	  RND r(1.0);
	  int flag, k;
	  double x, z1, zz, zz1;
      k=0;  flag = 0;
	  zz = (*f)(z);
      while (flag <= 100)
      {
		  k = k + 1;
		  x = -b+2.0*b*(r.rnd1()); 
		  z1 = z + x;
          zz1 = (*f)(z1);
          if (fabs(zz1)>=fabs(zz))
          { 
			  if (k == m) 
			  {
				  k = 0; flag = flag + 1; b = b/2.0; 
			  }
		  }
          else
          { 
			  k = 0;
			  z = z1; zz = zz1;
              if (fabs(zz)<eps)  return(z);
          }
      }
	  cout <<"b调整了100次！ 迭代不收敛！" <<endl;
      return(z);
  }

/*
//蒙特卡罗法求实根例
  #include <cmath>
  #include <iostream>
//  #include "蒙特卡罗法求实根.cpp"
  using namespace std;
  int main()
  { 
	  int m;
      double b,eps;
	  double z, x, mtclf(double);
      b=1.0; m=10; eps=0.00001;
	  x = 0.5;
      z = metcalo(x,b,m,eps,mtclf);
      cout <<"z = " <<z <<endl;
	  cout <<"检验 : f(z) = " <<mtclf(z) <<endl;
      return 0;
  }
//实函数方程
  double mtclf(double x)
  { 
	  double  y;
	  y = exp(-x*x*x) - sin(x)/cos(x) + 800.0;
      return(y);
  }
*/
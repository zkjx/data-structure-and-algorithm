//蒙特卡罗法求复根.cpp
  #include <cmath>
  #include <iostream>
  #include "复数运算类.h"
  #include "产生随机数类.h"
  using namespace std;
//z          根的初值。
//b          均匀分布随机数的端点初值。
//m          控制调节b的参数。
//eps        控制精度要求。
//f          计算方程左端函数值的函数名。
  //函数返回根的终值。
  //若程序显示“b调整了100次！迭代不收敛！迭代不收敛！”，则需调整b和m的值再试。
  complex mtcl(complex z, double b,int m, double eps, complex (*f)(complex))
  { 
	  RND r(1.0);
	  int flag, k;
      double x1,y1;
	  complex z1, zz, zz1;
      k=0; flag = 0;
	  zz = (*f)(z);
      while (flag<=100)
      {
		  k = k + 1;
		  x1 = -b+2.0*b*(r.rnd1());     //产生随机数对
		  y1 = -b+2.0*b*(r.rnd1());
		  z1 = z + complex(x1,y1);
          zz1 = (*f)(z1);
          if (zz1.cfabs()>=zz.cfabs())
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
              if (zz.cfabs()<eps)  return(z);
          }
      }
	  cout <<"b调整了100次！迭代不收敛！" <<endl;
      return(z);
  }

/*
//实函数方程求复根例
  #include <cmath>
  #include <iostream>
//  #include "蒙特卡罗法求复根.cpp"
  using namespace std;
  int main()
  { 
	  int m;
      double b,eps;
	  complex z, x, mtclf(complex);
      x=complex(0.5,0.5); 
	  b=1.0; m=10; eps=0.00001;
      z = mtcl(x,b,m,eps,mtclf);
      cout <<"z = "; z.prt(); cout <<endl;
      cout <<"检验: f(z) = "; mtclf(z).prt(); cout <<endl;
	  return 0;
  }
//实函数方程
  complex mtclf(complex x)    //要将系数化为复数
  { 
	  complex z;
      z = x*x - complex(6.0,0.0)*x + complex(13.0,0.0);
      return(z);
  }
*/
/*
//复函数方程求复根例
  #include <cmath>
  #include <iostream>
//  #include "蒙特卡罗法求复根.cpp"
  using namespace std;
  int main()
  { 
	  int m;
      double b,eps;
	  complex z, x, mtclf(complex);
      x=complex(0.5,0.5); 
	  b=1.0; m=10; eps=0.00001;
      z = mtcl(x,b,m,eps,mtclf);
      cout <<"z = "; z.prt(); cout <<endl;
      cout <<"检验: f(z) = "; mtclf(z).prt(); cout <<endl;
	  return 0;
  }
//复函数方程
  complex mtclf(complex x)
  { 
	  complex z;
      z = x*x + x*complex(1.0,1.0) + complex(-2.0,2.0);
      return(z);
  }
*/
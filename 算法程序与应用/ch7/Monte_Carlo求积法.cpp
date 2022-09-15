//Monte_Carlo求积法.cpp
  #include <cmath>
  #include <iostream>
  #include "产生随机数类.h"
  using namespace std;
//a          积分下限。
//b          积分上限。要求b>a。
//f          计算被积函数值f(x)的函数名。
  //函数返回积分值。
  double mtcl(double a, double b, double (*f)(double))
  { 
	  int m;
      double d,x,s;
	  RND r(1.0);
      s=0.0; d=65536.0;
      for (m=0; m<=65535; m++)
      { 
		  x=a+(b-a)*r.rnd1();
          s=s+(*f)(x);
      }
      s=s*(b-a)/d;
      return(s);
  }
/*
//Monte_Carlo求积法例
  #include <cmath>
  #include <iostream>
//  #include "Monte_Carlo求积法.cpp"
  using namespace std;
  int main()
  { 
	  double mtclf(double);
      cout <<"s = " <<mtcl(2.5,8.4,mtclf) <<endl;
      return 0;
  }
//计算被积函数值
  double mtclf(double x)
  { 
	  double y;
      y=x*x+sin(x);
      return(y);
  }
*/

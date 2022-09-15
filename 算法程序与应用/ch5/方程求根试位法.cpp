//方程求根试位法.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//a          求根区间左端点。
//b          求根区间右端点。
//eps        控制精度要求。
//f          方程左端函数f(x)的函数名。
//x          存放方程根的初值。返回迭代终值。
  //函数返回迭代次数。若为-1则表示f(a)f(b)>0。
  int fals(double a, double b, double eps, double (*f)(double), double *x)
  {
	  int m;
	  double fa, fb, y;
	  m = 0;
	  fa = (*f)(a);  fb = (*f)(b);
	  if (fa*fb > 0)  return(-1);
	  do
	  {
		  m = m + 1;
		  *x = (a*fb - b*fa)/(fb - fa);
          y = (*f)(*x);
		  if (y*fa < 0) { b = *x; fb = y; }
		  else  { a = *x; fa = y; }
	  } while (fabs(y) >= eps);
      return(m);
  }

/*
//方程求根试位法例
  #include <iostream>
  #include <cmath>
//  #include "方程求根试位法.cpp"
  using namespace std;
  int main ()      //主函数
  {
	  int k;
	  double x, func(double);
	  k = fals(1.0, 3.0, 0.000001, func, &x);   //执行试位法
	  cout <<"迭代次数 = " <<k <<endl;
	  cout <<"一个实根 x = " <<x <<endl;
	  return 0;
  }
//f(x)
  double func(double x)    //计算方程左端函数f(x)值
  {
	  double y;
	  y = x*x*x - 2*x*x + x - 2;
	  return y;
  }
*/


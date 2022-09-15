//方程求根newton法.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//x          存放方程根的初值。返回迭代终值。
//eps        控制精度要求。
//f          方程左端函数f(x)的函数名。         
//df         方程左端函数f(x)一阶导函数名。
  //函数返回迭代次数。若返回 -1 ，则表示出现df/dx=0的情况。程序最多迭代次数为500。
  int newt(double *x, double eps, double (*f)(double), double (*df)(double))
  { 
	  int k, interation;
      double y, dy, d, p, x0, x1;
	  interation = 500;         //最大迭代次数
      k = 0; x0 = *x; 
      y = (*f)(x0); dy = (*df)(x0);
      d=eps+1.0;
      while ((d>=eps)&&(k!=interation))
      { 
		  if (fabs(dy)+1.0==1.0)     //出现df(x)/dx=0
          { 
			  cout <<"dy == 0 !";  return(-1);
		  }
         x1 = x0 - y/dy;            //迭代
         y = (*f)(x1); dy = (*df)(x1);
         d=fabs(x1-x0); p=fabs(y);
         if (p>d) d=p;
         x0 = x1; k = k + 1;
      }
      *x = x0;
      return(k);
  }
/*
//方程求根newton法例
  #include <cmath>
  #include <iostream>
//  #include "方程求根newton法.cpp"
  using namespace std;
  int main()
  { 
	  int k;
      double x,eps;
	  double newtf(double x), newtdf(double x);
      eps=0.000001;  x=1.5;
      k=newt(&x,eps,newtf,newtdf);
      if (k>=0)
	  {
		  cout <<"迭代次数 = " <<k <<endl;
		  cout <<"迭代终值 x = " <<x <<endl;
	  }
      return 0;
  }
//f(x)
  double newtf(double x)
  { 
	  return(x*x*(x-1.0)-1.0);
  }
//df(x)/dx
  double newtdf(double x)
  {
	  return(3.0*x*x - 2.0*x);
  }
*/
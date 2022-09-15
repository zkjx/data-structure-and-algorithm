//方程求根aitken迭代法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//x          存放方程根的初值。返回迭代终值。
//eps        控制精度要求。
//f          简单迭代格式右端函数φ(x)的函数名。         
  //函数返回迭代次数。程序最多迭代次数为500。
  int atkn(double *x, double eps, double (*f)(double))
  { 
	  int flag, k, interation;
      double u, v, x0;
	  interation = 500;         //最大迭代次数
      k = 0; x0 = *x; flag = 0;
      while ((flag==0)&&(k!=interation))
      { 
		  k = k + 1; 
          u = (*f)(x0); v = (*f)(u);
          if (fabs(u-v)<eps) 
		  { 
			  x0 = v; flag = 1; 
		  }
          else 
			  x0 = v-(v-u)*(v-u)/(v-2.0*u+x0);
      }
      *x = x0; 
      return(k);
  }

/*
//方程求根aitken迭代法例
  #include <cmath>
  #include <iostream>
//  #include "方程求根aitken迭代法.cpp"
  using namespace std;
  int main()
  { 
	  int k;
      double x,eps,atknf(double);
      eps = 0.0000001;  x = 0.0;
      k = atkn(&x,eps,atknf);
      cout <<"迭代次数 = " <<k <<endl;
      cout <<"迭代终值 x = " <<x <<endl;
      return 0;
  }
//φ(x)
  double atknf(double x)
  { 
	  return(6.0-x*x);
  }
*/

//埃尔米特_高斯求积法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//f          计算被积函数值f(x)的函数名。
  //函数返回积分值。
  double hmgs(double (*f)(double))
  { 
	  int i;
      double x,g;
      double t[5]={-2.02018200,-0.95857190,
                     0.0,0.95857190,2.02018200};
      double c[5]={1.181469599,0.9865791417,
           0.9453089237,0.9865791417,1.181469599};
      g=0.0;
      for (i=0; i<=4; i++)
      { 
		  x=t[i]; g=g+c[i]*(*f)(x);
	  }
      return(g);
  }

/*
//埃尔米特_高斯求积法例
  #include <cmath>
  #include <iostream>
//  #include "埃尔米特_高斯求积法.cpp"
  using namespace std;
  int main()
  { 
	  double hmgsf(double);
      cout <<"g = " <<hmgs(hmgsf) <<endl;
      return 0;
  }
//计算被积函数值
  double hmgsf(double x)
  { 
	  double y;
      y=x*x*exp(-x*x);
      return(y);
  }
*/

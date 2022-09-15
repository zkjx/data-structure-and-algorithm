//正态分布函数.cpp
  #include <cmath>
  #include <iostream>
  #include "误差函数.cpp"
  using namespace std;
//a     数学期望值。
//d     d*d为方差值。要求d>0。
//x     随机变量值。
  //函数返回正态分布函数值。
  double gass(double a, double d, double x)
  { 
	  double y;
      if (d<=0.0) d=1.0e-10;
      y=0.5+0.5*errf((x-a)/(sqrt(2.0)*d));
      return(y);
  }
/*
//正态分布函数例
  #include <cmath>
  #include <iostream>
//  #include "正态分布函数.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double a0,d0,x,y;
      double a[2]={ -1.0,3.0};
      double d[2]={ 0.5,15.0};
      for (i=0; i<=1; i++)
      { 
		  a0=a[i]; d0=d[i]; x=-10.0;
          for (j=0; j<=4; j++)
          { 
			  y=gass(a0,d0,x);
              cout <<"P(" <<a0 <<", " <<d0 <<", " <<x <<")=" <<y <<endl;
              x=x+5.0;
          }
      }
      return 0;
  }
*/
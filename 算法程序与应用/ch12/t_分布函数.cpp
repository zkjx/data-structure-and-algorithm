//t_分布函数.cpp
  #include <iostream>
  #include <cmath>
  #include "不完全Beta函数.cpp"
  using namespace std;
//t     随机变量值。要求t>=0。
//n     自由度。
  //返回t分布函数值。
  double student(double t, int n)
  { 
	  double y;
      if (t<0.0) t=-t;
      y=1.0-inbeta(n/2.0,0.5,n/(n+t*t));
      return(y);
  }
/*
//t_分布函数例
  #include <iostream>
  #include <cmath>
//  #include "t_分布函数.cpp"
  using namespace std;
  int main()
  { 
	  int n;
      double t,y;
      for (n=1; n<=5; n++)
      { 
		  t=0.5; y=student(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
          t=5.0; y=student(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
      }
      return 0;
  }
*/

//误差函数.cpp
  #include "不完全Gamma函数.cpp"
  using namespace std;
//x      自变量值。
  //函数返回误差函数值。
  double errf(double x)
  { 
	  double y;
      if (x>=0.0) y=ingamma(0.5,x*x);
      else y=-ingamma(0.5,x*x);
      return(y);
  }
/*
//误差函数例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "误差函数.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double x,y;
	  x = 0.0;  y = errf(x);
	  cout <<setw(15) <<y <<endl;
      for (i=0; i<=7; i++)
      { 
		  for (j=0; j<=4; j++)
          { 
			  x = x + 0.05;   y=errf(x);
              cout <<setw(15) <<y;
          }
          cout <<endl;
      }
      return 0;
  }
*/
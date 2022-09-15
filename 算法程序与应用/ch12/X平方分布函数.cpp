//X平方分布函数.cpp
  #include <iostream>
  #include <cmath>
  #include "不完全gamma函数.cpp"
  using namespace std;
//x     自变量值。
//n     自由度。
  //返回X平方分布函数值。
  double chii(double x, int n)
  { 
	  double y;
      if (x<0.0) x=-x;
      y=ingamma(n/2.0,x/2.0);
      return(y);
  }
/*
//X平方分布函数例
  #include <iostream>
  #include <cmath>
//  #include "X平方分布函数.cpp"
  using namespace std;
  int main()
  { 
	  int n;
      double t,y;
      for (n=1; n<=5; n++)
      { 
		  t=0.5; y=chii(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
          t=5.0; y=chii(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
      }
      return 0;
  }
*/
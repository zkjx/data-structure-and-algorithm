//F_分布函数.cpp
  #include <iostream>
  #include <cmath>
  #include "不完全Beta函数.cpp"
  using namespace std;
//f      随机变量值。要求f>=0。
//n1     自由度。
//n2     自由度。
  //返回F分布函数值。
  double ffff(double f, int n1, int n2)
  { 
	  double y;
      if (f<0.0) f=-f;
      y=inbeta(n2/2.0,n1/2.0,n2/(n2+n1*f));
      return(y);
  }
/*
//F_分布函数例
  #include <iostream>
  #include <cmath>
//  #include "F_分布函数.cpp"
  using namespace std;
  int main()
  { 
	  int n1,n2,i;
      double y,f;
      int n[2]={ 2,5};
      int m[2]={ 3,10};
      for (i=0; i<=1; i++)
      { 
		  n1=n[i]; n2=m[i]; f=3.5;
          y=ffff(f,n1,n2);
          cout <<"P(" <<f <<", " <<n1 <<", " <<n2 <<")=" <<y <<endl;
          f=9.0; y=ffff(f,n1,n2);
          cout <<"P(" <<f <<", " <<n1 <<", " <<n2 <<")=" <<y <<endl;
      }
      return 0;
  }
*/

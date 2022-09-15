//复数运算类例.cpp
  #include  <iostream>
  #include  <cmath>
  #include  "复数运算类.h"
  using namespace std;
  int  main ()      //主函数
  {
	  double a, b, x;
	  complex  c;
	  cin >>a >>b;
      c=complex(a,b);
	  x=c.angle();
	  cout <<"c=";	  c.prt();
	  cout <<"=" <<c.cfabs() <<endl;
	  cout <<"幅角=" <<c.angle() <<endl;
	  return 0;
  }


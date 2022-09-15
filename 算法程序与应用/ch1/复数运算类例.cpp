//复数运算类例.cpp
  #include  <iostream>
  #include  <cmath>
  #include  "复数运算类.h"
  using namespace std;
  int  main ()      //主函数
  {
	  int i;
	  double a, b;
	  complex  c1, c2, c3, c, p[5];
	  cin >>a >>b;
	  c1 = complex(a, b);  cout <<"c1 = "; c1.prt(); cout <<endl;
	  cin >>a >>b;
	  c2 = complex(a, b);  cout <<"c2 = "; c2.prt(); cout <<endl;
	  cin >>a >>b;
	  c3 = complex(a, b);  cout <<"c3 = "; c3.prt(); cout <<endl;
	  c = c1 + c2;
	  cout <<"c1 + c2 = ";  c.prt(); cout <<endl;
	  c = c1 - c2;
	  cout <<"c1 - c2 = ";  c.prt(); cout <<endl;
	  c = c1 * c2;
	  cout <<"c1 * c2 = ";  c.prt(); cout <<endl;
	  c = c1 / c2;
	  cout <<"c1 / c2 = ";  c.prt(); cout <<endl;
	  c = c3.cpower(-3);
	  cout <<"c3 的-3次方 = ";  c.prt(); cout <<endl;
	  cout <<"c3 的5次方根为: " <<endl;
	  c3.croot(5, p);
	  for (i=0; i<5; i++)
	  {
		  p[i].prt(); cout <<endl;
	  }
      c = c3.cexp();
      cout <<"cexp(c3) = ";  c.prt(); cout <<endl;
	  c = c3.clog();
      cout <<"clog(c3) = ";  c.prt(); cout <<endl;
      c = c3.csin();
      cout <<"csin(c3) = ";  c.prt(); cout <<endl;
      c = c3.ccos();
      cout <<"ccos(c3) = ";  c.prt(); cout <<endl;
	  return 0;
  }


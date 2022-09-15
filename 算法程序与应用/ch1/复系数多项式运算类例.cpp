//复系数多项式运算类例.cpp
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  #include "复系数多项式运算类.h"
  using namespace std;
  int main ()
  {
	  int i;
	  double a, b;
	  complex  p1[4]={complex(2,1),complex(2,1),complex(1,1),complex(2,2)};
	  complex  p2[6]={complex(4,2),complex(-6,3),complex(5,-4),
		              complex(2,1),complex(-1,-1),complex(3,2)};
	  complex  q2[4]={complex(2,1),complex(3,2),complex(-6,-4),complex(2,1)};
	  complex  p3[5]={complex(8,3),complex(-5,4),complex(-3,4),
		              complex(6,-5),complex(3,-1)};
	  complex  q3[3]={complex(1,2),complex(-1,-3),complex(2,2)};
      complex  x, y, s2[9], s3[3], r3[2];
	  com_poly p, q, s, r;
	  cout <<"输入x = ";
	  cin >>a >>b;
	  x=complex(a,b);
	  p=com_poly(3,p1);
	  cout <<"多项式求值: " <<endl;
	  cout <<"x = "; x.prt(); cout <<endl;
	  cout <<"p(x) = "; y = p.poly_value(x); y.prt();  cout <<endl;
	  p=com_poly(5,p2);
	  q=com_poly(3,q2);
	  s=com_poly(8,s2);
      p.com_poly_mul (q, s);    //多项式相乘 s2 = p2*q2
	  cout <<"乘积多项式s2 = p2*q2 :" <<endl;
      for (i=0; i<=8; i++)       //输出乘积多项式s2的系数
	  {
		  cout <<"s2(" <<i <<") = ";  s2[i].prt();  cout <<endl;
	  }
	  p=com_poly(4,p3);
	  q=com_poly(2,q3);
	  s=com_poly(2,s3);
	  r=com_poly(1,r3);
      p.com_poly_div (q, s, r);  //多项式相除 s3 = p3/q3 余 r3
	  cout <<"p3/q3商多项式s3:" <<endl;
	  for (i=0; i<=2; i++)      //输出商多项式s3的系数
	  {
		  cout <<"s3(" <<i <<") = ";  s3[i].prt();  cout <<endl;
	  }
	  cout <<"p3/q3余多项式r3:" <<endl;
	  for (i=0; i<=1; i++)      //输出余多项式r3的系数
	  {
		  cout <<"r3(" <<i <<") = ";  r3[i].prt();  cout <<endl;
	  }
	  return 0;
  }

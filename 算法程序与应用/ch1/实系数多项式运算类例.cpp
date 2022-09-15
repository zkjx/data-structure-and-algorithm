//实系数多项式运算类.cpp
  #include  <iostream>
  #include  "实系数多项式运算类.h"
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  int main ()      //主函数
  {
	  int k;
	  double x[6] = { 0.9, 1.1, 1.3, -0.9, -1.1, -1.3 };
      double p1[7] = { -20.0,7.0,-7.0,1.0,3.0,-5.0,2.0 };
	  double p2[6] = { 4.0,-6.0,5.0,2.0,-1.0,3.0 };
	  double q2[4] = { 2.0,3.0,-6.0,2.0 };
	  double p3[5] = { 8.0,-5.0,-3.0,6.0,3.0 };
	  double q3[3] = { 1.0,-1.0,2.0 };
	  double s2[9], s3[3], r3[2];
      poly p, q, s, r;
      p = poly(6,p1);
	  cout <<"多项式求值: " <<endl;
	  for (k=0; k<6; k++)
         cout <<"p(" <<x[k] <<") = " <<p.poly_value(x[k]) <<endl;

	  p = poly(5,p2);
	  q = poly(3,q2);
	  s = poly(8,s2);
      p.poly_mul (q, s);    //多项式相乘 s2 = p2*q2
	  cout <<"乘积多项式s2 = p2*q2 :" <<endl;
      for (k=0; k<=8; k++)       //输出乘积多项式s2的系数
	  {
		  cout <<"s2(" <<k <<") = " <<s2[k] <<endl; 
	  }
	  p=poly(4,p3);
	  q=poly(2,q3);
	  s=poly(2,s3);
	  r=poly(1,r3);
      p.poly_div(q, s, r);  //多项式相除 s3 = p3/q3 余 r3
	  cout <<"p3/q3商多项式s3:" <<endl;
	  for (k=0; k<=2; k++)      //输出商多项式s3的系数
	  {
		  cout <<"s3(" <<k <<") = " <<s3[k] <<endl; 
	  }
	  cout <<"p3/q3余多项式r3:" <<endl;
	  for (k=0; k<=1; k++)      //输出余多项式r3的系数
	  {
		  cout <<"r3(" <<k <<") = " <<r3[k] <<endl; 
	  }
	  return 0;
  }


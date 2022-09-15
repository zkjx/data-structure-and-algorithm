//复系数多项式运算类.h
  #include  <iostream>
  #include  <cmath>
  #include  <fstream>
  #include "复数运算类.h"
  using namespace std;
  class  com_poly:public complex //声明com_poly是基类complex类的派生类
  {
  private: 
	       int N;              //复系数多项式次数
		   complex  *p;        //复系数多项式存储空间首地址
  public:
	       com_poly (int nn=0, complex *pp=NULL)    //构造函数
		   {  N = nn;  p = pp;  }
		   void  input ();                   //由键盘输入多项式复系数
           complex poly_value(complex);      //复系数多项式求值

//		   void com_poly operator + (com_poly&,com_poly&);  //复系数多项式相加
//		   void com_poly operator - (com_poly&,com_poly&);  //复系数多项式相减


           void com_poly_mul(com_poly&,com_poly&);  //复系数多项式相乘
           void com_poly_div(com_poly&,com_poly&,com_poly&);  //复系数多项式相除
  };


  //由键盘输入多项式复系数
  void com_poly::input ()
  {
	  int  i;
	  double a,b;
	  cout <<"多项式复系数:" <<endl;
      for (i=0; i<N+1; i++)              //输入多项式复系数
	  {
		  cout <<"p(" <<i <<") = ";
		  cin >>a >>b;  p[i]=complex(a, b);
	  }
  }

  //复系数多项式求值p(x)
  complex com_poly::poly_value(complex x)
  {
	  int k;
	  complex u;
	  u = p[N];
	  for (k=N-1; k>=0; k--)  u = u*x + p[k];
	  return u;
  }

  //复系数多项式相乘 s = p*q
  void com_poly::com_poly_mul(com_poly& q, com_poly& s)  
  {
      int i,j;
      for (i=0; i<=s.N; i++) s.p[i] = complex(0.0,0.0);
      for (i=0; i<=N; i++)
      for (j=0; j<=q.N; j++)
          s.p[i+j]=s.p[i+j] + p[i]*q.p[j];
	  return ;
  }

  //复系数多项式相除 s = p/q 余 r
  void com_poly::com_poly_div(com_poly& q, com_poly& s, com_poly& r)
  {
	  int i,j,mm,ll;
      for (i=0; i<=s.N; i++) s.p[i]=complex(0.0,0.0);
      if ( (q.p[q.N]).cfabs()+1.0==1.0)  return;
      ll=N;
      for (i=(s.N)+1; i>=1; i--)
      { 
		  s.p[i-1]=p[ll]/(q.p[q.N]);
          mm=ll;
          for (j=1; j<=q.N; j++)
          { 
			  p[mm-1]=p[mm-1]-s.p[i-1]*(q.p[(q.N)-j]);
              mm=mm-1;
          }
          ll=ll-1;
      }
      for (i=0; i<=r.N; i++) r.p[i]=p[i];	  
	  return;
  }

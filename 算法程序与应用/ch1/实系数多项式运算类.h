//实系数多项式运算类.h
  #include  <iostream>
  #include  <fstream>
  #include  <cmath>
  using namespace std;
  class  poly
  {
  private: 
	       int N;         //多项式次数
		   double  *p;    //多项式系数存储空间首地址
  public:
	       poly(int nn=0, double *pp=NULL)  //构造函数
		   { 
			   N = nn;  p=pp;
		   }
		   void  input ();             //由键盘输入多项式系数
           double poly_value(double);  //多项式求值
           void poly_mul(poly&,poly&);  //多项式相乘
           void poly_div(poly&,poly&,poly&);   //多项式相除
  };

  //由键盘输入多项式系数
  void poly::input () 
  {
	  int  i;
	  cout <<"多项式系数:" <<endl;
      for (i=0; i<N+1; i++)              //输入多项式系数
	  {
		  cout <<"p(" <<i <<") = ";
		  cin >>p[i];
	  }
  }

  //多项式求值p(x)
  double poly::poly_value(double x)
  {
	  int k;
	  double u;
	  u = p[N];
	  for (k=N-1; k>=0; k--)  u = u*x + p[k];
	  return u;
  }

  //多项式相乘 s = p*q
  void poly::poly_mul(poly& q, poly& s)
  {
      int i,j;
      for (i=0; i<=s.N; i++) s.p[i]=0.0;
      for (i=0; i<=N; i++)
      for (j=0; j<=q.N; j++)
          s.p[i+j]=s.p[i+j] + p[i]*q.p[j];
	  return ;
  }

  //多项式相除 s = p/q 余 r
  void poly::poly_div(poly& q, poly& s, poly& r)
  {
	  int i,j,mm,ll;
      for (i=0; i<=s.N; i++) s.p[i]=0.0;
      if (q.p[q.N]+1.0==1.0) return;
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

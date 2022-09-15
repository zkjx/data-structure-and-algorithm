//不完全Gamma函数.cpp
  #include <iostream>
  #include <cmath>
  #include "Gamma函数.cpp"
  using namespace std;
//a      自变量值。要求 a>0。
//x      自变量值。要求 x>=0。
  //函数返回不完全Gamma函数值。
  double ingamma(double a, double x)
  { 
	  int n, flag;
      double p,q,d,s,s1,p0,q0,p1,q1,qq;
      if ((a<=0.0)||(x<0.0))
      { 
		  if (a<=0.0) cout <<"err**a<=0!\n";
          if (x<=0.0) cout <<"err**x<0!\n";
          return(-1.0);
      }
      if (x+1.0==1.0) return(0.0);
      if (x>1.0e+35) return(1.0);
      q=log(x); q=a*q; qq=exp(q);
      if (x<1.0+a)
      { 
		  p=a; d=1.0/a; s=d; n = 0;
		  do
		  {
			  n = n + 1;
			  p = p+1.0; d = d*x/p; s = s+d;
			  flag = (fabs(d)>=fabs(s)*1.0e-07);
		  }
		  while ((n<=100)&&(flag));
          if (!flag)
		  {
			  s = s*exp(-x)*qq/gamma(a);
			  return(s);
		  }
      }
      else
      { 
		  s=1.0/x; p0=0.0; p1=1.0; q0=1.0; q1=x;
          for (n=1; n<=100; n++)
          { 
			  p0=p1+(n-a)*p0; q0=q1+(n-a)*q0;
              p=x*p0+n*p1; q=x*q0+n*q1;
              if (fabs(q)+1.0!=1.0)
              { 
				  s1=p/q; p1=p; q1=q;
                  if (fabs((s1-s)/s1)<1.0e-07)
                  { 
					  s=s1*exp(-x)*qq/gamma(a);
                      return(1.0-s);
                  }
                  s=s1;
              }
              p1=p; q1=q;
          }
      }
      cout <<"a too large !\n";
      s=1.0-s*exp(-x)*qq/gamma(a);
      return(s);
  }
/*
//不完全Gamma函数例
  #include <iostream>
  #include <cmath>
//  #include "不完全Gamma函数.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double y,s,t;
      double a[3]={0.5,5.0,50.0};
      double x[3]={0.1,1.0,10.0};
      for (i=0; i<=2; i++)
      for (j=0; j<=2; j++)
      { 
		  s=a[i]; t=x[j];
          y = ingamma(s,t);
		  cout <<"ingamma(" <<a[i] <<", " <<x[j] <<") = " <<y <<endl;
      }
      return 0;
  }
*/
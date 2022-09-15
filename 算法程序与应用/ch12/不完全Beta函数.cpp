//不完全Beta函数.cpp
  #include <cmath>
  #include <iostream>
  #include "Gamma函数.cpp"
  using namespace std;
//a       参数。要求a>0,否则返回函数值-1.0。
//b       参数。要求b>0,否则返回函数值-1.0。
//x       自变量。要求0=<x<=1，否则返回函数值1.0e+37。
  //函数返回不完全Beta函数值。
  double inbeta(double a, double b, double x)
  { 
	  double y;
      double bt(double,double,double);
      if (a<=0.0)
      { cout <<"err**a<=0!\n"; return(-1.0);}
      if (b<=0.0)
      { cout <<"err**b<=0!\n"; return(-1.0);}
      if ((x<0.0)||(x>1.0))
      { cout <<"err**x<0 or x>1 !\n";
        return(1.0e+70);
      }
      if ((x==0.0)||(x==1.0)) y=0.0;
      else
      { 
		  y=a*log(x)+b*log(1.0-x);
          y=exp(y);
          y=y*gamma(a+b)/(gamma(a)*gamma(b));
      }
      if (x<(a+1.0)/(a+b+2.0))
          y=y*bt(a,b,x)/a;
      else
          y=1.0-y*bt(b,a,1.0-x)/b;
      return(y);
  }

  double bt(double a, double b, double x)
  { 
	  int k;
      double d,p0,q0,p1,q1,s0,s1;
      p0=0.0; q0=1.0; p1=1.0; q1=1.0;
      for (k=1; k<=100; k++)
      { 
		  d=(a+k)*(a+b+k)*x;
          d=-d/((a+k+k)*(a+k+k+1.0));
          p0=p1+d*p0; q0=q1+d*q0; s0=p0/q0;
          d=k*(b-k)*x;
          d=d/((a+k+k-1.0)*(a+k+k));
          p1=p0+d*p1; q1=q0+d*q1; s1=p1/q1;
          if (fabs(s1-s0)<fabs(s1)*1.0e-07)
          return(s1);
      }
      cout <<"a or b too big !\n";
      return(s1);
  }
/
//不完全Beta函数例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "不完全Beta函数.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double x,a0,b0,y;
      double a[5]={ 0.5,0.5,1.0,5.0,8.0};
      double b[5]={ 0.5,5.0,3.0,0.5,10.0};
      x=0.0;
      for (j=0; j<=5; j++)
      { 
		  cout <<"x=" <<x <<endl;
          for (i=0; i<=4; i++)
          { 
			  a0=a[i]; b0=b[i];
              y=inbeta(a0,b0,x);
              cout <<"      B(" <<a0 <<", " <<b0 <<")=" <<y <<endl;
          }
          x=x+0.2;
      }
      return 0;
  }

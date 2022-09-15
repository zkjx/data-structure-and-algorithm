//Romberg求积法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//a          积分下限。
//b          积分上限。要求b>a。
//eps        积分精度要求。
//f          计算被积函数值f(x)的函数名。
  //函数返回积分值。
  double romb(double a, double b, double eps, double (*f)(double))
  { 
	  int m,n,i,k;
      double y[10],h,ep,p,x,s,q;
      h=b-a;
      y[0]=h*((*f)(a)+(*f)(b))/2.0;
      m=1; n=1; ep=eps+1.0;
      while ((ep>=eps)&&(m<=9))
      { 
		  p=0.0;
          for (i=0;i<=n-1;i++)
          { 
			  x=a+(i+0.5)*h;  p=p+(*f)(x);
          }
          p=(y[0]+h*p)/2.0;
          s=1.0;
          for (k=1;k<=m;k++)
          { 
			  s=4.0*s;
              q=(s*p-y[k-1])/(s-1.0);
              y[k-1]=p; p=q;
          }
          ep=fabs(q-y[m-1]);
          m=m+1; y[m-1]=q; n=n+n; h=h/2.0;
      }
      return(q);
  }

/*
//Romberg求积法例
  #include <cmath>
  #include <iostream>
//  #include "Romberg求积法.cpp"
  using namespace std;
  int main()
  { 
	  double a,b,eps,t,rombf(double);
      a=0.0; b=1.0; eps=0.000001;
      t = romb(a,b,eps,rombf);
      cout <<"t = " <<t <<endl;
      return 0;
  }
//计算被积函数值
  double rombf(double x)
  { 
	  return(x/(4.0+x*x));
  }
*/

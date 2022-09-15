//切比雪夫求积法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//a          积分下限。
//b          积分上限。要求b>a。
//eps        积分精度要求。
//f          计算被积函数值f(x)的函数名。
  //函数返回积分值。
  double cbsv(double a, double b, double eps, double (*f)(double))
  { 
	  int m,i,j;
      double h,d,p,ep,g,aa,bb,s,x;
      double t[5]={-0.8324975,-0.3745414,0.0,
                         0.3745414,0.8324975};
      m=1;
      h=b-a; d=fabs(0.001*h);
      p=1.0e+35; ep=1.0+eps;
      while ((ep>=eps)&&(fabs(h)>d))
      { 
		  g=0.0;
          for (i=1;i<=m;i++)
          { 
			  aa=a+(i-1.0)*h; bb=a+i*h;
              s=0.0;
              for (j=0;j<=4;j++)
              { 
				  x=((bb-aa)*t[j]+(bb+aa))/2.0;
                  s=s+(*f)(x);
              }
              g=g+s;
          }
          g=g*h/5.0;
          ep=fabs(g-p)/(1.0+fabs(g));
          p=g; m=m+1; h=(b-a)/m;
      }
      return(g);
  }
/*
//切比雪夫求积法例
  #include <cmath>
  #include <iostream>
//  #include "切比雪夫求积法.cpp"
  using namespace std;
  int main()
  { 
	  double a,b,eps,s,cbsvf(double);
      a=2.5; b=8.4; eps=0.000001;
      s=cbsv(a,b,eps,cbsvf);
      cout <<"s = " <<s <<endl;
      return 0;
  }
//计算被积函数值
  double cbsvf(double x)
  { 
	  double y;
      y=x*x+sin(x);
      return(y);
  }
*/
//指数积分.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//x     自变量值。
  //函数返回指数积分值。
  double expp(double x)
  { 
	  int m,i,j;
      double s,p,ep,h,aa,bb,w,xx,g,r,q;
      double t[5]={-0.9061798459,-0.5384693101,0.0,
                         0.5384693101,0.9061798459};
      double c[5]={0.2369268851,0.4786286705,0.5688888889,
                        0.4786286705,0.2369268851};
      m=1;
      if (x==0) x=1.0e-10;
      if (x<0.0) x=-x;
      r=0.57721566490153286060651;
      q=r+log(x);
      h=x; s=fabs(0.0001*h);
      p=1.0e+35; ep=0.000001; g=0.0;
      while ((ep>=0.0000001)&&(fabs(h)>s))
      { 
		  g=0.0;
          for (i=1;i<=m;i++)
          { 
			  aa=(i-1.0)*h; bb=i*h;
              w=0.0;
              for (j=0;j<=4;j++)
              { 
				  xx=((bb-aa)*t[j]+(bb+aa))/2.0;
                  w=w+(exp(-xx)-1.0)/xx*c[j];
              }
              g=g+w;
          }
          g=g*h/2.0;
          ep=fabs(g-p)/(1.0+fabs(g));
          p=g; m=m+1; h=x/m;
      }
      g=q+g;
      return(g);
  }
/*
//指数积分例
  #include <cmath>
  #include <iostream>
//  #include "指数积分.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double x,y;
      for (i=0; i<=9; i++)
      { 
		  x=0.05+0.2*i; y=expp(x);
          cout <<"x=" <<x <<"    Ei(x)=" <<y <<endl;
      }
      return 0;
  }
*/
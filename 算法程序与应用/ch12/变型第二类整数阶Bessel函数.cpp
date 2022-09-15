//变型第二类整数阶Bessel函数.cpp
  #include <cmath>
  #include <iostream>
  #include "变型第一类整数阶Bessel函数.cpp"
  using namespace std;
//n     阶数。要求n>0。
//x     自变量值。
  //函数返回变型第二类整数阶Bessel函数值。
  double b_bessel_2(int n, double x)
  { 
	  int i;
      double y,p,b0,b1;
      double a[7]={ -0.57721566,0.4227842,0.23069756,
                    0.0348859,0.00262698,0.0001075,0.0000074};
      double b[7]={ 1.0,0.15443144,-0.67278579,
                   -0.18156897,-0.01919402,-0.00110404,-0.00004686};
      double c[7]={ 1.25331414,-0.07832358,0.02189568,
                   -0.01062446,0.00587872,-0.0025154,0.00053208};
      double d[7]={ 1.25331414,0.23498619,-0.0365562,
                    0.01504268,-0.00780353,0.00325614,-0.00068245};
      if (n<0) n=-n;
      if (x<0.0) x=-x;
      if (x==0.0) return(1.0e+70);
      if (n!=1)
      { 
		  if (x<=2.0)
          {
			  y=x*x/4.0; p=a[6];
              for (i=5; i>=0; i--) p=p*y+a[i];
              p=p-b_bessel_1(0,x)*log(x/2.0);
          }
          else
          { 
			  y=2.0/x; p=c[6];
              for (i=5; i>=0; i--) p=p*y+c[i];
              p=p*exp(-x)/sqrt(x);
          }
      }
      if (n==0) return(p);
      b0=p;
      if (x<=2.0)
      { 
		  y=x*x/4.0; p=b[6];
          for (i=5; i>=0; i--) p=p*y+b[i];
          p=p/x+b_bessel_1(1,x)*log(x/2.0);
      }
      else
      { 
		  y=2.0/x; p=d[6];
          for (i=5; i>=0; i--) p=p*y+d[i];
          p=p*exp(-x)/sqrt(x);
      }
      if (n==1) return(p);
      b1=p;
      y=2.0/x;
      for (i=1; i<n; i++)
      { 
		  p=b0+i*y*b1; b0=b1; b1=p;
	  }
      return(p);
  }
/*
//变型第二类整数阶Bessel函数例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "变型第二类整数阶Bessel函数.cpp"
  using namespace std;
  int main()
  { 
	  int n,i;
      double x,y;
      for (n=0; n<=5; n++)
      { 
		  x=0.05;
          for (i=1; i<=4; i++)
          { 
			  y=b_bessel_2(n,x);
              cout <<"n=" <<n <<"   x=" <<setw(5) <<x 
				   <<"     K(n,x)=" <<y <<endl;
              x=x*10.0;
          }
      }
     return 0;
  }
*/
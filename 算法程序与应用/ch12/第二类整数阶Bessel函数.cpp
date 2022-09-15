//第二类整数阶Bessel函数.cpp
  #include <cmath>
  #include <iostream>
  #include "第一类整数阶Bessel函数.cpp"
  using namespace std;
//n     阶数。要求n>0。
//x     自变量值。
  //函数返回第二类整数阶Bessel函数值。
  double bessel_2(int n, double x)
  { 
	  int i;
      double y,z,p,q,s,b0,b1;
      double a[6]={ -2.957821389e+9,7.062834065e+9,-5.123598036e+8,
		            1.087988129e+7,-8.632792757e+4,2.284622733e+2};
      double b[6]={ 4.0076544269e+10,7.452499648e+8,7.189466438e+6,
		            4.74472647e+4,2.261030244e+2,1.0};
      double c[6]={ -4.900604943e+12,1.27527439e+12,-5.153438139e+10,
		            7.349264551e+8,-4.237922726e+6,8.511937935e+3};
      double d[7]={ 2.49958057e+13,4.244419664e+11,3.733650367e+9,
		            2.245904002e+7,1.02042605e+5,3.549632885e+2,1.0};
      double e[5]={ 1.0,-0.1098628627e-02,0.2734510407e-04,
		            -0.2073370639e-05,0.2093887211e-06};
      double f[5]={ -0.1562499995e-01,0.1430488765e-03,-0.6911147651e-05,
                     0.7621095161e-06,-0.934935152e-07};
      double g[5]={ 1.0,0.183105e-02,-0.3516396496e-04,0.2457520174e-05,
                    -0.240337019e-06};
      double h[5]={ 0.4687499995e-01, -0.2002690873e-03,0.8449199096e-05,
                    -0.88228987e-06,0.105787412e-06};
      if (n<0) n=-n;
      if (x<0.0) x=-x;
      if (x==0.0) return(-1.0e+70);
      if (n!=1)
      { 
		  if (x<8.0)
          { 
			  y=x*x; p=a[5]; q=b[5];
	          for (i=4; i>=0; i--)
              { 
				  p=p*y+a[i]; q=q*y+b[i];
			  }
              p=p/q+0.636619772*bessel_1(0,x)*log(x);
          }
          else
          { 
			  z=8.0/x; y=z*z;
              p=e[4]; q=f[4];
              for (i=3; i>=0; i--)
              { 
				  p=p*y+e[i]; q=q*y+f[i];
			  }
              s=x-0.785398164;
              p=p*sin(s)+z*q*cos(s);
              p=p*sqrt(0.636619772/x);
          }
      }
      if (n==0) return(p);
      b0=p;
      if (x<8.0)
      { 
		  y=x*x; p=c[5]; q=d[6];
          for (i=4; i>=0; i--)
          { 
			  p=p*y+c[i]; q=q*y+d[i+1];
		  }
          q=q*y+d[0];
          p=x*p/q+0.636619772*(bessel_1(1,x)*log(x)-1.0/x);;
      }
      else
      { 
		  z=8.0/x; y=z*z;
          p=g[4]; q=h[4];
          for (i=3; i>=0; i--)
          {
			  p=p*y+g[i]; q=q*y+h[i];
		  }
          s=x-2.356194491;
          p=p*sin(s)+z*q*cos(s);
          p=p*sqrt(0.636619772/x);
      }
      if (n==1) return(p);
      b1=p;
      s=2.0/x;
      for (i=1; i<=n-1; i++)
      { 
		  p=s*i*b1-b0; b0=b1; b1=p;
	  }
      return(p);
  }
/*
//第二类整数阶Bessel函数例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "第二类整数阶Bessel函数.cpp"
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
			  y=bessel_2(n,x);
              cout <<"n=" <<n <<"   x=" <<setw(5) <<x 
			       <<"    Y(n,x)=" <<y <<endl;
              x=x*10.0;
          }
      }
      return 0;
  }
*/
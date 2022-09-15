//方程求根对分法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//a        求根区间的左端点。
//b        求根区间的右端点。
//h        搜索求根所采用的步长。
//eps      控制精度要求。
//x[m]     存放返回的实根。实根个数由函数值返回。
//m        实根个数的预估值。
//f        方程左端函数f(x)的函数名。
  //函数返回搜索到的实根个数。若此值等于m，则有可能没有搜索完。
  int dhrt(double a, double b, double h, double eps, double x[], 
	                                  int m, double (*f)(double))
  { 
	  int n,js;
      double z,y,z1,y1,z0,y0;
	  if (a>b)
	  {
		  z = a; a = b; b = z;
	  }
      n=0; z=a; y=(*f)(z);
      while ((z<=b+h/2.0)&&(n!=m))
      { 
		  if (fabs(y)<eps)
          { 
			  n=n+1; x[n-1]=z;
              z=z+h/2.0; y=(*f)(z);
          }
          else
          { 
			  z1=z+h; y1=(*f)(z1);
              if (fabs(y1)<eps)
              { 
				  n=n+1; x[n-1]=z1;
                  z=z1+h/2.0; y=(*f)(z);
              }
              else if (y*y1>0.0)
              { 
				  y=y1; z=z1;
			  }
              else
              { 
				  js=0;
                  while (js==0)
                  { 
					  if (fabs(z1-z)<eps)
                      { 
						  n=n+1; x[n-1]=(z1+z)/2.0;
                          z=z1+h/2.0; y=(*f)(z);
                          js=1;
                      }
                      else
                      { 
						  z0=(z1+z)/2.0; y0=(*f)(z0);
                          if (fabs(y0)<eps)
                          { 
							  x[n]=z0; n=n+1; js=1;
                              z=z0+h/2.0; y=(*f)(z);
                          }
                          else if ((y*y0)<0.0)
                          { 
							  z1=z0; y1=y0;
						  }
                          else { z=z0; y=y0;}
                      }
                  }
              }
          }
      }
      return(n);
  }
/*
//方程求根对分法例
  #include <cmath>
  #include <iostream>
//  #include "方程求根对分法.cpp"
  using namespace std;
  int main()
  { 
	  int i,n;
      int m=6;
      double x[6];
      double dhrtf(double);
      n=dhrt(-2.0,5.0,0.2,0.000001,x,m,dhrtf);
      cout <<"根的个数 = " <<n <<endl;
      for (i=0; i<=n-1; i++)
          cout <<"x(" <<i <<") = " <<x[i] <<endl;
	  return 0;
  }
//f(x)
  double dhrtf(double x)
  { 
	  double z;
      z=(((((x-5.0)*x+3.0)*x+1.0)*x-7.0)*x+7.0)*x-20.0;
      return(z);
  }
*/
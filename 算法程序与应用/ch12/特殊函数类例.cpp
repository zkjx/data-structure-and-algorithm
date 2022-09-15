//特殊函数类例.cpp
  #include "特殊函数类.h"
  #include <iomanip>
  int main()
  { 
	  int i,j,n,n1,n2;
      double x,y,t,f,k;
	  FUNCTION p;

	  cout <<"Gamma函数例:" <<endl;
      for (i=1; i<=10; i++)
      { 
		  x=0.5*i; y=p.gamma(x);
          cout <<"x = " <<x <<"     gamma(x) = " <<y <<endl;
      }
      y = p.gamma(1.5)*p.gamma(2.5)/p.gamma(4.0);
      cout <<"B(1.5,2.5) = " <<y <<endl;

	  cout <<"不完全Gamma函数例:" <<endl;
      double a[3]={0.5,5.0,50.0};
      double b[3]={0.1,1.0,10.0};
      for (i=0; i<=2; i++)
      for (j=0; j<=2; j++)
      { 
          y = p.ingamma(a[i],b[j]);
		  cout <<"ingamma(" <<a[i] <<", " <<b[j] <<") = " <<y <<endl;
      }

	  cout <<"不完全Beta函数例:" <<endl;
      double a1[5]={ 0.5,0.5,1.0,5.0,8.0};
      double b1[5]={ 0.5,5.0,3.0,0.5,10.0};
      x=0.0;
      for (j=0; j<=5; j++)
      { 
		  cout <<"x=" <<x <<endl;
          for (i=0; i<=4; i++)
          { 
              y=p.inbeta(a1[i],b1[i],x);
              cout <<"      B(" <<a1[i] <<", " <<b1[i] <<")=" <<y <<endl;
          }
          x=x+0.2;
      }

	  cout <<"误差函数例:" <<endl;
	  x = 0.0;  y = p.errf(x);
	  cout <<setw(15) <<y <<endl;
      for (i=0; i<=7; i++)
      { 
		  for (j=0; j<=4; j++)
          { 
			  x = x + 0.05;   y=p.errf(x);
              cout <<setw(15) <<y;
          }
          cout <<endl;
      }

	  cout <<"第一类整数阶Bessel函数例:" <<endl;
      for (n=0; n<=5; n++)
      { 
		  x=0.05;
          for (i=1; i<=4; i++)
          { 
			  y=p.bessel_1(n,x);
			  cout <<"n=" <<n <<"   x=" <<setw(5) <<x 
			       <<"    J(n, x)=" <<y <<endl;
              x=x*10.0;
          }
      }

	  cout <<"第二类整数阶Bessel函数例:" <<endl;
      for (n=0; n<=5; n++)
      { 
		  x=0.05;
          for (i=1; i<=4; i++)
          { 
			  y=p.bessel_2(n,x);
              cout <<"n=" <<n <<"   x=" <<setw(5) <<x 
			       <<"    Y(n,x)=" <<y <<endl;
              x=x*10.0;
          }
      }

	  cout <<"变型第一类整数阶Bessel函数例:" <<endl;
      for (n=0; n<=5; n++)
      { 
		  x=0.05;
          for (i=1; i<=4; i++)
          { 
			  y=p.b_bessel_1(n,x);
              cout <<"n=" <<n <<"   x=" <<setw(5) <<x 
				   <<"    I(n,x)=" <<y <<endl;
              x=x*10.0;
          }
      }

	  cout <<"变型第二类整数阶Bessel函数例:" <<endl;
      for (n=0; n<=5; n++)
      { 
		  x=0.05;
          for (i=1; i<=4; i++)
          { 
			  y=p.b_bessel_2(n,x);
              cout <<"n=" <<n <<"   x=" <<setw(5) <<x 
				   <<"     K(n,x)=" <<y <<endl;
              x=x*10.0;
          }
      }

	  cout <<"正态分布函数例:" <<endl;
      double a2[2]={ -1.0,3.0};
      double d[2]={ 0.5,15.0};
      for (i=0; i<=1; i++)
      { 
		  x=-10.0;
          for (j=0; j<=4; j++)
          { 
			  y=p.gass(a2[i],d[i],x);
              cout <<"P(" <<a2[i] <<", " <<d[i] <<", " <<x <<")=" <<y <<endl;
              x=x+5.0;
          }
      }

	  cout <<"t_分布函数例:" <<endl;
      for (n=1; n<=5; n++)
      { 
		  t=0.5; y=p.student(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
          t=5.0; y=p.student(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
      }

	  cout <<"X平方分布函数例:" <<endl;
      for (n=1; n<=5; n++)
      { 
		  t=0.5; y=p.chii(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
          t=5.0; y=p.chii(t,n);
          cout <<"P(" <<t <<", " <<n <<")=" <<y <<endl;
      }

	  cout <<"F_分布函数例:" <<endl; 
	  n1=2; n2=3; 
	  f=3.5; y=p.ffff(f,n1,n2);
      cout <<"P(" <<f <<", " <<n1 <<", " <<n2 <<")=" <<y <<endl;
      f=9.0; y=p.ffff(f,n1,n2);
      cout <<"P(" <<f <<", " <<n1 <<", " <<n2 <<")=" <<y <<endl;
	  n1=5; n2=10; 
	  f=3.5; y=p.ffff(f,n1,n2);
      cout <<"P(" <<f <<", " <<n1 <<", " <<n2 <<")=" <<y <<endl;
      f=9.0; y=p.ffff(f,n1,n2);
      cout <<"P(" <<f <<", " <<n1 <<", " <<n2 <<")=" <<y <<endl;

	  cout <<"正弦积分例:" <<endl;
      for (i=0; i<=9; i++)
      { 
		  x=0.5+i+i; y=p.sinn(x);
          cout <<"x=" <<x <<"    Si(x)=" <<y <<endl;
      }

	  cout <<"余弦积分例:" <<endl;
      for (i=0; i<=9; i++)
      { 
		  x=0.5+i+i; y=p.coss(x);
          cout <<"x=" <<x <<"    Ci(x)=" <<y <<endl;
      }

	  cout <<"指数积分例:" <<endl;
      for (i=0; i<=9; i++)
      { 
		  x=0.05+0.2*i; y=p.expp(x);
          cout <<"x=" <<x <<"    Ei(x)=" <<y <<endl;
      }

	  cout <<"第一类椭圆积分例:" <<endl;
      for (i=0; i<=10; i++)
      { 
		  f=i*3.1415926/18.0;
          k=0.5; y=p.elp1(k,f);
          cout <<"F(" <<k <<", " <<setw(9) <<f <<")=" <<y;
          k=1.0; y=p.elp1(k,f);
          cout <<"       F(" <<k <<", " <<setw(9) <<f <<")=" <<y <<endl;
      }

	  cout <<"第二类椭圆积分例:" <<endl;
      for (i=0; i<=10; i++)
      { 
		  f=i*3.1415926/18.0;
          k=0.5; y=p.elp2(k,f);
          cout <<"F(" <<k <<", " <<setw(9) <<f <<")=" <<y;
          k=1.0; y=p.elp2(k,f);
          cout <<"       F(" <<k <<", " <<setw(9) <<f <<")=" <<y <<endl;
      }

      return 0;
  }

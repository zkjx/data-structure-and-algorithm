//Gamma函数.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//x     自变量值。要求x>0。
  //函数返回Gamma函数值。
  double gamma(double x)
  { 
	  int i;
      double y,t,s,u;
      double a[11]={ 0.0000677106,-0.0003442342,
           0.0015397681,-0.0024467480,0.0109736958,
           -0.0002109075,0.0742379071,0.0815782188,
           0.4118402518,0.4227843370,1.0};
      if (x<=0.0)
      { 
		  cout <<"err**x<=0!\n";
		  return(-1.0);
	  }
      y=x;
      if (y<=1.0) {  t=1.0/(y*(y+1.0)); y=y+2.0;}
      else if (y<=2.0) {  t=1.0/y; y=y+1.0; }
      else if (y<=3.0) t=1.0;
      else
      { 
		  t=1.0;
          while (y>3.0) { y=y-1.0; t=t*y;}
      }
      s=a[0]; u=y-2.0;
      for (i=1; i<=10; i++)  s=s*u+a[i];
      s=s*t;
      return(s);
  }
/*
//Gamma函数例
  #include <cmath>
  #include <iostream>
//  #include "Gamma函数.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double x,y;
      for (i=1; i<=10; i++)
      { 
		  x=0.5*i; y=gamma(x);
          cout <<"x = " <<x <<"     gamma(x) = " <<y <<endl;
      }
      y = gamma(1.5)*gamma(2.5)/gamma(4.0);
      cout <<"B(1.5,2.5) = " <<y <<endl;
      return 0;
  }
*/

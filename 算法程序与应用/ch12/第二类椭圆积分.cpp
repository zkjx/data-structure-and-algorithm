//第二类椭圆积分.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//k      要求0=<k<=1。
//f      参数。
  //函数返回第二类椭圆积分值。
  double elp2(double k, double f)
  { 
	  int n;
      double pi,y,e,ff;
      double ek(double,double);
      if (k<0.0) k=-k;
      if (k>1.0) k=1.0/k;
      pi=3.1415926; y=fabs(f);
      n=0;
      while (y>=pi) { n=n+1; y=y-pi;}
      e=1.0;
      if (y>=pi/2.0) { n=n+1; e=-e; y=pi-y;}
      if (n==0) ff=ek(k,y);
      else
      { 
		  ff=ek(k,pi/2.0);
          ff=2.0*n*ff+e*ek(k,y);
      }
      if (f<0.0) ff=-ff;
      return(ff);
  }

  double ek(double k, double f)
  { 
	  int m,i,j;
      double s,p,ep,h,aa,bb,w,xx,g,q;
      double t[5]={-0.9061798459,-0.5384693101,0.0,
                         0.5384693101,0.9061798459};
      double c[5]={0.2369268851,0.4786286705,0.5688888889,
                        0.4786286705,0.2369268851};
      m=1; g=0.0;
      h=fabs(f); s=fabs(0.0001*h);
      p=1.0e+35; ep=0.000001;
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
                  q=sqrt(1.0-k*k*sin(xx)*sin(xx));
                  w=w+q*c[j];
              }
              g=g+w;
          }
          g=g*h/2.0;
          ep=fabs(g-p)/(1.0+fabs(g));
          p=g; m=m+m; h=0.5*h;
      }
      return(g);
  }
/*
//第二类椭圆积分例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "第二类椭圆积分.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double f,k,y;
      for (i=0; i<=10; i++)
      { 
		  f=i*3.1415926/18.0;
          k=0.5; y=elp2(k,f);
          cout <<"E(" <<k <<", " <<setw(9) <<f <<")=" <<y;
          k=1.0; y=elp2(k,f);
          cout <<"       E(" <<k <<", " <<setw(9) <<f <<")=" <<y <<endl;
      }
      return 0;
  }
*/
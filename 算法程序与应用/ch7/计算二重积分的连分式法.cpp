//计算二重积分的连分式法.cpp
  #include <cmath>
  #include <iostream>
  #include "计算函数连分式新一节.cpp"
  #include "计算函数连分式值.cpp"
  using namespace std;
  //固定一个x，用连分式法计算一个对y的积分近似值。
  double pqg1(double x, double eps, 
	          void (*s)(double ,double []), double (*f)(double,double))
  { 
	  int m,n,k,j,flag;
	  double h[10],g[10],b[10],h0,g0,y[2],s0,s1,d,yy;
      m=0; n=1; 
	  (*s)(x,y);                   //计算上下限y[1]与y[0]
	  h0 = y[1]-y[0];  flag=0;
	  g0=h0*((*f)(x,y[0])+(*f)(x,y[1]))/2.0;       //梯形公式计算初值
      while ((m<10)&&(flag==0))
      { 
		  m=m+1; 
		  h[0]=h0; g[0]=g0;
		  b[0]=g[0];                            //计算b[0]
          j=1; s1=g[0];
          while (j<=7)
          { 
			  d=0.0;
			  for (k=0; k<=n-1; k++)
			  {
				  yy=y[0]+(k+0.5)*h[j-1];
				  d=d+(*f)(x,yy);
			  }
			  g[j]=(g[j-1]+h[j-1]*d)/2.0;         //变步长梯形求积法计算新近似值g[j]
			  h[j]=h[j-1]/2.0; n=2*n;
			  funpqj(h,g,b,j);                  //计算b[j]
			  s0=s1;
			  s1=funpqv(h,b,j,0.0);             //连分式法计算积分近似值s1
              if (fabs(s1-s0)>=eps)  j=j+1;
			  else  j=10; 
          }
		  h0=h[j-1]; g0=g[j-1];
          if (j==10) flag=1;
       }
       return(s1);
  }
//a          积分下限。
//b          积分上限。要求b>a。
//eps        积分精度要求。
//s          计算上下限的函数名。
//f          计算被积函数值f(x,y)的函数名。
  //函数返回积分值。
  double pqg2(double a, double b, double eps, 
	          void (*s)(double ,double []), double (*f)(double,double))
  { 
	  int k,j,m,flag,n;
	  double h[10],g[10],bb[10],h0,g0,d,s0,s1,x;
      m=0; n=1; 
	  h0 = b - a;  flag=0;
      s0=pqg1(a,eps,s,f);           //固定 x = a
	  s1=pqg1(b,eps,s,f);           //固定 x = b
      g0=h0*(s1+s0)/2.0;           //梯形公式计算初值
      while ((m<10)&&(flag==0))
      { 
		  m=m+1; 
		  h[0]=h0; g[0]=g0;
		  bb[0]=g[0];                            //计算b[0]
          j=1; s1=g[0];
          while (j<=7)
          { 
			  d=0.0;
			  for (k=0; k<=n-1; k++)
			  {
				  x = a + (k+0.5)*h[j-1];    //固定一个x
				  d = d + pqg1(x,eps,s,f);
			  }
			  g[j]=(g[j-1]+h[j-1]*d)/2.0;         //变步长梯形求积法计算新近似值g[j]
			  h[j]=h[j-1]/2.0; n=2*n;
			  funpqj(h,g,bb,j);                  //计算b[j]
			  s0=s1;
			  s1=funpqv(h,bb,j,0.0);             //连分式法计算积分近似值s1
              if (fabs(s1-s0)>=eps)  j=j+1;
			  else  j=10; 
          }
		  h0=h[j-1]; g0=g[j-1];
          if (j==10) flag=1;
       }
       return(s1);
  }
/*
//计算二重积分的连分式法例
  #include <cmath>
  #include <iostream>
//  #include "计算二重积分的连分式法.cpp"
  using namespace std;
  int main()
  { 
	  double a,b,eps,s,pqg2f(double,double);
      void  pqg2s(double,double []);
      a=0.0; b=1.0; eps=0.00001;
      s=pqg2(a,b,eps,pqg2s,pqg2f);
      cout <<"s = " <<s <<endl;
      return 0;
  }
//计算上下限y1(x)与y0(x)
  void pqg2s(double x, double y[2])
  { 
	  y[1]=sqrt(1.0-x*x);
      y[0]=-y[1];
      return;
  }
//计算被积函数值f(x,y)
  double pqg2f(double x, double y)
  { 
	  double z;
      z=exp(x*x+y*y);
      return(z);
  }
*/
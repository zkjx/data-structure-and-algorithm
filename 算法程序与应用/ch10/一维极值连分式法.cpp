//一维极值连分式法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//x       存放极值点初值。返回极值点。
//eps     控制精度要求。
//f       计算目标函数f(x)值的函数名。
//df      计算目标函数一阶导数值的函数名。
  //函数返回标志值。若>0为极大值点；若<0为极小值点;若=0则不是极值点。
  int max1(double *x, double eps, double (*f)(double), double (*df)(double))
  { 
	  int i,j,m,jt,flag,k;
      double xx,h,h1,h2,dx,y[10],b[10],z;
	  flag = 20;           //最大迭代次数
      k = 0; jt=1; h2=0.0;
      while (jt==1)
      { 
		  j=0;
          while (j<=7)
          { 
			  if (j<=2) xx = *x+0.01*j;
              else xx=h2;
              z = (*df)(xx);
              if (fabs(z)<eps)  { jt=0; j=10;}
              else
              {
				  h1 = z; h2=xx;
                  if (j==0) { y[0]=h1; b[0]=h2;}
                  else
                  { 
					  y[j]=h1; m=0; i=0;
                      while ((m==0)&&(i<=j-1))
					  { 
						  if (fabs(h2-b[i])+1.0==1.0) m=1;
			              else h2=(h1-y[i])/(h2-b[i]);
                          i=i+1;
					  }
                      b[j]=h2;
                      if (m!=0) b[j]=1.0e+35;
                      h2=0.0;
                      for (i=j-1; i>=0; i--) h2=-y[i]/(b[i+1]+h2);
                      h2=h2+b[0];
                  }
                  j=j+1;
              }
          }
          *x = h2;
          k = k + 1;
          if (k == flag)  jt=0;
      }
      xx = *x;
	  h = (*f)(xx);
      if (fabs(xx)<=1.0) dx=1.0e-05;
      else dx=fabs(xx*1.0e-05);
      xx = *x-dx;
      h1 = (*f)(xx); 
      xx = *x+dx;
      h2 = (*f)(xx);
      if ((h1+h2-2.0*h)>0.0) k = -1;
	  else if ((h1+h2-2.0*h)<0.0) k = 1;
	  else k = 0;
      return(k);
  }
/*
//一维极值连分式法例
  #include <cmath>
  #include <iostream>
  using namespace std;
//  #include "一维极值连分式法.cpp"
  int main()
  { 
	  int k;
      double max1f(double), max1df(double);
      double eps, x;
      eps = 1.0e-10; x = 1.0;
      k = max1(&x,eps,max1f,max1df);
      cout <<"点 x = " <<x;
      if (k<0) cout <<"  为极小值点" <<endl;
      else if (k>0) cout <<"  为极大值点" <<endl;
	  else cout <<"  不是极值点" <<endl;
      cout <<"极值  f(x) = " <<max1f(x) <<endl;
      return 0;
  }
//计算目标函数值
  double max1f(double x)
  { 
	  double  y;
	  y = (x-1.0)*(10.0-x);
      return(y);
  }
//计算目标函数导数值
  double max1df(double x)
  { 
	  double y;
      y = -2.0*x+11.0;
      return(y);
  }
*/
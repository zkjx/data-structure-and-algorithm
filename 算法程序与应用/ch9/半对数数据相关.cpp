//半对数数据相关.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//n            数据点数。
//x[n],y[n]    存放n个数据点。
//t            指数函数的底。要求t>0。
//a[2]         a[0]返回指数函数前的系数b;a[1]返回指数函数指数中的系数a。
//dt[5]        dt[0]偏差平方和。
//             dt[1]返回平均标准偏差。
//             dt[2]返回最大偏差。
//             dt[3]返回最小偏差。
//             dt[4]返回偏差平均值。
  void log1(int n, double x[], double y[], double t, double a[2], double dt[5])
  { 
	  int i;
      double xx,yy,dx,dxy;
      xx=0.0; yy=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  xx=xx+x[i]/n; 
          yy=yy+log(y[i])/log(t)/n;
      }
      dx=0.0; dxy=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  a[2]=x[i]-xx; dx=dx+a[2]*a[2];
          dxy=dxy+a[2]*(log(y[i])/log(t)-yy);
      }
      a[1]=dxy/dx; a[0]=yy-a[1]*xx;
      a[0]=a[0]*log(t); a[0]=exp(a[0]);
      dt[0]=0.0; dt[4]=0.0; dt[2]=0.0; dt[3]=1.0e+30;
      for (i=0; i<=n-1; i++)
      { 
		  dt[1]=a[1]*x[i]*log(t); dt[1]=a[0]*exp(dt[1]);
          dt[0]=dt[0]+(y[i]-dt[1])*(y[i]-dt[1]);
          dx=fabs(y[i]-dt[1]);
          if (dx>dt[2]) dt[2]=dx;
          if (dx<dt[3]) dt[3]=dx;
          dt[4]=dt[4]+dx/n;
      }
      dt[1]=sqrt(dt[0]/n);
      return;
  }
/*
//半对数数据相关例
  #include <iostream>
  #include <cmath>
//  #include "半对数数据相关.cpp"
  using namespace std;
  int main()
  { 
	  int n;
      double t,a[2],dt[5];
      double x[12]={0.96,0.94,0.92,0.90,0.88,
               0.86,0.84,0.82,0.80,0.78,0.76,0.74};
      double y[12]={558.0,313.0,174.0,97.0,55.8,
                  31.3,17.4,9.70,5.58,3.13,1.74,1.00};
      t=10.0; n=12;
      log1(n,x,y,t,a,dt);
      cout <<"拟合系数 :" <<endl;
      cout <<"a = " <<a[1] <<"   b = " <<a[0] <<endl;
      cout <<"偏差平方和 = " <<dt[0] <<endl;
	  cout <<"平均标准偏差 = " <<dt[1] <<endl;
	  cout <<"最大偏差 = " <<dt[2] <<endl;
	  cout <<"最小偏差 = " <<dt[3] <<endl;
	  cout <<"偏差平均值 = " <<dt[4] <<endl;
      return 0;
  }
*/
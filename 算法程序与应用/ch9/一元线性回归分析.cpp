//一元线性回归分析.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//n            观测点数。
//x[n],y[n]    分别存放n个观测点的自变量值与观测值。
//a[2]         返回回归系数。a[1]为一次项系数，a[0]为常数项。
//dt[6]        dt[0]返回偏差平方和
//             dt[1]返回平均标准偏差；
//             dt[2]返回回归平方和；
//             dt[3]返回最大偏差；
//             dt[4]返回最小偏差；
//             dt[5]返回偏差平均值。
  void sqt1(int n, double x[], double y[], double a[2], double dt[6])
  { 
	  int i;
      double xx,yy,e,f,q,u,p,umax,umin,s;
      xx=0.0; yy=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  xx=xx+x[i]/n; yy=yy+y[i]/n;
	  }
      e=0.0; f=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  q=x[i]-xx; e=e+q*q;
          f=f+q*(y[i]-yy);
      }
      a[1]=f/e; a[0]=yy-a[1]*xx;
      q=0.0; u=0.0; p=0.0;
      umax=0.0; umin=1.0e+30;
      for (i=0; i<=n-1; i++)
      { 
		  s=a[1]*x[i]+a[0];
          q=q+(y[i]-s)*(y[i]-s);
          p=p+(s-yy)*(s-yy);
          e=fabs(y[i]-s);
          if (e>umax) umax=e;
          if (e<umin) umin=e;
          u=u+e/n;
      }
      dt[1]=sqrt(q/n);
      dt[0]=q; dt[2]=p;
      dt[3]=umax; dt[4]=umin; dt[5]=u;
      return;
  }
/*
//一元线性回归分析例
  #include <iostream>
  #include <cmath>
//  #include "一元线性回归分析.cpp"
  using namespace std;
  int main()
  { 
    
	  double dt[6],a[2];
      double x[11]={ 0.0,0.1,0.2,0.3,0.4,0.5,
                          0.6,0.7,0.8,0.9,1.0};
      double y[11]={ 2.75,2.84,2.965,3.01,3.20,
                        3.25,3.38,3.43,3.55,3.66,3.74};
      sqt1(11,x,y,a,dt);
      cout <<"回归系数 :  " <<"a = " <<a[1] <<"    b = " <<a[0] <<endl;
      cout <<"偏差平方和 = " <<dt[0] <<endl;
	  cout <<"平均标准偏差 = " <<dt[1] <<endl;
	  cout <<"回归平方和 = " <<dt[2] <<endl;
	  cout <<"最大偏差 = " <<dt[3] <<endl;
	  cout <<"最小偏差 = " <<dt[4] <<endl;
	  cout <<"偏差平均值 = " <<dt[5] <<endl;
      return 0;
  }
*/
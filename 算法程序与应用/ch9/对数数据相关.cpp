//对数数据相关.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//n            数据点数。
//x[n],y[n]    存放n个数据点。x,y>0。
//a[2]         a[0]返回幂函数前的系数b;a[1]返回幂函数中的指数a。
//dt[5]        dt[0]偏差平方和。
//             dt[1]返回平均标准偏差。
//             dt[2]返回最大偏差。
//             dt[3]返回最小偏差。
//             dt[4]返回偏差平均值。
  void log2(int n, double x[], double y[], double a[2], double dt[5])
  { 
	  int i;
      double xx,yy,dx,dxy;
      xx=0.0; yy=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  xx=xx+log(x[i])/n; 
          yy=yy+log(y[i])/n;
      }
      dx=0.0; dxy=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  dt[0]=log(x[i])-xx; dx=dx+dt[0]*dt[0];
          dxy=dxy+dt[0]*(log(y[i])-yy);
      }
      a[1]=dxy/dx; a[0]=yy-a[1]*xx;
      a[0]=exp(a[0]);
      dt[0]=0.0; dt[4]=0.0; dt[2]=0.0; dt[3]=1.0e+30;
      for (i=0; i<=n-1; i++)
      { 
		  dt[1]=a[1]*log(x[i]); dt[1]=a[0]*exp(dt[1]);
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
//对数数据相关例
  #include <iostream>
  #include <cmath>
//  #include "对数数据相关.cpp"
  using namespace std;
  main()
  { 
	  int n;
      double a[2],dt[5];
      double x[10]={0.1,1.0,3.0,5.0,8.0,10.0,
                             20.0,50.0,80.0,100.0};
      double y[10]={0.1,0.9,2.5,4.0,6.3,7.8,
                              14.8,36.0,54.0,67.0};
      n=10;
      log2(n,x,y,a,dt);
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
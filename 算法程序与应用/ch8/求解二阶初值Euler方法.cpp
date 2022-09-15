//求解二阶初值Euler方法.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
  //改进欧拉公式以h为步长积分m步
  //t    自变量起点值
  //h    步长
  //y    存放函数初值。返回终点函数值。
  //z    存放函数一阶导数初值。返回终点函数一阶导数值。
  //m    步数
  //f    二阶微分方程右端函数f(t,y,z)。
  void euler21(double t,double h,double *y,double *z,int m,
	         double (*f)(double,double,double))
  { 
	  int j;
      double x,yy,zz,yc,zc,yk1,yk2,zk1,zk2;
	  yy=*y; zz=*z;
      for (j=0; j<=m-1; j++)
      {
		  x=t+j*h;
          yk1=zz;               //计算yK1
		  zk1=(*f)(x,yy,zz);    //计算zK1
		  x=t+(j+1)*h;
		  yc=yy+h*zk1;         //预报t[j+1]处的y值
		  zc=zz+h*yk1;         //预报t[j+1]处的z值
		  yk2=zc;             //计算yK2
		  zk2=(*f)(x,yc,zc);  //计算zk2
          yy=yy+h*(yk1+yk2)/2.0;         //计算t[j+1]处的y值
		  zz=zz+h*(zk1+zk2)/2.0;         //计算t[j+1]处的z值
      }
	  *y=yy; *z=zz;
      return;
  }

  //Euler方法变步长积分一步二阶初值问题
  //t      自变量起点值
  //h      步长
  //y      存放函数初值。返回终点函数值。
  //z      存放函数一阶导数初值。返回终点函数一阶导数值。
  //eps    精度要求
  //f      二阶微分方程右端函数f(t,y,z)。
  void euler2(double t, double h, double *y, double *z, double eps,
             double (*f)(double, double , double ))
  { 
	  int m;
      double p,ya,za,yb,zb;
      m=1;
	  p=1.0+eps;
      ya=*y;  za=*z;
	  euler21(t,h,&ya,&za,m,f);          //跨一步计算
      while (p>eps)
      { 
		  yb=*y;  zb=*z; m=m+m; h=h/2.0;
          euler21(t,h,&yb,&zb,m,f);       //跨m步计算
          p=fabs(yb-ya);                 //取误差
          za=zb;  ya=yb;
      }
	  *y=ya;  *z=za;
      return;
  }

/*
//求解二阶初值Euler方法例1
  #include <iostream>
  #include <iomanip>
//  #include "求解二阶初值Euler方法.cpp"
  using namespace std;
  int main()
  { 
	  int j;
      double t,h,eps,y,z;
      double  euler2_f(double, double, double);
      y=0.0; z=0.701836;
      t=0.0; h=0.1; eps=0.0000001;
      cout <<"t = " <<setw(6) <<t;
      cout <<setw(6) <<"y = " <<setw(10) <<y;
      cout <<setw(6) <<"z = " <<setw(10) <<z;
      cout <<endl;
      for (j=1; j<=10; j++)
      { 
		  euler2(t,h,&y,&z,eps,euler2_f);
          t=t+h;
		  cout <<"t = " <<setw(6) <<t;
          cout <<setw(6) <<"y = " <<setw(10) <<y;
		  cout <<setw(6) <<"z = " <<setw(10) <<z;
          cout <<endl;
      }
	  return 0;
  }
//计算二阶微分方程右端函数f(t,y,z)
  double euler2_f(double t, double y, double z)
  { 
	  double d;
      d=t+y;
      return(d);
  }
*/
/*
//求解二阶初值Euler方法例2
  #include <iostream>
  #include <iomanip>
//  #include "求解二阶初值Euler方法.cpp"
  using namespace std;
  int main()
  { 
	  int j;
      double t,h,eps,y,z;
      double  euler2_f(double, double, double);
	  y=1.0; z=0.0;
      t=0.0; h=0.1; eps=0.0000001;
      cout <<"t = " <<setw(6) <<t;
      cout <<setw(6) <<"y = " <<setw(10) <<y;
      cout <<setw(6) <<"z = " <<setw(10) <<z;
      cout <<endl;
      for (j=1; j<=10; j++)
      { 
		  euler2(t,h,&y,&z,eps,euler2_f);
          t=t+h;
		  cout <<"t = " <<setw(6) <<t;
          cout <<setw(6) <<"y = " <<setw(10) <<y;
		  cout <<setw(6) <<"z = " <<setw(10) <<z;
          cout <<endl;
      }
	  return 0;
  }
//计算二阶微分方程右端函数f(t,y,z)
  double euler2_f(double t, double y, double z)
  { 
	  double d;
      d = (6*t-3.0+t*z+3*y)/(1.0+t*t);
      return(d);
  }
*/
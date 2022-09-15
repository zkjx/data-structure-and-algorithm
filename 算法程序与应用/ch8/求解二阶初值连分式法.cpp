//求解二阶初值连分式法.cpp
  #include <iostream>
  #include <cmath>
  #include "计算函数连分式新一节.cpp"
  #include "计算函数连分式值.cpp"
  using namespace std;
  //改进欧拉公式以h为步长积分m步
  //t    自变量起点值
  //h    步长
  //y    存放函数初值。返回终点函数值。
  //z    存放函数一阶导数初值。返回终点函数一阶导数值。
  //m    步数
  //f    计算二阶微分方程的右端函数f(t,y,z)。
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

  //连分式法求解二阶初值
  //t    自变量起点值
  //h    步长
  //y    存放函数初值。返回终点函数值。
  //z    存放函数一阶导数初值。返回终点函数一阶导数值。
  //eps  精度要求
  //f    计算二阶微分方程的右端函数f(t,y,z)。
  using namespace std;
  void pqeuler2(double t,double h,double *y,double *z,double eps,
	           double (*f)(double,double,double))
  {
	  int j,il,flag,m;
	  double yy,zz,*hh,*gy,*gz,*yb,*zb,h0,d,ys0,ys1,zs,y0,z0;
	  yb=new double[10];
	  zb=new double[10];
	  hh=new double[10];
	  gy=new double[10];
	  gz=new double[10];
      yy=*y; zz=*z; 
	  il=0; flag=0;
	  m=1; h0=h;
      euler21(t,h0,&yy,&zz,m,f);      //Euler方法计算初值gy[0]与gz[0]
      y0=yy;  z0=zz;
	  while ((il<20)&&(flag==0))
      { 
		  il=il+1; 
		  hh[0]=h0;
		  gy[0]=y0;  gz[0]=z0;
		  yb[0]=gy[0];  zb[0]=gz[0];      //计算yb[0]与zb[0]
          j=1; 
		  ys1=gy[0]; 
		  while (j<=7)
          { 
			  yy=*y;  zz=*z;
			  m=m+m; hh[j]=hh[j-1]/2.0;
              euler21(t,hh[j],&yy,&zz,m,f); //Euler方法计算新近似值gy[j]与gz[j]
	          gy[j]=yy;  gz[j]=zz;
			  funpqj(hh,gy,yb,j);       //计算yb[j]
			  funpqj(hh,gz,zb,j);       //计算zb[j]
			  ys0=ys1; 
			  ys1=funpqv(hh,yb,j,0.0);  //连分式法计算积分近似值ys1
              zs=funpqv(hh,zb,j,0.0);   //连分式法计算积分近似值zs
			  d=fabs(ys1-ys0);
			  if (d>=eps)  j=j+1;
			  else  j=10;
          }
		  h0=hh[j-1]; 
		  y0=gy[j-1]; z0=gz[j-1];
          if (j==10) flag=1;
       }
	    *y=ys1;  *z=zs;
	   delete[] yb; delete[] zb; delete[] hh; delete[] gy; delete[]gz;
       return;
  }
/*
//求解二阶初值连分式法例
  #include <iostream>
  #include <iomanip>
//  #include "求解二阶初值连分式法.cpp"
  using namespace std;
  int main()
  {
	  int j;
      double t,h,eps,y,z;
      double  pqeuler2f(double, double, double);
      y=0.0; z=0.701836;
      t=0.0; h=0.1; eps=0.0000001;
      cout <<"t = " <<setw(6) <<t;
      cout <<setw(6) <<"y = " <<setw(10) <<y;
      cout <<setw(6) <<"z = " <<setw(10) <<z;
      cout <<endl;
      for (j=1; j<=10; j++)
      { 
		  pqeuler2(t,h,&y,&z,eps,pqeuler2f);
          t=t+h;
		  cout <<"t = " <<setw(6) <<t;
          cout <<setw(6) <<"y = " <<setw(10) <<y;
		  cout <<setw(6) <<"z = " <<setw(10) <<z;
          cout <<endl;
      }	  
	  return 0;
  }
//计算二阶微分方程的右端函数f(t,y,z)
  double pqeuler2f(double t, double y, double z)
  { 
	  double d;
      d=t+y;
      return(d);
  }
*/
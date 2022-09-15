//多元线性回归分析.cpp
  #include <iostream>
  #include <cmath>
  #include "对称正定方程组的平方根法.cpp"
  using namespace std;
//m         自变量个数。
//n         观测数据的组数。
//x[m][n]   每一列存放m个自变量的规测值。
//y[n]      存放随机变量y的n个规测值。
//a[m+1]    返回回归系数。
//dt[4]     分别返回偏差平方和、平均标准偏差、复相关系数与回归平方和。
//v[m]      返回m个自变量的偏相关系数。
  void sqt2(int m, int n, double x[], double y[], 
	        double a[], double dt[4], double v[])
  { 
	  int i,j,k,mm;
      double q,e,u,p,yy,s,r,pp,*b;
      b=new double[(m+1)*(m+1)];
      mm=m+1;
      b[mm*mm-1]=n;
      for (j=0; j<=m-1; j++)
      { 
		  p=0.0;
          for (i=0; i<=n-1; i++)  p=p+x[j*n+i];
          b[m*mm+j]=p;
          b[j*mm+m]=p;
      }
      for (i=0; i<=m-1; i++)
      for (j=i; j<=m-1; j++)
      { 
		  p=0.0;
          for (k=0; k<=n-1; k++)  p=p+x[i*n+k]*x[j*n+k];
          b[j*mm+i]=p;
          b[i*mm+j]=p;
      }
      a[m]=0.0;
      for (i=0; i<=n-1; i++)  a[m]=a[m]+y[i];
      for (i=0; i<=m-1; i++)
      { 
		  a[i]=0.0;
          for (j=0; j<=n-1; j++) a[i]=a[i]+x[i*n+j]*y[j];
      }
      chlk(b,mm,1,a);    //求解回归系数
      yy=0.0;
      for (i=0; i<=n-1; i++)  yy=yy+y[i]/n;
      q=0.0; e=0.0; u=0.0;
      for (i=0; i<=n-1; i++)
      { 
		  p=a[m];
          for (j=0; j<=m-1; j++)  p=p+a[j]*x[j*n+i];
          q=q+(y[i]-p)*(y[i]-p);     //偏差平方和
          e=e+(y[i]-yy)*(y[i]-yy);
          u=u+(yy-p)*(yy-p);
      }
      s=sqrt(q/n);      //平均标准偏差
      r=sqrt(1.0-q/e);  //复相关系数
      for (j=0; j<=m-1; j++)
      { 
		  p=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  pp=a[m];
              for (k=0; k<=m-1; k++)
                if (k!=j) pp=pp+a[k]*x[k*n+i];
              p=p+(y[i]-pp)*(y[i]-pp);
          }
          v[j]=sqrt(1.0-q/p);    //各自变量的偏相关系数
      }
      dt[0]=q; dt[1]=s; dt[2]=r; dt[3]=u;
      delete[] b; return;
  }
/*
//多元线性回归分析例
  #include <iostream>
  #include <cmath>
//  #include "多元线性回归分析.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double a[4],v[3],dt[4];
      double x[3][5]={ {1.1,1.0,1.2,1.1,0.9},
         {2.0,2.0,1.8,1.9,2.1},{3.2,3.2,3.0,2.9,2.9}};
      double y[5]={10.1,10.2,10.0,10.1,10.0};
      sqt2(3,5,&x[0][0],y,a,dt,v);
	  cout <<"回归系数 :" <<endl;
      for (i=0; i<=3; i++)  cout <<"a[" <<i <<"] = " <<a[i] <<endl;
      cout <<"偏差平方和 = " <<dt[0] <<endl;
	  cout <<"平均标准偏差 = " <<dt[1] <<endl;
	  cout <<"复相关系数 = " <<dt[2] <<endl;
	  cout <<"回归平方和 = " <<dt[3] <<endl;
      cout <<"偏相关系数 :" <<endl;
      for (i=0; i<=2; i++)  cout <<"v[" <<i <<"] = " <<v[i] <<endl;
      return 0;
  }
*/
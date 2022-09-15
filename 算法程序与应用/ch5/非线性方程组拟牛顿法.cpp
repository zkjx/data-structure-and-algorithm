//非线性方程组拟牛顿法.cpp
  #include <iostream>
  #include <cmath>
  #include "gauss消去法.cpp"
  using namespace std;
//n        非方程组阶数。
//eps      控制精度要求。
//h        增量初值,h>0。返回时将被破坏。
//x[n]     存放初值。返回方程组实数解。
//f        计算方程组各方程左端函数值的函数名。
  //函数返回实际迭代次数。若<0则表示因AZ=B奇异或beta=0而失败。本函数最大迭代次数为1000。
  int netn(int n, double eps, double h, double x[], 
	                       void (*f)(double x[],double y[],int n))
  { 
	  int i,j,k,interation;
      double t,ep,z,beta,d,*y,*a,*b;
	  interation = 1000;             //最大迭代次数
	  t = 0.1;                       //控制h大小
      y = new double[n];
      a = new double[n*n];
      b = new double[n];
      k = 0; ep=1.0+eps;
      while (ep>=eps)
      { 
		  (*f)(x,b,n);
          ep=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  z=fabs(b[i]);
              if (z>ep) ep=z;
          }
          if (ep>=eps)
          { 
			  k = k + 1;
              if (k==interation)       //达到最大迭代次数未收敛
              { 
				  delete[] y; delete[] b; delete[] a; return(k);
              }
              for (j=0; j<=n-1; j++)
              { 
				  z=x[j]; x[j]=x[j]+h;
                  (*f)(x,y,n);
                  for (i=0; i<=n-1; i++) a[i*n+j]=y[i];
                  x[j]=z;
              }
              if (gauss(a,b,n)==0)        //AZ=B奇异
              { 
				  delete[] y; delete[] b; delete[] a; return(-1);
			  }
              beta=1.0;
              for (i=0; i<=n-1; i++) beta=beta-b[i];
              if (fabs(beta)+1.0==1.0)    //beta=0
              { 
				  delete[] y; delete[] b; delete[] a; return(-1);
              }
              d=h/beta;
              for (i=0; i<=n-1; i++) x[i]=x[i]-d*b[i];
              h=t*h;
          }
      }
      delete[] y; delete[] b; delete[] a; return(k);
  }
/*
//非线性方程组拟牛顿法例
  #include <iostream>
  #include <cmath>
//  #include "非线性方程组拟牛顿法.cpp"
  using namespace std;
  int main()
  { 
	  int i, k;
      void netnf(double [],double [],int);
      double eps, h;
      double x[3]={1.0,1.0,1.0};
      h=0.1; eps=0.0000001; 
      k = netn(3,eps,h,x,netnf);
      cout <<"迭代次数 = " <<k <<endl;
      for (i=0; i<=2; i++)  cout <<"x(" <<i <<") = " <<x[i] <<endl;
      return 0;
  }
//方程组
  void netnf(double x[], double y[], int n)
  { y[0]=x[0]*x[0]+x[1]*x[1]+x[2]*x[2]-1.0;
    y[1]=2.0*x[0]*x[0]+x[1]*x[1]-4.0*x[2];
    y[2]=3.0*x[0]*x[0]-4.0*x[1]+x[2]*x[2];
    n=n;
    return;
  }
*/
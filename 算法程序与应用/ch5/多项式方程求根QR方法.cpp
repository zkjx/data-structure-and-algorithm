//多项式方程求根QR方法.cpp
  #include <cmath>
  #include <iostream>
  #include "求上H矩阵特征值的QR方法.cpp"
  using namespace std;
//a[n+1]       存放n次多项式的n+1个系数。
//n            多项式次数。
//xr[n]        返回n个根的实部。
//xi[n]        返回n个根的虚部。
//eps          控制精度要求。
  //函数返回在求上H矩阵特征值时返回的标志值。若>0则正常。
  int qrrt(double a[], int n, double xr[], double xi[], double eps)
  { 
	  int i,j;
      double *q;
      q = new double[n*n];
      for (j=0; j<=n-1; j++) q[j]=-a[n-j-1]/a[n];
      for (j=n; j<=n*n-1; j++) q[j]=0.0;
      for (i=0; i<=n-2; i++) q[(i+1)*n+i]=1.0;
      i=hhqr(q,n,xr,xi,eps);
      delete[] q; return(i);
  }

/*
//多项式方程求根QR方法例
  #include <cmath>
  #include <iostream>
//  #include "多项式方程求根QR方法.cpp"
  using namespace std;
  int main()
  { 
	  int i, n;
      double xr[6],xi[6],eps;
      double a[7]={-30.0,10.5,-10.5,1.5,4.5,-7.5,1.5};
      eps=0.000001;  n=6;
      i=qrrt(a,n,xr,xi,eps);
      if (i>0)
      { for (i=0; i<=5; i++)
          cout <<"x(" <<i <<") = " <<xr[i] <<"   J " <<xi[i] <<endl;
      }
	  return 0;
  }
*/

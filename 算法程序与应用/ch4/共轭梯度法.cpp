//共轭梯度法.cpp
  #include <iostream>
  #include <cmath>
  #include "矩阵相乘.cpp"
  using namespace  std;
//a[n][n]      存放对称正定矩阵。
//n            方程组阶数。
//b[n]         存放方程组右端常数向量。
//eps          控制精度要求。
//x[n]         返回方程组解向量。
  void grad(double a[],int n,double b[],double eps,double x[])
  { int i,k;
    double *p,*r,*s,*q,alpha,beta,d,e;
    p=new double[n];
    r=new double[n];
    s=new double[n];
    q=new double[n];
    for (i=0; i<=n-1; i++)
      { x[i]=0.0; p[i]=b[i]; r[i]=b[i]; }
    i=0;
    while (i<=n-1)
      { tmul(a,n,n,p,n,1,s);
        d=0.0; e=0.0;
        for (k=0; k<=n-1; k++)
           { d=d+p[k]*b[k]; e=e+p[k]*s[k]; }
        alpha=d/e;
        for (k=0; k<=n-1; k++)
           x[k]=x[k]+alpha*p[k];
        tmul(a,n,n,x,n,1,q);
        d=0.0;
        for (k=0; k<=n-1; k++)
          { r[k]=b[k]-q[k]; d=d+r[k]*s[k]; }
        beta=d/e; d=0.0;
        for (k=0; k<=n-1; k++) d=d+r[k]*r[k];
        d=sqrt(d);
        if (d<eps) 
          { delete[] p; delete[] r; delete[] s; delete[] q;return;}
        for (k=0; k<=n-1; k++)
           p[k]=r[k]-beta*p[k];
        i=i+1;
      }
    delete[] p; delete[] r; delete[] s; delete[] q;
    return;
  }

/*  #include <iostream>
  #include <cmath>
//  #include "共轭梯度法.cpp"
  using namespace  std;
  int main()
  { 
	  int i;
      double eps,x[4];
      double a[4][4]={{5.0,7.0,6.0,5.0},
                           {7.0,10.0,8.0,7.0},
                           {6.0,8.0,10.0,9.0},
                           {5.0,7.0,9.0,10.0}};
      double b[4]={23.0,32.0,33.0,31.0};
      eps=0.000001;
      grad(&a[0][0],4,b,eps,x);
      for (i=0; i<=3; i++)  cout <<"x(" <<i <<") = " <<x[i] <<endl;
	  return 0;
  }
*/

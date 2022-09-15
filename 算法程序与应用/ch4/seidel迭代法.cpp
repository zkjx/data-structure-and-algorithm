//seidel迭代法.cpp
  #include <iostream>
  #include <cmath>
  using namespace  std;
//a[n][n]     系数矩阵
//b[n]        常数向量
//n           方程组阶数
//x[n]        返回满足精度要求的解向量。若系数矩阵非对角优势，返回解向量0。
//eps         精度要求
  //若系数矩阵非对角优势，则显示错误信息，并返回0标志值。否则返回非0标志值。
  int seidel(double *a, double *b, int n, double *x, double eps)
  { 
	  int i,j,u,v;
      double p,t,s,q;
      for (i=0; i<=n-1; i++)
      { 
		  u=i*n+i; p=0.0; 
		  x[i]=0.0;           //置解向量初值
          for (j=0; j<=n-1; j++)
          if (i!=j)
          {
			  v=i*n+j; p=p+fabs(a[v]);
		  }
          if (p>=fabs(a[u]))     //检查系数矩阵是否对角优势
          { 
			  cout <<" 系数矩阵非对角优势！" <<endl; return 0;
		  }
      }
      p=eps+1.0;
      while (p>=eps)
      { 
		  p=0.0;
          for (i=0; i<=n-1; i++)
          { 
			  t=x[i]; s=0.0;
              for (j=0; j<=n-1; j++)
              if (j!=i) s=s+a[i*n+j]*x[j];
              x[i]=(b[i]-s)/a[i*n+i];
              q=fabs(x[i]-t)/(1.0+fabs(x[i]));
              if (q>p) p=q;
          }
      }
      return 1;
  }

/*
  #include <iostream>
//  #include "seidel迭代法.cpp"
  using namespace  std;
  int main()
  { 
	  int i;
      double eps;
      double a[4][4]={ 
		  {7.0,2.0,1.0,-2.0},
		  {9.0,15.0,3.0,-2.0},
		  {-2.0,-2.0,11.0,5.0},
		  {1.0,3.0,2.0,13.0}};
      double x[4],b[4]={4.0,7.0,-1.0,0.0};
      eps=0.000001;
      i=seidel(&a[0][0], b, 4, x, eps);
	  if (i!=0)
      for (i=0;i<4;i++)
        cout <<"x(" <<i <<")=" <<x[i] <<endl;
	  return 0;
  }
*/

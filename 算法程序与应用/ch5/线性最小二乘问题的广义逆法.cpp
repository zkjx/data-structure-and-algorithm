//线性最小二乘问题的广义逆法.cpp
  #include <iostream>
  #include <cmath>
  #include "求矩阵广义逆的奇异值分解法.cpp"
  using namespace  std;
//a[m][n]        超定方程组的系数矩阵A，返回时其对角线依次给出奇异值，其余元素为0。
//m              方程个数，也是系数矩阵行数。
//n              未知数个数，也是系数矩阵的列数。要求 m>=n 。
//b[m]           存放方程组右端的常数向量。
//x[n]           返回时方程组的最小二乘解。
//aa[n][m]       返回系数矩阵A的广义逆A+。
//eps            奇异值分解中的控制精度要求。
//u[m][m]        返回A的奇异值分解式中的左奇异向量U。
//v[n][n]        返回A的奇异值分解式中的右奇异向量V+。
//ka             ka = max(m,n) + 1。
  //函数返回标志值。若<0则表示失败；若>0则表示正常。
  int gmiv(double a[], int m, int n, double b[], double x[],
	         double aa[], double eps, double u[], double v[], int ka)
  { 
	  int i,j;
      i=ginv(a,m,n,aa,eps,u,v,ka);
      if (i<0) return(-1);
      for (i=0; i<=n-1; i++)
      { 
		  x[i]=0.0;
          for (j=0; j<=m-1; j++)  x[i]=x[i]+aa[i*m+j]*b[j];
      }
      return(1);
  }

/*
  #include <iostream>
  #include <cmath>
  #include <iomanip>
//  #include "线性最小二乘问题的广义逆法.cpp"
  using namespace  std;
  int main()
  { 
	  int i,j,m,n,ka;
      double x[3],aa[3][4],u[4][4],v[3][3];
      double a[4][3]={ {1.0,1.0,-1.0},{2.0,1.0,0.0},
                            {1.0,-1.0,0.0},{-1.0,2.0,1.0}};
      double b[4]={2.0,-3.0,1.0,4.0};
      double eps;
      m=4; n=3; ka=5; eps=0.000001;
      i=gmiv(&a[0][0],m,n,b,x,&aa[0][0],eps,&u[0][0],&v[0][0],ka);
      if (i>0)
      { 
		  cout <<"最小二乘解 :" <<endl;
		  for (i=0; i<=2; i++)
              cout <<"x(" <<i <<") = " <<x[i] <<endl;
          cout <<"广义逆 A+ :\n";
          for (i=0; i<=2; i++)
		  {
			  for (j=0; j<=3; j++)
				  cout <<setw(15) <<aa[i][j];
			  cout <<endl;
		  }
      }
	  return 0;
  }
*/

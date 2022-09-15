//线性最小二乘问题的Householder法.cpp
  #include <iostream>
  #include <cmath>
  #include "实矩阵的QR分解.cpp"
  using namespace  std;
//a[m][n]        超定方程组的系数矩阵，返回时存放QR分解式中的R矩阵。
//m              方程个数，也是系数矩阵行数。
//n              未知数个数，也是系数矩阵的列数。要求 m>=n 。
//b[m]           存放方程组右端的常数向量。返回时前n个分量存放方程组的最小二乘解。
//q[m][m]        返回QR分解式中的正交矩阵Q。
  //函数返回标志值。若=0则表示失败；否则表示正常。
  int gmqr(double a[], int m, int n, double b[], double q[])
  { 
	  int i,j;
      double d,*c;
      c=new double[n];
      i=maqr(a,m,n,q);
      if (i==0) 
	  { 
		  delete[] c; return(0);
	  }
      for (i=0; i<=n-1; i++)
      { 
		  d=0.0;
          for (j=0; j<=m-1; j++) d=d+q[j*m+i]*b[j];
          c[i]=d;
      }
      b[n-1]=c[n-1]/a[n*n-1];
      for (i=n-2; i>=0; i--)
      { 
		  d=0.0;
          for (j=i+1; j<=n-1; j++) d=d+a[i*n+j]*b[j];
          b[i]=(c[i]-d)/a[i*n+i];
      }
      delete[] c; return(1);
  }

/*
  #include <iostream>
  #include <iomanip>
  #include <cmath>
//  #include "线性最小二乘问题的Householder法.cpp"
  using namespace  std;
  int main()
  { int i,j,m,n;
    double a[4][3]={ {1.0,1.0,-1.0},{2.0,1.0,0.0},
                            {1.0,-1.0,0.0},{-1.0,2.0,1.0}};
    double b[4]={2.0,-3.0,1.0,4.0};
    double q[4][4];
    m=4; n=3;
    i=gmqr(&a[0][0],m,n,b,&q[0][0]);
    if (i!=0)
    { 
		cout <<"最小二乘解 :" <<endl;
		for (i=0; i<=2; i++)
            cout <<"x(" <<i <<") = " <<b[i] <<endl;
        cout <<"正交矩阵Q :" <<endl;
        for (i=0; i<=3; i++)
		{
			for (j=0; j<=3; j++)
				cout <<setw(15) <<q[i][j];
            cout <<endl;
		}
        cout <<"矩阵R :" <<endl;
        for (i=0; i<=3; i++)
		{
			for (j=0; j<=2; j++)
				cout <<setw(15) <<a[i][j];
            cout <<endl;
		}
	}
	return 0;
  }
*/

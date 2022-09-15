//对称正定矩阵求逆.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//a[n][n]       存放对称正定矩阵。返回其逆矩阵
  //函数返回标志值。等于0表示失败，大于0表示成功。
  int ssgj(double a[],int n)
  { int i,j,k,m;
    double w,g,*b;
    b=new double[n];
    for (k=0; k<=n-1; k++)
      { w=a[0];
        if (fabs(w)+1.0==1.0)
          { delete[] b; cout <<"fail\n"; return(0);}
        m=n-k-1;
        for (i=1; i<=n-1; i++)
          { g=a[i*n]; b[i]=g/w;
            if (i<=m) b[i]=-b[i];
            for (j=1; j<=i; j++)
              a[(i-1)*n+j-1]=a[i*n+j]+g*b[j];
          }
        a[n*n-1]=1.0/w;
        for (i=1; i<=n-1; i++)
          a[(n-1)*n+i-1]=b[i];
      }
    for (i=0; i<=n-2; i++)
    for (j=i+1; j<=n-1; j++)
      a[i*n+j]=a[j*n+i];
    delete[] b;
    return(1);
  }
/*
  #include <cmath>
  #include <iostream>
//  #include "对称正定矩阵求逆.cpp"
  #include "矩阵相乘.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double a[4][4]={ {5.0,7.0,6.0,5.0},
                            {7.0,10.0,8.0,7.0},
                            {6.0,8.0,10.0,9.0},
                            {5.0,7.0,9.0,10.0}};
      double b[4][4],c[4][4];
      for (i=0; i<=3; i++)
      for (j=0; j<=3; j++)  b[i][j]=a[i][j];
      i=ssgj(&b[0][0],4);
      if (i>0)
      { 
		  cout <<"矩阵 A:" <<endl;
          for (i=0; i<=3; i++)
          { 
			  for (j=0; j<=3; j++)  cout <<a[i][j] <<"    ";
              cout <<endl;
          }
		  cout <<"逆矩阵 A-:" <<endl;
          for (i=0; i<=3; i++)
          { 
			  for (j=0; j<=3; j++)  cout <<b[i][j] <<"    ";
              cout <<endl;
          }
          tmul(&a[0][0],4,4,&b[0][0],4,4,&c[0][0]);
		  cout <<"检验矩阵 AA-:" <<endl;
          for (i=0; i<=3; i++)
          { 
			  for (j=0; j<=3; j++)  cout <<c[i][j] <<"    ";
              cout <<endl;
          }
      }
	  return 0;
  }
*/
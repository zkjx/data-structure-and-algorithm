//Toeplitz方程组.cpp
  #include <iostream>
  #include <cmath>
  using namespace  std;
//t[n]       存放n阶T型矩阵中的n个元素。
//n          方程组阶数。
//b[n]       存放方程组右端的常数向量。
//x[n]       返回方程组的解向量。
  //函数返回标志值。若=0则表示失败；若>0则表示正常。
  int tlvs(double t[], int n, double b[], double x[])
  { 
	  int i,j,k;
      double a,beta,q,c,h,*y,*s;
      s=new double[n];
      y=new double[n];
      a=t[0];
      if (fabs(a)+1.0==1.0)
      { 
		  delete[] s; delete[] y; return(0);
	  }
      y[0]=1.0; x[0]=b[0]/a;
      for (k=1; k<=n-1; k++)
      { 
		  beta=0.0; q=0.0;
          for (j=0; j<=k-1; j++)
          { 
			  beta=beta+y[j]*t[j+1];
              q=q+x[j]*t[k-j];
          }
          if (fabs(a)+1.0==1.0)
		  { 
			  delete[] s; delete[] y; return(0);
		  }
          c=-beta/a; s[0]=c*y[k-1]; y[k]=y[k-1];
          if (k!=1)
          for (i=1; i<=k-1; i++)
              s[i]=y[i-1]+c*y[k-i-1];
          a=a+c*beta;
          if (fabs(a)+1.0==1.0)
          { 
			  delete[] s; delete[] y; return(0);
		  }
          h=(b[k]-q)/a;
          for (i=0; i<=k-1; i++)
          { 
			  x[i]=x[i]+h*s[i]; y[i]=s[i];
		  }
          x[k]=h*y[k];
      }
      delete[] s; delete[] y;
      return(1);
  }

/*
  #include <iostream>
  #include <cmath>
//  #include "Toeplitz方程组.cpp"
  using namespace  std;
  int main()
  { 
	  int i;
      double x[6];
      double t[6]={6.0,5.0,4.0,3.0,2.0,1.0};
      double b[6]={11.0,9.0,9.0,9.0,13.0,17.0};
      if (tlvs(t,6,b,x)>0)
      for (i=0; i<=5; i++)
          cout <<"x(" <<i <<") = " <<x[i] <<endl;
	  return 0;
  }
*/

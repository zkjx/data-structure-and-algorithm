//方程求根连分式法.cpp
  #include <cmath>
  #include <iostream>
  #include "计算函数连分式值.cpp"
  #include "计算函数连分式新一节.cpp"
  using namespace std;
//xx      方程根初值。返回迭代终值。
//eps     控制精度要求。
//f       方程左端函数f(x)的函数名。
  //函数返回迭代次数。一次迭代最多作到七节连分式。本函数最多迭代20次。
  int pqroot(double *xx,double eps,double (*f)(double))
  {
	  int j,k,flag;
	  double *x,*y,*b,x0;
	  b=new double[10];
	  x=new double[10];
	  y=new double[10];
      k=0; x0=*xx; flag=0;
      while ((k<20)&&(flag==0))
      { 
		  k=k+1; 
		  j=0;
		  x[0]=x0;   y[0]=(*f)(x[0]); 
		  b[0]=x[0];                            //计算b[0]
		  j=1;
		  x[1]=x0+0.1;   y[1]=(*f)(x[1]);
          while (j<=7)
          { 
			  funpqj(y,x,b,j);                  //计算b[j]
			  x[j+1]=funpqv(y,b,j,0.0);         //计算x[j+1]
              y[j+1]=(*f)(x[j+1]);              //计算y[j+1]
			  x0=x[j+1];
              if (fabs(y[j+1])>=eps) j=j+1;
			  else 
			  { 
				  cout <<"最后一次迭代连分式节数=" <<j <<endl;
				  j=10; 
			  }
          }
          if (j==10) flag=1;
	  }
	  *xx = x0;
	  delete[] b; delete[] x; delete[] y;
      return(k);
   }
/*
//方程求根连分式法例
  #include <cmath>
  #include <iostream>
//  #include "方程求根连分式法.cpp"
  using namespace std;
  int main()
  { 
	  int k;
	  double x,eps,pqrootf(double);
      eps=0.0000001; x=1.0;
	  k=pqroot(&x,eps,pqrootf);
      cout <<"迭代次数 = " <<k <<endl;
      cout <<"方程根为 x = " <<x <<endl;
      cout <<endl;
	  cout <<"检验精度 : f(x)=" <<pqrootf(x) <<endl;  //检验精度
	  return 0;
  }
//f(x)
  double pqrootf(double x)
  { 
	  double y;
      y=x*x*(x-1.0)-1.0;
      return(y);
  }
*/
/*
  double pqrootf(double x)
  { 
	  double y;
      y=x*x+x-6.0;
      return(y);
  }
*/
/*
  double pqrootf(double x)
  { 
	  double y;
      y=exp(-x*x*x)-sin(x)/cos(x)+800;
      return(y);
  }
*/
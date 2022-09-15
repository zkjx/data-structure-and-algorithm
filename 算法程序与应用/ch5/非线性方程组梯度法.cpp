//非线性方程组梯度法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//n           方程个数，也是未知数个数。
//eps         控制精度要求。
//x[n]        存放一组初值。返回一组实数解。
//f           计算目标函数值以及目标函数n个偏导数的函数名。
  //函数返回实际迭代次数。若<0则表示因D=0而失败。本函数最大迭代次数为1000。
  int snse(int n,double eps,double x[],double (*f)(double [],double [],int))
  {
	  int i,k,flag,interation;
	  double y,*yy,d,s;
	  interation = 1000;          //最大迭代次数
	  yy=new double[n];
      k=0;  flag=0;
      while ((k<interation)&&(flag==0))
      {
		  y = (*f)(x,yy,n);          //计算目标函数值F以及目标函数的n个偏导数
          if (y<eps)  flag = 1;
          else
          {
			  k = k + 1;
			  d=0.0;
              for (i=0; i<=n-1; i++) d=d+yy[i]*yy[i];   //计算D
              if (d+1.0==1.0) 
			  {  
				  delete[] yy;   return(-1);
			  }
              s=y/d;
              for (i=0; i<=n-1; i++) 
			      x[i]=x[i]-s*yy[i];              //计算新的校正值X
		  }
       }
	   delete[] yy; 
       return(k);
  }
/*
//非线性方程组梯度法例
  #include <cmath>
  #include <iostream>
//  #include "非线性方程组梯度法.cpp"
  using namespace std;
  int main()
  { 
	  int i,k;
      double eps, snsef(double [], double [], int);
      double x[3]={1.5,6.5,-5.0};
      eps=0.000001;
      k = snse(3,eps,x,snsef);
	  cout <<"迭代次数 = " <<k <<endl;
	  for (i=0; i<=2; i++)
             cout <<"x(" <<i <<")=" <<x[i] <<endl;
	  return 0;
  }

  double snsef(double x[],double y[],int n)
  { double z,f1,f2,f3,df1,df2,df3;
    n=n;
    f1=x[0]-5.0*x[1]*x[1]+7.0*x[2]*x[2]+12.0;
    f2=3.0*x[0]*x[1]+x[0]*x[2]-11.0*x[0];
    f3=2.0*x[1]*x[2]+40.0*x[0];
    z=f1*f1+f2*f2+f3*f3;
    df1=1.0; df2=3.0*x[1]+x[2]-11.0; df3=40.0;
    y[0]=2.0*(f1*df1+f2*df2+f3*df3);
    df1=-10.0*x[1]; df2=3.0*x[0]; df3=2.0*x[2];
    y[1]=2.0*(f1*df1+f2*df2+f3*df3);
    df1=14.0*x[2]; df2=x[0]; df3=2.0*x[1];
    y[2]=2.0*(f1*df1+f2*df2+f3*df3);
    return(z);
  }
*/
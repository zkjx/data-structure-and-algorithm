//复形调优法.cpp
  #include <cmath>
  #include <iostream>
  #include "产生随机数类.h"
  using namespace std;
//n             变量个数。
//m             函数约束条件的个数。
//a[n]          依次存放常数约束条件中的变量x的下界。
//b[n]          依次存放常数约束条件中的变量x的上界。
//alpha         存放反射系数。
//eps           控制精度要求。
//x[n+1]        前n个分量存放初始复形的第1个顶点坐标值（要求满足所有约束条件），
//              返回极小值点各坐标值；最后一个分量返回极小值。
//xx[n+1][2n]   前n行返回最后复形的2n个顶点坐标（1列为1个顶点）；
//              最后一行返回最后复形的2n个顶点上的目标函数值。
//s             计算函数约束条件中的上、下限以及条件值的函数名。
//f             计算目标函数值的函数名。
  //函数返回迭代次数。本函数最多迭代500次。
  int cplx(int n, int m, double a[], double b[],  double eps, 
	       double x[], double xx[], 
		   void (*s)(int,int,double [],double [],double [],double []), 
		   double (*f)(double [],int))
  { 
	  RND p;
      int r,g,i,j,kt,it,jt,flag,k;
      double fj,fr,fg,z,alpha,*c,*d,*w,*xt,*xf;
      c=new double[m];
      d=new double[m];
      w=new double[m];
      xt=new double[n];
      xf=new double[n];
      p = RND(0);
	  alpha = 1.3;      //反射系数
      for (i=0; i<=n-1; i++)  xx[i*n*2]=x[i];
      xx[n*n*2]=(*f)(x,n);
      for (j=1; j<=2*n-1; j++)
      { 
		  for (i=0; i<=n-1; i++)
		  { 
			  xx[i*n*2+j]=a[i]+(b[i]-a[i])*(p.rnd1());
              x[i]=xx[i*n*2+j];
          }
          it=1;
          while (it==1)
          { 
			  it=0; r=0; g=0;
              while ((r<n)&&(g==0))
              { 
				  if ((a[r]<=x[r])&&(b[r]>=x[r])) r=r+1;
                  else g=1;
              }
              if (g==0)
              { 
				  (*s)(n,m,x,c,d,w);
                  r=0;
                  while ((r<m)&&(g==0))
                  { 
					  if ((c[r]<=w[r])&&(d[r]>=w[r])) r=r+1;
                      else g=1;
                  }
              }
              if (g!=0)
              {
				  for (r=0; r<=n-1; r++)
                  {
					  z=0.0;
                      for (g=0; g<=j-1; g++)
                          z=z+xx[r*n*2+g]/(1.0*j);
                      xx[r*n*2+j]=(xx[r*n*2+j]+z)/2.0;
                      x[r]=xx[r*n*2+j];
                  }
                  it=1;
              }
              else xx[n*n*2+j]=(*f)(x,n);
          }
      }
      flag = 500; k = 0; it = 1;
      while (it == 1)
      { 
		  it = 0;
          fr=xx[n*n*2]; r=0;
          for (i=1; i<=2*n-1; i++)
            if (xx[n*n*2+i]>fr)
            {
				r=i; fr=xx[n*n*2+i];
			}
          g=0; j=0; fg=xx[n*n*2];
          if (r==0)
          { 
			  g=1; j=1; fg=xx[n*n*2+1];
		  }
          for (i=j+1; i<=2*n-1; i++)
            if (i!=r)
              if (xx[n*n*2+i]>fg)
              { 
				  g=i; fg=xx[n*n*2+i];
			  }
          for (i=0; i<=n-1; i++)
          {
			  xf[i]=0.0;
              for (j=0; j<=2*n-1; j++)
                if (j!=r)
                    xf[i]=xf[i]+xx[i*n*2+j]/(2.0*n-1.0);
              xt[i]=(1.0+alpha)*xf[i]-alpha*xx[i*n*2+r];
		  }
          jt=1;
          while (jt==1)
          { 
			  jt=0;
              z=(*f)(xt,n);
              while (z>fg)
              { 
				  for (i=0; i<=n-1; i++)
                       xt[i]=(xt[i]+xf[i])/2.0;
                  z=(*f)(xt,n);
              }
              j=0;
              for (i=0; i<=n-1; i++)
              { 
				  if (a[i]>xt[i])
                  { 
					  xt[i]=xt[i]+0.000001; j=1;
				  }
                  if (b[i]<xt[i])
                  { 
					  xt[i]=xt[i]-0.000001; j=1;
				  }
              }
              if (j!=0) jt=1;
              else
              { 
				  (*s)(n,m,xt,c,d,w);
                  j=0; kt=1;
                  while ((kt==1)&&(j<m))
                  { 
					  if ((c[j]<=w[j])&&(d[j]>=w[j])) j=j+1;
                      else kt=0;
                  }
                  if (j<m)
                  { 
					  for (i=0; i<=n-1; i++)
                        xt[i]=(xt[i]+xf[i])/2.0;
                      jt=1;
                  }
              }
          }
          for (i=0; i<=n-1; i++)  xx[i*n*2+r]=xt[i];
          xx[n*n*2+r]=z;
          fr=0.0; fg=0.0;
          for (j=0; j<=2*n-1; j++)
          { 
			  fj=xx[n*n*2+j];
              fr=fr+fj/(2.0*n);
              fg=fg+fj*fj;
          }
          fr=(fg-2.0*n*fr*fr)/(2.0*n-1.0);
		  k = k + 1; 
          if (fr>=eps)  
		  {
			  if (k < flag) it = 1;
		  }
      }
      for (i=0; i<=n-1; i++)
      {
		  x[i]=0.0;
          for (j=0; j<=2*n-1; j++)
              x[i]=x[i]+xx[i*n*2+j]/(2.0*n);
      }
      z=(*f)(x,n); x[n]=z;
      delete[] c; delete[] d; delete[] w;
      delete[] xt; delete[] xf;
      return(k);
  }

/*
//复形调优法例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "复形调优法.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      void  cplxs(int,int,double [],double [],double [],double []);
      double  cplxf(double [],int);
      double eps,a[2],b[2],x[3],xx[3][4];
      x[0]=0.0; x[1]=0.0;
      a[0]=0.0; a[1]=0.0;
      b[0]=1.0e+35; b[1]=b[0];
      eps=1.0e-30; 
      i=cplx(2,2,a,b,eps,x,&xx[0][0],cplxs,cplxf);
      cout <<"迭代次数 = " <<i <<endl;
      cout <<"复形顶点坐标与目标函数值 :" <<endl;
      for (i=0; i<=3; i++)
	  {
		  for (j=0; j<=1; j++) 
			  cout <<"    xx(" <<j <<")=" <<setw(10) <<xx[j][i];
          cout <<"    f = " <<xx[2][i] <<endl;
      }
	  cout <<"极小值点坐标与极小值 :" <<endl;
      for (i=0; i<=1; i++)
			  cout <<"    x(" <<i <<")=" <<setw(10) <<x[i];
	  cout <<"      极小值 = " <<x[2] <<endl;
      return 0;
  }
//计算目标函数值
  double cplxf(double x[], int n)
  { 
	  double y;
      n=n;
      y=-(9.0-(x[0]-3.0)*(x[0]-3.0));
      y=y*x[1]*x[1]*x[1]/(27.0*sqrt(3.0));
      return(y);
  }
//计算函数约束条件中的上、下限以及条件值
  void cplxs(int n, int m, double x[], double c[], double d[], double w[])
  { 
	  n=n; m=m;
      c[0]=0.0; c[1]=0.0;
      d[0]=x[0]/sqrt(3.0); d[1]=6.0;
      w[0]=x[1]; w[1]=x[0]+x[1]*sqrt(3.0);
      return;
  }
*/
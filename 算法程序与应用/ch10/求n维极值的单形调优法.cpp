//求n维极值的单形调优法.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//n               变量个数。
//x[n+1]          前n个分量返回极小值点的n个坐标；最后一个分量返回极小值。
//eps             控制精度要求。
//xx[n+1][n+1]    前n行返回最后单形的n+1个顶点坐标；
//                最后一行返回最后单形的n+1个顶点的目标函数值。
//f               计算目标函数值的函数名。
  //函数返回迭代次数。本函数最多迭代500次。
  int jsim(int n, double x[], double eps, double xx[], double (*f)(double [],int))
  { 
	  int r,g,i,j,l,kk,k;
      double nn,fe,fr,fl,fg,ft,ff,d,u,v;
      double *xt,*xf,*xe;
      xt=new double[n];
      xf=new double[n];
      xe=new double[n];
	  d = 1.0;          //初始单形中任意两顶点间的距离
	  u = 1.6;          //扩张系数  1.2<u<2.0
	  v = 0.4;          //收缩系数  0.0<v<1.0
	  k = 500;          //最大迭代次数。
      kk=0; nn=1.0*n;
      fr=sqrt(nn+1.0);
      fl=d*(fr-1.0)/(1.414*nn);
      fg=d*(fr+nn-1.0)/(1.414*nn);
      for(i=0; i<=n-1; i++)
      for(j=0; j<=n; j++)  xx[i*(n+1)+j]=0.0;
      for(i=1; i<=n; i++)
      for(j=0; j<=n-1; j++) xx[j*(n+1)+i]=fl;
      for(i=1; i<=n; i++)  xx[(i-1)*(n+1)+i]=fg;
      for(i=0; i<=n; i++)
      { 
		  for(j=0; j<=n-1; j++) xt[j]=xx[j*(n+1)+i]; 
          xx[n*(n+1)+i]=(*f)(xt,n); 
      }
      ft=1.0+eps;
      while ((kk<k)&&(ft>eps))
      { 
		  kk=kk+1;
          fr=xx[n*(n+1)+0]; fl=xx[n*(n+1)+0]; r=0; l=0;
          for (i=1; i<=n; i++)
          { 
			  if (xx[n*(n+1)+i]>fr) { r=i; fr=xx[n*(n+1)+i];}
              if (xx[n*(n+1)+i]<fl) { l=i; fl=xx[n*(n+1)+i];}
          }
          g=0; fg=xx[n*(n+1)+0];
          j=0;
          if (r==0) { g=1; fg=xx[n*(n+1)+1]; j=1;}
          for (i=j+1; i<=n; i++)
            if ((i!=r)&&(xx[n*(n+1)+i]>fg))
            { g=i; fg=xx[n*(n+1)+i];}
          for (j=0; j<=n-1; j++)
          { 
			  xf[j]=0.0;
              for (i=0; i<=n; i++)
                if (i!=r)
                  xf[j]=xf[j]+xx[j*(n+1)+i]/nn;
              xt[j]=2.0*xf[j]-xx[j*(n+1)+r];
          }
          ft=(*f)(xt,n);
          if (ft<xx[n*(n+1)+l])
          { 
			  for (j=0; j<=n-1; j++)
                xf[j]=(1.0+u)*xt[j]-u*xf[j];
              ff=(*f)(xf,n);
              if (ff<xx[n*(n+1)+l])
              { 
				  for (j=0; j<=n-1; j++) xx[j*(n+1)+r]=xf[j];
                  xx[n*(n+1)+r]=ff;
              }
              else
              { 
				  for (j=0; j<=n-1; j++)  xx[j*(n+1)+r]=xt[j];
                  xx[n*(n+1)+r]=ft;
              }
          }
          else
          { 
			  if (ft<=xx[n*(n+1)+g])
              {
				  for (j=0; j<=n-1; j++) xx[j*(n+1)+r]=xt[j];
                  xx[n*(n+1)+r]=ft;
              }
              else 
              { 
				  if (ft<=xx[n*(n+1)+r])
                  { 
					  for (j=0; j<=n-1; j++)  xx[j*(n+1)+r]=xt[j];
                      xx[n*(n+1)+r]=ft;
                  }
                  for (j=0; j<=n-1; j++)
                      xf[j]=v*xx[j*(n+1)+r]+(1.0-v)*xf[j];
                  ff=(*f)(xf,n);
                  if (ff>xx[n*(n+1)+r])
                    for (i=0; i<=n; i++)
                    { 
						for (j=0; j<=n-1; j++)
                        { 
							xx[j*(n+1)+i]=(xx[j*(n+1)+i]+
				                        	xx[j*(n+1)+l])/2.0;
                            x[j]=xx[j*(n+1)+i]; xe[j]=x[j];
                        }
                        fe=(*f)(xe,n); xx[n*(n+1)+i]=fe;
                    }
                  else
                  { 
					  for (j=0; j<=n-1; j++)  xx[j*(n+1)+r]=xf[j];
                      xx[n*(n+1)+r]=ff;
                  }
              }
          }
          ff=0.0; ft=0.0;
          for (i=0; i<=n; i++)
          {
			  ff=ff+xx[n*(n+1)+i]/(1.0+nn);  
			  ft=ft+xx[n*(n+1)+i]*xx[n*(n+1)+i];
          }
          ft=(ft-(1.0+n)*ff*ff)/nn;
      }
      for (j=0; j<=n-1; j++)
      {
		  x[j]=0.0;
          for (i=0; i<=n; i++)
                x[j]=x[j]+xx[j*(n+1)+i]/(1.0+nn);
          xe[j]=x[j];
      }
      fe=(*f)(xe,n); x[n]=fe;
      delete[] xt; delete[] xf; delete[] xe;
      return(kk);
  }
/*
//求n维极值的单形调优法例
  #include <iostream>
  #include <cmath>
  #include <iomanip>
//  #include "求n维极值的单形调优法.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double  jsimf(double [],int);
      double eps,x[3],xx[3][3];
      eps=1.0e-30;
      i=jsim(2,x,eps,&xx[0][0],jsimf);
      cout <<"迭代次数 = " <<i <<endl;
      cout <<"顶点坐标与目标函数值 :" <<endl;
      for (i=0; i<=2; i++)
		  cout <<"x(0)=" <<setw(10) <<xx[0][i] 
		       <<"    x(1)=" <<setw(10) <<xx[1][i]
			   <<"    f=" <<xx[2][i] <<endl;
	  cout <<"极小值点与极小值 :" <<endl;
      for (i=0; i<=1; i++)
		  cout <<"x(" <<i <<")=" <<x[i] <<endl;
	  cout <<"极小值 = " <<x[2] <<endl;
      return 0;
  }
//计算目标函数值
  double jsimf(double x[], int n)
  { double y;
    n=n;
    y=x[1]-x[0]*x[0]; y=100.0*y*y;
    y=y+(1.0-x[0])*(1.0-x[0]);
    return(y);
  }
*/
//计算多重积分的高斯法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//n          积分重数。
//js[n]      js[k]表示第k层积分区间所划分的子区间个数。
//s          计算各层积分上下限（要求所有的上限>下限）的函数名。
//f          计算被积函数值f(X)的函数名。
  //函数返回积分值。
  double gaus_int(int n, int js[], void (*s)(int,int,double [],double []), 
	                                       double (*f)(int,double []))
  { 
	  int m,j,k,q,l,*is;
      double y[2],p,*x,*a,*b;
      double t[5]={-0.9061798459,-0.5384693101,0.0,
                         0.5384693101,0.9061798459};
      double c[5]={0.2369268851,0.4786286705,0.5688888889,
                        0.4786286705,0.2369268851};
      is=new int[2*(n+1)];
      x=new double[n];
      a=new double[2*(n+1)];
      b=new double[n+1];
      m=1; l=1;
      a[n]=1.0; a[2*n+1]=1.0;
      while (l==1)
      { 
		  for (j=m;j<=n;j++)
          { 
			  (*s)(j-1,n,x,y);     //计算j-1层积分区间的上下限y[1]与y[0]
              a[j-1]=0.5*(y[1]-y[0])/js[j-1];  
              b[j-1]=a[j-1]+y[0];
              x[j-1]=a[j-1]*t[0]+b[j-1];   //高斯点
              a[n+j]=0.0;
              is[n+j]=1;     //这是j-1层积分的第1个子区间
			  is[j-1]=1;     //的第1个高斯点
          }
          j=n; q=1;      //从最内层积分开始
          while (q==1)
          { 
			  k=is[j-1];       //取j-1层积分区间当前子区间上的高斯点序号
              if (j==n) p=(*f)(n,x);   //计算高斯点上的被积函数值
              else p=1.0;
              a[n+j]=a[n+j+1]*a[j]*p*c[k-1]+a[n+j];
              is[j-1]=is[j-1]+1;   //置j-1层积分区间当前子区间的下一个高斯点序号
              if (is[j-1]>5)    //j-1层积分区间当前子区间上的高斯点全部计算完
			  {
				  if (is[n+j]>=js[j-1])  //j-1层积分区间的所有子区间考虑完
				  { 
					  j=j-1; q=1;   //考虑前一层的积分区间
                      if (j==0)     //已到最外层
					  { 
						  p=a[n+1]*a[0]; 
						  delete[] is; delete[] x; delete[] a; delete[] b; 
						  return(p);
					  }
				  }
                  else    //j-1层积分区间还有子区间
				  { 
					  is[n+j]=is[n+j]+1;    //置j-1层积分区间的下一个子区间
                      b[j-1]=b[j-1]+a[j-1]*2.0;
                      is[j-1]=1; k=is[j-1];    //这是j-1层积分区间当前子区间的第1个
                      x[j-1]=a[j-1]*t[k-1]+b[j-1];  //高斯点
                      if (j==n) q=1;   //这是最内层
                      else q=0;        //这不是最内层
				  }
			  }
              else   //计算j-1层积分区间当前子区间上的下一个高斯点
              { 
				  k=is[j-1];
                  x[j-1]=a[j-1]*t[k-1]+b[j-1];
                  if (j==n) q=1;   //这是最内层
                  else q=0;        //这不是最内层
              }
          }
          m=j+1;
      }
	  return(0.0);
  }

/*
//计算多重积分的高斯法例
  #include <cmath>
  #include <iostream>
//  #include "计算多重积分的高斯法.cpp"
  using namespace std;
  int main()
  { 
	  int js[3]={4,4,4};
	  void gauss(int,int,double [],double []);
      double s,gausf(int,double []);
      s=gaus_int(3,js,gauss,gausf);
      cout <<"s = " <<s <<endl;
      return 0;
  }
//计算各层积分上下限
  void gauss(int j, int n, double x[], double y[2])
  { 
	  double q;
      n=n;
      switch (j)
      { 
	    case 0: { y[0]=0.0; y[1]=1.0; break;}
        case 1: { y[0]=0.0; y[1]=sqrt(1.0-x[0]*x[0]); break;}
        case 2: { q=x[0]*x[0]+x[1]*x[1]; y[0]=sqrt(q);
                  y[1]=sqrt(2.0-q); break;
                }
        default: { }
      }
      return;
  }
//计算被积函数值
  double gausf(int n, double x[])
  { 
	  double z;
      n=n;
      z=x[2]*x[2];
      return(z);
  }
*/
/*
//计算多重积分的高斯法例
  #include <cmath>
  #include <iostream>
//  #include "计算多重积分的高斯法.cpp"
  using namespace std;
  int main()
  { 
	  int js[3]={10,10,10};
	  void gauss(int,int,double [],double []);
      double s,gausf(int,double []);
      s=gaus_int(3,js,gauss,gausf);
      cout <<"s = " <<s <<endl;
      return 0;
  }
//计算各层积分上下限
  void gauss(int j, int n, double x[], double y[2])
  { 
      n=n;
      switch (j)
      { 
	    case 0: { y[0]=1.0; y[1]=2.0; break;}
        case 1: { y[0]=1.0; y[1]=2.0; break;}
        case 2: { y[0]=1.0; y[1]=2.0; break;
                }
        default: { }
      }
      return;
  }
//计算被积函数值
  double gausf(int n, double x[])
  { 
	  double z;
      n=n;
      z=x[0]*x[0]+x[1]*x[1]+x[2]*x[2];
      return(z);
  }
*/
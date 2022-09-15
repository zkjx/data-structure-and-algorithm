//光滑插值.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//x[n]       存放给定的n个结点值。
//y[n]       存放给定n个结点上的函数值。
//n          给定的结点个数。
//t　　　　　指定的插值点。
//s[4]　　   返回插值点所在子区间上的三次多项式系数。
  //函数返回指定插值点处的函数近似值。
  double akima(double x[], double y[], int n, double t, double s[4])
  { 
	  int k,m,j;
      double u[5],p,q;
      s[0]=0.0; s[1]=0.0; s[2]=0.0; s[3]=0.0;
      if (n<1) return(0.0);
      if (n==1) { s[0]=y[0];  return(y[0]);}
      if (n==2)
      { 
		  s[0]=y[0]; s[1]=(y[1]-y[0])/(x[1]-x[0]);
          p=(y[0]*(t-x[1])-y[1]*(t-x[0]))/(x[0]-x[1]);
          return(p);
      }
      if (t<=x[1]) k=0;          //确定插值点t所在的子区间
      else if (t>=x[n-1]) k=n-2;
      else
	  { 
		  k=1; m=n-1;
          while (((k-m)!=1)&&((k-m)!=-1))
          { 
			  j=(k+m)/2;
              if (t<=x[j]) m = j;
              else k = j;
          }
	  }
      u[2]=(y[k+1]-y[k])/(x[k+1]-x[k]);
      if (n==3)
      { 
		  if (k==0)
          { 
			  u[3]=(y[2]-y[1])/(x[2]-x[1]);
              u[4]=2.0*u[3]-u[2];
              u[1]=2.0*u[2]-u[3];
              u[0]=2.0*u[1]-u[2];
          }
          else
          { 
			  u[1]=(y[1]-y[0])/(x[1]-x[0]);
              u[0]=2.0*u[1]-u[2];
              u[3]=2.0*u[2]-u[1];
              u[4]=2.0*u[3]-u[2];
          }
      }
      else
      { 
		  if (k<=1)
          { 
			  u[3]=(y[k+2]-y[k+1])/(x[k+2]-x[k+1]);
              if (k==1)
              { 
				  u[1]=(y[1]-y[0])/(x[1]-x[0]);
                  u[0]=2.0*u[1]-u[2];
                  if (n==4) u[4]=2.0*u[3]-u[2];
                  else u[4]=(y[4]-y[3])/(x[4]-x[3]);
              }
              else
              { 
				  u[1]=2.0*u[2]-u[3];
                  u[0]=2.0*u[1]-u[2];
                  u[4]=(y[3]-y[2])/(x[3]-x[2]);
              }
          }
          else if (k>=(n-3))
          { 
			  u[1]=(y[k]-y[k-1])/(x[k]-x[k-1]);
              if (k==(n-3))
              { 
				  u[3]=(y[n-1]-y[n-2])/(x[n-1]-x[n-2]);
                  u[4]=2.0*u[3]-u[2];
                  if (n==4) u[0]=2.0*u[1]-u[2];
                  else u[0]=(y[k-1]-y[k-2])/(x[k-1]-x[k-2]);
              }
              else
              { 
				  u[3]=2.0*u[2]-u[1];
                  u[4]=2.0*u[3]-u[2];
                  u[0]=(y[k-1]-y[k-2])/(x[k-1]-x[k-2]);
              }
          }
          else
          { 
			  u[1]=(y[k]-y[k-1])/(x[k]-x[k-1]);
              u[0]=(y[k-1]-y[k-2])/(x[k-1]-x[k-2]);
              u[3]=(y[k+2]-y[k+1])/(x[k+2]-x[k+1]);
              u[4]=(y[k+3]-y[k+2])/(x[k+3]-x[k+2]);
          }
      }
      s[0]=fabs(u[3]-u[2]);
      s[1]=fabs(u[0]-u[1]);
      if ((s[0]+1.0==1.0)&&(s[1]+1.0==1.0))
         p=(u[1]+u[2])/2.0;
      else p=(s[0]*u[1]+s[1]*u[2])/(s[0]+s[1]);
      s[0]=fabs(u[3]-u[4]);
      s[1]=fabs(u[2]-u[1]);
      if ((s[0]+1.0==1.0)&&(s[1]+1.0==1.0))
         q=(u[2]+u[3])/2.0;
      else q=(s[0]*u[2]+s[1]*u[3])/(s[0]+s[1]);
      s[0]=y[k];
      s[1]=p;
      s[3]=x[k+1]-x[k];
      s[2]=(3.0*u[2]-2.0*p-q)/s[3];
      s[3]=(q+p-2.0*u[2])/(s[3]*s[3]);
      p=t-x[k];
      p=s[0]+s[1]*p+s[2]*p*p+s[3]*p*p*p;
      return(p);
  }
/*
//光滑插值例
  #include <cmath>
  #include <iostream>
//  #include "光滑插值.cpp"
  using namespace std;
  int main()
  { 
	  int i, n;
      double t, z;
      double x[11]={-1.0,-0.95,-0.75,-0.55,-0.3,0.0,
                         0.2,0.45,0.6,0.8,1.0};
      double y[11]={0.0384615,0.0424403,0.06639,0.116788,
           0.307692,1.0,0.5,0.164948,0.1,0.0588236,0.0384615};
      double s[4];
      n=11;
      for (i=0; i<=10; i++)
	  {
		  t = x[i];
		  z = akima(x,y,n,t,s);
		  cout <<"t = " <<t <<"     z = f(t) = " <<z <<endl;
		  cout <<"s0 = " <<s[0] <<endl;
		  cout <<"s1 = " <<s[1] <<endl;
		  cout <<"s2 = " <<s[2] <<endl;
		  cout <<"s3 = " <<s[3] <<endl;
	  }

      t=-0.85; z = akima(x,y,n,t,s);
		  cout <<"t = " <<t <<"     z = f(t) = " <<z <<endl;
		  cout <<"s0 = " <<s[0] <<endl;
		  cout <<"s1 = " <<s[1] <<endl;
		  cout <<"s2 = " <<s[2] <<endl;
		  cout <<"s3 = " <<s[3] <<endl;
      t=0.15; z = akima(x,y,n,t,s);
		  cout <<"t = " <<t <<"     z = f(t) = " <<z <<endl;
		  cout <<"s0 = " <<s[0] <<endl;
		  cout <<"s1 = " <<s[1] <<endl;
		  cout <<"s2 = " <<s[2] <<endl;
		  cout <<"s3 = " <<s[3] <<endl;
      return 0;
  }
*/
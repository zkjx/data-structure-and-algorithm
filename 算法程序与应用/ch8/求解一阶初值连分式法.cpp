//求解一阶初值连分式法.cpp
  #include <iostream>
  #include <cmath>
  #include "计算函数连分式新一节.cpp"
  #include "计算函数连分式值.cpp"
  using namespace std;
//改进欧拉公式以h为步长积分m步
  void euler1(double t, double h, int n, double y[], int m,
	         void (*f)(double,double [],int,double []))
  { 
	  int i,j;
      double x,*c,*d;
      c=new double[n];
      d=new double[n];
      for (j=0; j<=m-1; j++)
      { 
		  for (i=0; i<=n-1; i++) c[i]=y[i];
	      x=t+j*h;
          (*f)(x,y,n,d);
          for (i=0; i<=n-1; i++)  y[i]=c[i]+h*d[i];
          x=t+(j+1)*h;
          (*f)(x,y,n,d);
          for (i=0; i<=n-1; i++)  d[i]=c[i]+h*d[i];
          for (i=0; i<=n-1; i++)  y[i]=(y[i]+d[i])/2.0;
      }
      delete[] c; delete[] d;
      return;
  }

//t           积分起始点。
//h           积分步长。
//n           一阶微分方程组中方程个数，也是未知函数个数。
//y[n]        存放n个未知函数在起始点t处的函数值。
//            返回n个未知函数在t+h处的函数值。
//eps         控制精度要求。
//f           计算微分方程组中各方程右端函数值的函数名。
  void pqeuler(double t,double h,int n,double y[],double eps,
	           void (*f)(double,double [],int,double []))
  {
	  int i,j,il,flag,m;
	  double *hh,*g,*b,h0,*g0,*yy,d,*s0,*s1;
	  s0=new double[n];
	  s1=new double[n];
	  g0=new double[n];
	  yy=new double[n];
	  b=new double[n*10];
	  hh=new double[10];
	  g=new double[n*10];
      for (i=0; i<n; i++)  yy[i]=y[i];
	  il=0; flag=0;
	  m=1; h0=h;
      euler1(t,h0,n,yy,m,f);                  //Euler方法计算初值g[i][0]
	  for (i=0; i<n; i++)  g0[i]=yy[i];
	  while ((il<20)&&(flag==0))
      { 
		  il=il+1; 
		  hh[0]=h0;
		  for (i=0; i<n; i++)                   //计算b[i][0]
		  {
			  g[i*10+0]=g0[i];
			  b[i*10+0]=g[i*10+0];
		  }
          j=1; 
		  for (i=0; i<n; i++)  s1[i]=g[i*n+0];
		  while (j<=7)
          { 
			  for(i=0; i<n; i++)   yy[i]=y[i]; 
			  m=m+m; hh[j]=hh[j-1]/2.0;
              euler1(t,hh[j],n,yy,m,f);            //Euler方法计算新近似值g[i][j]
	          for (i=0; i<n; i++)  g[i*10+j]=yy[i];
			  for (i=0; i<n; i++)
			  {
				  funpqj(hh,&g[i*10],&b[i*10],j);                  //计算b[i][j]

			  }
			  for (i=0; i<n; i++)  s0[i]=s1[i];

              for (i=0; i<n; i++)
			  {
				  s1[i]=funpqv(hh,&b[i*10],j,0.0);    //连分式法计算积分近似值s1[i]
			  }
              d=0.0;
			  for (i=0; i<n; i++)
			  {
				  if (fabs(s1[i]-s0[i])>d)  d=fabs(s1[i]-s0[i]);
			  }			  
			  if (d>=eps)  j=j+1;
			  else  j = 10;
          }
		  h0=hh[j-1]; 
		  for (i=0; i<n; i++)   g0[i]=g[i*10+j-1];
          if (j==10) flag=1;
       }
	   for (i=0; i<n; i++)  y[i]=s1[i];
	   delete[] b; delete[] hh; delete[] g;
	   delete[] s0; delete[] s1; delete[] g0; delete[] yy;
       return;
  }
/*
//求解一阶初值连分式法例
  #include <iostream>
  #include <cmath>
  #include <iomanip>
//  #include "求解一阶初值连分式法.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double t,h,eps,y[2];
      void  pqeulerf(double, double [], int, double []);
      t=0.0; h=0.1; eps=0.0000001;
      y[0]=1.0; y[1]=0.0;
      cout <<"t = " <<t;
      for (i=0; i<=1; i++)
		  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
      cout <<endl;
      for (j=1; j<=10; j++)
      { 
		  pqeuler(t,h,2,y,eps,pqeulerf);
          t=t+h;
          cout <<"t = " <<t;
          for (i=0; i<=1; i++)
			  cout <<"  y(" <<i <<") = " <<setw(10) <<y[i];
          cout <<endl;
      }
	  return 0;
  }

  void pqeulerf(double t,double y[],int n,double d[])
  { 
	  t=t; n=n;
	  d[0]=-y[1]; d[1]=y[0];
	  return;
  }
*/
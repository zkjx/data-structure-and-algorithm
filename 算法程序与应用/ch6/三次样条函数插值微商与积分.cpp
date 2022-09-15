//三次样条函数插值微商与积分.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//n            给定结点个数。
//x[n]         存放给定n个结点值。
//y[n]         存放给定n个结点上的函数值。当flag=3时，要求y[0]=y[n-1],dy[0]=dy[n-1],ddy[0]=ddy[n-1]。
//dy[n]        返回给定n个结点上的一阶导数值。当flag=1时，要求dy[0]与dy[n-1]给定。
//ddy[n]       返回给定n个结点上的二阶导数值。当flag=2时，要求ddy[0]与ddy[n-1]给定。
//m            指定插值点个数。
//t[m]         存放定m个插值点值。
//z[m]         返回指定m个插值点上的函数值。
//dz[m]        返回指定m个插值点上的一阶导数值。
//ddz[m]       返回指定m个插值点上的二阶导数值。
//flag         边界条件类型。
  //函数返回积分值。
  double splin(int n, double x[], double y[], double dy[], double ddy[],
	           int m, double t[], double z[], double dz[], double ddz[], int flag)
  { 
	  int i,j;
      double h0,h1,alpha,beta,g,y0,y1,u,*s;
      s = new double[n];
//计算给定n个结点上的一阶导数值
      if (flag == 1)              //第一种边界类型
	  {
		  s[0]=dy[0]; dy[0]=0.0;
          h0=x[1]-x[0];
          for (j=1;j<=n-2;j++)
		  { 
			  h1=x[j+1]-x[j];
              alpha=h0/(h0+h1);
              beta=(1.0-alpha)*(y[j]-y[j-1])/h0;
              beta=3.0*(beta+alpha*(y[j+1]-y[j])/h1);
              dy[j]=-alpha/(2.0+(1.0-alpha)*dy[j-1]);
              s[j]=(beta-(1.0-alpha)*s[j-1]);
              s[j]=s[j]/(2.0+(1.0-alpha)*dy[j-1]);
              h0=h1;
		  }
          for (j=n-2;j>=0;j--)
              dy[j]=dy[j]*dy[j+1]+s[j];
	  }
	  else if (flag == 2)        //第二种边界类型
	  {
		  dy[0]=-0.5;
          h0=x[1]-x[0];
          s[0]=3.0*(y[1]-y[0])/(2.0*h0)-ddy[0]*h0/4.0;
          for (j=1;j<=n-2;j++)
		  { 
			  h1=x[j+1]-x[j];
              alpha=h0/(h0+h1);
              beta=(1.0-alpha)*(y[j]-y[j-1])/h0;
              beta=3.0*(beta+alpha*(y[j+1]-y[j])/h1);
              dy[j]=-alpha/(2.0+(1.0-alpha)*dy[j-1]);
              s[j]=(beta-(1.0-alpha)*s[j-1]);
              s[j]=s[j]/(2.0+(1.0-alpha)*dy[j-1]);
              h0=h1;
		  }
          dy[n-1]=(3.0*(y[n-1]-y[n-2])/h1+ddy[n-1]*h1/
                   2.0-s[n-2])/(2.0+dy[n-2]);
          for (j=n-2;j>=0;j--)
              dy[j]=dy[j]*dy[j+1]+s[j];
	  }
	  else if (flag == 3)       //第三种边界类型
	  {
		  h0=x[n-1]-x[n-2];
          y0=y[n-1]-y[n-2];
          dy[0]=0.0; ddy[0]=0.0; ddy[n-1]=0.0;
          s[0]=1.0; s[n-1]=1.0;
          for (j=1;j<=n-1;j++)
		  { 
			  h1=h0; y1=y0;
              h0=x[j]-x[j-1];
              y0=y[j]-y[j-1];
              alpha=h1/(h1+h0);
              beta=3.0*((1.0-alpha)*y1/h1+alpha*y0/h0);
              if (j<n-1)
			  { 
				  u=2.0+(1.0-alpha)*dy[j-1];
                  dy[j]=-alpha/u;
                  s[j]=(alpha-1.0)*s[j-1]/u;
                  ddy[j]=(beta-(1.0-alpha)*ddy[j-1])/u;
			  }
		  }
          for (j=n-2;j>=1;j--)
		  { 
			  s[j]=dy[j]*s[j+1]+s[j];
              ddy[j]=dy[j]*ddy[j+1]+ddy[j];
		  }
          dy[n-2]=(beta-alpha*ddy[1]-(1.0-alpha)*ddy[n-2])/
                  (alpha*s[1]+(1.0-alpha)*s[n-2]+2.0);
          for (j=2;j<=n-1;j++)
              dy[j-2]=s[j-1]*dy[n-2]+ddy[j-1];
          dy[n-1]=dy[0];
	  }
	  else
	  {
		  cout <<"没有这种边界类型！" <<endl;
		  delete[] s; return(0.0);
	  }
//计算n个给定结点上的二阶导数值
      for (j=0;j<=n-2;j++) s[j]=x[j+1]-x[j];
      for (j=0;j<=n-2;j++)
      { 
		  h1=s[j]*s[j];
          ddy[j]=6.0*(y[j+1]-y[j])/h1-2.0*(2.0*dy[j]+dy[j+1])/s[j];
      }
      h1=s[n-2]*s[n-2];
      ddy[n-1]=6.*(y[n-2]-y[n-1])/h1+2.*(2.*dy[n-1]+dy[n-2])/s[n-2];
//计算插值区间上的积分
      g=0.0;
      for (i=0;i<=n-2;i++)
      { 
		  h1=0.5*s[i]*(y[i]+y[i+1]);
          h1=h1-s[i]*s[i]*s[i]*(ddy[i]+ddy[i+1])/24.0;
          g=g+h1;
      }
//计算m个指定插值点处的函数值，一阶导数值以及二阶导数值
      for (j=0;j<=m-1;j++)
      { 
		  if (t[j]>=x[n-1]) i=n-2;
          else
          { 
			  i=0;
              while (t[j]>x[i+1]) i=i+1;
          }
          h1=(x[i+1]-t[j])/s[i];
          h0=h1*h1;
          z[j]=(3.0*h0-2.0*h0*h1)*y[i];
          z[j]=z[j]+s[i]*(h0-h0*h1)*dy[i];
          dz[j]=6.0*(h0-h1)*y[i]/s[i];
          dz[j]=dz[j]+(3.0*h0-2.0*h1)*dy[i];
          ddz[j]=(6.0-12.0*h1)*y[i]/(s[i]*s[i]);
          ddz[j]=ddz[j]+(2.0-6.0*h1)*dy[i]/s[i];
          h1=(t[j]-x[i])/s[i];
          h0=h1*h1;
          z[j]=z[j]+(3.0*h0-2.0*h0*h1)*y[i+1];
          z[j]=z[j]-s[i]*(h0-h0*h1)*dy[i+1];
          dz[j]=dz[j]-6.0*(h0-h1)*y[i+1]/s[i];
          dz[j]=dz[j]+(3.0*h0-2.0*h1)*dy[i+1];
          ddz[j]=ddz[j]+(6.0-12.0*h1)*y[i+1]/(s[i]*s[i]);
          ddz[j]=ddz[j]-(2.0-6.0*h1)*dy[i+1]/s[i];
	  }
      delete[] s;
      return(g);
  }

/*
//第一种边界条件例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "三次样条函数插值微商与积分.cpp"
  using namespace std;
  int main()
  { 
	  int n,m,i;
      double s;
      double dy[12],ddy[12],z[8],dz[8],ddz[8];
      double x[12]={0.52,8.0,17.95,28.65,50.65,104.6,
                       156.6,260.7,364.4,468.0,507.0,520.0};
      double y[12]={5.28794,13.84,20.2,24.9,31.1,36.5,
                         36.6,31.0,20.9,7.8,1.5,0.2};
      double t[8]={4.0,14.0,30.0,60.0,130.0,230.0,
                        450.0,515.0};
      dy[0]=1.86548; dy[11]=-0.046115;
      n=12; m=8;
      s = splin(n, x, y, dy, ddy, m, t, z, dz, ddz, 1);
      cout <<setw(15) <<"x[i]" <<setw(15) <<"y[i]" <<setw(15) 
		   <<"dy[i]" <<setw(15) <<"ddy[i]" <<endl;
      for (i=0;i<=11;i++)
		  cout <<setw(15) <<x[i] <<setw(15) <<y[i] <<setw(15) 
		       <<dy[i] <<setw(15) <<ddy[i] <<endl;
      cout <<"s = " <<s <<endl;
      cout <<setw(15) <<"t[i]" <<setw(15) <<"z[i]" <<setw(15) 
		   <<"dz[i]" <<setw(15) <<"ddz[i]" <<endl;
      for (i=0;i<=7;i++)
		  cout <<setw(15) <<t[i] <<setw(15) <<z[i] <<setw(15) 
		       <<dz[i] <<setw(15) <<ddz[i] <<endl;
      return 0;
  }
*/
/*
//第二种边界条件例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "三次样条函数插值微商与积分.cpp"
  using namespace std;
  int main()
  { 
	  int n,m,i;
      double s;
      double dy[12],ddy[12],z[8],dz[8],ddz[8];
      double x[12]={0.52,8.0,17.95,28.65,50.65,104.6,
                       156.6,260.7,364.4,468.0,507.0,520.0};
      double y[12]={5.28794,13.84,20.2,24.9,31.1,36.5,
                         36.6,31.0,20.9,7.8,1.5,0.2};
      double t[8]={4.0,14.0,30.0,60.0,130.0,230.0,
                        450.0,515.0};
      ddy[0]=-0.279319; ddy[11]=0.011156;
      n=12; m=8;
      s = splin(n, x, y, dy, ddy, m, t, z, dz, ddz, 2);
      cout <<setw(15) <<"x[i]" <<setw(15) <<"y[i]" <<setw(15) 
		   <<"dy[i]" <<setw(15) <<"ddy[i]" <<endl;
      for (i=0;i<=11;i++)
		  cout <<setw(15) <<x[i] <<setw(15) <<y[i] <<setw(15) 
		       <<dy[i] <<setw(15) <<ddy[i] <<endl;
      cout <<"s = " <<s <<endl;
      cout <<setw(15) <<"t[i]" <<setw(15) <<"z[i]" <<setw(15) 
		   <<"dz[i]" <<setw(15) <<"ddz[i]" <<endl;
      for (i=0;i<=7;i++)
		  cout <<setw(15) <<t[i] <<setw(15) <<z[i] <<setw(15) 
		       <<dz[i] <<setw(15) <<ddz[i] <<endl;
      return 0;
  }
*/
/*
//第三种边界条件例
  #include <cmath>
  #include <iostream>
  #include <iomanip>
//  #include "三次样条函数插值微商与积分.cpp"
  using namespace std;
  int main()
  { 
	  int n,m,i,j;
      double u,s;
      double x[37],y[37],dy[37],ddy[37];
      double t[36],z[36],dz[36],ddz[36];
      for (i=0;i<=36;i++)
      { 
		  x[i]=i*6.2831852/36.0; y[i]=sin(x[i]);
      }
      for (i=0;i<=35;i++)  t[i]=(0.5+i)*6.2831852/36.0;
      n=37; m=36;
      s = splin(n, x, y, dy, ddy, m, t, z, dz, ddz, 3);
      cout <<setw(15) <<"x[i]" <<setw(15) <<"y[i]=sin(x)" <<setw(15) 
		   <<"dy[i]" <<setw(15) <<"ddy[i]" <<endl;
      cout <<setw(15) <<x[0] <<setw(15) <<y[0] <<setw(15) 
		   <<dy[0] <<setw(15) <<ddy[0] <<endl;
      for (i=0;i<=35;i++)
	  {
		  u=t[i]*36.0/0.62831852;       //弧度化为度
		  cout <<setw(15) <<u <<setw(15) <<z[i] <<setw(15) 
		       <<dz[i] <<setw(15) <<ddz[i] <<endl;
		  u=x[i+1]*36.0/0.62831852;     //弧度化为度
          j=i+1;
		  cout <<setw(15) <<u <<setw(15) <<y[j] <<setw(15) 
		       <<dy[j] <<setw(15) <<ddy[j] <<endl;
	  }
      cout <<"s = " <<s <<endl;
      return 0;
  }
*/
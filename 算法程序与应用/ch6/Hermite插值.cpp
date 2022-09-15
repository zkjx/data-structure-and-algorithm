//Hermite插值.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//x[n]         存放n个给定的有序结点值。
//y[n]         存放n个给定结点上的函数值。
//dy[n]        存放n个给定结点上的一阶导数值。
//n            给定结点的个数。
//t            指定插值点值。
  //函数返回指定插值点t处的函数近似值。
  double hermite(double x[], double y[], double dy[], int n, double t)
  { 
	  int i,j;
      double z,p,q,s;
      z=0.0;
      for (i=1;i<=n;i++)
      { 
		  s=1.0;
          for (j=1;j<=n;j++)
            if (j!=i) s=s*(t-x[j-1])/(x[i-1]-x[j-1]);
          s=s*s;
          p=0.0;
          for (j=1;j<=n;j++)
            if (j!=i) p=p+1.0/(x[i-1]-x[j-1]);
          q=y[i-1]+(t-x[i-1])*(dy[i-1]-2.0*y[i-1]*p);
          z=z+q*s;
      }
      return(z);
  }
/*
//Hermite插值例
  #include <cmath>
  #include <iostream>
//  #include "Hermite插值.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double t,z;
      double x[10]={0.1,0.15,0.3,0.45,0.55,0.6,0.7,0.85,0.9,1.0};
      double y[10]={0.904837,0.860708,0.740818,0.637628,0.576950,
                       0.548812,0.496585,0.427415,0.406570,0.367879};
      double dy[10];
      for (i=0;i<=9;i++) dy[i]=-y[i];
      t=0.356; z=hermite(x,y,dy,10,t);
      cout <<"t = " <<t <<"     z = " <<z <<endl;
      return 0;
  }
*/
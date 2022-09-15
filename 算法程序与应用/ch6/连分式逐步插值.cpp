//连分式逐步插值.cpp
  #include <cmath>
  #include <iostream>
  #include "计算函数连分式新一节.cpp"
  #include "计算函数连分式值.cpp"
  using namespace std;
//x[n]      存放结点值x[0]～x[n-1]
//y[n]      存放结点函数值y[0]～y[n-1]
//n         数据点个数。实际插值时最多取离插值点t最近的八个点。
//eps       精度要求
//t         插值点值
  //返回插值点t处的连分式函数值
  double funpq(double x[],double y[],int n,double eps,double t)
  { 
	  int i,j,k,l,m;
      double p,q,u;
	  double b[8],xx[8],yy[8];  //最多取离插值点t最近的八个点
      p=0.0;
      if (n<1) return(p);              //结点个数不对，返回
      if (n==1) { p=y[0]; return(p);}  //只有一个结点，取值返回
      m=8;                            //最多取8个点
      if (m>n) m=n;
      if (t<=x[0]) k=1;                //第一个结点离插值点最近
      else if (t>=x[n-1]) k=n;         //最后一个结点离插值点最近
      else
      { 
		  k=1; j=n;
          while ((k-j!=1)&&(k-j!=-1))  //二分法寻找离插值点最近的点
          { 
			  l=(k+j)/2;
              if (t<x[l-1]) j=l;
              else k=l;
          }
          if (fabs(t-x[l-1])>fabs(t-x[j-1])) k=j;
      }
      j=1; l=0;
      for (i=1;i<=m;i++)          //从数据表中取m个结点
      { 
		  k=k+j*l;
          if ((k<1)||(k>n))
          { 
			  l=l+1; j=-j; k=k+j*l;
		  }
          xx[i-1]=x[k-1]; yy[i-1]=y[k-1];
          l=l+1; j=-j;
      }
      j=0; b[0]=yy[0]; p=b[0];
	  u=1.0+eps;
	  while ((j<m-1)&&(u>=eps))
	  {
		  j=j+1;
		  funpqj(xx,yy,b,j);       //计算新一节的b[j]
          q=funpqv(xx,b,j,t);      //计算函数连分式在t处的函数值
		  u=(fabs(q-p));
		  p=q;
	  }
      return(p);
  }
/*
//连分式逐步插值例
  #include <cmath>
  #include <iostream>
//  #include "连分式逐步插值.cpp"
  using namespace std;
  int main()
  {
	  double t,z;
      double x[10]={-1.0,-0.8,-0.65,-0.4,-0.3,
                         0.0,0.2,0.45,0.8,1.0};
      double y[10]={0.0384615,0.0588236,0.0864865,0.2,0.307692,
                         1.0,0.5,0.164948,0.0588236,0.0384615};
      t=-0.85; z=funpq(x,y,10,0.0000001,t);
      cout <<"t = " <<t <<"      z = " <<z <<endl;
	  t=0.25; z=funpq(x,y,10,0.0000001,t);
      cout <<"t = " <<t <<"      z = " <<z <<endl;
	  return 0;
  }
*/

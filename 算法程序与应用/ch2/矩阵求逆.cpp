//矩阵求逆.cpp
  #include "复数运算类.h"
  #include <cmath>
  #include <iostream>
  using namespace std;
  double ffabs(double p)        //计算实数的绝对值
  {
	  double q;
	  q = fabs(p);
	  return(q);
  }
  double ffabs(complex p)      //计算复数的模
  {
	  double q;
	  q = p.cfabs();
	  return(q);
  }
  double ff(double p)         //计算1.0/p
  {
	  double q;
	  q = 1.0/p;
	  return(q);
  }
  complex ff(complex p)       //计算(1+j0)/p
  {
	  complex q;
	  q = complex(1.0, 0.0)/p;
	  return(q);
  }
//a   原矩阵。返回逆矩阵。
//n   矩阵阶数
  template <class T>        //模板声明T为类型参数
  int inv(T a[], int n)       //若矩阵奇异，则返回标志值0，否则返回标志值非0。
  { 
	  int *is,*js,i,j,k,l,u,v;
	  double d, q;
      T p;
      is=new int[n];
      js=new int[n];
      for (k=0; k<=n-1; k++)
      { 
		  d=0.0;
          for (i=k; i<=n-1; i++)      //选主元
          for (j=k; j<=n-1; j++)
          { 
			  l=i*n+j; 
			  q = ffabs(a[l]);        //计算元素绝对值（模）
              if (q>d) { d=q; is[k]=i; js[k]=j;}
          }
          if (d+1.0==1.0)            //矩阵奇异
          { 
			  delete[] is; delete[] js; 
			  cout <<"矩阵奇异！" <<endl;
              return(0);             //返回奇异标志值
          }
          if (is[k]!=k)
            for (j=0; j<=n-1; j++)     //行交换
            { 
				u=k*n+j; v=is[k]*n+j;
                p=a[u]; a[u]=a[v]; a[v]=p;
            }
          if (js[k]!=k)
            for (i=0; i<=n-1; i++)     //列交换
            { 
				u=i*n+k; v=i*n+js[k];
                p=a[u]; a[u]=a[v]; a[v]=p;
            }
          l=k*n+k;
          a[l] = ff(a[l]);            //计算1/a[l]
          for (j=0; j<=n-1; j++)      //归一化
            if (j!=k)
            { u=k*n+j; a[u]=a[u]*a[l];}
          for (i=0; i<=n-1; i++)      //消元计算
          if (i!=k)
            for (j=0; j<=n-1; j++)
              if (j!=k)
              { 
				  u=i*n+j;
                  a[u]=a[u]-a[i*n+k]*a[k*n+j];
              }
          for (i=0; i<=n-1; i++)
            if (i!=k)
            { u=i*n+k; a[u]=(a[u]-a[u]-a[u])*a[l];}
      }
      for (k=n-1; k>=0; k--)      //恢复行列交换
      { 
		  if (js[k]!=k)
            for (j=0; j<=n-1; j++)
            { 
				u=k*n+j; v=js[k]*n+j;
				p=a[u]; a[u]=a[v]; a[v]=p;
            }
          if (is[k]!=k)
            for (i=0; i<=n-1; i++)
            {
				u=i*n+k; v=i*n+is[k];
                p=a[u]; a[u]=a[v]; a[v]=p;
            }
      }
      delete[] is; delete[] js;
      return(1);
  }


/*
//实矩阵求逆例
  #include <cmath>
  #include <iostream>
//  #include "矩阵求逆.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double a[4][4]={ {0.2368,0.2471,0.2568,1.2671},
                            {1.1161,0.1254,0.1397,0.1490},
                            {0.1582,1.1675,0.1768,0.1871},
                            {0.1968,0.2071,1.2168,0.2271}};
      double b[4][4];
      for (i=0; i<=3; i++)
      for (j=0; j<=3; j++)  b[i][j]=a[i][j];
      i=inv(&b[0][0],4);
      if (i!=0)
      { 
		  cout <<"实矩阵 A:" <<endl;
          for (i=0; i<=3; i++)
          { 
			  for (j=0; j<=3; j++)  cout <<a[i][j]<<"    ";
              cout <<endl;
          }
          cout <<"逆矩阵 A-:" <<endl;;
          for (i=0; i<=3; i++)
          { 
			  for (j=0; j<=3; j++)  cout <<b[i][j]<<"    ";
              cout <<endl;
          }
	  }
	  return 0;
  }
*/
/*
//复矩阵求逆例
  #include <cmath>
  #include <iostream>
//  #include "矩阵求逆.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      complex b[4][4];
      complex a[4][4]=
	  { {complex(0.2368,0.1345),complex(0.2471,0.1678),
	            complex(0.2568,0.1875),complex(1.2671,1.1161)},
        {complex(1.1161,1.2671),complex(0.1254,0.2017),
		        complex(0.1397,0.7024),complex(0.1490,0.2721)},
        {complex(0.1582,-0.2836),complex(1.1675,-1.1967),
		        complex(0.1768,0.3556),complex(0.1871,-0.2078)},
        {complex(0.1968,0.3576),complex(0.2071,-1.2345),
		        complex(1.2168,2.1185),complex(0.2271,0.4773)}
	  };
      for (i=0; i<=3; i++)
      for (j=0; j<=3; j++)  b[i][j]=a[i][j]; 
      i=inv(&b[0][0],4);
	  i = 1;
      if (i!=0)
      { 
		  cout <<"复矩阵 A:" <<endl;
          for (i=0; i<=3; i++)
          { 
			  for (j=0; j<=3; j++)  { a[i][j].prt(); cout <<"  "; }
              cout <<endl;
          }
		  cout <<"逆矩阵 A-:" <<endl;
          for (i=0; i<=3; i++)
          { 
			  for (j=0; j<=3; j++)  { b[i][j].prt(); cout <<"  "; }
              cout <<endl;
          }
	  }
	  return 0;
  }
*/
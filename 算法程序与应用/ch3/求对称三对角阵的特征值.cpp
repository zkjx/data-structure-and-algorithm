//求对称三对角阵的特征值.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//b[n]       存放n阶实对称三角阵的主对角线上的元素。返回时存放全部特征值。
//c[n]       前n-1个元素存放实对称三角阵的次对角线上的元素。
//q[n][n]    若存放n阶单位矩阵，则返回实对称三对角阵T的特征向量组；
//           若存放由3.1节中的函数strq()所返回的一般实对称矩阵A的豪斯荷尔德
//           变换的乘积矩阵Q，则返回实对称矩阵A的特征向量组。其中q中的第j列
//           为与数组b中第j个特征值对应的特征向量。
//eps        控制精度要求。
  //返回的标志值为迭代次数。本程序最多迭代100次。
  int sstq(int n,double b[],double c[],double q[],double eps)
  { 
	  int i,j,k,m,it,u,v;
      double d,f,h,g,p,r,e,s;
      c[n-1]=0.0; d=0.0; f=0.0;
      for (j=0; j<=n-1; j++)
      { 
		  it=0;
          h=eps*(fabs(b[j])+fabs(c[j]));
          if (h>d) d=h;
          m=j;
          while ((m<=n-1)&&(fabs(c[m])>d)) m=m+1;
          if (m!=j)
          { 
			  do
              { 
				  if (it==100)
                  { 
					  cout <<"迭代了100次！\n";  return(it);
				  }
                  it=it+1;
                  g=b[j];
                  p=(b[j+1]-g)/(2.0*c[j]);
                  r=sqrt(p*p+1.0);
                  if (p>=0.0) b[j]=c[j]/(p+r);
                  else b[j]=c[j]/(p-r);
                  h=g-b[j];
                  for (i=j+1; i<=n-1; i++)  b[i]=b[i]-h;
                  f=f+h; p=b[m]; e=1.0; s=0.0;
                  for (i=m-1; i>=j; i--)
                  { 
					  g=e*c[i]; h=e*p;
                      if (fabs(p)>=fabs(c[i]))
                      { 
						  e=c[i]/p; r=sqrt(e*e+1.0);
                          c[i+1]=s*p*r; s=e/r; e=1.0/r;
                      }
                      else
					  { 
						  e=p/c[i]; r=sqrt(e*e+1.0);
                          c[i+1]=s*c[i]*r;
                          s=1.0/r; e=e/r;
                      }
                      p=e*b[i]-s*g;
                      b[i+1]=h+s*(e*g+s*b[i]);
                      for (k=0; k<=n-1; k++)
                      { 
						  u=k*n+i+1; v=u-1;
                          h=q[u]; q[u]=s*q[v]+e*h;
                          q[v]=e*q[v]-s*h;
                      }
				  }
                  c[j]=s*p; b[j]=e*p;
			  }
              while (fabs(c[j])>d);
		  }
          b[j]=b[j]+f;
      }
      for (i=0; i<=n-1; i++)
      {
		  k=i; p=b[i];
          if (i+1<=n-1)
          { 
			  j=i+1;
              while ((j<=n-1)&&(b[j]<=p))
              { k=j; p=b[j]; j=j+1;}
          }
          if (k!=i)
          {
			  b[k]=b[i]; b[i]=p;
              for (j=0; j<=n-1; j++)
              { 
				  u=j*n+i; v=j*n+k;
                  p=q[u]; q[u]=q[v]; q[v]=p;
              }
          }
      }
      return(it);
  }

/*
  #include <cmath>
  #include <iostream>
  #include "约化对称矩阵为三对角阵.cpp"
//  #include "求对称三对角阵的特征值.cpp"
  using namespace std;
  int main()
  { 
	  int i,j,k;
      double q[5][5],b[5],c[5];
      double a[5][5]={ {10.0,1.0,2.0,3.0,4.0},
       {1.0,9.0,-1.0,2.0,-3.0},
	  {2.0,-1.0,7.0,3.0,-5.0},
       {3.0,2.0,3.0,12.0,-1.0},
	  {4.0,-3.0,-5.0,-1.0,15.0}};
      double eps=0.000001;
      i=strq(&a[0][0],5,&q[0][0],b,c);   //约化对称矩阵A为三对角阵
	  if (i==0)  return 0;
      cout <<"原对称矩阵 A:\n";
      for (i=0; i<=4; i++)
      { 
		  for (j=0; j<=4; j++)  cout <<a[i][j] <<"    ";
          cout <<endl;
      }
	  cout <<"乘积矩阵 Q:\n";
      for (i=0; i<=4; i++)
      { 
		  for (j=0; j<=4; j++)  cout <<q[i][j] <<"    ";
          cout <<endl;
      }
      cout <<"对称三对角阵主对角线元素:\n";
      for (i=0; i<=4; i++)  cout <<b[i] <<"    ";
      cout <<endl;
      cout <<"对称三对角阵次对角线元素:\n";
      for (i=0; i<=4; i++)  cout <<c[i] <<"    ";
      cout <<endl;
      k=sstq(5,b,c,&q[0][0],eps);    //求对称矩阵A的特征值
      cout <<"迭代次数= " <<k <<endl;
	  cout <<"对称矩阵A的特征值:\n";
      for (i=0; i<=4; i++)  cout <<b[i] <<"    ";
      cout <<endl;
      cout <<"对称矩阵A的特征向量组:\n";
      for (i=0; i<=4; i++)
      { 
		  for (j=0; j<=4; j++)  cout <<q[i][j] <<"    ";
          cout <<endl;
      }
      return 0;
  }
*/
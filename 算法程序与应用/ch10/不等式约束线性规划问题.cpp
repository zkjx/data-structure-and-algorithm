//不等式约束线性规划问题.cpp
  #include <iostream>
  #include <cmath>
  #include "实矩阵求逆.cpp"
  #include "实矩阵相乘.cpp"
  using namespace std;
//m             不等式约束条件个数。
//n             变量个数。
//a[m][m+n]     左边n列存放不等式约束条件左端的系数矩阵，右边m列为单位矩阵。
//b[m]          存放不等式约束条件右端项值。
//c[m+n]        存放目标函数中的系数，其中后m个分量为0。
//x[m+n]        前n个分量返回目标函数f的极小值点的n个坐标；
//              第n+1个分量返回目标函数f的极小值。
  //函数返回标志值。若=0表示矩阵求逆失败，若<0表示目标函数值无界，若>0正常。
  int lplq(int m,int n, double a[], double b[], double c[], double x[])
  { 
	  int i,mn,k,j,*js;
      double s,z,dd,y,*p,*d;
      js=new int[m];
      p=new double[m*m];
      d=new double[m*(m+n)];
      for (i=0; i<=m-1; i++) js[i]=n+i;
      mn=m+n; s=0.0;
      while (1==1)
      { 
		  for (i=0; i<=m-1; i++)
          for (j=0; j<=m-1; j++)  p[i*m+j]=a[i*mn+js[j]];
          k=inv(p,m);
          if (k==0)
          { 
			  x[n]=s; 
			  delete[] js; delete[] p; delete[] d; return(k);
          }
          tmul(p,m,m,a,m,mn,d);
          for (i=0; i<=mn-1; i++) x[i]=0.0;
          for (i=0; i<=m-1; i++)
          { 
			  s=0.0;
              for (j=0; j<=m-1; j++) s=s+p[i*m+j]*b[j];
              x[js[i]]=s;
          }
          k=-1; dd=1.0e-35;
          for (j=0; j<=mn-1; j++)
          { 
			  z=0.0;
              for (i=0; i<=m-1; i++) z=z+c[js[i]]*d[i*mn+j];
              z=z-c[j];
              if (z>dd) { dd=z; k=j;}
          }
          if (k==-1)
          { 
			  s=0.0;
              for (j=0; j<=n-1; j++)  s=s+c[j]*x[j];
	          x[n]=s; 
			  delete[] js; delete[] p; delete[] d; return(1);
          }
          j=-1;
          dd=1.0e+20;
          for (i=0; i<=m-1; i++)
          if (d[i*mn+k]>=1.0e-20)
          { 
			  y=x[js[i]]/d[i*mn+k];
              if (y<dd) { dd=y; j=i;}
          }
          if (j==-1) 
          { 
			  x[n]=s; 
			  delete[] js; delete[] p; delete[] d; return(-1);
          }
          js[j]=k;
      }
	  return 0;
  }
/*
//不等式约束线性规划问题例
  #include <iostream>
  #include <cmath>
//  #include "不等式约束线性规划问题.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double x[6];
      double a[3][6]={ {1.0,2.0,7.0,1.0,0.0,0.0},
	  {1.0,4.0,13.0,0.0,1.0,0.0},
	  {0.0,2.0,8.0,0.0,0.0,1.0}};
      double b[3]={10.0,18.0,13.0};
      double c[6]={-4.0,-9.0,-26.0,0.0,0.0,0.0};
      i=lplq(3,3,&a[0][0],b,c,x);
      if (i>0)
      { 
		  cout <<"目标函数极小值点 :" <<endl;
		  for (i=0; i<=2; i++) 
			  cout <<"x(" <<i <<")=" <<x[i] <<endl;
		  cout <<"目标函数极小值 = " <<x[3] <<endl;
      }
	  return 0;
  }
*/
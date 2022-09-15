//切比雪夫曲线拟合.cpp
  #include <iostream>
  #include <cmath>
  using namespace std;
//x[n]       存放给定数据点的X坐标。
//y[n]       存放给定数据点的Y坐标。
//n          给定数据点的个数。
//a[m]       返回m - 1次拟合多项式的系数。
//m          拟合多项式的项数。要求m<=min(n,20)。
  //函数返回拟合多项式的偏差最大值。
  double chir(double x[], double y[], int n, double a[], int m)
  { 
	  int m1,i,j,l,ii,k,im,ix[21];
      double h[21],ha,hh,y1,y2,h1,h2,d,hm;
	  double b[21];
      for (i=0; i<m; i++) b[i]=0.0;
      if (m>n) m=n;
      if (m>20) m=20;
      m1=m+1;
      ha=0.0;
      ix[0]=0; ix[m]=n-1;
      l=(n-1)/m; j=l;
      for (i=1; i<=m-1; i++)
      { ix[i]=j; j=j+l;}
      while (1==1)
      { 
		  hh=1.0;
          for (i=0; i<=m; i++)
          { b[i]=y[ix[i]]; h[i]=-hh; hh=-hh;}
          for (j=1; j<=m; j++)
          { 
			  ii=m1; y2=b[ii-1]; h2=h[ii-1];
              for (i=j; i<=m; i++)
              { 
				  d=x[ix[ii-1]]-x[ix[m1-i-1]];
                  y1=b[m-i+j-1];
                  h1=h[m-i+j-1];
                  b[ii-1]=(y2-y1)/d;
                  h[ii-1]=(h2-h1)/d;
                  ii=m-i+j; y2=y1; h2=h1;
              }
          }
          hh=-b[m]/h[m];
          for (i=0; i<=m; i++) b[i]=b[i]+h[i]*hh;
          for (j=1; j<=m-1; j++)
          { 
			  ii=m-j; d=x[ix[ii-1]];
              y2=b[ii-1];
              for (k=m1-j; k<=m; k++)
              { 
				  y1=b[k-1]; b[ii-1]=y2-d*y1;
                  y2=y1; ii=k;
              }
          }
          hm=fabs(hh);
          if (hm<=ha) 
		  { 
			  for (i=0; i<m; i++) a[i] = b[i];
			  return(-hm);
		  }
          b[m]=hm; ha=hm; im=ix[0]; h1=hh;
          j=0;
          for (i=0; i<=n-1; i++)
          { 
			  if (i==ix[j]) { if (j<m) j=j+1;}
              else
              { 
				  h2=b[m-1];
                  for (k=m-2; k>=0; k--)  h2=h2*x[i]+b[k];
                  h2=h2-y[i];
                  if (fabs(h2)>hm)
                  { hm=fabs(h2); h1=h2; im=i;}
              }
          }
          if (im==ix[0]) 
		  {
			  for (i=0; i<m; i++)  a[i] = b[i];
			  return(b[m]);
		  }
          i=0;l=1;
          while (l==1)
          { 
			  l=0;
              if (im>=ix[i])
              { 
				  i=i+1;
                  if (i<=m) l=1;
              }
          }
          if (i>m) i=m;
          if (i==(i/2)*2) h2=-hh;
          else h2=hh;
          if (h1*h2>=0.0) ix[i]=im;
          else
          { 
			  if (im<ix[0])
              { 
				  for (j=m-1; j>=0; j--)  ix[j+1]=ix[j];
                  ix[0]=im;
              }
              else
              { 
				  if (im>ix[m])
                  { 
					  for (j=1; j<=m; j++)  ix[j-1]=ix[j];
                      ix[m]=im;
                  }
                  else ix[i-1]=im;
              }
          }
      }
  }

/*
//切比雪夫曲线拟合例
  #include <iostream>
  #include <cmath>
//  #include "切比雪夫曲线拟合.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      double x[101],y[101],a[6], p;
      for (i=0; i<=100; i++)
      { 
		  x[i]=-1.0+0.02*i;  y[i]=atan(x[i]);
      }
      p = chir(x,y,101,a,6);
	  cout <<"拟合多项式系数 :" <<endl;
      for (i=0; i<6; i++)
          cout <<"a(" <<i <<") = " <<a[i] <<endl;
      cout <<"偏差最大值 = " <<p <<endl;
      return 0;
  }
*/

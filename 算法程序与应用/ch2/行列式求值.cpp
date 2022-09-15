//行列式求值.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//a[n][n]       存放方阵A的元素。返回时被破坏。
  //函数返回行列式值。
  double sdet(double a[],int n)
  { int i,j,k,is,js,l,u,v;
    double f,det,q,d;
    f=1.0; det=1.0;
    for (k=0; k<=n-2; k++)
      { q=0.0;
        for (i=k; i<=n-1; i++)
        for (j=k; j<=n-1; j++)
          { l=i*n+j; d=fabs(a[l]);
	    if (d>q) { q=d; is=i; js=j;}
          }
        if (q+1.0==1.0)
          { det=0.0; return(det);}
        if (is!=k)
          { f=-f;
            for (j=k; j<=n-1; j++)
              { u=k*n+j; v=is*n+j;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        if (js!=k)
          { f=-f;
            for (i=k; i<=n-1; i++)
              { u=i*n+js; v=i*n+k;
                d=a[u]; a[u]=a[v]; a[v]=d;
              }
          }
        l=k*n+k;
        det=det*a[l];
        for (i=k+1; i<=n-1; i++)
          { d=a[i*n+k]/a[l];
            for (j=k+1; j<=n-1; j++)
              { u=i*n+j;
                a[u]=a[u]-d*a[k*n+j];
              }
          }
      }
    det=f*det*a[n*n-1];
    return(det);
  }
/*
  #include <cmath>
  #include <iostream>
//  #include "行列式求值.cpp"
  using namespace std;
  int main()
  { 
	  double a[4][4]={ {1.0,2.0,3.0,4.0},
                            {5.0,6.0,7.0,8.0},
                            {9.0,10.0,11.0,12.0},
                            {13.0,14.0,15.0,16.0}};
      double b[4][4]={ {3.0,-3.0,-2.0,4.0},
                            {5.0,-5.0,1.0,8.0},
                            {11.0,8.0,5.0,-7.0},
                            {5.0,-1.0,-3.0,-1.0}};
      cout <<"det(A)=" <<sdet(&a[0][0], 4) <<endl;
      cout <<"det(B)=" <<sdet(&b[0][0], 4) <<endl;
	  return 0;
  }
*/


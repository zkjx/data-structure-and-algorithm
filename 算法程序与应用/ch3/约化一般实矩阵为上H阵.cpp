//约化一般实矩阵为上H阵.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//a[n][n]    一般实矩阵。返回上H矩阵。
  void hhbg(double a[],int n)
  { 
	  int i,j,k,u,v;
      double d,t;
      for (k=1; k<=n-2; k++)
      { 
		  d=0.0;
          for (j=k; j<=n-1; j++)
          {
			  u=j*n+k-1; t=a[u];
              if (fabs(t)>fabs(d))  { d=t; i=j;}
          }
          if (fabs(d)+1.0!=1.0)
          { 
			  if (i!=k)
              {
				  for (j=k-1; j<=n-1; j++)
                  {
					  u=i*n+j; v=k*n+j;
                      t=a[u]; a[u]=a[v]; a[v]=t;
                  }
                  for (j=0; j<=n-1; j++)
                  {
					  u=j*n+i; v=j*n+k;
                      t=a[u]; a[u]=a[v]; a[v]=t;
                  }
              }
              for (i=k+1; i<=n-1; i++)
              {
				  u=i*n+k-1; t=a[u]/d; a[u]=0.0;
                  for (j=k; j<=n-1; j++)
                  {
					  v=i*n+j;   a[v]=a[v]-t*a[k*n+j];
                  }
                  for (j=0; j<=n-1; j++)
                  { 
					  v=j*n+k;  a[v]=a[v]+t*a[j*n+i];
                  }
              }
          }
      }
      return;
  }

/*
  #include <cmath>
  #include <iostream>
//  #include "约化一般实矩阵为上H阵.cpp"
  using namespace std;
  int main()
  { 
	  int i,j;
      double a[5][5]={ {1.0,6.0,-3.0,-1.0,7.0},
      {8.0,-15.0,18.0,5.0,4.0},
	  {-2.0,11.0,9.0,15.0,20.0},
      {-13.0,2.0,21.0,30.0,-6.0},
	  {17.0,22.0,-5.0,3.0,6.0}};
      cout <<"原矩阵 A:\n";
      for (i=0; i<=4; i++)
      { 
		  for (j=0; j<=4; j++)  cout <<a[i][j] <<"    ";
          cout <<endl;;
      }
      hhbg(&a[0][0],5);
      cout <<"上H矩阵 A:\n";
      for (i=0; i<=4; i++)
      { 
		  for (j=0; j<=4; j++)  cout <<a[i][j] <<"    ";
          cout <<endl;;
      }
	  return 0;
  }
*/
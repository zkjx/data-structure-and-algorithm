//Toeplitz矩阵求逆.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//t[n]     存放T型矩阵中的元素t[0]～t[n-1]。
//tt[n]    后n-1个元素存放T型矩阵中tt[1]～tt[n-1]。
//b[n][n]  返回T型矩阵的逆矩阵。
  //函数返回标志值。0表示失败，大于0表示成功。
  int trch(double t[],double tt[],int n,double b[])
  { int i,j,k;
    double a,s,*c,*r,*p;
    c=new double[n];
    r=new double[n];
    p=new double[n];
    if (fabs(t[0])+1.0==1.0)
	{ delete[] c; delete[] r; delete[]p;
      cout <<"fail\n"; return(0);
    }
    a=t[0]; c[0]=tt[1]/t[0]; r[0]=t[1]/t[0];
    for (k=0; k<=n-3; k++)
      { s=0.0;
        for (j=1; j<=k+1; j++) s=s+c[k+1-j]*tt[j];
        s=(s-tt[k+2])/a;
	    for (i=0; i<=k; i++) p[i]=c[i]+s*r[k-i];
        c[k+1]=-s;
        s=0.0;
        for (j=1; j<=k+1; j++) s=s+r[k+1-j]*t[j];
        s=(s-t[k+2])/a;
        for (i=0; i<=k; i++)
          { r[i]=r[i]+s*c[k-i];
            c[k-i]=p[k-i];
          }
        r[k+1]=-s;
	    a=0.0;
        for (j=1; j<=k+2; j++) a=a+t[j]*c[j-1];
        a=t[0]-a;
        if (fabs(a)+1.0==1.0)
          { delete[] c; delete[] r; delete[]p;
            cout <<"fail\n"; return(0);
          }
      }
    b[0]=1.0/a;
    for (i=0; i<=n-2; i++)
      { k=i+1; j=(i+1)*n;
        b[k]=-r[i]/a; b[j]=-c[i]/a;
      }
    for (i=0; i<=n-2; i++)
    for (j=0; j<=n-2; j++)
      { k=(i+1)*n+j+1;
        b[k]=b[i*n+j]-c[i]*b[j+1];
        b[k]=b[k]+c[n-j-2]*b[n-i-1];
      }
    delete[] c; delete[] r; delete[]p;
    return(1);
  }
/*
  #include <cmath>
  #include <iostream>
//  #include "Toeplitz矩阵求逆.cpp"
  using namespace std;
  int main()
  { int n,i,j,k;
    double t[6]={10.0,5.0,4.0,3.0,2.0,1.0};
    double tt[6]={0.0,-1.0,-2.0,-3.0,-4.0,-5.0};
    double b[6][6],a[6][6];
    n=6;
    i=trch(t,tt,n,&b[0][0]);
    if (i>0)
    { 
		cout <<"B=inv(T):\n";
        for (i=0; i<=5; i++)
        { 
			for (j=0; j<=5; j++)  cout <<b[i][j] <<"  ";
            cout <<endl;
        }
        cout <<"A=T*B:\n";
        for (i=1; i<=6; i++)
        for (j=1; j<=6; j++)
        { 
			a[i-1][j-1]=0.0;
            for (k=1; k<=j-1; k++)
              a[i-1][j-1]=a[i-1][j-1]+b[i-1][k-1]*t[j-k];
            a[i-1][j-1]=a[i-1][j-1]+b[i-1][j-1]*t[0];
            for (k=j+1; k<=6; k++)
              a[i-1][j-1]=a[i-1][j-1]+b[i-1][k-1]*tt[k-j];
        }
        for (i=0; i<=5; i++)
        { 
			for (j=0; j<=5; j++)  cout <<a[i][j] <<"  ";
            cout <<endl;
        }
    }
	return 0;
  }
*/
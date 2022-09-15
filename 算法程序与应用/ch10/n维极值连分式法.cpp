//n维极值连分式法.cpp
  #include <cmath>
  #include <iostream>
  using namespace std;
//n         自变量个数。
//x[n]      存放极值点初值。返回极值点。
//eps       控制精度要求。
//f         计算目标函数值与各偏导数值的函数名。
  //函数返回标志值。若>0为极大值点；若<0为极小值点;若=0为鞍点。
  int maxn(int n, double x[], double eps, double (*f)(double [],int,int))
  { 
	  int i,j,m,kk,jt,il,k;
      double y[10],b[10],p,z,t,h1,h2,ff,dx;
      k = 0; jt=20; h2=0.0;
      while (jt!=0)
      { 
		  t=0.0;
          for (i=1; i<=n; i++)
          { 
			  ff=(*f)(x,n,i);  t=t+fabs(ff);
          }
          if (t<eps) jt=0;
          else
          { 
			  for (i=0; i<=n-1; i++)
              { 
				  il=5;
                  while (il!=0)
                  { 
					  j=0; t=x[i]; il=il-1;
                      while (j<=7)
                      { 
						  if (j<=2) z=t+j*0.01;
                          else z=h2;
                          x[i]=z;
                          ff=(*f)(x,n,i+1);
                          if (fabs(ff)+1.0==1.0) { j=10; il=0;}
                          else
                          {
							  h1=ff; h2=z;
                              if (j==0)  { y[0]=h1; b[0]=h2;}
                              else
                              { 
								  y[j]=h1; m=0; kk=0;
                                  while ((m==0)&&(kk<=j-1))
                                  { 
									  p=h2-b[kk];
                                      if (fabs(p)+1.0==1.0) m=1;
                                      else h2=(h1-y[kk])/p;
                                      kk=kk+1;
                                  }
                                  b[j]=h2;
                                  if (m!=0) b[j]=1.0e+35;
                                  h2=0.0;
                                  for (kk=j-1; kk>=0; kk--)  h2=-y[kk]/(b[kk+1]+h2);
                                  h2=h2+b[0];
                              }
                              j=j+1;
                          }
                      }
                      x[i]=h2; 
                  }
                  x[i]=z;
              }
              jt = jt - 1;
          }
      }
      k=1;
      ff=(*f)(x,n,0); x[n]=ff;
      dx=0.00001; t=x[0];
      x[0]=t+dx; h1=(*f)(x,n,0);
      x[0]=t-dx; h2=(*f)(x,n,0);
      x[0]=t;
      t=h1+h2-2.0*ff;
      if (t>0.0) k=-1;
      j=1; jt=1;
      while (jt==1)
      { 
		  j=j+1; dx=0.00001; jt=0;
          t=x[j-1];
          x[j-1]=t+dx; h2=(*f)(x,n,0);
          x[j-1]=t-dx; h1=(*f)(x,n,0);
          x[j-1]=t; t=h1+h2-2.0*ff;
          if ((t*k<0.0)&&(j<n)) jt=1;
      }
      if (t*k>0.0) k=0;
      return(k);
  }
/*
//n维极值连分式法例
  #include <cmath>
  #include <iostream>
//  #include "n维极值连分式法.cpp"
  using namespace std;
  int main()
  { 
	  int k,j;
      double eps,x[3];
      double maxnf(double [],int,int);
      eps=0.000001; x[0]=0.0; x[1]=0.0;
      k = maxn(2,x,eps,maxnf);
      cout <<"点 :" <<endl;
	  for (j=0; j<=1; j++) 
		  cout <<"x(" <<j <<") = " <<x[j] <<endl;
	  if (k == 0) cout <<"为鞍点" <<endl;
	  else if (k>0) cout <<"为极大值点" <<endl;
	  else cout <<"为极小值点" <<endl;
      cout <<"极值 = " <<maxnf(x,2,0) <<endl;
      return 0;
  }
//计算目标函数值与各偏导数值
  double maxnf(double x[], int n, int j)
  { 
	  double y;
      n=n;
      switch(j)
      { case 0: y=(x[0]-1.0)*(x[0]-10.0)
                  +(x[1]+2.0)*(x[1]+2.0)+2.0;
                break;
        case 1: y=2.0*(x[0]-1.0); break;
        case 2: y=2.0*(x[1]+2.0); break;
        default: {}
      }
      return(y);
  }
*/
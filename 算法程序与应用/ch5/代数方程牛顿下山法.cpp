//代数方程牛顿下山法.cpp
  #include "复数运算类.h"
  #include <cmath>
  #include <iostream>
  using namespace std;
//a[n+1]      存放n次多项式的n+1个复系数。
//n           多项式方程的次数。
//xx[n]       返回n个复根。
  //函数返回标志值。若<0则表示多项式为零次多项式；否则正常返回。
  int srrt(complex a[], int n, complex xx[])
  { 
	  int m,i,jt,k,is,it,flag;
	  complex  xy, xy1, dxy, uv, uv1;
      double t,p,q,w,dd,dc,c, g,pq,g1;
      m=n;
      while ((m>0)&&(a[m].cfabs()+1.0==1.0)) m=m-1;
      if (m<=0)
      { 
		  cout <<"零次多项式！" <<endl; 
		  return(-1);
	  }
      for (i=0; i<=m; i++)  a[i]=a[i]/a[m];   //归一化
      for (i=0; i<=m/2; i++)
      { 
		  xy=a[i]; a[i]=a[m-i]; a[m-i]=xy;
	  }
      k=m; is=0; w=1.0;
      jt=1;
      while (jt==1)
      { 
		  pq=a[k].cfabs();
	      while (pq<1.0e-12)
          { 
			  xx[k-1] = complex(0.0, 0.0); k=k-1;
              if (k==1)
              { 
				  xx[0] = complex (0.0,0.0)- a[1]*complex(w,0.0)/a[0];
                  return(1);
              }
              pq=a[k].cfabs();
          }
	      q=log(pq); q=q/(1.0*k); q=exp(q);
          p=q; w=w*p;
          for (i=1; i<=k; i++)
          { 
			  a[i]=a[i]/complex(q,0.0); 
			  q=q*p;
		  }
		  xy = complex(0.0001,0.2);
		  xy1 = xy;
		  dxy = complex(1.0,0.0);
          g=1.0e+37; 

      l40:
		  uv = a[0];
          for (i=1; i<=k; i++) uv = uv*xy1 + a[i];
		  g1 = (uv.cfabs())*(uv.cfabs());
          if (g1>=g)
          { 
			  if (is!=0)
              {
				  flag = 0;
                  while (flag==0)
				  {
					  c = c + dc;
					  dxy = complex(dd*cos(c), dd*sin(c)); 
					  xy1 = xy + dxy; 
					  if (c<=6.29) { flag = 1; it = 0;}
					  else 
					  {
						  dd = dd/1.67;
						  if (dd<=1.0e-007) { flag = 1; it = 1;}
					      else  c = 0.0;
					  }
				  }
                  if (it==0) goto l40;
			  }
              else
              {
				  it = 1;
				  while (it==1)
				  {
					  t = t/1.67; it = 0;
                      xy1 = xy - dxy*complex(t,0.0);
					  if (k>=30)
					  {
						  p = xy1.cfabs();
						  q = exp(75.0/k);
						  if (p>=q)  it = 1;
					  }
				  }
                  if (t>=1.0e-03) goto l40;
                  if (g>1.0e-18)
                  {
					  is = 1;
					  dd = dxy.cfabs();
					  if (dd>1.0)  dd = 1.0;
					  dc = 6.28/(4.5*k);  c = 0.0;
				      flag = 0;
                      while (flag==0)
					  {
						  c = c + dc;
						  dxy = complex(dd*cos(c), dd*sin(c));
						  xy1 = xy + dxy;
					      if (c<=6.29) { flag = 1; it = 0;}
					      else 
						  {
							  dd = dd/1.67;
						      if (dd<=1.0e-007) { flag = 1; it = 1;}
					          else  c = 0.0;
						  }
					  }
                      if (it==0) goto l40;
				  }
			  }
              for (i=1; i<=k; i++) a[i]=a[i] + a[i-1]*xy;
              xx[k-1] = xy*complex(w,0.0);
              k = k - 1;
              if (k==1) 
				  xx[0] = complex(0.0,0.0)- a[1]*complex(w,0.0)/a[0]; 
		  }
          else
		  { 
			  g=g1; is = 0; 
			  xy = xy1;
              if (g<=1.0e-22)
			  {
				  for (i=1; i<=k; i++) a[i]=a[i] + a[i-1]*xy;
                  xx[k-1] = xy*complex(w,0.0);
                  k = k - 1;
                  if (k==1) 
				        xx[0] = complex(0.0,0.0)- a[1]*complex(w,0.0)/a[0];
			  }
              else
              { 
				  uv1 = a[0]*complex(1.0*k, 0.0); 
                  for (i=2; i<=k; i++)
                      uv1 = uv1*xy + complex(k-i+1.0,0.0)*a[i-1];
                  p = (uv1.cfabs())*(uv1.cfabs());
                  if (p<=1.0e-20)
                  { 
					  is = 1;
					  dd = dxy.cfabs();
					  if (dd>1.0)  dd = 1.0;
					  dc = 6.28/(4.5*k);  c = 0.0;
				      flag = 0;
                      while (flag==0)
					  {
						  c = c + dc;
						  dxy = complex(dd*cos(c), dd*sin(c));
                          xy1 = xy + dxy;
					      if (c<=6.29) { flag = 1; it = 0;}
					      else 
						  {
							  dd = dd/1.67;
						      if (dd<=1.0e-007) { flag = 1; it = 1;}
					          else  c = 0.0;
						  }
					  }
                      if (it==0) goto l40;
				      for (i=1; i<=k; i++)  a[i]=a[i] + a[i-1]*xy;
                      xx[k-1] = xy*complex(w,0.0);
                      k = k - 1;
                      if (k==1) 
				         xx[0] = complex(0.0,0.0)- a[1]*complex(w,0.0)/a[0];
				  }
                  else
				  {
					  dxy = uv/uv1;
                      t=1.0+4.0/k;
				      it = 1;
				      while (it==1)
					  {
						  t = t/1.67; it = 0;
						  xy1 = xy - dxy*complex(t,0.0);
					      if (k>=30)
						  {
							  p = xy1.cfabs();
						      q = exp(75.0/k);
						      if (p>=q)  it = 1;
						  }
					  }
                      if (t>=1.0e-03) goto l40;
                      if (g>1.0e-18)
                      { 
						  is = 1;
					      dd = dxy.cfabs();
					      if (dd>1.0)  dd = 1.0;
					      dc = 6.28/(4.5*k);  c = 0.0;
				          flag = 0;
                          while (flag==0)
						  {
							  c = c + dc;
							  dxy = complex(dd*cos(c), dd*sin(c));
							  xy1 = xy + dxy;
					          if (c<=6.29) { flag = 1; it = 0;}
					          else 
							  {
								  dd = dd/1.67;
						          if (dd<=1.0e-007) { flag = 1; it = 1;}
					              else  c = 0.0;
							  }
						  }
                          if (it==0) goto l40;
					  }
				      for (i=1; i<=k; i++)  a[i]=a[i] + a[i-1]*xy;
                      xx[k-1] = xy*complex(w,0.0);
                      k = k - 1;
                      if (k==1) 
				         xx[0] = complex(0.0,0.0)- a[1]*complex(w,0.0)/a[0];
				  }
			  }
		  }
          if (k==1) jt=0;
          else jt=1;
      }
      return(1);
  }

/*
//复系数代数方程例
  #include <cmath>
  #include <iostream>
  #include "复系数多项式运算类.h"
//  #include "代数方程牛顿下山法.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      complex z[5];
      complex b[6],a[6]={complex(0.1,-100),complex(21.33,0.0),complex(4.9,-19.0),
		            complex(0.0,-0.01),complex(3.0,3.0),complex(1.0,0.0)};
	  for (i=0; i<=5; i++) b[i] = a[i];
	  com_poly p;
	  p = com_poly(5,a);
      i=srrt(b,5,z);
      if (i>0)
      { 
		  for (i=0; i<=4; i++)
		  {
			  cout <<"z(" <<i <<") = "; z[i].prt(); cout <<endl;
		  }
	      cout <<"检验:" <<endl;
		  for (i=0; i<=4; i++)
		  {
			  cout <<"f(" <<i <<") = ";
			  p.poly_value(z[i]).prt(); cout <<endl;
		  }
	  }
	  return 0;
  }
*/
/*
//实系数代数方程例
  #include <cmath>
  #include <iostream>
  #include "复系数多项式运算类.h"
//  #include "代数方程牛顿下山法.cpp"
  using namespace std;
  int main()
  { 
	  int i;
      complex z[6];
      complex b[7],a[7]={ complex(-20.0,0.0),complex(7.0,0.0),complex(-7.0,0.0),
		   complex(1.0,0.0),complex(3.0,0.0),complex(-5.0,0.0),complex(1.0,0.0)};
	  com_poly p;
	  for (i=0; i<7; i++)  b[i] = a[i];
	  p = com_poly(6,a);
      i=srrt(b,6,z);
      if (i>0)
      { 
		  for (i=0; i<=5; i++)
		  {
			  cout <<"z(" <<i <<") = "; z[i].prt(); cout <<endl;
		  }
	      cout <<"检验:" <<endl;
		  for (i=0; i<=5; i++)
		  {
			  cout <<"f(" <<i <<") = ";
			  p.poly_value(z[i]).prt(); cout <<endl;
		  }
	  }
	  return 0;
  }
*/
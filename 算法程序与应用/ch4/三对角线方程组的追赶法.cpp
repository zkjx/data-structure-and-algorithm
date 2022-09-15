//三对角线方程组的追赶法.cpp
  #include <iostream>
  #include <cmath>
  using namespace  std;
//b[m]       以行为主存放三对角阵中三条对角线上的元素。
//n          方程组阶数。
//m          三对角阵3条对角线的元素个数。m = 3n - 2。
//d[n]       存放方程组右端的常数向量。返回方程组的解向量。
  //函数返回标志值。若<0则表示m的值不对；若=0则表示失败；若>0则表示正常。
  int trde(double b[], int n, int m, double d[])
  { 
	  int k,j;
      double s;
      if (m!=(3*n-2))   return -2;
      for (k=0;k<=n-2;k++)
      { 
		  j=3*k; s=b[j];
          if (fabs(s)+1.0==1.0)  return 0;
          b[j+1]=b[j+1]/s;
          d[k]=d[k]/s;
          b[j+3]=b[j+3]-b[j+2]*b[j+1];
          d[k+1]=d[k+1]-b[j+2]*d[k];
      }
      s=b[3*n-3];
      if (fabs(s)+1.0==1.0)  return 0;
      d[n-1]=d[n-1]/s;
      for (k=n-2;k>=0;k--)  d[k]=d[k]-b[3*k+1]*d[k+1];
      return(2);
  }

/*
  #include <iostream>
  #include <cmath>
//  #include "三对角线方程组的追赶法.cpp"
  using namespace  std;
  int main()
  { 
	  int i;
      double b[13]={13.0,12.0,11.0,10.0,9.0,8.0,7.0,
                         6.0,5.0,4.0,3.0,2.0,1.0};
      double d[5]={3.0,0.0,-2.0,6.0,8.0};
      if (trde(b,5,13,d)>0)
      for (i=0;i<=4;i++)
        cout <<"x(" <<i <<") = " <<d[i] <<endl;
	  return 0;
  }
*/

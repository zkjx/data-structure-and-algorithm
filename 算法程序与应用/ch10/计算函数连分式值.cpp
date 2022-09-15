//计算函数连分式值.cpp
  //x   存放n个结点值x[0]～x[n-1]。
  //b   存放连分式中的n+1个参数b[0]～b[n]
  //n   连分式的节数（注意：常数项b[0]为第0节）
  //t   自变量值
  //函数返回t处的函数连分式值
  double funpqv(double x[],double b[],int n,double t)
  { 
	  int k;
      double u;
      u=b[n];
      for (k=n-1; k>=0; k--)
      { 
		  if (fabs(u)+1.0==1.0)
			  u=1.0e+35*(t-x[k])/fabs(t-x[k]);
          else
			  u=b[k]+(t-x[k])/u;
      }
      return(u);
  }


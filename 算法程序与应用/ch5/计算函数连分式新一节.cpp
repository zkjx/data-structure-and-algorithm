//计算函数连分式新一节.cpp
  //x   存放结点值x[0]～x[j]
  //y   存放结点函数值y[0]～y[j]
  //b   存放连分式中的参数b[0]～b[j-1]，返回时新增加b[j]。
  //j   连分式增加的节号。即本函数计算新增加的b[j]。
  void funpqj(double x[],double y[],double b[],int j)
  { 
	  int k,flag=0;
      double u;
	  u=y[j];
	  for (k=0; (k<j)&&(flag==0); k++)
	  {
		  if ((u-b[k])+1.0==1.0) flag=1;
		  else
			  u=(x[j] - x[k])/(u-b[k]);
	  }
      if (flag==1) u=1.0e+35;
	  b[j]=u;
      return;
  }

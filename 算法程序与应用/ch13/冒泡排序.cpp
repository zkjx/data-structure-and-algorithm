//冒泡排序.cpp
    #include <iostream>
    #include <cmath>
	using namespace std;
//n         待排序序列长度。
//p[n]      待排序序列。
	template <class T>
    void bub_sort(int n, T p[])
	{ 
		int m,k,j,i;
        T d;
        k=0; m=n-1;
        while (k<m)
		{ 
			j=m-1; m=0;
            for (i=k; i<=j; i++)       //从前往后扫描
              if (p[i]>p[i+1])         //顺序不对，交换
			  { 
				  d=p[i]; p[i]=p[i+1]; p[i+1]=d; 
				  m=i;
			  }
            j=k+1; k=0;
            for (i=m; i>=j; i--)       //从后往前扫描
              if (p[i-1]>p[i])         //顺序不对，交换
			  {
				  d=p[i]; p[i]=p[i-1]; p[i-1]=d;
				  k=i;
			  }
		}
        return;
	}
/*
//冒泡排序例
  #include <iomanip>
//  #include "冒泡排序.cpp"
  #include "产生随机数类.h"
  int main()
  { 
	  RND r(5);
	  int i,j;
      double p[70],*s;
	  for (i=0; i<70; i++)  //产生70个0～1之间的随机数
		  p[i] = r.rnd1();
      for (i=0; i<70; i++)   //转换成0～999之间的随机数
		  p[i]=0.0+999.0*p[i];
	  cout <<"排序前:" <<endl;
      for (i=0; i<10; i++)    //共10行
      { 
		  for (j=0; j<7; j++)  //一行7个
            cout <<setw(10) <<p[7*i+j];
          cout <<endl;
      }
      s = p+7; 
      bub_sort(49,s);         //对2～8行数据用冒泡法排序
	  cout <<"排序后:" <<endl;
      for (i=0; i<10; i++)
      { 
		  for (j=0; j<7; j++)
            cout <<setw(10) <<p[7*i+j];
          cout <<endl;
      }
      return 0;
  }
*/
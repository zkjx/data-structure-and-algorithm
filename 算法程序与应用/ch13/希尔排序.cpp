//希尔排序.cpp
    #include <iostream>
    #include <cmath>
	using namespace std;
//n         待排序序列长度。
//p[n]      待排序序列。
	template <class T>
    void shel_sort(int n, T p[])
	{ 
		int k,j,i;
        T t;
        k=n/2;
        while (k>0)
		{ 
			for (j=k; j<=n-1; j++)
			{ 
				t=p[j]; i=j-k;
                while ((i>=0)&&(p[i]>t))
				{
					p[i+k]=p[i]; i=i-k;
				}
                p[i+k]=t;
			}
            k=k/2;
		}
        return;
	}
/*
//希尔排序例
  #include <iomanip>
//  #include "希尔排序.cpp"
  #include "产生随机数类.h"
  int main()
  { 
	  RND r(5);
	  int i,j;
      int p[100],*s;
	  for (i=0; i<100; i++)  //产生100个1～999之间的随机整数
		  p[i] = r.rndab(1,999);
	  cout <<"排序前:" <<endl;
      for (i=0; i<10; i++)    //共10行
      { 
		  for (j=0; j<10; j++)  //一行10个
            cout <<setw(6) <<p[10*i+j];
          cout <<endl;
      }
      s = p+10; 
      shel_sort(70,s);         //对2～8行数据用快速排序法排序
	  cout <<"排序后:" <<endl;
      for (i=0; i<10; i++)
      { 
		  for (j=0; j<10; j++)
            cout <<setw(6) <<p[10*i+j];
          cout <<endl;
      }
      return 0;
  }
*/
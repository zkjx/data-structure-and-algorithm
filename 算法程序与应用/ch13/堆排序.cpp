//堆排序.cpp
    #include <iostream>
    #include <cmath>
	using namespace std;
	//调整建堆
    template <class T>
    void sift(T p[], int i, int n)
	{ 
		int j;
        T t;
        t=p[i]; j=2*(i+1)-1;
        while (j<=n)
		{ 
			if ((j<n)&&(p[j]<p[j+1])) j=j+1;
            if (t<p[j])
			{ 
				p[i]=p[j]; i=j; j=2*(i+1)-1;
			}
            else j=n+1;
		}
        p[i]=t;
        return;
	}
//n         待排序序列长度。
//p[n]      待排序序列。
	template <class T>
    void hap_sort(int n, T p[])
	{ 
		int i,mm;
        T t;
        mm=n/2;
        for (i=mm-1; i>=0; i--)//无序序列建堆
           sift(p,i,n-1);  
        for (i=n-1; i>=1; i--)
		{
			t=p[0]; p[0]=p[i]; p[i]=t;  //堆顶元素换到最后
            sift(p,0,i-1);  //调整建堆
		}
        return;
	}
/*
//堆排序例
  #include <iomanip>
//  #include "堆排序.cpp"
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
      hap_sort(49,s);         //对2～8行数据用堆排序法排序
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
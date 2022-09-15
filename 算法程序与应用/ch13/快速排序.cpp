//快速排序.cpp
    #include <iostream>
    #include <cmath>
    #include "冒泡排序.cpp"
	using namespace std;
    //表的分割
    template <class T>
    int split(int n, T p[])
	{ 
		int i,j,k,l;
        T t;
        i=0; j=n-1;
        k=(i+j)/2;
        if ((p[i]>=p[j])&&(p[j]>=p[k])) l=j;
        else if ((p[i]>=p[k])&&(p[k]>=p[j])) l=k;
        else l=i;
        t=p[l];   //选取一个元素为T
	    p[l]=p[i]; 
        while (i!=j)
		{ 
			while ((i<j)&&(p[j]>=t)) j=j-1; //逐渐减小j，直到发现p[j]<t
            if (i<j)
			{ 
				p[i]=p[j]; i=i+1;
                while ((i<j)&&(p[i]<=t)) i=i+1;//逐渐增大i，直到发现p[i]>t
                if (i<j)	{ p[j]=p[i]; j=j-1;}
			}
		}
        p[i]=t;
        return(i);  //返回分界线位置
	}
//n         待排序序列长度。
//p[n]      待排序序列。
	template <class T>
    void qck_sort(int n, T p[])
	{
		int m, i;
        T *s;
        if (n>10)        //子表长度大于10，用快速排序
		{ 
			i=split(n,p);       //对表进行分割 
            qck_sort(i, p);        //对前面的子表进行快速排序
	        s=p+(i+1);
            m=n-(i+1);
            qck_sort(m, s);     //对后面的子表进行快速排序
		}
        else  //子表长度小于10，用冒泡排序
		    bub_sort(n, p);
        return;
	}
/*
//快速排序例
  #include <iomanip>
//  #include "快速排序.cpp"
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
      qck_sort(70,s);         //对2～8行数据用快速排序法排序
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
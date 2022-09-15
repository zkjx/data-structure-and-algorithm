//数据排序类例.cpp
  #include <iomanip>
  #include "数据排序类.h"
  #include "产生随机数类.h"
  using namespace std;
  int main()
  { 
	  int i,j;

	  cout <<"冒泡排序例:" <<endl;
	  RND r(5);
	  DATA_SORT<double> q;
      double p[70];
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
      q.bub_sort(49,p+7);         //对2～8行数据用冒泡法排序
	  cout <<"排序后:" <<endl;
      for (i=0; i<10; i++)
      { 
		  for (j=0; j<7; j++)
            cout <<setw(10) <<p[7*i+j];
          cout <<endl;
      }

	  cout <<"快速排序例" <<endl;
	  RND r1(5);
	  DATA_SORT<int> q1;
      int p1[100];
	  for (i=0; i<100; i++)  //产生100个1～999之间的随机整数
		  p1[i] = r1.rndab(1,999);
	  cout <<"排序前:" <<endl;
      for (i=0; i<10; i++)    //共10行
      { 
		  for (j=0; j<10; j++)  //一行10个
            cout <<setw(6) <<p1[10*i+j];
          cout <<endl;
      }
      q1.qck_sort(70,p1+10);         //对2～8行数据用快速排序法排序
	  cout <<"排序后:" <<endl;
      for (i=0; i<10; i++)
      { 
		  for (j=0; j<10; j++)
            cout <<setw(6) <<p1[10*i+j];
          cout <<endl;
      }

	  cout <<"希尔排序例" <<endl;
	  RND r2(5);
	  DATA_SORT<int> q2;
      int p2[100];
	  for (i=0; i<100; i++)  //产生100个1～999之间的随机整数
		  p2[i] = r2.rndab(1,999);
	  cout <<"排序前:" <<endl;
      for (i=0; i<10; i++)    //共10行
      { 
		  for (j=0; j<10; j++)  //一行10个
            cout <<setw(6) <<p2[10*i+j];
          cout <<endl;
      } 
      q2.shel_sort(70,p2+10);         //对2～8行数据用快速排序法排序
	  cout <<"排序后:" <<endl;
      for (i=0; i<10; i++)
      { 
		  for (j=0; j<10; j++)
            cout <<setw(6) <<p2[10*i+j];
          cout <<endl;
      }

	  cout <<"堆排序例" <<endl;
	  RND r3(5);
	  DATA_SORT<double> q3;
      double p3[70];
	  for (i=0; i<70; i++)  //产生70个0～1之间的随机数
		  p3[i] = r3.rnd1();
      for (i=0; i<70; i++)   //转换成0～999之间的随机数
		  p3[i]=0.0+999.0*p3[i];
	  cout <<"排序前:" <<endl;
      for (i=0; i<10; i++)    //共10行
      { 
		  for (j=0; j<7; j++)  //一行7个
            cout <<setw(10) <<p3[7*i+j];
          cout <<endl;
      } 
      q3.hap_sort(49,p3+7);            //对2～8行数据用堆排序法排序
	  cout <<"排序后:" <<endl;
      for (i=0; i<10; i++)
      { 
		  for (j=0; j<7; j++)
            cout <<setw(10) <<p3[7*i+j];
          cout <<endl;
      }

      return 0;
  }

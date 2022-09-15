//产生随机数类例.cpp
  #include  <iostream>
  #include  <cmath>
  #include  "产生随机数类.h"
  using namespace std;
  int main()
  {
	  int i, j, r, a, b;
	  double u, g;
	  RND p;
      cout <<"产生50个0～1之间的随机数如下:" <<endl;
	  r = 5;
      p = RND(r);
	  for (i=0; i<=9; i++)
	  {
		  for (j=0; j<=4; j++)  cout <<p.rnd1() <<"    ";
		  cout <<endl;
	  }

      cout <<"产生50个101～200之间的随机整数如下:" <<endl;
      r = 1; a = 101; b = 200;
      p = RND(r);
	  for (i=0; i<=4; i++)
	  {
		  for (j=0; j<=9; j++)  cout <<p.rndab(a, b) <<"    ";
		  cout <<endl;
	  }

      cout <<"产生50个均值为1.0,方差为1.5*1.5的正态分布的随机数如下:" <<endl;
      r = 3; u = 1.0; g = 1.5; 
      p = RND(r);
	  for (i=0; i<=9; i++)
	  {
		  for (j=0; j<=4; j++)  cout <<p.rndg(u, g) <<"    ";
		  cout <<endl;
	  }

      return 0;
  }


//求解二阶边值问题试射法.cpp
    #include <iostream>
    #include <cmath>
    #include "求解二阶初值Euler方法.cpp"
    using namespace std;
//n          积分区间等分数
//a          积分区间左端点
//b          积分区间右端点。要求b>a。
//eps        控制精度要求
//y[n+1]     y[0]存放左端点边界值y(a)，y[n]存放右端点边界值y(b)。
//           返回n+1个等距离散点上的数值解。
//f          计算二阶常微分方程右端函数f(t,y,z)
    //函数返回y在左端点处的一阶导数值
    double  shoot(int n, double a, double b, double eps, double y[],
		          double (*f)(double,double,double))
	{
		int k;
		double h, x, yy, zz, z, zz1, zz2, y0, yn, p;
		h = (b-a)/n; y0 = y[0]; yn = y[n];		
		z = 0.0;  
		yy = y[0]; zz = z;         //取函数y的初值与一阶导数初值
        for (k=0; k<n; k++)        //计算n个等距离散点上的数值解
		{
			x = a + k*h; 
			euler2(x,h,&yy,&zz,eps,f);//Euler法求解二阶初值变步长积分一步
            y[k+1] = yy; 
		}
		if (y[n]-yn > 0)    //若终点数值解值>终点边界值
		{
			zz2 = z;
			do
			{
				zz = zz2 - 0.1;	//函数y的一阶导数初值缩小		
                yy = y[0];      //函数y初值
                for (k=0; k<n; k++)  //计算n个等距离散点上的数值解
				{
					x = a + k*h;
					euler2(x,h,&yy,&zz,eps,f);
                    y[k+1] = yy; 
				}
				if (y[n]-yn > 0) zz2 = zz2 - 0.1; //保留缩小后的值
			}while (y[n]-yn > 0);
			zz1 = zz2 - 0.1;    //保留一阶导数初值的下限
		}
		else
		{
			zz1 = z;
			do
			{
				zz = zz1 + 0.1;	//函数y的一阶导数初值增加		
                yy = y[0];      //函数y初值
                for (k=0; k<n; k++)  //计算n个等距离散点上的数值解
				{
					x = a + k*h;
					euler2(x,h,&yy,&zz,eps,f);
                    y[k+1] = yy; 
				}
				if (y[n]-yn < 0) zz1 = zz1 + 0.1; //保留增加后的值
			}while (y[n]-yn < 0);
			zz2 = zz1 + 0.1;     //保留一阶导数初值的上限
		}
		do     //对分搜索
		{
			zz = (zz1 + zz2)/2; 
			z = zz; 			
            yy = y[0];         //函数y初值
            for (k=0; k<n; k++)  //计算n个等距离散点上的数值解
			{
				x = a + k*h;
				euler2(x,h,&yy,&zz,eps,f);
                y[k+1] = yy; 
			}
			p = fabs(zz1-zz2);
			if (y[n]-yn > 0)  zz2 = z;
			else  zz1 = z;
		}while (p > 0.0000001);
		return(z);		
	}

/*
//求解二阶边值问题试射法例1
    #include <iostream>
    #include <cmath>
//    #include "求解二阶边值问题试射法.cpp"
    using namespace std;
	int main()
	{
		int k;
		double dy0, y[11], f(double,double,double);
		y[0] = 0.0;  y[10] = 1.0;
		dy0 = shoot(10, 0.0, 1.0, 0.0000001, y, f);
		cout <<"初始斜率 = " <<dy0 <<endl;
		for (k=0; k<11; k++)
			cout <<"x = " <<0.1*k <<"     y = " << y[k] <<endl;
		return 0;
	}
//计算二阶微分方程右端函数值
    double  f(double t, double y, double z)
	{
		double d;
		d = t + y;
		return(d);
	}
*/
/*
//求解二阶边值问题试射法例2
    #include <iostream>
    #include <cmath>
//    #include "求解二阶边值问题试射法.cpp"
    using namespace std;
	int main()
	{
		int k;
		double dy0, y[11], f(double,double,double);
		y[0] = 1.0;  y[10] = 2.0;
		dy0 = shoot(10, 0.0, 1.0, 0.0000001, y, f);
		cout <<"初始斜率 = " <<dy0 <<endl;
		for (k=0; k<11; k++)
			cout <<"x = " <<0.1*k <<"     y = " << y[k] <<endl;
		return 0;
	}
//计算二阶微分方程右端函数值
    double  f(double t, double y, double z)
	{
		double d;
		d = (6*t-3.0+t*z+3*y)/(1.0+t*t);
		return(d);
	}
*/
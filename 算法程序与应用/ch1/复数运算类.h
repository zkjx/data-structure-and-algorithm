//复数运算类.h
  #include  <iostream>
  #include  <cmath>
  using namespace std;
  class  complex
  {
  private: 
		   double  R;
		   double  I;
  public:
	       complex (double real=0, double imag=0)    //构造函数
		   { R = real;  I = imag;  }
		   void prt ()                             //复数输出
		   { 
			   cout <<"(" <<R <<", " <<I <<")" ; 
			                            //输出形式为:(实部, 虚部)
			   return;
		   }
		   double cfabs()                         //复数模
		   {
			   double y;
			   y=sqrt(R*R+I*I);
			   return y;
		   }
		   double angle()                        //复数幅角
		   {
			   double y;
			   y = atan2(I, R);
			   return(y);
		   }
		   complex operator + (complex& c2)         //复数加法
		   {
			   complex c;
			   c.R = R + c2.R;  c.I = I + c2.I; 
			   return c;
		   }
		   complex operator - (complex& c2)         //复数减法
		   {
			   complex c;
			   c.R = R - c2.R;  c.I = I - c2.I; 
			   return c;
		   }
		   complex operator * (complex& c2)          //复数乘法
		   {
			   complex c;
			   double p, q, s;
			   p = R*c2.R; q = I*c2.I;
			   s = (R+I)*(c2.R+c2.I);
			   c.R = p - q;  c.I = s - p - q;
			   return c;
		   }
		   complex operator / (complex& c2)           //复数除法
		   {
			   complex c;
			   double p, q, s, w;
			   p = R*c2.R; q = - I*c2.I;
			   s = (R+I)*(c2.R-c2.I);
			   w = (c2.R)*(c2.R) + (c2.I)*(c2.I);
			   if (w + 1.0 != 1.0)
			   {
				   c.R = (p - q)/w;  c.I = (s - p - q)/w;
			   }
			   else
			   {
				   c.R =1e+300 ;  c.I =1e+300 ;
			   }
			   return c;
		   }
		   complex cpower (int n)              //复数乘幂
		   {
			   complex  c;
			   double r, q;
			   q = atan2(I, R);
			   r = sqrt(R*R + I*I);
			   if (r+1.0 != 1.0)
			   { r = n*log(r);  r = exp(r); }
			   c.R = r*cos(n*q);  c.I = r*sin(n*q);
			   return  c;
		   }
		   void croot (int n, complex *p)                 //复数的n次方根
		   {
			   complex c;
			   int k;
			   double r, q, t;
			   if (n < 1) return;
			   q = atan2(I, R);
			   r = sqrt(R*R + I*I);
			   if (r+1.0 != 1.0)
			   { r = (1.0/n)*log(r);  r = exp(r); }
			   for (k=0; k<n; k++)
			   {
				   t = (2.0*k*3.1415926 + q)/n;
				   c.R = r*cos(t);  c.I = r*sin(t);
				   p[k] = c;
			   }
		   }
		   complex cexp ()                      //复数指数
		   {
			   complex c;
			   double p;
			   p = exp(R);
			   c.R = p*cos(I);  c.I = p*sin(I);
			   return c;
		   }
		   complex clog ()                       //复数对数
		   {
			   complex c;
			   double p;
			   p = R*R + I*I;
			   p = log(sqrt(p));
			   c.R = p;  c.I = atan2(I, R);
			   return c;
		   }
		   complex csin ()                       //复数正弦
		   {
			   complex c;
			   double p, q;
			   p = exp(I); q = exp(-I);
			   c.R = sin(R)*(p+q)/2;
			   c.I = cos(R)*(p-q)/2;
               return c;
		   }
		   complex ccos()                       //复数余弦
		   {
			   complex c;
			   double p, q;
			   p = exp(I); q = exp(-I);
			   c.R = cos(R)*(p+q)/2;
			   c.I = -sin(R)*(p-q)/2;
               return c;
		   }
  };


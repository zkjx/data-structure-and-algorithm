//数据排序类.h
  #include  <iostream>
  #include  <cmath>
  #include  <fstream>
  using namespace std;
  template <class T>
  class  DATA_SORT
  {
  private: 
		   
		   
  public:
	       
		   void bub_sort(int , T *);             //冒泡排序
		   void qck_sort(int , T *);             //快速排序
           int split(int ,T []);               //表分割
		   void shel_sort(int , T *);            //希尔排序
		   void hap_sort(int , T *);             //堆排序
		   void sift(T *, int , int);         //调整建堆

  };
//冒泡排序
	template <class T>
	void DATA_SORT<T>::bub_sort(int n, T *p)
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
//快速排序
	template <class T>
	void DATA_SORT<T>::qck_sort(int n, T *p)
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
    //表的分割
    template <class T>
	int DATA_SORT<T>::split(int n, T p[])
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
//希尔排序
	template <class T>
	void DATA_SORT<T>::shel_sort(int n, T *p)
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
//堆排序
	template <class T>
	void DATA_SORT<T>::hap_sort(int n, T *p)
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
	//调整建堆
    template <class T>
	void DATA_SORT<T>::sift(T p[], int i, int n)
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




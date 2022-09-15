//#include <string.h>  
#include <assert.h>
#include "String.h"
//using namespace std;
 
class seqString {  
private: 
	char *str;								// 动态分配串的数组空间
	int curLen;								// curLen是串的当前长度
	friend std::ostream& operator <<(std::ostream &out,seqString &s);
	friend int strcmp(seqString *s1, seqString *s2);
public: 
	seqString(char *s);						// 构造函数
	seqString(const seqString & t);				// 拷贝构造函数
	~seqString();								// 析构函数
	int length()const;						// 求串长度
	seqString& strCpy(const seqString &s);			// 将串s复制到本串
	seqString subStr(int pos,int n );			// 取子串
	seqString& strCat(const seqString &s);		// 字符串连接
	int compare(const seqString &s);			// 字符串比较
	seqString& operator=(const seqString &s);		// 重载赋值运算=，功能同copy
	char& operator[](int n);				// 重载下标运算[]
	seqString& replace(int i,int j,const seqString &t); // 将串中从第i个字符开始的j个字符用t串替换
};

seqString::seqString(char *s="") {// 构造函数
    int i=0;
    curLen=0;
    while(s[curLen]!='\0') curLen++;		// curLen = strlen(s) ;  
    str = new char [curLen+1]; 
    assert(str != '\0');					// 当开辟动态区域不成功时，运行异常退出 
    while(s[i]!='\0') {					// 串s赋值给str
        str[i]=s[i];
        i++;
    }									// strcpy(str, s);
    str[i]='\0';
}


seqString::seqString(const seqString & s) {		// 拷贝构造函数
    int i=0;
    curLen=s.curLen; 
    str = new char [curLen+1]; 
    assert(str != '\0');					// 当开辟动态区域不成功时，运行异常退出 
    while(s.str[i]!='\0') {
        str[i]=s.str[i];
        i++;
    }
    str[i]='\0';
} 

	seqString & seqString::strCat(const seqString & s){		
		int i=0,j=0;
		seqString temp(*this);
		curLen+=s.curLen; 
		delete []str;
		str = new char[curLen+1]; 
		assert(str != '\0');	// 当开辟动态区域不成功时，运行异常退出 
		while(temp.str[i]!='\0')
			str[i]=temp.str[i++];		
		while(s.str[j]!='\0')
			str[i++]=s.str[j++];
		str[i]='\0';
		return *this;
	} 



	seqString& seqString::replace(int pos,int num,const seqString &t){
	seqString temp(*this);
	int i=0,j=0;
	if(pos<1 || num<0){
	//	cout<<"参数错误"<<endl;	//检查参数及置换后的长度的合法性
		return *this;
	} 
	curLen+=t.curLen-j; 
	delete []str;
	str = new char[curLen+1]; 
	assert(str != '\0');	// 当开辟动态区域不成功时，运行异常退出 

	while(i<pos-1)
		str[i]=temp.str[i++];
	
	while(j<t.curLen)
		str[i++]=t.str[j++];
	
	j=pos+num-1;
	while(temp.str[j]!='\0')
		str[i++]=temp.str[j++];
	str[i]='\0';
	return *this;
}

	seqString::~seqString() 
	{	
		delete []str;
		curLen=0;
	} 

	int seqString::length()const						//需要加const因下面operater=中的const参数
	{
		return  curLen-1;
	}


	seqString & seqString::operator=(const seqString &s)	{	//重载=
	int i=0;
		delete []str;
		curLen=s.length();
		str=new char[curLen+1];
		while(s.str[i]!='\0'){
		str[i]=s.str[i];
			i++;
		}
		str[i]='\0';
		return *this;
	}

	seqString& seqString::strCpy(const seqString &s)	{		// 将串s复制到本串
	int i=0;
		delete []str;
		curLen=s.curLen;
		str=new char[curLen+1];
		assert(str != '\0');					// 当开辟动态区域不成功时，运行异常退出 
		while(s.str[i]!='\0'){
			str[i]=s.str[i];
			i++;
		}
		str[i]='\0';
		return *this;
	}

	char& seqString::operator[](int n)					//重载[]
	{
		return str[n];
	}

	std::ostream& operator <<(std::ostream &out,seqString &s) //重载<<   若using namespace std;则可去掉std
	{
		out<<s.str;							
		return out;
	}

seqString seqString::subStr(int pos,int n){ 	// 从下标为pos的位置开始向右取长度为n的子串
    int i;  
    seqString tmp(""); 												
    if (pos >= curLen||pos < 0)			// 起始下标pos错误
        return tmp;						// 返回空串		
    if(n > curLen - pos)					// n大于从pos开始到串尾元素个数
        n=curLen-pos;					// 修改n的值

    delete []tmp.str; 					// 释放原来的存储空间 
    tmp.curLen= n; 
    tmp.str = new char[n+1]; 
    assert(tmp.str != NULL) ;				// 当开辟动态区域不成功时，运行异常退出
    for (i =0; i < n; i++)
        tmp.str[i] = str[pos+i];  		// pos开始长度为n的子串赋值给tmp	
    tmp.str[i] = '\0';  					
    return tmp; 
	}


	int seqString::compare(const seqString &s)			// 用类的成员函数实现比较当前字符串和s的大小，引用做参数
	{	int i = 0;   
		while (s.str[i] != '\0'  &&  this->str[i] != '\0' ) 
		{   
			if (this->str[i] > s.str[i])			// this大于s
				return 1;  
			else if (this->str[i] < s.str[i])		// this小于s
				return -1;   
			i++;   
		}   
		if (this->str[i] == '\0' && s.str[i] != '\0')   
			return -1;								// s有剩余元素，大于this
		else if (s.str[i] == '\0' && this->str[i] != '\0')   
			return 1;								// this有剩余元素，大于s
		return 0;									// 均无剩余元素，相等

	}
	  
	int strcmp(seqString *s1, seqString *s2)				// 用友元函数实现字符串比较，指针做参数
	{   
		int i = 0;   
		while (s2->str[i] != '\0'  ||  s1->str[i] != '\0' ) 
		{   
			if (s1->str[i] > s2->str[i])			// s1大于s2
				return 1;   
			else if (s1->str[i] < s2->str[i])		// s1小于s2
				return -1;   
			i++;   
		}   
		if (s1->str[i] == '\0' && s2->str[i] != '\0')   
			return -1;								// s2有剩余元素，大于s1
		else if (s2->str[i] == '\0' && s1->str[i] != '\0')   
			return 1;								// s1有剩余元素，大于s2
		return 0;									// 均无剩余元素，相等
	} 
 

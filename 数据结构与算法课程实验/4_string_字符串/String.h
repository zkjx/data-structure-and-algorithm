#ifndef _SEQ_STRING_H_
#define _SEQ_STRING_H_
#include<iostream>
#include <cstring> 
using namespace std;

class outOfRange:public exception {    				// 用于检查范围的有效性
public:    
   const char* what()const throw()    
   {    return "ERROR! OUT OF RANGE.\n";    } 
};  
class badSize:public exception {    				// 用于检查长度的有效性
public:    
   const char* what()const throw()    
   {    return "ERROR! BAD SIZE.\n";    }  
};

class String
{
public:
	String(const char *str = NULL);					// 构造函数
	String(const String &str);						// 拷贝构造函数
	~String(){delete []data;}						// 析构函数

	int capacity()const{return maxSize;}			// 最大存储容量
	int size()const{return curLength;}				// 求字符串长度
	bool empty()const{return curLength==0;}			// 判空

	String subStr(int pos,int num)const;			// 从pos位置开始取长度为n的子串
	int compare(const String &s) const;				// 比较当前字符串和s的大小,返回值参照strcmp设计
	int bfFind(const String &s, int pos = 0) const;	// 朴素的模式匹配算法，从pos开始查找字符串s在当前串中的位置
	String &insert(int pos,const String &s);		// 在pos位置插入字符串s
	String &erase(int pos, int num);				// 删除从pos开始的num个字符，返回修改后的字符串
	const char* toCharStr() const{ return data; }	// 获取字符数组data
	int  kmpFind(const String &t, int pos = 0);			// kmp模式匹配
	void  getNext(const String &t,int *next);				// 获取next数组
	void  getNextVal(const String&t,int *nextVal);		// 获取nextVal数组

	bool operator==(const String &str) const;		// 重载==，判断两个字符串是否相等
	String& operator+(const String &str) ;			// 重载+
	String& operator=(const String &str);			// 重载=
	char& operator[](int n) const;					// 重载[]

	friend istream& operator>>(istream &cin, String &str);	// 输入串
	friend ostream& operator<<(ostream &cout, String &str);	// 输出串
private:
	char *data;										// 字符串
	int maxSize;									// 最大存储容量
	int curLength;									// 串的长度
	void resize(int len);							// 扩大数组空间
};
int String:: kmpFind(const String &t,int pos){ 
    if(t.curLength == 0)return 0;					// 注意：c++不允许申请大小是0的数组
    if(curLength < t.curLength)return -1;			// 如果主串比子串短，匹配失败
    int i = 0,j = 0;							// 目标串和模式串的指针
    int *next=new int[t.curLength];				// next数组
    getNextVal(t,next); 							// 为next数组赋值
    while ( i < curLength  &&  j < t.curLength) {	// 比较对应字符
        if( j == -1 || data[i] == t.data[j])		// 情况1、2
            i++,  j++;
        else j = next[j];						// 情况3
    }
    delete []next;
    if ( j >= t.curLength)  return (i - t.curLength);
    else  return -1;
}

void  String::getNext(const String &t,int *next){ 
    int i=0,j=-1;
    next[0]=-1; 
    while(i<t.curLength-1){ 
        if((j==-1)||(t[i]==t[j])) {
            ++i, ++j; 
            next[i]=j;
        }
        else  j=next[j];
    }
}

void  String::getNextVal(const String&t,int *nextVal){ 	// 求模式串T的next数组修正值存入数组next
    int i=0,j=-1;
    nextVal[0]=-1; 
    while(i<t.curLength-1){ 
        if((j==-1)||(t[i]==t[j])){
            ++i,++j;
            if(t[i]!=t[j]) nextVal[i]=j;		
            else  nextVal[i]=nextVal[j];
        }
        else  j=nextVal[j];
    }
}


/*注意，类的成员函数中，有一些是加了const修饰的，表示这个函数不会对类的成员进行任何修改。一些函数的输入参数也加了const修饰，表示该函数不会对改变这个参数的值。

二 具体实现
下面逐个进行成员函数的实现。

同样构造函数适用一个字符串数组进行String的初始化，默认的字符串数组为空。这里的函数定义中不需要再定义参数的默认值，因为在类中已经声明过了。

另外，适用C函数strlen的时候需要注意字符串参数是否为空，对空指针调用strlen会引发内存错误。
*/
int String::compare(const String &s) const		// 用类的成员函数实现比较当前字符串和s的大小，引用做参数
{
	int i = 0;   
	while (s.data[i] != '\0'  ||  this->data[i] != '\0' ) 
	{   
		if (this->data[i] > s.data[i])			// this大于s
			return 1;  
		else if (this->data[i] < s.data[i])		// this小于s
			return -1;   
		i++;   
	}   
	if (this->data[i] == '\0' && s.data[i] != '\0')   
		return -1;								// s有剩余元素，大于this
	else if (s.data[i] == '\0' && this->data[i] != '\0')   
		return 1;								// this有剩余元素，大于s
	return 0;									// 均无剩余元素，相等

	// 上述代码可替换成调用strcmp函数，即：return strcmp(data,s.toCharStr());
}

int String::bfFind(const String &s, int pos) const{
    int i = 0, j = 0;						// 目标串和模式串的指针
    if (curLength < s.curLength) 				// 主串比子串短，匹配失败 
        return -1;          			 
    while (i < curLength && j < s.curLength){	
        if (data[i] ==s.data[j])  			// 对应字符相等指针后移
            i++,  j++; 
        else  	{   							// 对应字符不相等时
            i = i - j + 1;					// 主串指针回溯
            j = 0;							// 子串从头开始
        } 
    } 
    if ( j >= s.curLength) 
        return (i - s.curLength); 			// 返回子串在主串中的位置
    else return -1; 
}



String & String::insert(int pos,const String &s){
	if (pos > curLength||pos < 0)			// 插入位置pos错误
		throw outOfRange();					// 返回空串		

	if(curLength+s.curLength > maxSize)		// 空间不够
		resize(2*(curLength+s.curLength));

	for (int i = curLength; i >= pos; i--)	// 下标i在[curLength..pos]范围
		data[i+s.curLength] = data[i];		// 的元素往后移动s.curLength步,包括'\0'

	for(int j=0 ;j < s.curLength; j++)		// 存储s串字符
		data[pos+j] = s.data[j];

	curLength += s.curLength;				// 修改串的长度
	return *this;
}

String & String::erase(int pos, int num){
	if (pos < 0 || pos > curLength-1)			// 合法的删除位置为[0..curLengt-1] 
		throw outOfRange();		

	if(num < 0)throw badSize();	

	if(num > curLength - pos)					// num大于从pos开始到串尾元素个数
        num = curLength-pos;					// 修改num的值

    for (int j = pos+num; j <=curLength ; j++)	// 下标j+1在[pos+num..curLength]范围
        data[j-num] = data[j] ;					// 的元素往前移动num步,包括'\0'

    curLength -= num; 							// 修改串的长度
	return *this;
}

String String::subStr(int pos,int num)const{	
    int i;  
    String tmp(""); 												
    if (pos > curLength||pos < 0)				// pos的合法范围是[0.. curLength]
        throw outOfRange();					// 抛出异常

	if(num < 0)throw badSize();	

    if(num > curLength - pos)					// num大于从pos开始到串尾元素个数
        num = curLength-pos;					// 修改num的值

    delete []tmp.data; 						// 释放tmp原来的存储空间 
    tmp.maxSize = tmp.curLength = num; 	
    tmp.data = new char[num+1]; 				// 申请大小为num+1的存储空间

    for (i =0; i < num; i++)					// 长度为num的子串赋值给tmp
        tmp.data[i] = data[pos+i];  
    tmp.data[i] = '\0';  					
    return tmp; 
}


 String::String(const char *str)				// 构造函数
{
	maxSize = 2*strlen(str);
	data = new char[maxSize + 1];
	strcpy(data,str);
	curLength = strlen(data);	 
}

String::String(const String &str)				// 拷贝构造函数
{
	maxSize = str.maxSize;
	data = new char[maxSize + 1];
	strcpy(data, str.toCharStr());
	curLength = str.curLength;	 
}

//重载字符串连接运算，这个运算会返回一个新的字符串。

String& String::operator+(const String &str)	// 重载+
{
	if( maxSize < curLength+str.size() )
		resize(2*(curLength+str.size()));	

	strcat(data,str.data);
	curLength += str.curLength;	 
	return *this;
}

void String::resize(int len)
{
		maxSize = len;
		char *temp = new char[maxSize + 1];
		strcpy(temp,data);
		delete []data;
		data=temp;
}
//重载字符串赋值运算，这个运算会改变原有字符串的值，为了避免内存泄露，这里释放了原先申请的内存再重新申请一块适当大小的内存存放新的字符串。

String& String::operator=(const String &str)	// 重载=
{
	if (this == &str)	return *this;

	delete []data;
	maxSize = str.maxSize;
	data = new char[maxSize + 1];
	strcpy(data, str.toCharStr());
	curLength = str.curLength;	 
	return *this;
}

bool String::operator==(const String &str) const// 重载==
{
	if (curLength!= str.curLength)	return false;
	return strcmp(data, str.data) ? false : true;
}
//重载字符串索引运算符，进行了一个简单的错误处理，当长度太大抛出异常。

inline char& String::operator[](int n) const	// 重载[]
{
	if (n >= curLength) throw outOfRange();		// 错误处理
	else return data[n];
}

//重载输入运算符，先申请一块足够大的内存用来存放输入字符串，再进行新字符串的生成。这是一个比较简单朴素的实现，网上很多直接is>>str.data的方法是错误的，因为不能确定str.data的大小和即将输入的字符串的大小关系。

istream& operator>>(istream &cin, String &str)	// 输入
{
	char *temp=new char[1000];					// 申请一块内存
	cin >> temp;
	str.maxSize = 2*strlen(temp);
	str.data = new char[str.maxSize + 1];
	strcpy(str.data,temp);
	str.curLength=strlen(temp);
	delete []temp;
	return cin;
}
//重载输出运算符，只需简单地输出字符串的内容即可。注意为了实现形如cout<<a<<b的连续输出，这里需要返回输出流。上面的输入也是类似。

ostream& operator<<(ostream &cout, String &str)	// 输出
{
	cout << str.data;
	return cout;
}

#endif

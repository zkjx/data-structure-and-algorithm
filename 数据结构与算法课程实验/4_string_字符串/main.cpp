#include <cstdlib>    
  
#include <iostream>    
#include "String.h"    
#include <cstring>   
using namespace std;  
/* 
int index(seqString &T,seqString &P);   
int main(int argc, char *argv[])   
{  
	char *s = "how are you ?";   
      
	seqString*t1 = new seqString(s); 
	seqString*t2 = new seqString("friend");
	//cout<<(*t1)<<"当前长度是"<<t1->length()<<endl;   
	t1->replace(13,1,*t2);
	cout<<(*t1)<<"当前长度是"<<t1->length()<<endl;   

	//cout <<t1->subStr(0,6)<< endl;   // 取子串

	seqString t3("how");
	seqString t4="abc";
	seqString t5("");
	cout << t3<< endl;  
	
	//t3.strCpy(t5.strCpy("how r u ?"));
	//t3.strCat(t4);  

	//cout<<"t3:"<<t3<<",t4:"<<t4<<t3.length()+t4.length()<<endl;
										
	//cout << strcmp(t1,t2)<<"  "<<t1->compare(*t2)<<endl;	// 字符串比较
	
	cout <<index(t3, *t2)<<endl;					// 子串定位

    system("PAUSE");   
    return EXIT_SUCCESS;   
}   

// 返回子串T在主串S中的位置，若T并非S的子串则返回0。index不是类的成员函数。
	int index(seqString &S,seqString &T) {			// 朴素的模式匹配算法
    int i = 0;							// 目标串（主串）的下标变量 
    int j = 0;							// 模式串（子串）的下标变量 
    int sLen = S.length();				// 主串长度 
    int tLen = T.length();				// 子串长度 
    if  (sLen < tLen) 					// 如果目标比模式短，匹配无法成功 
        return 0;          			 
    while (i < sLen && j < tLen)  {		// 反复比较对应字符来开始匹配 
        if (S[i] ==T[j])  
            i++,  j++; 
        else  	{   						// 对应字符不相等时，主串指针回溯，子串从头开始
            i = i - j + 1;  
            j = 0; 
        } 
    } 
    if ( j >= tLen) 
        return (i - tLen+1); 				// 返回子串在主串中的位置
    else return 0; 
}
*/
int main(int argc, char *argv[])   
{  
	const char *s = "how are you ?";   
      
	String*t1 = new String(s); 
	String*t2 = new String("friend");

	cout<<(*t1)<<"当前长度是"<<t1->size()<<",capacity="<<t1->capacity()<<endl; 
	
	String ss = t1->subStr(0,5);
	cout <<"substr=";
	cout<<ss;
	cout<< endl;   // 取子串

	String t3("");
	String t4=" you!";

	cout << t3<<"在t1中第一次出现的位置是："<<t1->bfFind(t3)<<endl;
	cout << t3<<"在t1中第一次出现的位置是："<<t1->kmpFind(t3)<<endl;

	cout<<*t1<<"和"<<*t2<<t1->compare(*t2)<<endl;//比较当前字符串和s的大小,compare函数在>时返回1，<时返回-1，==时返回0 
	cout<<t4<<"和"<<t3<<t4.compare(t3)<<endl;//比较当前字符串和s的大小,compare函数在>时返回1，<时返回-1，==时返回0 
	cout<<t3<<"和"<<t3<<t3.compare(t3)<<endl;//比较当前字符串和s的大小,compare函数在>时返回1，<时返回-1，==时返回0 

	cout<<t3.insert(0,*t1);
	cout<<"当前长度是"<<t3.size()<<",capacity="<<t3.capacity()<<endl; 	//  在pos位置插入字符串s
	cout<<t1->erase(3,0)<<endl;//删除pos开始的num个字符，返回修改后的字符串
	t3=t3+t4;

	cout<<t3[0]<<endl;

    system("PAUSE");   
    return EXIT_SUCCESS;   
}

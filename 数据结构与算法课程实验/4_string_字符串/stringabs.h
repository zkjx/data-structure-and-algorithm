#ifndef _STRING_ABSTRACT_TYPE_H_
#define _STRING_ABSTRACT_TYPE_H_
class stringAbstractType
{
public:
	virtual int capacity()const=0;			// 最大存储容量
	virtual int size()const=0;				// 求字符串长度
	virtual bool empty()const=0;		// 判空
	virtual stringAbstractType subStr(int pos,int num)const=0;			// 从pos位置开始取长度为n的子串
	virtual int compare(const stringAbstractType &s) const=0;				// 比较当前字符串和s的大小
	virtual int bfFind(const stringAbstractType &s, int pos = 0) const=0;	// BF从pos开始查找字符串s在当前串中的位置
	virtual stringAbstractType &insert(int pos,const stringAbstractType &s)=0;		// 在pos位置插入字符串s
	virtual stringAbstractType &erase(int pos, int num)=0;				// 删除从pos开始的num个字符，返回修改后的字符串
	virtual ~stringAbstractType(){};									// 析构函数
};
#endif
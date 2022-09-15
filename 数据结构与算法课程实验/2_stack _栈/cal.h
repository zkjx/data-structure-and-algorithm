#ifndef _CAL_H_
#define _CAL_H_
#include "linkStack.h"  
#include <iostream> 
#include <cmath>
#include <cstring> 
using namespace std;  
class calculator{
private:
    linkStack<char> optr;				// 运算符栈
    linkStack<double> opnd;				// 运算数栈
    char* infix;						// 存储中缀表达式的字符数组
    char* postfix;						// 存储后缀表达式的字符数组，用于例3.4 
    int  size;							// 中缀表达式字符串的长度
public:	
    calculator(const char *s);					// 构造函数    	
    ~calculator();						// 析构函数
    double spellNum(char* fix,int& i);		// 拼数，将数字字符转换成double类型的数字
    int priorInStack(char item);			// 计算栈内运算符优先级
    int priorOutStack(char ch);			// 计算栈外运算符优先级
    int precede(char item,char ch);		// 比较栈内外运算符优先次序
    double operate(double a,char theta,double b);	// a与b进行theta运算
    double calculateInfix();				// 中缀表达式求值
    double calculatePostfix();			// 后缀表达式求值，用于例3.4
    void infixToPostfix () ;				// 中缀表达式转后缀表达式，用于例3.4
    void printInfix ();					// 输出中缀表达式
    void printPostfix();					// 输出后缀表达式，用于例3.4
};
//其中：precede是计算运算符优先级的函数，两个运算符比较可有大于、等于、小于三种结果，这里若相等，则消除一对括号'('')'或'='。operate是运算函数，根据弹出栈的运算符(+、-、*、/)和两个操作数进行相应运算。
//下面异常类用于除数为0异常：
class divideByZero:public exception {    	
public:    
   const char* what()const throw()    
   {    return "ERROR! DIVIDE BY ZERO.\n";    } 
};
//下面异常类用于表达式出错：
class wrongExpression:public exception {    
public:    
   const char* what()const throw()    
   {    return "ERROR! BAD EXPRESSION.\n";    } 
};
//中缀表达式求值的基本操作如下：
//[算法3.13]	构造函数
calculator::calculator(const char *s) { 	 
    size = strlen(s) ;   
    infix = new char [size +1]; // infix存储中缀表达式
    postfix = new char [2*size]; // postfix存储后缀表达式
    strcpy(infix,s); 			
}

//[算法3.14]	析构函数
calculator::~calculator() { 			 
    delete []infix;
    delete []postfix;
} 

//[算法3.15]	拼数
double calculator::spellNum(char* fix,int& i) {	// 将数字字符转拼成double类型的数字
    double num1=0,num2=0,num;
    int j=0;
    while(fix[i] >= '0' && fix[i] <= '9') 		// 处理小数点以前部分
        num1 = num1*10 +fix[i++]-'0';  
    if(fix[i]=='.') {						// 处理小数点以后部分
        i++; 
        while(fix[i] >= '0' && fix[i] <= '9')
            num2 += (fix[i++]- '0')*1.0/pow(10.0,++j); 			
    }  
    return num=num1+num2;
}
//[算法3.16]	计算栈内运算符优先级
int calculator::priorInStack(char item) {	 	// 参见表3.1
    int in;
    switch(item) {
        case '=':in=0;break;
        case '(':in=1;break;
        case '*':
        case '/':in=5;break;
        case '+':
        case '-':in=3;break;
        case ')':in=6;break;
    }
    return in;
}
//[算法3.17]	计算栈外运算符优先级
int calculator::priorOutStack(char ch)	{		// 参见表3.1
    int out;
    switch(ch) {
        case '=':out=0;break;
        case '(':out=6;break;
        case '*':
        case '/':out=4;break;
        case '+':
        case '-':out=2;break;
        case ')':out=1;break;
        default: throw wrongExpression();
    }
    return out;
}
//[算法3.18]	比较栈内外运算符优先次序
int calculator::precede(char item,char ch){ 		
    if(priorInStack(item) < priorOutStack(ch))  return -1;
    else if(priorInStack(item) == priorOutStack(ch))  return 0;
    else return 1;
}
//[算法3.19]	完成一次算数运算
double calculator::operate(double a,char theta,double b)  { 
    double result;
    switch(theta) {
        case '+' : 	result=a+b;break;
        case '-' : 	result=a-b;break;
        case '*' : 	result=a*b;break;
        case '/' :
            if ( fabs(b) <= 1e-6 )  throw divideByZero(); 
            else {
                result=a/b;
                break;
            }
    }
    return result;
}
//[算法3.20]	中缀表达式求值
double  calculator::calculateInfix(){	
    optr.clear();
    opnd.clear();
    int i=0;
    char item,theta;
    double num,a,b;
    optr.push('=');							// '='置于栈底，级别最低
    while(!optr.empty()){
        if((infix[i]>='0'&& infix[i]<='9')||infix[i]=='.'){
            num=spellNum(infix,i);
            opnd.push(num);					// 数字字符，入栈
        }   
        else {
            item = optr.getTop();
            switch(precede(item,infix[i])){ 	// infix[i]与栈顶运算符比较
                case -1:optr.push(infix[i]);	// infix[i]级别高，入栈
                        i++;					// i指向下一字符
                        break;
                case 0: item = optr.pop();		// 删除括号或'='
                        if(item != '=')i++;		// i指向下一字符
                        break;
                case 1: theta = optr.pop();   	// infix[i]级别低，弹出一个运算符
                        b = opnd.pop(); a = opnd.pop();  	// 弹出两个操作数
                        opnd.push(operate(a,theta,b));	// 进行相应运算，结果入栈
            }  
        }
    }
    num=opnd.pop();
    if(!opnd.empty())throw wrongExpression();
    return num;
}
//说明：上述代码中“b = opnd.pop(); a = opnd.pop();”弹出两个操作数，此处没有判断栈是否为空，因为当栈为空时，linkList的pop()操作会抛出outOfRange异常。
//[算法3.21]	输出表达式
void  calculator::printInfix(){
    int i=0;
    while(infix[i]!='\0')
        cout<<infix[i++];
    cout<<endl;
}
void  calculator::infixToPostfix(){
    int i=0,j=0;							// i、j分别是中缀表达式和后缀表达式的下标
    char item;
    optr.clear();
    optr.push('=');							// '='置于栈底，优先级最低
    while(!optr.empty()){	
        if((infix[i]>='0'&& infix[i]<='9')||infix[i]=='.')
            postfix[j++]=infix[i++];			// 数字字符直接存储到后缀表达式中 
        else {
            postfix[j++]=' ';					// 空格用以区分后缀表达式中各组成部分
            item=optr.getTop();
            switch(precede(item,infix[i])){		// infix[i]与栈顶运算符比较
                case -1:optr.push(infix[i]);	// infix[i]级别高，入栈
                        i++;   break;			// i指向下一字符
                case 0: item=optr.pop();		// 删除括号或'='
                        if(item != '=')i++;	    // i指向下一字符
                        break;
                case 1: item=optr.pop();		// item级别高，出栈
                        postfix[j++]=item;		// item存储到后缀表达式中
            }  
        }
    }
    postfix[j]='\0';						// 字符串结束标志
}
//[算法3.23]	后缀表达式求值
double calculator::calculatePostfix(){			// 对后缀表达式求值
    opnd.clear();
    int i=0;
    double num,a,b;
    while (postfix[i]!='\0'){					// '\0'是后缀表达式结束标志
        if((postfix[i]>='0'&&postfix[i]<='9')||postfix[i]=='.') {
            num=spellNum(postfix,i);			// 遇到数字字符或小数点，拼数
            opnd.push(num);					// num压入数字栈
        }
        else if(postfix[i]==' ')i++;			// 空格跳过
        else {
            b=opnd.pop();  a=opnd.pop(); 		// 弹出两个操作数					
            if(postfix[i]=='+')  num=a+b;
            if(postfix[i]=='-')  num=a-b;
            if(postfix[i]=='*')  num=a*b;
            if(postfix[i]=='/'){
                if( fabs(b) <= 1e-6 ) throw divideByZero();
                else num=a/b;
            }
            opnd.push(num);					// 运算结果压栈
            i++;	
        }
    }
    num=opnd.pop();
    if(!opnd.empty()) throw wrongExpression();
    return num;
}
//[算法3.24]	输出后缀表达式
void  calculator::printPostfix(){
    int i=0;
    while(postfix[i]!='\0')
        cout<<postfix[i++];
    cout<<endl;
}


#endif

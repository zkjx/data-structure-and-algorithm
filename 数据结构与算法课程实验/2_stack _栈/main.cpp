#include <cstdlib>    
#include <iostream>     
#include<stack>
#include<string>
using namespace std;   
#include "linkStack.h"  
#include "seqStack.h" 
#include "CAL.h"

template <class T> 	 
void testStack(Stack<T> &s)
{
	for (int i=0; i<10; ++i) s.push(2*i);
	cout<<"curLength="<<s.size()<<endl;
	while (!s.empty())  cout << s.pop() << ' ';
	cout<<"\ncurLength="<<s.size()<<endl;

	try{
		cout <<s.getTop();
	}
	catch(outOfRange& me){
		cout<<me.what();
	}
}
// 求阶乘
template <class T> 	   
long factorial(Stack<T> &s,long n) {   
     long result = 1;   
     while (n > 0)                  // 不满足递归出口          
        s.push(n--);                // 按递归规则把相应数据压栈    
     while (!s.empty()) {         // 递归出口满足，开始进行返回处理    
        result *= s.pop();  
     }    
     return result;   
}
// 进制转换
void convert(){
    linkStack<int> S;   		// 栈S
    int N,e;   
    cin>>N;						// 读入十进制数
    while(N!=0) {
        S.push(N%16);			// 将得到的八进制数位入栈
        N=N/16;					// 数N除以8作新的被除数
    }
    while(!S.empty()){
        e=S.pop(); 
		if(e > 9)  
	          cout<<char(e-10+'a');
		else  cout<<e<<" ";			// 输出八进制数
    }
    cout<<endl;
}
// 括号匹配1
bool match(){
    linkStack<char> S;   							// 使用3.1.3中实现的链栈
    char item;
    int i=0;
    string expression;
    getline(cin,expression);							// 输入字符串
    while(i < expression.size()){  					// 扫描字符串
        switch (expression[i]){
            case '(':S.push(expression[i]);    break;	// 左括号 ( 压栈
            case ')':								// 右括号 ) 将与栈顶元素匹配
                if(S.empty()||(item=S.getTop())!='('){	// 失配
                    cout<<"mismatched\n";    return false;
                } 
                else   S.pop();     break; 			// 匹配
            case '[':S.push(expression[i]);    break; 	// 左括号 [ 压栈
            case ']':				 				// 右括号 ] 将与栈顶元素匹配
                if(S.empty()||(item=S.getTop())!='['){ 	// 失配
                    cout<<"mismatched\n";    return false;
                } 
                else   S.pop();     break; 			// 匹配
            case '{':S.push(expression[i]);    break; 	// 左括号 { 压栈
            case '}': 								// 右括号 } 将与栈顶元素匹配
                if(S.empty()||(item=S.getTop())!='{'){ 	// 失配
                    cout<<"mismatched\n";    return false;
                } 
                else   S.pop();    break; 				// 匹配
        };
        i++;
    }
    if(S.empty()) {  cout<<"matched\n";    return true;  } 
    else{  cout<<"mismatched\n";    return false; }		// 栈非空，失配
}
// 括号匹配2
bool match2(){
    stack<char> S;   // 栈S
	string expression;
    getline(cin,expression);
	char item;
	int i=0;
    while(i< expression.size()){  				// '\0'表示字符串结束 
        switch (expression[i]){
            case '(':S.push(expression[i]);    break;		// 左括号 ( 压栈
            case ')':							// 右括号 ) 将与栈顶元素匹配
                if(S.empty()||(item=S.top())!='('){
                    cout<<") mismatched\n";    return false;
                } 
                else   S.pop();     break;
            case '[':S.push(expression[i]);    break; 		// 左括号 [ 压栈
            case ']':				 			// 右括号 ] 将与栈顶元素匹配
                if(S.empty()||(item=S.top())!='['){
                    cout<<"] mismatched\n";    return false;
                } 
                else   S.pop();     break;
            case '{':S.push(expression[i]);    break; 		// 左括号 { 压栈
            case '}': 							// 右括号 } 将与栈顶元素匹配
                if(S.empty()||(item=S.top())!='{'){
                    cout<<"} mismatched\n";    return false;
                } 
                else   S.pop();    break;
        };
		i++;
    }
    if(S.empty()) {
        cout<<"matched\n";    return true;
    } 
    else{
    	while(!S.empty())
        {
        	cout<<S.top()<<" ";
        	S.pop();
	}	
		cout<<" mismatched\n";    return false;
    }
}

 
// 测试表达式求值
/*
int main()   
{   char x;
	calculator C("12*(6-3.5)/8=");
//	cout<<"input a string:\n";
//	cout<<"中缀表达式计算结果"<<C.calculateInfix()<<endl;
	try{

	cout<<"输出中缀表达式";
	C.printInfix();

	cout<<"计算中缀表达式的结果";
	cout<<C.calculateInfix()<<endl;

	C.infixToPostfix();

	cout<<"输出后缀表达式";
	C.printPostfix();

	cout<<"计算后缀表达式的结果";	
	cout<<C.calculatePostfix()<<endl;
	}
	catch(exception &me)
	{
		cout<<me.what();
	}

	cin>>x;
	return 0;
} 
*/

// 测试栈
int main( )   
{	
	linkStack<int> ls;
	seqStack<int> ss;
	testStack(ss);
	testStack(ls);

    long x;  
	cout<<"input a number:\n";
    cin >> x;   
    cout<< "the factioral of "<< x
		<< " is: " << factorial(ls,x)<<endl;  

	match();
	cin>>x;
	return 0;
}  
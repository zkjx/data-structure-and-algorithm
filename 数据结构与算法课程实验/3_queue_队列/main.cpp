#include<iostream>
#include <cstdlib>    
using namespace std;
#include"linkQueue.h"
#include"seqQueue.h"

template <class T>
void testQueue(Queue<T>& s)
{
	for (int i=0; i<10; ++i) s.enQueue(i+1);
	cout<<"curLength="<<s.size()<<endl;

	while (!s.empty())  cout << s.deQueue() << ' ';
	cout<<"\ncurLength="<<s.size()<<endl;

	try{
		cout <<s.getHead();
	}
	catch(outOfRange&me){
		cout<<me.what();
	}
}

int main()
{
	seqQueue<int> sq;
	linkQueue<int> lq;
	testQueue(sq);
	testQueue(lq);
	system("pause");
	return 0;
}

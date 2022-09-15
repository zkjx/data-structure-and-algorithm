#include <iostream>
using namespace std;

#ifndef _Queue_h

struct QueueRecord;
typedef struct QueueRecord *Queue;

int IsEmpty( Queue Q ); //Rear + 1 = Front
int IsFull( Queue Q );  //Rear = Front && Size = Maxsize - 1 ( 0 占用一个状态 )
Queue CreateQueue( int MaxElements );
void DisposeQueue( Queue Q );
void MakeEmpty( Queue Q );
void Enqueue( ElementType X , Queue Q );
Elemtype Front( Queue Q );
void Dequeue( Queue Q );
ElemType FrontAndDequeue( Queue Q );

#endif /* _Queue_h */

/* Place in implementation file */
/* Stack implementation is a linked list with a header */
#define MinQueueSize ( 5 )

struct QueueRecord
{
    int Capacity;
    int Front;
    int Rear;
    int Size;
    ElementType *Array;
};

int IsEmpty( Queue Q )
{
    return Q->Size == 0;
}

void
MakeEmpty( Queue Q )
{
    Q->Size = 0;
    Q->Front = 1;
    Q->Rear = 0;
}

static int
succ( int value , Queue Q )
{
    if( ++value == Q->Capacity ) value = 0;
    return value;
}

void
Enqueue( ElementType X , Queue Q )
{
    if( IsFull( Q ) ) Error( "Full queue " );
    else
    {
        Q->Size++;
        Q->Rear = succ( Q->Rear , Q );
        Q->Array[ Q->Rear ] = X;
    }
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

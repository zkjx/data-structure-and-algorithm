#include <iostream>
using namespace std;

#ifndef _BinHeap_H

struct HeapStruct;
typedef struct HeapStruct *PriorityQueue;

PriorityQueue Initialize( int MaxElements );
void Destory( PriorityQueue H );
void MakeEmpty( PriorityQueue H );
void Insert( ElementType X , PriorityQueue H );
ElementType DeleteMin( PriorityQueue H );
ElementType FindMin( PriorityQueue H );
int IsEmpty( PriorityQueue H );
int IsFull( PriorityQueue H );

#endif /* _BinHeap_H */

/* Place in implementation file */
struct HeapStruct
{
    int Capacity;
    int Size;
    ElementType *Element;
};

PriorityQueue
Initialize( int MaxElements )
{
    PriorityQueue H;

    if( MaxElements < MinPQSize ) Error( "Priority queue is too small" );

    H = malloc( sizeof( struct HeapStruct ) );
    if( H == NULL ) FatalError( "Out of space!!!" );

    /* Allocate the array plus one extra for sentinel */
    H->Element = malloc( sizeof( MaxElements + 1 ) * sizeof( ElementType ) );
    if( H->Element == NULL ) FatalError( "Out of space!!!" );

    H->Capacity = MaxElements;
    H->Size = 0;
    H->Element[ 0 ] = MinData;

    return H;
}

/* H->Element[0] is a sentinel */
void
Insert( ElementType X , PriorityQueue H )
{
    if( IsFull( H ) )
    {
        Error( "Priority queue is full" );
        return;
    }

    for(int i = ++H->Size; H->Element[ i / 2 ] > X ; i /= 2 ) H->Element[ i ] = H->Element[ i / 2 ];
    H->Element[ i ] = X;
}

ElementType
DeleteMin( PriorityQueue H )
{
    int i , child;
    ElementType MinElement , LastElement;

    if( IsEmpty( H ) )
    {
        Error( "Priority queue is empty" );
        return H->Element[ 0 ];
    }
    MinElement = H->Element[ 0 ];
    LastElement = H->Element[ H->Size-- ];

    for( i = 1; i * 2 <= H->Size; i = child )
    {
        /* Find smaller child */
        child = i * 2;
        if( child != H->Size && H->Element[ child ] ) H->Element[ i ] = H->Element[ child ];
        else break;
    }
    H->Element[ i ] = LastElement;
    return MinElement;
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

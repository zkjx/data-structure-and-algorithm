#include <iostream>
using namespace std;

#ifndef _Stack_h

struct StackRecord;
typedef struct StackRecord *Stack;

int IsEmpty( Stack S );
int IsFull( Stack S );
Stack CreateStack( int MaxElements );
void DisposeStack( Stack S );
void MakeEmpty( Stack S );
void Push( Elemtype X, Stack S );
void Pop( Stack S );
Elemtype Top( Stack S );
Elemtype TopAndPop( Stack S );


#endif /* _Stack_h */

/* Place in implementation file */
/* Stack implementation is a linked list with a header */
#define EmptyTOS ( -1 )
#define MinStackSize ( 5 )

struct StackRecord
{
    int Capacity;
    int TopOfStack;
    ElementType *Array;
};

Stack
CreateStack( int MaxElements)
{
    Stack S;

    if( MaxElements < MinStackSize) Error( "Stack size is too small" );

    S = malloc( sizeof( struct StackRecord ) );
    if( S == NULL) FatalError( "Out of space!!!" );

    S->Array = malloc( sizeof( ElementType ) * MaxElements );
    if( S->Array == NULL ) FatalError( "Out of space!!!" );
    S->Capacity = MaxElements;
    MakeEmpty( S );

    return S;
}

void
DisposeStack( Stack S )
{
    if( S )
    {
        free( S->Array );
        free( S );
    }
}

int
IsEmpty( Stack S )
{
    return S->TopOfStack == EmptyTOS;
}

void
MakeEmpty( Stack S )
{
    S->TopOfStack = EmptyTOS;
}

viod
Push( Elemtype X, Stack S )
{
    if( IsFull( S ) ) Error( "Full stack" );
    else S->Array[++S->TopOfStack] = X;
}

Elemtype
Top( Stack S)
{
    if( !IsEmpty( S ) ) return S->Array[ S->TopOfStack ];
    Error( "Empty stack " );
    return 0;   /* Return value used to avoid waring */
}

void
Pop( Stack S )
{
    if( IsEmpty( S )) Error( "Empty stack " );
    else S->TopOfStack--;
}

Elemtype
TopAndPop( Stack S)
{
    if( !IsEmpty( S ) ) return S->Array[ S->TopOfStack-- ];
    Error( "Empty stack " );
    return 0;   /* Return value used to avoid waring */
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

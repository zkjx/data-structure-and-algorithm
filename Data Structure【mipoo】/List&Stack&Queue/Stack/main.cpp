#include <iostream>
using namespace std;

#ifndef _Stack_h

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode Stack;

int IsEmpty( Stack S );
Stack CreateStack( void );
void DisposeStack( Stack S );
void MakeEmpty( Stack S );
void Push( Elemtype X , Stack S );
Elemtype Top( Stack S );
void Pop( Stack S );

#endif /* _Stack_h */

/* Place in implementation file */
/* Stack implementation is a linked list with a header */
struct Node{
    Elemtype Element;
    PtrToNode Next;
};

int
IsEmpty( Stack S )
{
    return S->Next == NULL;
}

Stack
CreateStack( void )
{
    Stack S;
    S = malloc( sizeof( struct Node ) );
    if( S == NULL) FatalError("Out of space !!!");
    S->Next == NULL;
    MakeEmpty( S );
    return S;
}

void
MakeEmpty( Stack S )
{
    if( S == NULL ) ERROR("Must use CreatStack First");
    else while( !IsEmpty( S )) Pop( S );
}

void
Push( Stack S )
{
    PtrToNode TmpCell;

    TmpCell = malloc( sizeof( struct Node ) );
    if( TmpCell == NULL ) FatalError("Out of space !!!");
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
}

ElementType
Top( Stack S )
{
    if( !IsEmpty( S ) ) return S->Next->Element;
    ERROR("Empty Stack");
    return 0; /* Return value used to avoid waring */
}

void
Pop( Stack S )
{
    PtrToNode FirstCell;
    if( IsEmpty( S ) ) ERROR("Empty Stack");
    else
    {
        FirstCell = S->Next;
        S->Next = S->Next->Next;
        free( FirstCell );
    }
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

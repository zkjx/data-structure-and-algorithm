#include <iostream>
using namespace std;

#ifndef _List_H

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

List MakeEmpty( List L );   //建立一个空链表
int IsEmpty( List L );
int IsLast( Position P , List L );
Position Find( ElemType X , List L );
void Delete( Elemtype X , List L );
Position FindPrevious( Elemtype X , List L );
void Insert( Elemtype X , List L , Position P );
void DeleteList( List L );
Position Header( List L );  //未实现
Position First( List L );   //未实现
Position Advance( Position P ); //未实现
ElementType Retrieve( Position P ); //未实现

#endif /* _List_H */

/* Place in the implementation file */

/* Make a new List */
List
MakeEmpty( List L )
{
    List L;

    L = malloc( sizeof( struct Node ) );
    if( L == NULL ) FatalError( "Out of space !!!");

    return L;
}

/* Return true if L is empty */
int
IsEmpty( List L )
{
    return L->Next == NULL;
}

/* Return true if P is the last position in List L */
/* Rarameter L is used in this implementation */
int
IsLast( Position P , List L )
{
    return P->Next == NULL;
}

/* Return Position of X in L ; NULL if not found */
Position
Find( Elemtype X , List L )
{
    Position P;
    P = L->Next;
    while(P && P->Element != X) P = P->Next;
    return P;
}

/* Delete first occurence of X from a list */
/* Assume use of a header node* */
void
Delete( Elemtype X , List L )
{
    Position P , TmpCell;

    P = FindPrevious( X , L );

    if(!IsLast( P , L) )    /* Assumption of header use*/
    {

        TmpCell = P->Next;
        P->Next = TmpCell->Next;    /* Bypass deleted Cell */
        free( TmpCell );
    }
}

/* If X is not found , then Next field of returned */
/* Position is NULL */
/* Assumes a header */
Position
FindPrevious( Elemtype X , List L )
{
    Position P;
    P = L;
    while(P->Next && P->Next->Element != X) P = P->Next;
    return P;
}

/* Insert( after legal position P ) */
/* Header implementation assumed */
/* Parameter L is unused in this implementation */
void
Insert( Elemtype X , List L , Position P )
{
    Position TmpCell;

    TmpCell = malloc( sizeof( struct Node ) );
    if( TmpCell == NULL ) FatalError( "Out of space !!!");

    TmpCell->Element = X;
    TmpCell->Next = P->Next;
    P->Next = TmpCell;
}

/* Delete List L */
void
DeleteList( List L )
{
    Position P , Tmp;

    P = L->Next;    /*Header assumed*/
    L->Next = NULL;

    while( P )
    {
        Tmp = P->Next;
        free( P );
        P = Tmp;
    }
}
struct Node
{
    Elemtype Element;   //int data
    Position Next;      //int* next;
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

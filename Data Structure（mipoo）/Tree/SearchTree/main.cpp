#include <iostream>
using namespace std;

#ifndef _Tree_H

struct TreeNode;
typedef struct TreeNode *Position;
typedef struct TreeNode *SearchTree;

SearchTree MakeEmpty( SearchTree T );
Position Find( ElementType X , SearchTree T );
Position FindMin( SearchTree T );
Position FindMax( SearchTree T );
SearchTree Insert( ElementType X , SearchTree T );
SearchTree Delete( ElementType X , SearchTree T );
ElementType Retrieve( Position P );
void PreOrder( SearchTree T );
void InOrder( SearchTree T );
void PostOrder( SearchTree T );
int Height( SearchTree T );

#endif /* _Tree_H */

/* Place in implementation file */
struct TreeNode
{
    ElementType Element;
    SearchTree Left;
    SearchTree Right;
};

SearchTree
MakeEmpty( SearchTree T )
{
    if(T)
    {
        MakeEmpty( T->Left );
        MakeEmpty( T->Right );
        free( T );
    }
    return NULL;
}

Position
Find( ElementType X , SearchTree T )
{
    if( T == NULL ) return NULL;
    if( X < T->Element ) return Find( X , T->Left );
    else
    if( X > T->Element ) return Find( X , T->Right );
    else return T;
}

Position
FindMin( SearchTree T ) /* 递归实现*/
{
    if( T == NULL ) return NULL;
    else
    if( T->Left == T ) return T;
    else return FindMin( T->Left );
}

Position
FindMax( SearchTree T ) /* 非递归实现 */
{
    if(T) while( T->Right ) T = T->Right;
    return T;
}

SearchTree
Insert( ElementType X , SearchTree T )
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof ( struct TreeNode ) );
        if( T == NULL ) FatalError( "Out of space!!!" );
        else
        {
            T->Element = X;
            T->Left = T->Right = NULL;
        }
    }
    else
    if( X < T->Element ) T->Left = Insert( X, T->Left );
    else
    if( X > T->Element ) T->Right = Insert( X , T->Right );
    /* Else X os in the tree already we'll do nothing */

    return T; /* Do not forget this line!!! */
}

/* 如果删除的次数不多,通常用懒惰删除(lazy deletion):做一个删除标记 而不做真正的删除 */
SearchTree
Delete( ElementType X , SearchTree T )
{
    Position TmpCell;

    if( T == NULL ) Error( "Element not found" );
    else
    if( X < T->Element ) T->Left = Delete( X , T->Left );

    else
    if( X > T->Element) T->Right = Delete( X , T->Right );

    else /* Found element to be deleted */
    if( T->Left && T->Right ) /* Twp children */
    {
        /* Replace with smallest in right subtree */
        TmpCell = FindMin( T->Right );
        T->Element = TmpCell->Element;
        T->Right = Delete( T->Element , T->Right);
    }
    else /*One or zero children */
    {
        TmpCell = T;
        if( T->Left == NULL ) T = T->Right; /* Also handle 0 children */
        else if( T->Right == NULL ) T = T->Left;
        free( TmpCell );
    }
    return T;
}

int
Height( SearchTree T )
{
    if( T == NULL ) return -1;
    return 1 + max( Height( T->Left ) , Height( T->Right ) );
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

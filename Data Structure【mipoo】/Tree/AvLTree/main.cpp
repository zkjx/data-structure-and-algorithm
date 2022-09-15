#include <iostream>
using namespace std;

#ifndef _AvLTree_H

struct AvlNode;
typedef struct AvlNode *Position;
typedef struct AvlNode *AvlTree;

AvlTree MakeEmpty( AvlTree T );
Position Find( ElementType X , AvlTree T );
Position FindMin( AvlTree T );
Position FindMax( AvlTree T );
AvlTree Insert( ElementType X , AvlTree T );
AvlTree Delete( ElementType X , AvlTree T );
ElementType Retrieve( Position P );
static int Height( Position P );
AvlTree SingleRotateWithLeft( Position P );     //LL
AvlTree SingleRotateWithRight( Position P );    //RR
AvlTree DoubleRotateWithLeft( Position P );     //LR : LR型就是先做RR型再做LL型旋转 故名双旋转
AvlTree DoubleRotateWithRight( Position P );    //RL ：RL型就是先做LL型再做RR型旋转
#endif /* _AvLTree_H */


/* Place in implementation file */
struct AvlNode
{
    ElementType Element;
    AvlTree Left;
    AvlTree Right;
    int Height;
};

static int
Height( Position P )
{
    if( P == NULL ) return -1;
    else return P->Height;
}

AvlTree
Insert( ElementType X , AvlTree T )
{
    if( T == NULL )
    {
        /* Create and return a one-node tree */
        T = malloc( sizeof ( struct AvlNode ) );
        if( T == NULL ) FatalError( "Out of space!!!" );
        else
        {
            T->Element = X; T->Height = 0; //根节点的深度为0
            T->Left = T->Right = NULL;
        }
    }
    else
    if( X < T->Element )
    {
        T->Left = Insert( X , T->Left );
        if( Height( T->Left ) - Height( T->Right ) == 2 )
            if( X < T->Left->Element )
                T = SingleRotateWithLeft( T );  //单旋转
            else
                T = DoubleRotateWithLeft( T );  //双旋转
    }
    else
    if( X > T->Element )
    {
        T->Right = Insert( X , T->Right );
        if( Height( T->Right ) - Height( T->Left ) == 2 )
            if( X > T->Right->Element )
                T = SingleRotateWithRight( T );
            else
                T = DoubleRotateWithRight( T );
    }
    /* Else X is in the tree alreadly;we'll do nothing */

    T->Height = max( Height( T->Left ) , Height( T->Right ) ) + 1;
    return T;
}

/* This function can be called only if k2 has a left child */
/* Perfrom a retate between a node (k2) and its left child */
/* Update height , then return new root */
/*      k2                      */
/*     /      LL       k1       */
/*    k1     ---->    /  \      */
/*   /               x    k2    */
/*  x                           */
static Position
SingleRotateWithLeft( Position K2 ) /* LL型旋转就是把中间节点提上来 */
{
    Position K1;

    K1 = K2->Left;
    K2->Left = K1->Right;
    K1->Right = K2;

    K2->Height = max( Height( K2->Left ) , Height( K2->Right ) + 1 ) + 1;
    K1->Right = max( Height( K1->Left ) , K2->Height ) + 1;

    return K1; /* New root */
}

/* This function can be called only if K3 has a left */
/* child and K3's left child has a right child */
/* Do the left-right double rotation */
/* Update heights , then return new root */

/*        k3                k3                  K2         */
/*       /  \     RR       /  \     LL         /  \        */
/*     k1    D   ---->    k2   D   ---->      /    \       */
/*    /  \               /  \               K1      K3     */
/*   A    k2            k1   C             /  \    /  \    */
/*       /  \          /  \               A    B  C    D   */
/*      B    C        A    B                               */
static Position
DoubleRotateWithLeft( Position K3 ) /* LR型就是先做RR旋转再做LL旋转 */
{
    /* Rotate between K1 and K2 */
    K3->Left = SingleRotateWithLeft( K3->Left );

    /* Rotate betweem K3 and K2 */
    return SingleRotateWithLeft( K3 );
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

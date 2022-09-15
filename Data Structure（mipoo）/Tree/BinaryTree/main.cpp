#include <iostream>
using namespace std;

typedef struct TreeNode *PtrToNode;
typedef struct PtrToNode BinaryTree;

int Height( SearchTree T );

struct TreeNode
{
    ElementType Element;
    Tree Left;
    Tree Right;
};

int
Height( BinaryTree T )
{
    if( T == NULL ) return -1;
    return 1 + max( Height( T->Left ) , Height( T->Right ) );
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

#include <iostream>
using namespace std;

typedef unsigned int Index;

Index Hash( const char *key , int TableSize );
Index Hash_2( const char *key , int TableSize );
Index Hash_3( const char *key , int TableSize );

Index
Hash( const char *key , int TableSize )
{
    unsigned int HashVal = 0;

    while( *key != '\0' ) HashVal += *key; /* ASCII码之和 */
    return HashVal % TableSize;
}

Index
Hash_2( const char *key , int TableSize )
{
    return( key[ 0 ] + 27 * key[ 1 ] + 729 * key[ 2 ] ) % TableSize;
}

Index
Hash_3( const char *key , int TableSize )
{
    unsigned int HashVal = 0;
    while( *key != '\0' ) HashVal = ( HashVal << 5 ) + *key++;
    return( key[ 0 ] + 27 * key[ 1 ] + 729 * key[ 2 ] ) % TableSize;
}

#ifndef _HashSep_H /* 使用链接法解决冲突的HASHTABLE */

struct ListNode;
typedef struct ListNode *Position;
struct HashTbl;
typedef struct HashTbl *HashTable;

HashTable InitializeTable( int TableSize );
void DestoryTable( HashTable H );
Position Find( ElementType Key , HashTable H );
void Insert( ElementType Key , HashTable H );
ElementType Retrieve( Position P );
/* Routines such as Delete and MakeEmpty are omitted */

#endif /* _HashSep_H */



/* Place in implementation file */
struct ListNode
{
    ElementType Element;
    Position Next;
};

typedef Position List;

/* List *TheList will be an array of lists, allocated later */
/* The lists use headers */
/* through this wastes space */
struct HashTbl
{
    int TableSize;
    List *TheLists;
};

HashTable
InitializeTable( int TableSize )
{
    HashTable H;

    if( TableSize < MinTableSize)
    {
        Errir( "Table size too small" );
        return NULL;
    }

    /* Allocate table */
    H = malloc( sizeof( struct HashTbl ) );
    if( H == NULL ) FatalError( "Out of space!!!" );

    H->TableSize = NextPrime( TableSize );

    /* Allocate array if lists */
    H->TheLists = malloc( sizeof( List ) * H->TableSize ) ;
    if( H->TheLists == NULL )  FatalError( "Out of space!!!" );

    /* Allocate list headers */
    for(int i = 0 ; i < H->TableSize; i++ )
    {
        H->TheLists[ i ] = malloc( sizeof( struct ListNode ) );
        if(H->TheLists[ i ] == NULL ) FatalError( "Out of space!!!" );
        else H->TheLists[ i ]->Next = NULL;
    }

    return H;
}

Position
Find( ElemmentType Key , HashTable H )
{
    Position P;
    List L;

    L = H->TheLists[ Hash( key , H->TableSize ) ];
    P = L->Next;
    while( P && P->Element != key ) P = P->Next; //用strcmp重载 ！=
    return P;
}

void
Insert( ElementType Key , HashTable H )
{
    Position Pos , NewCell;
    List L;

    Pos = Find( Key , H );
    if( Pos == NULL ) /* Key is not found */
    {
        NewCell = malloc( sizeof( struct ListNode ) );
        if( NewCell == NULL ) FatalError( "Out of space!!!" );
        else
        {
            L = H->TheLists[ Hash( Key , H->TableSize ) ];
            NewCell->Next = L->Next;
            NewCell->Element = Key; /* 用strcpy重载= */
            L->Next = NewCell;
        }
    }
}

#ifndef _HashQuad_H /* 使用开放定址法解决冲突的HASHTABLE */

// typedef unsigned int Index;
typedef Index Position_Quad

struct HashTbl_Quad ;
typedef struct HashTbl_Quad *HashTable_Quad;

HashTable_Quad InitializeTable_Quad( int TableSize );
void DestoryTable_Quad( HashTable_Quad H );
Position_Quad Find_Quad( ElementType Key , HashTable_Quad H );
void Insert_Quad( ElementType Key , HashTable_Quad H );
ElementType Retrieve_Quad( Position_Quad P , HashTable_Quad H );
HashTable_Quad Rehash_Quad(HashTable_Quad H );

/* Routines such as Delete and MakeEmpty are omitted */

#endif /* _HashQuad_H */


/* Place in implementation file */
enum KindOfEntry { Legitimate , Empty , Deleted }; //enum　枚举名　{枚举元素1,枚举元素2,……};

struct HashEntry
{
    ElementType Element;
    enum KindOfEntry Info;
};

typedef struct HashEntry Cell;

/* Cell *TheCells will be an array of */
/* HashEntry cells , allocated later */
struct HashTbl_Quad
{
    int TableSize;
    Cell *TheCells;
};

HashTbl_Quad
InitializeTable_Quad( int TableSize )
{
    HashTbl_Quad H;

    if( TableSize < MinTableSize)
    {
        Errir( "Table size too small" );
        return NULL;
    }

    /* Allocate table */
    H = malloc( sizeof( struct HashTbl_Quad ) );
    if( H == NULL ) FatalError( "Out of space!!!" );

    H->TableSize = NextPrime( TableSize );

    /* Allocate array if lists */
    H->TheCells = malloc( sizeof( Cell ) * H->TableSize ) ;
    if( H->TheCells == NULL )  FatalError( "Out of space!!!" );

    /* Allocate list headers */
    for(int i = 0 ; i < H->TableSize; i++ )
        H->TheCells[i].Info = Empty;

    return H;
}

Position_Quad
Find_Quad( ElementType Key , HashTable_Quad H )
{
    Position_Quad CurrentPos;
    int CollisionNum;

    CollisionNum = 0;
    CurrentPos = Hash( Key , H->TableSize );
    while( H->TheCells[ CurrentPos ].Infp != Empty && H->TheCells[ CurrentPos ].Element != Key ) //用strcmp重载！=
    {
        CurrentPos += 2 * ++CollisionNum -1;
        if(CurrentPos >= H->TableSize ) CurrentPos -= H->TableSize;
    }

    return CurrentPos;
}

void
Insert_Quad( ElementType Key , HashTable_Quad H )
{
    Position Pos;

    Pos = Find( Key , H );
    if( H->TheCells[ Pos ].Info != Legitimate ) //用strcmp重载！=
    {
        /* OK to insert here */
        H->TheCells[ Pos ].Info = Legitimate;
        H->TheCells[ Pos ].Element = Key;  // //用strcpy重载=
    }
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

#include <iostream>
using namespace std;

typedef struct TreeNode *PtrToNode;

struct TreeNode //左孩子右兄弟表示法 *在UNIX系统中文件的实现使用三叉树 其中一项指向父目录*
{
    ElementType Element;
    PtrToNode FirstChild;
    PtrToNode NextSibling;
};

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}

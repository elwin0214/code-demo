#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;


struct str
{
    int len;
    int free;
    char buf[];
};

str* salloc(int len)
{
    str *p = (str*)malloc(sizeof(str) + len);
    p->len = len;
    p->free = len;
    return p;
};

void sfree(str *s)
{
    free(s);
};

size_t append(str *ps, const char* s, size_t len)
{   

    memcpy(ps->buf, s, len);
    ps->free = ps->free - len;
    return len;
};

int main()
{
    cout << sizeof(str) << endl;
    int len = 10;
    str* ps = salloc(10);
    append(ps, "abc", len);

    cout<< string(ps->buf, ps->len - ps->free)<<endl;

     

    return 0;
}
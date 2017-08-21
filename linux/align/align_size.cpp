#include <iostream>

using namespace std;

struct S1 
{
short b[3];
};

struct S2 
{
short b[3];
} __attribute__ ((aligned (8)));

int main()
{
    cout<<"sizeof(short)=" <<sizeof(short)<<endl;
    cout<<"sizeof(S1)=" <<sizeof(S1)<<endl;
    cout<<"sizeof(S2)=" <<sizeof(S2)<<endl;//8
    cout<<"sizeof(1)=" <<sizeof(1)<<endl;//8
    return 0;
}
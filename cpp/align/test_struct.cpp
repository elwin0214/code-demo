#include <iostream>

using namespace std;

struct A
{
    
};
struct AC : public A
{
    
};

struct B
{
    A a;
};


struct C
{
    char a;
};
struct D : C
{
    int i;
};

struct E
{
    C c;//1
    int i;
};


struct A1
{
virtual void f();
};

struct A2 : public A1
{
virtual void f()
{

}
};

int main()
{
    cout<< sizeof(A) <<endl; //1
    cout<< sizeof(AC) <<endl; //1

    cout<< sizeof(B) <<endl; //1
    cout<< sizeof(C) <<endl; //1
    cout<< sizeof(D) <<endl; //8
    cout<< sizeof(E) <<endl; //8
    cout<< sizeof(A1) <<endl; //8 64位

}
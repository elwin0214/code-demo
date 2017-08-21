#include <iostream>

using namespace std;

class A
{

public:
    virtual void f()
    {
        cout<< "A.f()"<<endl;
    }
};


class B : public A
{
public:
    virtual void f()
    {
        cout<< "B.f()" <<endl;
    }
private:
    int value;
};



int main()
{
    A a1;
    cout<< sizeof(A) <<endl;
    A a2;
    a2 = a1;

    B b1;
    cout<<"sizeof(B)" <<sizeof(B) <<endl;
    a1 = b1;//会合成构造函数
    a1.f();
}
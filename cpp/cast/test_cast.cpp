#include <iostream>

using namespace std;

class A
{
public:
    virtual void f(){cout << "A.f()" <<endl; }
};

class B
{
public:
    virtual void f(){cout << "B.f()" <<endl; }
};

class C : public A , public B
{
public:
    virtual void f(){cout << "C.f()" <<endl; }
};

int main()
{
    C c;
    B* pb = static_cast<B*>(&c);//类型相关
    pb->f();

    cout << pb <<" == " << &c  << ":" << (pb == (&c)) << endl;  //true 实际地址不相同

    B* pb2 = reinterpret_cast<B*>(&c);//类型不相关
    pb2->f();//C.f

    cout << pb2 <<" == " << &c  << ":" << (pb2 == (&c)) << endl;  //true 地址相同

    return 0;
}


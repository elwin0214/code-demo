#include <iostream>

using namespace std;

struct test
{

    test()
    {
        call();
    }
    void noconstobj_call_const() const
    {
        cout<<"noconstobj_call_const() const"<<endl;

    }
    void f() const
    {
        cout<<"f() const"<<endl;
    }
    void f()
    {
        cout<<"f()"<<endl;
    }
    void call()//const wont go here
    {
        f();
    }
    void call() const
    {
        f();
    }

    void only_const() const //会当做一个const 对象来调用
    {
        cout<<"only_const()"<<endl;
    }

};

void call_test(test t)
{

};
void call_const_test(const test &t)
{

};

int main()
{
    test t;
    t.f();
    const test &ct = t;
    ct.f();
    ct.call();
    call_test(test());//no const
    call_const_test(test());//no const
    t.noconstobj_call_const();
    t.only_const();
}


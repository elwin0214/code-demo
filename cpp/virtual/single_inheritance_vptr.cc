#include <iostream>
#include <typeinfo>

// 32位系统 (Fun)*((int*)*(int*)(&b)+0);
// 64位系统 (Fun)*((long*)*(long*)(&b)+0); 或者 (Fun)*((int**)*(int**)(&b)+0);
using namespace std;

class Base
{
public:
    virtual void f(){cout << "Base::f" << endl;}
    virtual void g(){cout << "Base::g" << endl;}

};

class Derive : public Base
{
public://这里换成private 照样运行
    virtual void f(){cout << "Derive::f" << endl;cout << "addr=" << this<<endl;}
public:
    virtual void f1(){cout << "Derive::f1" << endl;cout << "addr=" << this<<endl;}
    virtual void g1(){cout << "Derive::g1" << endl;}  
};



typedef void (*Func)(void);
Func vfunc(int **objAddr, int index)
{
    return (Func)*((int**)*objAddr + index);
};


int main()
{
    Base b;
    vfunc((int**)&b, 0)();
    vfunc((int**)&b, 1)();
    //vfunc((int*)&b, 2)();
    //vfunc((int*)&b, 3)();

    Derive d;
    vfunc((int**)&d, 0)();
    vfunc((int**)&d, 1)();
    vfunc((int**)&d, 2)();
    vfunc((int**)&d, 3)();

    Base *p = &d;
    p->f();

    cout <<  typeid(p).name()  <<endl;  //base 
    cout <<  typeid(*p).name()  <<endl;  //base 
    cout <<  typeid(&d).name()  <<endl;

    //d.f();
    return 0;
}
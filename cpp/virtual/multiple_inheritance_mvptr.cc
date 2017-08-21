#include <iostream>

// 32位系统 (Fun)*((int*)*(int*)(&b)+0);
// 64位系统 (Fun)*((long*)*(long*)(&b)+0); 或者 (Fun)*((int**)*(int**)(&b)+0);
using namespace std;

class Base1
{
public:
    virtual void f(){cout << "Base1::f" << endl;}
    virtual void g(){cout << "Base1::g" << endl;}

};

class Base2
{
public:
    virtual void f(){cout << "Base2::f" << endl; }
    virtual void g(){cout << "Base2::g" << endl;}

};


class Derive : public Base1, public Base2
{
public:
    virtual void f(){cout << "Derive::f" << endl;cout << "addr=" << this<<endl;}

public:
    virtual void f1(){cout << "Derive::f1" << endl;}
    virtual void g1(){cout << "Derive::g1" << endl;}  
};



typedef void (*Func)(void);
Func vfunc(int **objAddr, int index)
{
    return (Func)*((int**)*objAddr + index);
};

int main()
{
    cout << sizeof(Derive) <<endl;// 2 个vptr
    Derive d;
    vfunc((int**)&d, 0)();//Base1 
    vfunc((int**)&d, 1)();
    vfunc((int**)&d, 2)();
    vfunc((int**)&d, 3)();

    cout << "====Base2 vptr" <<endl;
    vfunc((int**)&d + 1, 0)();//Base2
    vfunc((int**)&d + 1, 1)();

    Base2 *pb = &d;
    pb->f(); //静态编译 

    Base1 *pb1 = &d;
    pb1->f(); //静态编译 

    return 0;
}



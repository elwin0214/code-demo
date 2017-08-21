#include <iostream>

using namespace std;
struct A
{
    A()
    {
        cout<<"A()" <<endl;
    }
};

struct B
{
    B()
    {
        cout<<"B()" <<endl;
    }
};

struct C
{
    A a_;  //先初始化
    B b_;

    C():b_(),a_()
    {
        cout<<"C()" <<endl;
    }
};
struct D
{
    A a_; //调用A()  
 
    D()
    {
        cout<<"D()" <<endl;
    }
};

struct A1
{
    A1(int i)
    {
        cout<<"A()" <<endl;
    }
};

struct A2
{   
    const A1 &a1_;
    A2(A1 a1):a1_(a1)
    {
        cout<<"A()" <<endl;
    }
};

struct A3
{   

    A1 a1;
    A2 a2;// a2 依赖于 a1 构造，必须声明在a1后面， 按声明顺序构造

    A3():a1(1),a2(a1)
    {
        cout<<"A()" <<endl;
    }
};



int main()
{   C *p1 = new C;
    C *p2 = new C();
    C c;
    cout << " to D "<< endl;
    D d;
    return 0;
}
#include <iostream>
using namespace std;

struct A
{
  A()
  {
    cout << "A()" << endl;
  }

  A(const A&)
  {
    cout << "A(const A&)" << endl;
  }

  A& operator=(const A&)
  {
    cout << "A& operator=(const A&)" << endl;
    return *this;
  }

  A(A &&a)
  {
    cout << "A(A&&)" << endl;
  }

  A& operator=(A&&)
  {
    return *this;
  }

  ~A()
  {
    cout << "~A()" << endl;
  }

};


struct B
{
  B(A a):a_(std::move(a))
  {

  }

  ~B()
  {
    cout << "~B()" << endl;
  }

  A a_;
};

struct C
{
  C(A &&a):a_(a)  //copy
  {

  }
  
  ~C()
  {
    cout << "~C()" << endl;
  }

  A a_;
};

struct D
{
  D(A &&a):a_(std::move(a))  //move
  {

  }
  
  ~D()
  {
    cout << "~D()" << endl;
  }

  A a_;
};


int main()
{
  {
    A a;  //con
    B b(a);// copy + move
  }
  /*
  A()
  A(const A&)
  A(A&&)
  ~A()
  ~B()
  ~A()
  ~A()
*/

  {
    A a;  //con
    C c(std::move(a));//copy
  }
  /*
  A()
A(const A&)
~C()
~A()
~A()
*/
  {
    A a;  //con
    D d(std::move(a));//move
  }
  /*
  A()
A(A&&)
~D()
~A()
~A()
*/

  //B b2(A());
  return 0;
}
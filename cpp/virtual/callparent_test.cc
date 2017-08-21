#include <iostream>

using namespace std;


struct P
{
  int value;

  P():value(0)
  {

  }
  virtual void f()
  {
    value = value + 1;
    cout << "P::f()" << endl;
    g();
  }

  void g()
  {
    cout << "P::g()" << endl;
  }
};

struct C : public P
{
  virtual void f()
  {
    P::f();
    value = value + 2;
    cout << "C::f()" << value << endl;
    g();// C::g()
  }

  void g()
  {
    cout << "C::g()" << endl;
  }
};

int main()
{
  C c;
  P *p = &c;
  p->f(); 
}


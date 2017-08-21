#include <iostream>
using namespace std;
struct A
{
  template<typename T>
  void f(T t)
  {
    cout << "A::f(T t)" << endl;
  }

  template<int>
  void f(int i)
  {
    cout << "A::f(int i)" << endl;
  }
};

int main()
{
  A a;
  //a.template f("string");
  a.f("string");
  a.f(1);
  a.template f(1);

}

#include <iostream>
#include <string>

using namespace std;

struct A
{

};

struct B : public A
{

};

struct C
{
  
};
int main()
{
  B* pb = new B();
  A* pa = static_cast<A*>(pb);
  A* pa1 = new A();
  pb = static_cast<B*>(pa1);

  //A* pa2 = static_cast<A>(new C());
  //pb = dynamic_cast<B*>(pa);
  return 0;
}
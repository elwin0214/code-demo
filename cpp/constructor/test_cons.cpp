#include <iostream>
#include <vector>

using namespace std;

class A
{
public:
 A()
{
}

int f()
{
  int sum = 0;
  for(int i=0;i<100;i++)
  {
    sum = sum +i;
  }
  return sum;
}
};

class B
{

};

class C : public B
{

};

int main()
{
    // A a;
    // A b;
    // A c(a);
    // A d = c;
  A a;
  a.f();

  vector<B> vb(10);

  B *p = new C();
  C *pc = dynamic_cast<C*>(p);
  return 0;
}

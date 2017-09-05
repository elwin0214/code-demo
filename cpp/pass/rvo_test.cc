#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

struct A
{
  A()
  {
    A::count_construct++;
  }
  
  A(const A&)
  {
    A::count_copyconstruct++;
  }
  static int count_construct ;
  static int count_copyconstruct ;

  static void clear()
  {
    A::count_construct = 0;
    A::count_copyconstruct = 0;
  }
};

int A::count_construct = 0;
int A::count_copyconstruct = 0;

A f(bool i)
{
  A a;
  A b;
  if (i)
  {
    return a;
  }
  else
    return b;
}

A g()
{
  A a;
  return a;
}
int main()
{
  A a1 = f(true); // copy
  assert(1 == A::count_copyconstruct);
  A::clear();
  A a2 = g();
  assert(1 == A::count_construct);
  assert(0 == A::count_copyconstruct);

  return 0;
}
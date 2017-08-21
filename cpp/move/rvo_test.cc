#include <iostream>
#include <string>

using namespace std;

struct A
{
  A()
  {

  }
  
  A(const A&)
  {
    cout << "copy" << endl;
    //return *this;
  }

};

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
int main()
{
  f(true); // copy
  return 0;
}
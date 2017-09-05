#include <iostream>
using namespace std;

struct A
{
  A()
  {

  }

  A(const A&)
  {
    cout << "A(const A&)" << endl;
  }

  A& operator=(const A&)
  {
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
};


struct B
{
  B(A a):a_(std::move(a))
  {

  }
  A a_;
};

int main()
{
  A a;
  B b(a);
  //B b2(A());
  return 0;
}
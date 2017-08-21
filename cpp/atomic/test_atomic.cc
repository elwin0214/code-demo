#include <atomic>
#include <iostream>

namespace test
{
using namespace std;

class A
{
  
};

class B
{
  ~B()
  {

  }
};

class Test
{
public:
  Test():a(1)
  {

  }
  void f()
  {
    int sum = a + 1;
    cout << sum << endl;
  }
private:
  atomic<int> a;
};

}

int main()
{
  std::atomic<int> ai;
  std::atomic<test::A> a;

  //atomic<B> b;

}
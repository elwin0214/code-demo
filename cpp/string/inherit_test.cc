#include <iostream>
using namespace std;

template<typename T>
class Test
{
public:
  static void f(T t);//{return true;}
};

class CTest : public Test<char>
{
public:
  static void f(char c) { cout << "CTest::f()" << endl; }
};

int main()
{
  CTest::f('a');
  return 0;
}
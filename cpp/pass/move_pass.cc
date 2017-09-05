#include <iostream>
#include <string>

using namespace std;
/*
（1）非const左值引用只能绑定到非const左值；

（2）const左值引用可绑定到const左值、非const左值、const右值、非const右值；

（3）非const右值引用只能绑定到非const右值；

（4）const右值引用可绑定到const右值和非const右值。
*/

//http://www.cnblogs.com/catch/p/3507883.html
//http://zh.cppreference.com/w/cpp/utility/forward
//Things that are declared as rvalue reference can be lvalues or rvalues.
// The distinguishing criterion is: if it has a name, then it is an lvalue. Otherwise, it is an rvalue.

struct A
{
  void call(const std::string& value)
  {
    cout << "A::call(const &)" << endl;
  }

  void call(std::string&& value)
  {
    cout << "A::call(&&)" << endl;
  }

};

struct B
{
  void call(const std::string& value)
  {
    cout << "B::call(const &)" << endl;
  }
};

int main()
{
  std::string s1 = "abc";
  A a;
  a.call(s1); //A::call(const &)
  a.call(std::move(s1)); //A::call(&&)
  a.call("abc"); //A::call(&&)

  B b;
  b.call(std::move(s1));//B::call(const &)
  b.call("abc");//B::call(const &)

  return 0;
}
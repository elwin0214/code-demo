#include <string>
#include <iostream>

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
void f(string&& s)
{
 cout << "f(string&& s)" << endl;
};

void f(const string& s)
{
  cout << "f(const string& s)" << endl;
};

int main()
{
  f("abc");//lvalue rvalue 区别是是否有名字？？

  return 0;
}


#include <iostream>
#include <string>

using namespace std;

struct A
{
  void call(const std::string& value)
  {
    cout << "const &" << endl;
  }

  void call(std::string&& value)
  {
    cout << "&&" << endl;
  }

};

int main()
{
  std::string s1 = "abc";
  A a;
  a.call(s1);
  a.call(std::move(s1));
  return 0;
}
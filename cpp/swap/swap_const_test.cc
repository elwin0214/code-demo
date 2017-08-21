#include <vector>
#include <iostream>

using namespace std;



int main()
{
  vector<string> vec;
  vector<string> tmp;
  //vec.swap(std::vector<string>());// error std::vector<string>() cannot bind to no-const lvalue
  // swap 会改变参数内部。hash
  vec.swap(tmp);//void swap( vector& other );
  return 0;
}

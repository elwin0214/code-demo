#include <stdio.h>
#include "test_disass_con.h"


Test::Test()
{

};

Test::Test(int i, int j):value_(i+j)
{

};

void Test::noinline_func()
{
  for (int i = 0; i < 100; i++)
    value_ = value_ + i;
};

Test::~Test()
{

};


class UndefinedConstructor
{

};

struct DefinedConstructor
{
 DefinedConstructor(){}
};


struct WrapperUndefinedConstructor    //1处调用才会 创建默认构造函数
{
DefinedConstructor b;
};
//g++ -o test_disass_con.o test_disass_con.cc -g
//otool -tV test_disass_con.o 
int main()
{
  UndefinedConstructor ta;
  //WrapperUndefinedConstructor tc;  //1
  Test t1;
  Test t2(2);
  Test t3(3, 4);

  return 0;
}
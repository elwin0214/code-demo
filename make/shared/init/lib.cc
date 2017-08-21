#include "lib.h"
#include <iostream>

using namespace std;

Test::Test()
{
  cout << "Test()" << endl;
};

Test::~Test()
{
  cout << "~Test()" << endl;
};

Test Test::instance;


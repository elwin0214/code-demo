#include "lib.h"
#include <iostream>
using namespace std;

int main()
{
  cout << "main()" <<endl;
}

/*
Test()
main()
~Test()
*/

//g++ -fPIC -shared lib.cc -c  -o lib.so 
// g++ main.cc  lib.so  -o main -Xlinker -rpath ./
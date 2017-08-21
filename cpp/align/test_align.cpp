#include <iostream>
using namespace std;

struct A
{
  int i;
};

struct B
{
  long i;
};

struct C
{
  char i;
};//1

struct D
{
  char a[5];
};//

struct E
{
    char a[];
};//

int main()
{
  cout<< sizeof(A) <<endl;//4
  cout<< sizeof(B) <<endl;//8
  cout<< sizeof(C) <<endl;//1
  cout<< sizeof(D) <<endl;//5
  cout<< sizeof(E) <<endl;//0
  return 0;
}
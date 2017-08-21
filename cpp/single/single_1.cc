#include <iostream>
#include <string>

using namespace std;


template<typename T>
class Singleton
{

public:
  static T* get()
  {
    static T t;
    return &t;
  }
};

struct D
{
  ~D()
  {
    cout << "~D()" << endl;
  }
};

int main()
{
  D* pd = Singleton<D>::get();

  return 0;
}



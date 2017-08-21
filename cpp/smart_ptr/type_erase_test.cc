#include <functional>
#include <iostream>
using namespace std;

template <typename T>
void delete_deleter(void* p) 
{
  delete static_cast<T*>(p);
}

template <typename T>
struct my_unique_ptr 
{
  std::function<void(void*)> deleter;
  T * p;

  template <typename U>
  my_unique_ptr(U* p, std::function<void(void*)> deleter = &delete_deleter<U>) 
     : p(p), deleter(deleter) 
  {

  }

  ~my_unique_ptr() 
  {
    deleter(p);   
  }
};

struct A
{
  ~A()
  {
    cout << "~A()" << endl;
  }
};

int main() {
   my_unique_ptr<void> p(new A()); // deleter == &delete_deleter<A>
}
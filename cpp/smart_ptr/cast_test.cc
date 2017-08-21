#include <iostream>
#include <memory>

using namespace std;
//  1.type erase in shared_ptr & unique_ptr
//  If T is a derived class of some base B, then std::unique_ptr<T> is implicitly
//  convertible to std::unique_ptr<B>. The default deleter of 
//  the resulting std::unique_ptr<B> will use operator delete for B, 
//  leading to undefined behavior unless the destructor of B is virtual.
//  Note that std::shared_ptr behaves differently: std::shared_ptr<B>
//  will use the operator delete for the type T and the owned object 
//  will be deleted correctly even if the destructor of B is not virtual.
struct P
{
  void f() { cout << "f()" << endl;}

  ~P() { cout << "~P()" << endl; }
};

struct C : public P
{
  ~C() { cout << "~C()" << endl; }
};

struct VP
{

  void f() { cout << "f()" << endl; }

  virtual ~VP() { cout << "~VP()" << endl; }
};

struct VC : public VP
{
  virtual ~VC() { cout << "~VC()" << endl; }
};

int main()
{
  
  cout << "static_cast for shared_ptr" << endl;
  {
    shared_ptr<void> ptr(new C());
    shared_ptr<P> p_ptr = static_pointer_cast<P>(ptr);
    p_ptr.reset();
    ptr.reset();
  }
   
  cout << "static_cast can not be used for unique_ptr" << endl;
  {
   //unique_ptr<C> p1(new C());
   //unique_ptr<P> p2 = static_pointer_cast<P>(p1); // error
    unique_ptr<P> ptr1(new C());// ~P()
    unique_ptr<VP> ptr2(new VC());// ~VC ~VP()
  }
  return 0;
}
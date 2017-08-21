#include <functional>
#include <memory>
#include <string>
#include <iostream>


using namespace std;

class C : public std::enable_shared_from_this<C>
{

public:
  void f()
  {
    shared_ptr<C> p = shared_from_this();
    p->g();
  }
    
  void g()
  {
    cout<< "g()" <<endl;
  }
    
  ~C()
  {
    cout<<"~C()" <<endl;
  }
};

int main()
{
  shared_ptr<C> sp = make_shared<C>();
  sp->f();

  shared_ptr<C> sp2(new C());
  sp2->f();
}

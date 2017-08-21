#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;
/*
（1）非const左值引用只能绑定到非const左值；

（2）const左值引用可绑定到const左值、非const左值、const右值、非const右值；

（3）非const右值引用只能绑定到非const右值；

（4）const右值引用可绑定到const右值和非const右值。

*/
class A
{

public:
  A(int value):value_(value)
  {

  }
  A(const A& a):value_(a.value_)
  {
    cout << "A(const A& a) value = " << (a.value_) << endl;
  }

  A& operator=(const A& a)
  {
    value_ = a.value_;
    cout << "A& operator=(const A& a) value = " << (a.value_) << endl;
    return *this;
  }

  A(const A&& a):value_(a.value_)
  {
    cout << "A(const A&& a) value_ = " << (value_) << " value = " << a.value_ << endl;
  }

  A& operator=(const A&& a)
  {
    value_ = a.value_;
    cout << "A& operator=(const A&& a) value = " << (a.value_) << endl;
    return *this;
  }

private:
  int value_;
};

struct B
{

};

void const_lvalue(const A& a)
{
 A a1 = a;
};

void const_rvalue(const A&& a)
{
 A a1 = a;//std::move(a);  //copy
};
void const_rvalue_noconst(A&& a)
{
 A a1 = std::move(a);   //move 必须要加上 move才可以 
};

A&& return_rvalue()
{
  A a(2);//std::move(a);
 return std::move(a);
};

int main()
{

  B b;
  B b1(std::move(b));//ok

  A a(1);
  A ta_2(2);
  vector<A> vec;

  cout << "goto push" << endl;
  vec.push_back(std::move(a));
  cout << "vec.capacity = " << vec.capacity() << endl;
  vec.push_back(std::move(ta_2));//move
  cout << "vec.capacity = " << vec.capacity() << endl;
  vec.push_back((ta_2));//copy
  cout << "vec.capacity = " << vec.capacity() << endl;
  vec.push_back(A(3));//move
  cout << "vec.capacity = " << vec.capacity() << endl;

  unique_ptr<A> pa(new A(1));
  //unique_ptr<A> pa_1(pa);
  unique_ptr<A> pa_1(std::move(pa));
  //unique_ptr<A> pa_2 = pa_1 ;//(std::move(pa));


  const_rvalue(A(3));
  cout << "call : const_lvalue(std::move(a));" << endl;
  const_lvalue(std::move(a));

  cout << "call : const_rvalue(std::move(a));" << endl;
  const_rvalue(std::move(a)); //copy

  cout << "call : const_rvalue_noconst(std::move(a));" << endl;
  const_rvalue_noconst(std::move(a)); //move

  const A& c = a;
  //cout << "call : const_rvalue_noconst(std::move(c));" << endl;
  //const_rvalue_noconst(std::move(c));   error



  cout << "================call : A a2 = return_rvalue();" << endl;
  A&& a2 = return_rvalue();//move

  cout << "================call : return_rvalue();" << endl;
  return_rvalue(); //null

  cout << "================call : const A& a3 = std::move(a);" << endl;
  const A& a3 = std::move(a);
  A a4 = a3; //copy 

  A a5 = std::move(a3); //move 

  A&& a6 = std::move(a); //引用
  A a7 = a6; //copy
  //

}

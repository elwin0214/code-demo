#include <map>
#include <iostream>
#include <assert.h>
using namespace std;

struct C
{ 
  C(){}
  C(const C& c) 
  {
    if (this == &c) return;
    count_copy_con += 1;
  }
  C(C&& c) {
    if (this == &c) return;
    count_move_con += 1;
  }
  C& operator=(const C& c)
  { 
    if (this == &c) return *this;
    count_copy_assign += 1;
    return *this;
  }
  C& operator=(C&& c)
  { 
    if (this == &c) return *this;
    count_move_assign += 1;
    return *this;
  }

  ~C() 
  {
   //cout << "~C()" << endl;
  }
  static void print_count()
  {
    cout << "cc = " << count_copy_con 
         << " mc = " << count_move_con
         << " ca = " << count_copy_assign
         << " ma = " << count_move_assign << endl;
  }
  static void clean()
  {
    count_copy_con = 0;
    count_move_con = 0;
    count_copy_assign = 0;
    count_move_assign = 0;
  }
  static int count_copy_con;
  static int count_move_con;
  static int count_copy_assign;
  static int count_move_assign;
};
int C::count_copy_con = 0;
int C::count_move_con = 0;
int C::count_copy_assign = 0;
int C::count_move_assign = 0;

void test_access()
{
  map<int ,int> m;
  cout<<m.size() <<endl;
  m[1];//已经分配了一块内存
  cout<<m.size() <<endl;// 1
}

void test_insert()
{
  cout << "m[1] = C()" << endl;
  map<int, C> m;
  { 
    C::clean();
    m[1] = C();  // 2
    C::print_count();
    assert(1 == C::count_move_assign);
    
  }

  cout << "m[1] = c" << endl;
  { 

    C::clean();
    C c;
    m[2] = c;  // 2
    C::print_count();
    assert(1 == C::count_copy_assign);
    
  }

  cout << "m[1] = move(c)" << endl;
  { 

    C::clean();
    C c;
    m[2] = std::move(c);  // 2
    C::print_count();
    assert(1 == C::count_move_assign);
    
  }

  cout << "m.insert(pair<int, C>(2, C()));" << endl;
  {
    C::clean();
    m.insert(pair<int, C>(3, C()));  // 3
    C::print_count();
    assert(2 == C::count_move_con);
    assert(0 == C::count_move_assign);
  }

  cout << "m.insert(pair<int, C>(2, C);" << endl;
  {
    C::clean();
    C c;
    m.insert(pair<int, C>(3, c));  // 3
    C::print_count();
    //assert(2 == C::count_move_con);
    //assert(0 == C::count_move_assign);
  }

}

int main()
{
  //test_access();
  test_insert();
}
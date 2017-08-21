//http://www.cnblogs.com/xubin0523/archive/2012/05/31/2528968.html
class P
{
public:
  void f(){}
  void f(int i){}
};

class C : public P
{
public:
  void f(){}
};

int main()
{
  C c;
  c.f();
  c.f(1);

  return 0;
}

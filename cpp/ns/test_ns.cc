namespace a
{
 
namespace c
{
  class T2;
}

namespace b
{

struct T1
{
  c::T2 *p2;
};
}
}

namespace a
{
namespace c
{

struct T2
{
};
  
}
}

//https://stackoverflow.com/questions/2059665/why-cant-i-forward-declare-a-class-in-a-namespace-like-this
int main()
{
  a::b::T1 t1;
  t1.p2 = new a::c::T2();
  return 0;
}
#include <future>

using namespace std;

future<int> create()
{
  std::promise<int> p;
  return p.get_future();
}

int main()
{
  future<int> fu = create();
  fu.get();

}
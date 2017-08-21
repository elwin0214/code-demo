#include <iostream>
#include <string>
using namespace std;

template<typename T>
class Singleton
{

public:
  static T* instance()
  {
    static T object;
    return &object;
  }

  struct Creator
  {
    Creator()
    {
      Singleton<T>::instance();
    }
  };

private:


  Singleton(){}
  Singleton(const Singleton& t){}


private:
  static Creator creator_;
};

 

template<typename T>
typename Singleton<T>::Creator Singleton<T>::creator_;

struct Data
{
  Data()
  {
    cout << "Data()" << endl;
  }
  ~Data()
  {
    cout << "~Data()" << endl;
  }
};

int main()
{
  Data* pd = Singleton<Data>::instance();

  return 0;
}
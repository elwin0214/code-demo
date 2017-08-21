#include <iostream>
#include <execinfo.h>
#include <string>

using namespace std;

struct Exception
{
  string stack_;

  Exception()
  {
    fillStackTrace();
  }

  Exception(const Exception& e)
  {
    cout << "Exception()" << endl;
    //return *this;
  }

  void fillStackTrace()
  { 
    const int len = 128;
    void* buffer[len];
    int nptrs = ::backtrace(buffer, len);
    char** strings = ::backtrace_symbols(buffer, nptrs);

    if (strings)
    {
      for (int i = 0; i < nptrs; i++)
      {
        stack_.append(strings[i]);
        stack_.append("\n");
      }
    }
  }

  string& toString()
  {
    return stack_;
  }
};

struct ParamException : Exception
{

};

void f()
{
 // Exception e;
  cout << "begin to throw" << endl;
  throw ParamException();
}

void g()
{
  f();
}

int main()
{
  try
  {
    g();
  }
  catch(ParamException& e)
  { 
    //e.fillStackTrace();
    cout << "param " << e.toString() << endl;
  }
  catch(Exception& e)
  { 
    //e.fillStackTrace();
    cout << e.toString() << endl;
  }
}
#include <string>
#include <iostream>

using namespace std;

struct ci_char_traits : public std::char_traits<char> 
{
  static bool eq(char c1, char c2) 
  {
    cout << "eq" << endl;
    return std::toupper(c1) == std::toupper(c2);
  }
  static bool ne(char c1, char c2)
  {
    return std::toupper(c1) != std::toupper(c2);
  }
  static bool lt(char c1, char c2) 
  {
    return std::toupper(c1) <  std::toupper(c2);
  }

  static int compare(const char* s1, const char* s2, size_t n) 
  {
    while( n-- != 0 ) 
    {
      if( std::toupper(*s1) < std::toupper(*s2) ) return -1;
      if( std::toupper(*s1) > std::toupper(*s2) ) return 1;
      ++s1; ++s2;
    }
    return 0;
  }
};

typedef std::basic_string<char, ci_char_traits> cstring;
int main()
{
  cstring s1 = "abc";
  cstring s2 = "Abc";
  cout << (s1 == s2) << endl;
  return 0;
}
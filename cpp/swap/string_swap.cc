#include <string.h>
#include <utility>
#include <iostream>
#include <assert.h>
//1.operator= 异常安全
//2.swap 
//3.operator==
namespace test
{
class string
{
public:
  string(size_t n):length_(n),data_(new char[n + 1])
  {
    ::memset(data_, 0, length_ + 1);
  }

  string(const char* str):length_(::strlen(str)),data_(new char[length_ + 1])
  {
    ::memset(data_, 0, length_ + 1);
    ::memcpy(data_, str, length_);
  }

  string(const string& str):length_(str.length()),data_(new char[length_ + 1])
  {
    ::memset(data_, 0, length_ + 1);
    ::memcpy(data_, str.data_, length_);
  }

  string& operator=(string str)//异常安全
  {
    //if (this == &str) return *this;
    //std::swap(data_, str)
    std::cout << "operator = " << std::endl;
    swap(str);
    return *this;
  }

  string operator+(const string &str)
  {
    if (str.length() == 0)
    {
      return *this;
    }
    string tmp(length_ + str.length_);
    ::memcpy(tmp.data_, data_, length_);
    ::memcpy(tmp.data_ + length_, str.data_, str.length_);
    return tmp;
  }

  void swap(string& str)
  {
    std::swap(data_, str.data_);
    std::swap(length_, str.length_);
  }

  size_t length()const{return length_;} 

  bool operator==(const string& s)
  {
    return 0 == ::strcmp(data_, s.data_);
  }

  const char* c_str() const
  {
    return data_;
  } 

  ~string()
  {
    delete[] data_;
  }

friend bool operator==(test::string str1, const char* str2);

private:
  size_t length_;
  char *data_;
};

bool operator==(test::string str1, const char* str2)
{
  return 0 == ::strcmp(str1.data_, str2);
};

void swap(string& s1, string& s2)
{
  s1.swap(s2);
  std::cout << "swap" << std::endl;
};

}

void test_construct()
{
  test::string s1(2);
  test::string s2("abc");
  test::string s3(s2);
  test::string s4 = s3;
  test::string s5("abcd");
  s5 = s3;
  std::cout << s5.c_str()  << std::endl;
  assert (s5 == s3);
};

void test_swap()
{
  {
    test::string s10("a");
    test::string s11("b");
    swap(s10, s11); // test::swap
  }

  {
    test::string s10("a");
    test::string s11("b");
    using namespace std;
    swap(s10, s11);
  }
};

void test_add()
{
  test::string s1("a");
  test::string s2("b");
  test::string s3 = s1 + s2;
  assert(s3 == "ab");
}

int main()
{
  test_construct();
  test_swap();
  test_add();
  return 0;
}
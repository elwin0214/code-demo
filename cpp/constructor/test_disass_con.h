
class Test
{

public:
  Test();
  
  Test(int value):value_(2)
  {

  };
  Test(int a, int b);

  inline void inline_func()
  {
    value_ = value_ + 100;
  };

  void noinline_func();

  ~Test();

private:
  int value_;
};
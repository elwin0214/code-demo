#include <unistd.h> //_exit
#include <iostream>
using namespace std;

struct Test
{
    Test(const char *str):str_(str)
    {
        cout<<"Test() " <<str_ <<endl;
    }
    ~Test()
    {
        cout<<"~Test() " <<str_ <<endl;
    }
    const char *str_;
};

Test g_test("global");

int main()
{

    static Test s_test("static");
    Test l_test("local");
    //exit(0);//析构全局变量，刷新io，关闭文件描述符，调用atexit注册的函数
    //_exit(0);
    return 0;//先析构局部变量，弹栈，再调用exit
}


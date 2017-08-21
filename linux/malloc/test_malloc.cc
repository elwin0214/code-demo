#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

using namespace std;

//http://www.gnu.org/software/libc/manual/html_node/Hooks-for-Malloc.html
//http://blog.sina.com.cn/s/blog_8588208901017qgb.html
//https://sploitfun.wordpress.com/2015/02/10/understanding-glibc-malloc/
//http://drops.wooyun.org/tips/6595
//https://siddhesh.in/archive.html
//https://jipanyang.wordpress.com/2014/06/09/glibc-malloc-internal-arena-bin-chunk-and-sub-heap-1/
int main(int argc, char* argv[])
{
 char* p = (char*) malloc();


}
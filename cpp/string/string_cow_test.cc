#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

//no COW

int main()
{
    string s1("abc");
    string s2 = s1;
 
    fprintf(stdout, "string 1 addr=%x\n",  (s1.c_str()));
    fprintf(stdout, "string 2 addr=%x\n",  (s2.c_str()));

    s1[4] ='d';

    fprintf(stdout, "string 1 addr=%x\n",  (s1.c_str()));
    fprintf(stdout, "string 2 addr=%x\n",  (s2.c_str()));
    s1[1] ='d';
    fprintf(stdout, "string 1 addr=%x\n",  (s1.c_str()));
    fprintf(stdout, "string 2 addr=%x\n",  (s2.c_str()));
   

    return 0;

}
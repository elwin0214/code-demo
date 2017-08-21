#include <iostream>
#include <unistd.h> //_exit

/**
    man 建议使用atexit 而不使用 on_exit

*/
using namespace std;

void call_at_exit()
{
    cout<<"call_at_exit"<<endl;
};

int main()
{
    atexit(call_at_exit);
   // _exit(0); //dont call
   // exit(0); //call 
    return 0; //call 

}
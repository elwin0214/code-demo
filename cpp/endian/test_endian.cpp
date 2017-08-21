#include <iostream>
#include <stdio.h>  

using namespace std;

typedef union
{  
    unsigned short value;  
    unsigned char bytes[2];  
}Test;  
  
int main()
{
    int i = 1;
    char* p = (char*)&i;
    cout << (*p == 1) <<endl;

    Test test_value;  
    test_value.value = 0x1234;  
  
    if(test_value.bytes[0] == 0x12 && test_value.bytes[1] == 0x34)  
        printf("big ending");  
    else if(test_value.bytes[0] == 0x34 && test_value.bytes[1] == 0x12)  
        printf("little ending");  
    else  
        printf("use test_value error");  
    return 0;
}
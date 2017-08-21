#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char *argv[])
{


    char *p = (char*)malloc(100 * 1024 * 1024);
    if (argc >=1 && strcmp( argv[0], "write"))
    {
        for (int i = 0 ; i < 100 * 1024 * 1024 ; i++)
        {
            *p = 'a';
            p++;
        }
    }

    sleep(1000);

}
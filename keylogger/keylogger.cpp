// #include "HttpRequest.h"
// #include "ServerRequest.h"
#include <conio.h>
#include <stdio.h>
#include <iostream>

int main(int argc, char **argv)
{
    while (true)
    {
        if (kbhit() != 0)
        {
            std::cout << getch() << std::endl;
            std::cout << kbhit() << std::endl;
        }
    }
    return 0;
}
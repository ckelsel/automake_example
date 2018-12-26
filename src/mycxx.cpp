#include "mycxx.h"

// ios::exceptions
#include <iostream>     // std::cerr
#include <fstream>      // std::ifstream

int cxx_func()
{
    std::ifstream file;
    file.open("test.txt");
    file.close();

    return 0;
}

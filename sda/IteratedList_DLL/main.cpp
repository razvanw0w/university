#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
    testAll();
    std::cout << "Passed short test!\n";
    std::cout.flush();
    testAllExtended();
    std::cout << "Passed extended test!\n";
    std::cout.flush();
    return 0;
}
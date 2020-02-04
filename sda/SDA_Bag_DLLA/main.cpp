#include <iostream>
#include "ShortTest.h"
#include "ExtendedTest.h"

int main() {
    testAll();
    std::cout << "Passed short test!\n";
    testAllExtended();
    std::cout << "Passed extended test!\n";
    return 0;
}
#include <iostream>
#include "DirectedGraphUserInterface.h"
#include "UndirectedGraphUserInterface.h"
#include "DirectedGraphMatrixUserInterface.h"
#include "DAGUserInterface.h"

int main() {
    UndirectedGraphUserInterface ui{"random2.txt"};
    ui.runApplication();
    return 0;
}
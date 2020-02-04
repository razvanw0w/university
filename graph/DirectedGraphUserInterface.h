#ifndef GRAPH_C_USERINTERFACE_H
#define GRAPH_C_USERINTERFACE_H

#include "DirectedGraph.h"
#include <iostream>

class DirectedGraphUserInterface {
private:
    DirectedGraph graph;
    void option1();
    void option2();
    void option3();
    void option4();
    void option5();
    void option6();
    void option7();
    void option8();
    void option9();
    void option10();
    void option11();
    void option12();
    void option13();
    void option14();
    void option15();
    void option16();

public:
    explicit DirectedGraphUserInterface(const std::string& fileName);
    void printUserOptions();
    void runApplication();
};


#endif //GRAPH_C_USERINTERFACE_H
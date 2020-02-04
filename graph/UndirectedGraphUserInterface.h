//
// Created by razvan on 24.03.2019.
//

#ifndef GRAPH_C_UndirectedGraphUserInterface_H
#define GRAPH_C_UndirectedGraphUserInterface_H

#include "DirectedGraph.h"
#include "UndirectedGraph.h"
#include <iostream>

class UndirectedGraphUserInterface {
private:
    UndirectedGraph graph;
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

public:
    explicit UndirectedGraphUserInterface(const std::string& fileName);
    void printUserOptions();
    void runApplication();
};


#endif //GRAPH_C_UndirectedGraphUserInterface_H

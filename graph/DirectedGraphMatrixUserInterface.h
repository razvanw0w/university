//
// Created by razvan on 21.04.2019.
//

#ifndef GRAPH_C___DIRECTEDGRAPHMATRIXUSERINTERFACE_H
#define GRAPH_C___DIRECTEDGRAPHMATRIXUSERINTERFACE_H

#include "DirectedGraphMatrix.h"
#include <iomanip>
#include <iostream>

class DirectedGraphMatrixUserInterface {
private:
    DirectedGraphMatrix graph;
    void option1();
    void option2();
    void option3();

public:
    explicit DirectedGraphMatrixUserInterface(const std::string& fileName);
    void printUserOptions();
    void runApplication();
};


#endif //GRAPH_C___DIRECTEDGRAPHMATRIXUSERINTERFACE_H

//
// Created by razvan on 11.05.2019.
//

#ifndef GRAPH_C___DAGUSERINTERFACE_H
#define GRAPH_C___DAGUSERINTERFACE_H


#include "DirectedGraph.h"

class DAGUserInterface {
private:
    DirectedGraph activityGraph;
    void printActivityGraphDetails();

public:
    explicit DAGUserInterface(const std::string& fileName);
    void runApplication();
};


#endif //GRAPH_C___DAGUSERINTERFACE_H

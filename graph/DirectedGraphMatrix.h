//
// Created by razvan on 21.04.2019.
//

#ifndef GRAPH_C___DIRECTEDGRAPHMATRIX_H
#define GRAPH_C___DIRECTEDGRAPHMATRIX_H

#include <vector>
#include <string>

class DirectedGraphMatrix {
private:
    const int INFINITY = 0x3f3f3f3f;
    std::vector <std::vector <int> > adjacencyMatrix;
    int numberOfVertices;

public:
    void loadGraphFromFile(const std::string& fileName);
    DirectedGraphMatrix();
    DirectedGraphMatrix(int numberOfVertices);
    int getNumberOfVertices() const;
    std::vector <std::vector <int> > getMinimumCostMatrix();
    std::vector <std::pair <std::pair <int, int>, int> > getMinimumCostWalk(int startVertex, int endVertex);
};


#endif //GRAPH_C___DIRECTEDGRAPHMATRIX_H

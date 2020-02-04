//
// Created by razvan on 21.04.2019.
//

#include <fstream>
#include "DirectedGraphMatrix.h"
#include <iostream>

void DirectedGraphMatrix::loadGraphFromFile(const std::string &fileName) {
    std::ifstream fin(fileName);
    int x, y, cost;
    int numberOfEdges;

    fin >> numberOfVertices;
    fin >> numberOfEdges;
    adjacencyMatrix = std::vector<std::vector<int> >(numberOfVertices, std::vector<int>(numberOfVertices, INFINITY));
    for (int i = 0; i < numberOfEdges; ++i) {
        fin >> x >> y >> cost;
        adjacencyMatrix[x][y] = cost;
    }
    fin.close();
}

DirectedGraphMatrix::DirectedGraphMatrix() : numberOfVertices{0} {}

DirectedGraphMatrix::DirectedGraphMatrix(int numberOfVertices) : numberOfVertices{numberOfVertices} {
    adjacencyMatrix = std::vector<std::vector<int> >(numberOfVertices, std::vector<int>(numberOfVertices, INFINITY));
}

int DirectedGraphMatrix::getNumberOfVertices() const {
    return numberOfVertices;
}

std::vector<std::vector<int> > DirectedGraphMatrix::getMinimumCostMatrix() {
    auto costMatrix = adjacencyMatrix;

    for (int i = 0; i < numberOfVertices; ++i)
        costMatrix[i][i] = 0;

    for (int k = 0; k < numberOfVertices; ++k) {
        for (int i = 0; i < numberOfVertices; ++i) {
            for (int j = 0; j < numberOfVertices; ++j) {
                if (adjacencyMatrix[i][k] != INFINITY && adjacencyMatrix[k][j] != INFINITY) {
                    if (costMatrix[i][j] > costMatrix[i][k] + costMatrix[k][j]) {
                        costMatrix[i][j] = costMatrix[i][k] + costMatrix[k][j];
                    }
                }
            }
        }
    }
    return costMatrix;
}

std::vector<std::pair<std::pair<int, int>, int> >
DirectedGraphMatrix::getMinimumCostWalk(int startVertex, int endVertex) {
    auto costMatrix = adjacencyMatrix;
    std::vector<std::vector<int> > nextMatrix(numberOfVertices, std::vector<int>(numberOfVertices, -1));

    for (int i = 0; i < numberOfVertices; ++i) {
        costMatrix[i][i] = 0;
        nextMatrix[i][i] = i;
        for (int j = 0; j < numberOfVertices; ++j) {
            if (costMatrix[i][j] != INFINITY) {
                nextMatrix[i][j] = j;
            }
        }
    }

    for (int k = 0; k < numberOfVertices; ++k) {
        for (int i = 0; i < numberOfVertices; ++i) {
            for (int j = 0; j < numberOfVertices; ++j) {
                if (adjacencyMatrix[i][k] != INFINITY && adjacencyMatrix[k][j] != INFINITY) {
                    if (costMatrix[i][j] > costMatrix[i][k] + costMatrix[k][j]) {
                        costMatrix[i][j] = costMatrix[i][k] + costMatrix[k][j];
                        nextMatrix[i][j] = nextMatrix[i][k];
                    }
                }
            }
        }
    }
    std::vector<std::pair<std::pair<int, int>, int> > walk;
    if (costMatrix[startVertex][endVertex] == INFINITY)
        return walk;

    int currentNode = startVertex;
    int nextNode;
    while (currentNode != endVertex) {
        nextNode = nextMatrix[currentNode][endVertex];
//        if (nextNode == -1)
//            break;
        walk.push_back({{currentNode, nextNode}, adjacencyMatrix[currentNode][nextNode]});
        currentNode = nextNode;
    }
//    if (walk.size() == 0 || walk[walk.size() - 1].first.second != endVertex)
//        return std::vector <std::pair <std::pair <int, int>, int> >{};
    std::cout << "The best cost: " << costMatrix[startVertex][endVertex] << '\n';
    return walk;
}

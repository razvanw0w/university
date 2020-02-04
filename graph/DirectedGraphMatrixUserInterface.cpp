//
// Created by razvan on 21.04.2019.
//

#include "DirectedGraphMatrixUserInterface.h"

void DirectedGraphMatrixUserInterface::option1() {
    auto matrix = graph.getMinimumCostMatrix();
    int n = graph.getNumberOfVertices();

    const int INFINITY = 0x3f3f3f3f;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] == INFINITY)
                std::cout << std::setw(2) << "oo ";
            else
                std::cout << std::setw(2) << matrix[i][j] << " ";
        }
        std::cout << '\n';
    }
}
DirectedGraphMatrixUserInterface::DirectedGraphMatrixUserInterface(const std::string &fileName) {
    graph.loadGraphFromFile(fileName);
}

void DirectedGraphMatrixUserInterface::printUserOptions() {
    std::cout << "1. Print the matrix of the minimum costs\n";
    std::cout << "2. Find a lowest cost walk between two vertices\n";
    std::cout << "3. Exit\n";
}

void DirectedGraphMatrixUserInterface::runApplication() {
    int userChoice = 0;
    while (userChoice != 3) {
        printUserOptions();
        std::cout << "Your choice: ";
        std::cin >> userChoice;
        switch (userChoice) {
            case 1: option1(); break;
            case 2: option2(); break;
            default: break;
        }
    }
}

void DirectedGraphMatrixUserInterface::option2() {
    int startVertex, endVertex;
    std::cout << "Start vertex: ";
    std::cin >> startVertex;
    std::cout << "\nEnd vertex: ";
    std::cin >> endVertex;
    std::cout << '\n';

    auto walk = graph.getMinimumCostWalk(startVertex, endVertex);
    if (walk.size() == 0) {
        std::cout << "NO WALK AVAILABLE\n";
        return;
    }
    for (const auto& node: walk) {
        std::cout << node.first.first << ' ' << node.first.second << ' ' << node.second << '\n';
    }
}

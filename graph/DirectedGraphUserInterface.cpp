#include "DirectedGraphUserInterface.h"

DirectedGraphUserInterface::DirectedGraphUserInterface(const std::string& fileName): graph{}
{
    graph.loadGraphFromFile(fileName);
}

void DirectedGraphUserInterface::runApplication() {
    int choice = 0;
    while (choice != 17) {
        printUserOptions();
        std::cout << "Your choice?: ";
        std::cin >> choice;
        try {
            switch (choice) {
                case 1: option1(); break;
                case 2: option2(); break;
                case 3: option3(); break;
                case 4: option4(); break;
                case 5: option5(); break;
                case 6: option6(); break;
                case 7: option7(); break;
                case 8: option8(); break;
                case 9: option9(); break;
                case 10: option10(); break;
                case 11: option11(); break;
                case 12: option12(); break;
                case 13: option13(); break;
                case 14: option14(); break;
                case 15: option15(); break;
                case 16: option16(); break;
                default: break;
            }
        }
        catch (std::runtime_error& error) {
            std::cout << error.what() << '\n';
        }
    }
}

void DirectedGraphUserInterface::printUserOptions() {
    std::cout << "1. Print the list of the vertices and all the edges\n";
    std::cout << "2. Print the number of vertices\n";
    std::cout << "3. Test if there is an edge between two nodes\n";
    std::cout << "4. Print the in degree of a node\n";
    std::cout << "5. Print the out degree of a node\n";
    std::cout << "6. Print the outbound edges of a node\n";
    std::cout << "7. Print the inbound edges of a node\n";
    std::cout << "8. Print the cost associated to an edge\n";
    std::cout << "9. Modify the cost associated to an edge\n";
    std::cout << "10. Add an edge\n";
    std::cout << "11. Remove an edge\n";
    std::cout << "12. Add a node\n";
    std::cout << "13. Remove a node\n";
    std::cout << "14. Print all the strongly connected components\n";
    std::cout << "15. Find the number of distinct walks of minimum cost between 2 vertices\n";
    std::cout << "16. For a DAG, find the number of distinct walks between 2 vertices\n";
    std::cout << "17. Exit\n";
}

void DirectedGraphUserInterface::option1() {
    auto iteratorPair = graph.parseSetOfVertices();
    for (auto it = iteratorPair.first; it != iteratorPair.second; ++it)
        std::cout << *it << " ";
    std::cout << '\n';
    for (auto it = iteratorPair.first; it != iteratorPair.second; ++it) {
        auto outboundIteratorPair = graph.parseOutboundEdges(*it);
        for (auto it2 = outboundIteratorPair.first; it2 != outboundIteratorPair.second; ++it2) {
            std::cout << *it << " " << *it2 << " " << graph.getCost(*it, *it2) << '\n';
        }
    }
}

void DirectedGraphUserInterface::option2() {
    std::cout << graph.getNumberOfVertices() << '\n';
}

void DirectedGraphUserInterface::option3() {
    int source, target;
    std::cout << "Provide the source: ";
    std::cin >> source;
    std::cout << "\nProvide the target: ";
    std::cin >> target;
    if (graph.isEdge(source, target))
        std::cout << "\nThere exists edge between " << source << " and " << target << "\n";
    else
        std::cout << "\nThere is no edge between " << source << " and " << target << "\n";
}

void DirectedGraphUserInterface::option4() {
    int vertex;
    std::cout << "Provide the vertex: ";
    std::cin >> vertex;
    std::cout << "\nIn degree: " << graph.getInDegree(vertex) << '\n';
}

void DirectedGraphUserInterface::option5() {
    int vertex;
    std::cout << "Provide the vertex: ";
    std::cin >> vertex;
    std::cout << "\nOut degree: " << graph.getOutDegree(vertex) << '\n';
}

void DirectedGraphUserInterface::option6() {
    int vertex;
    std::cout << "Provide the vertex: ";
    std::cin >> vertex;
    std::cout << '\n';
    auto iteratorPair = graph.parseOutboundEdges(vertex);
    for (auto it = iteratorPair.first; it != iteratorPair.second; ++it)
        std::cout << *it << " ";
    std::cout << '\n';
}

void DirectedGraphUserInterface::option7() {
    int vertex;
    std::cout << "Provide the vertex: ";
    std::cin >> vertex;
    std::cout << '\n';
    auto iteratorPair = graph.parseInboundEdges(vertex);
    for (auto it = iteratorPair.first; it != iteratorPair.second; ++it)
        std::cout << *it << " ";
    std::cout << '\n';
}

void DirectedGraphUserInterface::option8() {
    int source, target;
    std::cout << "Provide the source: ";
    std::cin >> source;
    std::cout << "\nProvide the target: ";
    std::cin >> target;
    int cost = graph.getCost(source, target);
    std::cout << "\nCost: " << cost << '\n';
}

void DirectedGraphUserInterface::option9() {
    int source, target, cost;
    std::cout << "Provide the source: ";
    std::cin >> source;
    std::cout << "\nProvide the target: ";
    std::cin >> target;
    std::cout << "\nProvide the new cost: ";
    std::cin >> cost;
    graph.setCost(source, target, cost);
    std::cout << "\nCost modified to " << cost << '\n';
}

void DirectedGraphUserInterface::option10() {
    int source, target, cost;
    std::cout << "Provide the source: ";
    std::cin >> source;
    std::cout << "\nProvide the target: ";
    std::cin >> target;
    std::cout << "\nProvide the cost: ";
    std::cin >> cost;
    graph.addEdge(source, target, cost);
    std::cout << "\nAdded edge from " << source << " to " << target << " with cost " << cost << '\n';
}

void DirectedGraphUserInterface::option11() {
    int source, target, cost;
    std::cout << "Provide the source: ";
    std::cin >> source;
    std::cout << "\nProvide the target: ";
    std::cin >> target;
    graph.removeEdge(source, target);
    std::cout << "\nRemoved edge from " << source << " to " << target << '\n';
}

void DirectedGraphUserInterface::option12() {
    int vertex;
    std::cout << "Provide the vertex: ";
    std::cin >> vertex;
    graph.addVertex(vertex);
    std::cout << "\nAdded vertex " << vertex << '\n';
}

void DirectedGraphUserInterface::option13() {
    int vertex;
    std::cout << "Provide the vertex: ";
    std::cin >> vertex;
    graph.removeVertex(vertex);
    std::cout << "\nRemoved vertex " << vertex << '\n';
}

void DirectedGraphUserInterface::option14() {
    std::vector <DirectedGraph> stronglyConnectedComponents = graph.getStronglyConnectedComponents();
    for (auto& stronglyConnectedComponent: stronglyConnectedComponents) {
        std::cout << "==========================================\n";
        std::cout << "Vertices: ";
        auto verticesIteratorPair = stronglyConnectedComponent.parseSetOfVertices();
        for (auto it = verticesIteratorPair.first; it != verticesIteratorPair.second; ++it)
            std::cout << *it << ' ';
        std::cout << '\n';
        std::cout << "Edges\n";
        for (auto it = verticesIteratorPair.first; it != verticesIteratorPair.second; ++it) {
            auto outboundIteratorPair = stronglyConnectedComponent.parseOutboundEdges(*it);
            for (auto it2 = outboundIteratorPair.first; it2 != outboundIteratorPair.second; ++it2) {
                std::cout << *it << " " << *it2 << '\n';
            }
        }
        std::cout << "==========================================\n";
    }
}

void DirectedGraphUserInterface::option15() {
    int source, target;
    std::cout << "Provide the source: ";
    std::cin >> source;
    std::cout << "\nProvide the target: ";
    std::cin >> target;
    std::cout << "\n" << graph.getNumberOfDistinctWalksOfMinimumCost(source, target) << '\n';
}

void DirectedGraphUserInterface::option16() {
    int source, target;
    std::cout << "Provide the source: ";
    std::cin >> source;
    std::cout << "\nProvide the target: ";
    std::cin >> target;
    std::cout << "\n" << graph.getNumberOfDistinctWalksDAG(source, target) << '\n';
}

//
// Created by razvan on 26.03.2019.
//

#include <iostream>
#include "UndirectedGraph.h"

void UndirectedGraph::loadUnweightedGraphFromFile(const std::string &fileName) {
    std::ifstream fin(fileName);
    int numberOfEdges;
    int source, target, cost;

    fin >> numberOfVertices >> numberOfEdges;
    for (int i = 0; i < numberOfVertices; ++i) {
        setOfVertices.push_back(i);
        adjacencyList[i] = std::vector<int>();
        adjacencyList[i] = std::vector<int>();
    }

    int realNumber = 0;
    for (int i = 0; i < numberOfEdges; ++i) {
        fin >> source >> target;
        if (!isEdge(source, target)) {
            ++realNumber;
            listOfEdges.push_back({source, target});
            adjacencyList[target].push_back(source);
            adjacencyList[source].push_back(target);
        }
    }
    std::cout << realNumber << " edges\n";
    fin.close();
}

bool UndirectedGraph::doesVertexExist(int vertex) const {
    return std::find(setOfVertices.begin(), setOfVertices.end(), vertex) != setOfVertices.end();
}

UndirectedGraph::UndirectedGraph(const UndirectedGraph &graph) {
    numberOfVertices = graph.numberOfVertices;
    adjacencyList = graph.adjacencyList;
    setOfVertices = graph.setOfVertices;
    listOfEdges = graph.listOfEdges;
}

UndirectedGraph &UndirectedGraph::operator=(const UndirectedGraph &graph) {
    if (this != &graph) {
        numberOfVertices = graph.numberOfVertices;
        adjacencyList = graph.adjacencyList;
        setOfVertices = graph.setOfVertices;
        listOfEdges = graph.listOfEdges;
    }
    return *this;
}

int UndirectedGraph::getNumberOfVertices() const {
    return numberOfVertices;
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
UndirectedGraph::parseSetOfVertices() const {
    return {setOfVertices.begin(), setOfVertices.end()};
}

bool UndirectedGraph::isEdge(int firstVertex, int secondVertex) {
    if (!doesVertexExist(firstVertex) || !doesVertexExist(secondVertex)) {
        throw std::runtime_error("invalid vertex");
    }
    return std::find(adjacencyList[firstVertex].begin(), adjacencyList[firstVertex].end(), secondVertex) !=
           adjacencyList[firstVertex].end();
}

int UndirectedGraph::getDegree(int vertex) {
    if (!doesVertexExist(vertex)) {
        throw std::runtime_error("invalid vertex");
    }
    return adjacencyList[vertex].size();
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
UndirectedGraph::parseNeighbours(int vertex) {
    if (!doesVertexExist(vertex)) {
        throw std::runtime_error("invalid vertex");
    }
    return {adjacencyList[vertex].begin(), adjacencyList[vertex].end()};
}

void UndirectedGraph::addVertex(int vertex) {
    if (doesVertexExist(vertex)) {
        throw std::runtime_error("vertex already existing");
    }
    setOfVertices.push_back(vertex);
    adjacencyList[vertex] = std::vector<int>();
    ++numberOfVertices;
}

void UndirectedGraph::addEdge(int source, int target) {
    if (isEdge(source, target)) {
        throw std::runtime_error("edge already existing");
    }
    adjacencyList[source].push_back(target);
    adjacencyList[target].push_back(source);
}

void UndirectedGraph::removeEdge(int source, int target) {
    if (!isEdge(source, target)) {
        throw std::runtime_error("edge doesn't exist");
    }
    adjacencyList[source].erase(std::find(adjacencyList[source].begin(), adjacencyList[source].end(), target));
    adjacencyList[target].erase(std::find(adjacencyList[target].begin(), adjacencyList[target].end(), source));
}

void UndirectedGraph::removeVertex(int vertex) {
    if (!doesVertexExist(vertex))
        throw std::runtime_error("invalid vertex");
    for (const int &neighbour: adjacencyList[vertex]) {
        adjacencyList[neighbour].erase(
                std::find(adjacencyList[neighbour].begin(), adjacencyList[neighbour].end(), vertex));
    }
    adjacencyList.erase(adjacencyList.find(vertex));
    setOfVertices.erase(std::find(setOfVertices.begin(), setOfVertices.end(), vertex));
}

std::vector<UndirectedGraph> UndirectedGraph::getConnectedComponents() {
    std::map<int, bool> visited;
    std::vector<int> connectedComponentVertices;
    std::vector<UndirectedGraph> connectedComponents;
    UndirectedGraph currentConnectedComponent;

    for (const int &vertex: setOfVertices) {
        visited[vertex] = false;
    }
    for (const int &vertex: setOfVertices) {
        if (!visited[vertex]) {
            connectedComponentVertices = std::vector<int>();
            connectedComponentsDFS(vertex, visited, connectedComponentVertices);
            currentConnectedComponent = createConnectedComponentGraph(connectedComponentVertices);
            connectedComponents.push_back(currentConnectedComponent);
        }
    }
    return connectedComponents;
}

void UndirectedGraph::connectedComponentsDFS(int vertex, std::map<int, bool> &visited,
                                             std::vector<int> &connectedComponentVertices) {
    if (visited[vertex])
        return;
    visited[vertex] = true;
    for (const int &neighbour: adjacencyList[vertex]) {
        if (!visited[neighbour])
            connectedComponentsDFS(neighbour, visited, connectedComponentVertices);
    }
    connectedComponentVertices.push_back(vertex);
}

UndirectedGraph::UndirectedGraph() : numberOfVertices{0} {
}

UndirectedGraph UndirectedGraph::createConnectedComponentGraph(const std::vector<int> &connectedComponentVertices) {
    UndirectedGraph graph;
    for (const int &vertex: connectedComponentVertices) {
        graph.addVertex(vertex);
    }
    for (const int &vertex: connectedComponentVertices) {
        for (const int &neighbour: adjacencyList[vertex]) {
            if (!graph.isEdge(vertex, neighbour))
                graph.addEdge(vertex, neighbour);
        }
    }
    return graph;
}

std::vector<int> UndirectedGraph::getMinimumVertexCover() {
    std::vector<int> sol = std::vector<int>(numberOfVertices + 1);
    sol[0] = -1;
    std::vector<int> realSolution;
    bool found = false;
    for (int i = 1; i <= numberOfVertices && found == false; ++i) {
        generateSubsetWithPrecisedLength(sol, 1, i, found);
        if (found == true) {
            for (int j = 1; j <= i; ++j) {
                realSolution.push_back(sol[j]);
            }
        }
    }
    return realSolution;
}

std::vector<int> UndirectedGraph::getApproximateVertexCover() {
    UndirectedGraph graph = *this;
    std::vector<int> result;
    int x, y;
    while (graph.listOfEdges.empty() == false) {
        auto edge = graph.listOfEdges[0];
        x = edge.first;
        y = edge.second;
        result.push_back(x);
        result.push_back(y);
        auto it1 = std::remove_if(graph.listOfEdges.begin(), graph.listOfEdges.end(),
                                  [&x](const std::pair<int, int> &e) { return e.first == x || e.second == x; });
        graph.listOfEdges.erase(it1, graph.listOfEdges.end());
        auto it2 = std::remove_if(graph.listOfEdges.begin(), graph.listOfEdges.end(),
                                  [&y](const std::pair<int, int> &e) { return e.first == y || e.second == y; });
        graph.listOfEdges.erase(it2, graph.listOfEdges.end());
    }
//    result.pop_back();
    return result;
}

void UndirectedGraph::generateSubsetWithPrecisedLength(std::vector<int> &sol, int step, const int &len, bool &found) {
    if (step == len + 1) {
        if (found == false) {
            if (testIfVertexCover(sol, len)) {
                found = true;
            }
        }
        return;
    }
    if (found == true)
        return;

    for (int vertex = sol[step - 1] + 1; vertex < numberOfVertices && found == false; ++vertex) {
        sol[step] = vertex;
        generateSubsetWithPrecisedLength(sol, step + 1, len, found);
    }
}

bool UndirectedGraph::testIfVertexCover(std::vector<int> &sol, const int &len) {
    for (auto edge: listOfEdges) {
        int x = edge.first;
        int y = edge.second;

        bool found = false;
        for (int i = 1; i <= len && found == false; ++i) {
            if (sol[i] == x || sol[i] == y)
                found = true;
        }
        if (found == false)
            return false;
    }

    return true;
}

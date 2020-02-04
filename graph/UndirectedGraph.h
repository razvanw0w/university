//
// Created by razvan on 26.03.2019.
//

#ifndef GRAPH_C_UNDIRECTEDGRAPH_H
#define GRAPH_C_UNDIRECTEDGRAPH_H

#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <stdexcept>

class UndirectedGraph {
private:
    int numberOfVertices;
    std::map <int, std::vector <int> > adjacencyList;
    std::vector <std::pair <int, int> > listOfEdges;
    std::vector <int> setOfVertices;
    bool doesVertexExist(int vertex) const;
    void connectedComponentsDFS(int vertex, std::map<int, bool>& visited, std::vector<int>& connectedComponentVertices);
    UndirectedGraph createConnectedComponentGraph(const std::vector<int>& connectedComponentVertices);
    void generateSubsetWithPrecisedLength(std::vector <int>& sol, int step, const int& len, bool& found);
    bool testIfVertexCover(std::vector <int> &sol, const int& len);
    
public:
    UndirectedGraph();
    void loadUnweightedGraphFromFile(const std::string& fileName);
    UndirectedGraph(const UndirectedGraph& graph);
    UndirectedGraph& operator=(const UndirectedGraph& graph);
    int getNumberOfVertices() const;
    std::pair <std::vector <int>::const_iterator, std::vector <int>::const_iterator> parseSetOfVertices() const;
    bool isEdge(int firstVertex, int secondVertex);
    int getDegree(int vertex);
    std::pair <std::vector <int>::const_iterator, std::vector <int>::const_iterator> parseNeighbours(int vertex);
    void addVertex(int vertex);
    void addEdge(int source, int target);
    void removeEdge(int source, int target);
    void removeVertex(int vertex);
    std::vector<UndirectedGraph> getConnectedComponents();
    std::vector<int> getMinimumVertexCover();
    std::vector<int> getApproximateVertexCover();
};


#endif //GRAPH_C_UNDIRECTEDGRAPH_H

#ifndef GRAPH_C_DIRECTEDGRAPH_H
#define GRAPH_C_DIRECTEDGRAPH_H

#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <stack>
#include "Activity.h"

class DirectedGraph {
private:
    int numberOfVertices;
    std::map <int, std::vector <int> > inboundEdges;
    std::map <int, std::vector <int> > outboundEdges;
    std::map <std::pair <int, int>, int> edgeCosts;
    std::vector <int> setOfVertices;
    std::vector <Activity> activities;

    void TarjanDFS(int vertex, int& currentIndex, std::map <int, int>& associatedIndex,
                   std::map <int, int>& lowlinkIndex, std::stack <int>& stack, std::map<int, bool>& onStack,
                   std::vector <std::vector <int> >& stronglyConnectedComponentsVerticesList);
    DirectedGraph createStronglyConnectedComponent(const std::vector <int>& verticesList);
    std::vector <int> dijkstra(int startingNode, int targetNode);
    DirectedGraph buildDijkstraDAG(std::vector <int> distances);
    void DAGDynamicProgrammingDFS(int node, std::vector <bool>& visited, std::vector <int>& dp);
    bool activityTopologicalSortingDFS(int node, std::vector<bool> &processed, std::vector<bool> &inProcess, std::vector <int>& sorted);

public:
    bool doesVertexExist(int vertex) const;
    void loadGraphFromFile(const std::string& fileName);
    void loadActivityGraphFromFile(const std::string& fileName);
    DirectedGraph();
    DirectedGraph(const DirectedGraph& graph);
    DirectedGraph& operator=(const DirectedGraph& graph);
    int getNumberOfVertices() const;
    std::pair <std::vector <int>::const_iterator, std::vector <int>::const_iterator> parseSetOfVertices() const;
    bool isEdge(int firstVertex, int secondVertex);
    int getInDegree(int vertex);
    int getOutDegree(int vertex);
    std::pair <std::vector <int>::const_iterator, std::vector <int>::const_iterator> parseInboundEdges(int vertex);
    std::pair <std::vector <int>::const_iterator, std::vector <int>::const_iterator> parseOutboundEdges(int vertex);
    int getCost(int firstVertex, int secondVertex);
    void setCost(int firstVertex, int secondVertex, int cost);
    void addVertex(int vertex);
    void addEdge(int source, int target, int cost);
    void removeEdge(int source, int target);
    void removeVertex(int vertex);
    int getNumberOfDistinctWalksOfMinimumCost(int startingVertex, int endingVertex);
    int getNumberOfDistinctWalksDAG(int startingVertex, int endingVertex);
    std::vector<DirectedGraph> getStronglyConnectedComponents();
    std::vector<Activity> getFullActivityStatus();
    std::vector <int> getActivityTopologicalSorting();
};


#endif //GRAPH_C_DIRECTEDGRAPH_H

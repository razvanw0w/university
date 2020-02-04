//
// Created by razvan on 24.03.2019.
//

#include "DirectedGraph.h"
#include <queue>
#include <iostream>

void DirectedGraph::loadGraphFromFile(const std::string &fileName) {
    std::ifstream fin(fileName);
    int numberOfEdges;
    int source, target, cost;

    fin >> numberOfVertices >> numberOfEdges;
    for (int i = 0; i < numberOfVertices; ++i) {
        setOfVertices.push_back(i);
        inboundEdges[i] = std::vector<int>();
        outboundEdges[i] = std::vector<int>();
    }

    for (int i = 0; i < numberOfEdges; ++i) {
        fin >> source >> target >> cost;
        inboundEdges[target].push_back(source);
        outboundEdges[source].push_back(target);
        edgeCosts[{source, target}] = cost;
    }
}

bool DirectedGraph::doesVertexExist(int vertex) const {
    return std::find(setOfVertices.begin(), setOfVertices.end(), vertex) != setOfVertices.end();
}

int DirectedGraph::getNumberOfVertices() const {
    return setOfVertices.size();
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
DirectedGraph::parseSetOfVertices() const {
    return {setOfVertices.begin(), setOfVertices.end()};
}

bool DirectedGraph::isEdge(int firstVertex, int secondVertex) {
    if (!doesVertexExist(firstVertex) || !doesVertexExist(secondVertex)) {
        throw std::runtime_error("invalid vertex");
    }
    return std::find(outboundEdges[firstVertex].begin(), outboundEdges[firstVertex].end(), secondVertex) !=
           outboundEdges[firstVertex].end();
}

int DirectedGraph::getInDegree(int vertex) {
    if (doesVertexExist(vertex) == false) {
        throw std::runtime_error("invalid vertex");
    }
    return inboundEdges[vertex].size();
}

int DirectedGraph::getOutDegree(int vertex) {
    if (doesVertexExist(vertex) == false) {
        throw std::runtime_error("invalid vertex");
    }
    return outboundEdges[vertex].size();
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
DirectedGraph::parseInboundEdges(int vertex) {
    if (doesVertexExist(vertex) == false) {
        throw std::runtime_error("invalid vertex");
    }
    return {inboundEdges[vertex].begin(), inboundEdges[vertex].end()};
}

std::pair<std::vector<int>::const_iterator, std::vector<int>::const_iterator>
DirectedGraph::parseOutboundEdges(int vertex) {
    if (doesVertexExist(vertex) == false) {
        throw std::runtime_error("invalid vertex");
    }
    return {outboundEdges[vertex].begin(), outboundEdges[vertex].end()};
}

int DirectedGraph::getCost(int firstVertex, int secondVertex) {
    if (isEdge(firstVertex, secondVertex)) {
        return edgeCosts[{firstVertex, secondVertex}];
    } else {
        throw std::runtime_error("there is no edge");
    }
}

void DirectedGraph::setCost(int firstVertex, int secondVertex, int cost) {
    if (isEdge(firstVertex, secondVertex)) {
        edgeCosts[{firstVertex, secondVertex}] = cost;
    }
}

void DirectedGraph::addVertex(int vertex) {
    if (doesVertexExist(vertex)) {
        throw std::runtime_error("invalid vertex");
    }
    setOfVertices.push_back(vertex);
    inboundEdges[vertex] = std::vector<int>();
    outboundEdges[vertex] = std::vector<int>();
}

void DirectedGraph::addEdge(int source, int target, int cost) {
    if (isEdge(source, target)) {
        throw std::runtime_error("edge already exists");
    }
    inboundEdges[target].push_back(source);
    outboundEdges[source].push_back(target);
    edgeCosts[{source, target}] = cost;
}

void DirectedGraph::removeEdge(int source, int target) {
    if (!isEdge(source, target))
        throw std::runtime_error("edge does not exist");
    inboundEdges[target].erase(std::find(inboundEdges[target].begin(), inboundEdges[target].end(), source));
    outboundEdges[source].erase(std::find(outboundEdges[source].begin(), outboundEdges[source].end(), target));
    edgeCosts.erase(edgeCosts.find({source, target}));
}

void DirectedGraph::removeVertex(int vertex) {
    if (!doesVertexExist(vertex))
        throw std::runtime_error("invalid vertex");
    for (const int &neighbour: inboundEdges[vertex]) {
        outboundEdges[neighbour].erase(
                std::find(outboundEdges[neighbour].begin(), outboundEdges[neighbour].end(), vertex));
        edgeCosts.erase(edgeCosts.find({neighbour, vertex}));
    }
    for (const int &neighbour: outboundEdges[vertex]) {
        inboundEdges[neighbour].erase(
                std::find(inboundEdges[neighbour].begin(), inboundEdges[neighbour].end(), vertex));
        edgeCosts.erase(edgeCosts.find({vertex, neighbour}));
    }
    inboundEdges.erase(inboundEdges.find(vertex));
    outboundEdges.erase(outboundEdges.find(vertex));
    setOfVertices.erase(std::find(setOfVertices.begin(), setOfVertices.end(), vertex));
}

DirectedGraph::DirectedGraph(const DirectedGraph &graph) {
    numberOfVertices = graph.numberOfVertices;
    inboundEdges = graph.inboundEdges;
    outboundEdges = graph.outboundEdges;
    edgeCosts = graph.edgeCosts;
    setOfVertices = graph.setOfVertices;
}

DirectedGraph &DirectedGraph::operator=(const DirectedGraph &graph) {
    if (this != &graph) {
        numberOfVertices = graph.numberOfVertices;
        inboundEdges = graph.inboundEdges;
        outboundEdges = graph.outboundEdges;
        edgeCosts = graph.edgeCosts;
        setOfVertices = graph.setOfVertices;
    }
    return *this;
}

std::vector<DirectedGraph> DirectedGraph::getStronglyConnectedComponents() {
    std::map<int, int> associatedIndex, lowlinkIndex;
    std::map<int, bool> onStack;
    std::stack<int> stack;
    std::vector<std::vector<int> > stronglyConnectedComponentsVerticesList;
    std::vector<DirectedGraph> stronglyConnectedComponents;
    int currentIndex = 0;

    for (const int &vertex: setOfVertices) {
        associatedIndex[vertex] = 0;
        lowlinkIndex[vertex] = 0;
        onStack[vertex] = false;
    }
    for (const int &vertex: setOfVertices) {
        if (associatedIndex[vertex] == 0) {
            TarjanDFS(vertex, currentIndex, associatedIndex, lowlinkIndex, stack, onStack,
                      stronglyConnectedComponentsVerticesList);
        }
    }
    for (const auto &verticesList: stronglyConnectedComponentsVerticesList) {
        stronglyConnectedComponents.push_back(createStronglyConnectedComponent(verticesList));
    }
    return stronglyConnectedComponents;
}

DirectedGraph::DirectedGraph() : numberOfVertices{0} {

}

void DirectedGraph::TarjanDFS(int vertex, int &currentIndex, std::map<int, int> &associatedIndex,
                              std::map<int, int> &lowlinkIndex, std::stack<int> &stack, std::map<int, bool> &onStack,
                              std::vector<std::vector<int> > &stronglyConnectedComponentsVerticesList) {
    associatedIndex[vertex] = lowlinkIndex[vertex] = ++currentIndex;
    stack.push(vertex);
    onStack[vertex] = true;

    for (const int &neighbour: outboundEdges[vertex]) {
        if (associatedIndex[neighbour] == 0) {
            TarjanDFS(neighbour, currentIndex, associatedIndex, lowlinkIndex, stack, onStack,
                      stronglyConnectedComponentsVerticesList);
            lowlinkIndex[vertex] = std::min(lowlinkIndex[vertex], lowlinkIndex[neighbour]);
        } else if (onStack[neighbour]) {
            lowlinkIndex[vertex] = std::min(lowlinkIndex[vertex], lowlinkIndex[neighbour]);
        }
    }

    if (associatedIndex[vertex] == lowlinkIndex[vertex]) {
        int extractedVertex;
        stronglyConnectedComponentsVerticesList.push_back(std::vector<int>{});
        do {
            extractedVertex = stack.top();
            stack.pop();
            onStack[extractedVertex] = false;
            stronglyConnectedComponentsVerticesList.back().push_back(extractedVertex);
        } while (extractedVertex != vertex);
    }
}

DirectedGraph DirectedGraph::createStronglyConnectedComponent(const std::vector<int> &verticesList) {
    DirectedGraph graph;
    for (const int &vertex: verticesList)
        graph.addVertex(vertex);
    for (const int &vertex: verticesList) {
        for (const int &neighbour: outboundEdges[vertex]) {
            if (std::find(verticesList.begin(), verticesList.end(), neighbour) != verticesList.end())
                graph.addEdge(vertex, neighbour, edgeCosts[{vertex, neighbour}]);
        }
    }
    return graph;
}

std::vector<int> DirectedGraph::dijkstra(int startingNode, int targetNode) {
    std::vector<int> dist = std::vector<int>(numberOfVertices, 0x3f3f3f3f);
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int> >, std::greater<std::pair<int, int> > > heap;
    dist[startingNode] = 0;
    heap.push({0, startingNode});

    int node, cost;
    while (!heap.empty()) {
        node = heap.top().second;
        cost = heap.top().first;
        heap.pop();

        if (node == targetNode)
            return dist;
        if (dist[node] < cost)
            continue;
        for (const auto &neighbour: outboundEdges[node]) {
            if (dist[neighbour] > cost + edgeCosts[{node, neighbour}]) {
                dist[neighbour] = cost + edgeCosts[{node, neighbour}];
                heap.push({dist[neighbour], neighbour});
            }
        }
    }
    return dist;
}

DirectedGraph DirectedGraph::buildDijkstraDAG(std::vector<int> distances) {
    DirectedGraph dag;
    for (const int &vertex: setOfVertices) {
        for (const int &neighbour: outboundEdges[vertex]) {
            if (distances[neighbour] == distances[vertex] + edgeCosts[{vertex, neighbour}]) {
                if (!dag.doesVertexExist(vertex))
                    dag.addVertex(vertex);
                if (!dag.doesVertexExist(neighbour))
                    dag.addVertex(neighbour);
//                std::cerr << vertex << " " << neighbour << " " << edgeCosts[{vertex, neighbour}] << '\n';
//                std::cerr.flush();
                dag.addEdge(vertex, neighbour, edgeCosts[{vertex, neighbour}]);
            }
        }
    }
    return dag;
}

void DirectedGraph::DAGDynamicProgrammingDFS(int node, std::vector<bool> &visited, std::vector<int> &dp) {
    visited[node] = true;
    for (const int &neighbour: outboundEdges[node]) {
        if (!visited[neighbour])
            DAGDynamicProgrammingDFS(neighbour, visited, dp);
    }
    for (const int &neighbour: outboundEdges[node]) {
        dp[node] += dp[neighbour];
    }
}

int DirectedGraph::getNumberOfDistinctWalksOfMinimumCost(int startingVertex, int endingVertex) {
    auto distances = dijkstra(startingVertex, endingVertex);
    if (distances[endingVertex] == 0x3f3f3f3f)
        return 0;
    DirectedGraph dag = buildDijkstraDAG(distances);
    std::vector<int> dp = std::vector<int>(numberOfVertices);
    std::vector<bool> visited = std::vector<bool>(numberOfVertices, false);
    dp[endingVertex] = 1;
    dag.DAGDynamicProgrammingDFS(startingVertex, visited, dp);
//    for (int i = 0; i < numberOfVertices; ++i)
//        std::cerr << dp[i] << " ";
    std::cerr.flush();
    return dp[startingVertex];
}

int DirectedGraph::getNumberOfDistinctWalksDAG(int startingVertex, int endingVertex) {
    std::vector<int> dp = std::vector<int>(numberOfVertices);
    std::vector<bool> visited = std::vector<bool>(numberOfVertices, false);
    dp[endingVertex] = 1;
    for (const int &vertex: setOfVertices) {
        if (!visited[vertex]) {
            DAGDynamicProgrammingDFS(vertex, visited, dp);
        }
    }
    return dp[startingVertex];
}

void DirectedGraph::loadActivityGraphFromFile(const std::string &fileName) {
    std::ifstream fin(fileName);
    fin >> numberOfVertices;
    numberOfVertices += 2; // will add dummy start and end activity
    activities = std::vector<Activity>(numberOfVertices);
    Activity startActivity{0, 0};
    activities[0] = startActivity;

    for (int i = 0; i < numberOfVertices; ++i) {
        setOfVertices.push_back(i);
        inboundEdges[i] = std::vector<int>();
        outboundEdges[i] = std::vector<int>();
    }

    int index, duration, precedentActivitiesNumber, precedentActivity;
    for (int i = 1; i < numberOfVertices - 1; ++i) {
        fin >> index >> precedentActivitiesNumber;
        if (precedentActivitiesNumber == 0) {
            inboundEdges[index].push_back(0);
            outboundEdges[0].push_back(index);
        }
        while (precedentActivitiesNumber--) {
            fin >> precedentActivity;
            inboundEdges[index].push_back(precedentActivity);
            outboundEdges[precedentActivity].push_back(index);
        }
        fin >> duration;
        activities[index] = Activity{index, duration};
    }
    activities[numberOfVertices - 1] = Activity{numberOfVertices - 1, 0};
    for (int i = 1; i < numberOfVertices - 1; ++i) {
        if (getOutDegree(i) == 0) {
            inboundEdges[numberOfVertices - 1].push_back(i);
            outboundEdges[i].push_back(numberOfVertices - 1);
        }
    }
}

std::vector<int> DirectedGraph::getActivityTopologicalSorting() {
    std::vector<int> sorted;
    std::vector<bool> processed = std::vector<bool>(numberOfVertices, false);
    std::vector<bool> inProcess = std::vector<bool>(numberOfVertices, false);
    bool outcome = activityTopologicalSortingDFS(0, processed, inProcess, sorted);
    if (outcome == false) {
        throw std::runtime_error{"The graph IS NOT A DAG"};
    } else {
        std::reverse(sorted.begin(), sorted.end());
        return sorted;
    }
}

bool DirectedGraph::activityTopologicalSortingDFS(int node, std::vector<bool> &processed, std::vector<bool> &inProcess,
                                                  std::vector<int> &sorted) {
    inProcess[node] = true;
    bool outcome;
    for (const int &neighbour: outboundEdges[node]) {
        if (inProcess[neighbour]) {
            return false;
        }
        if (processed[neighbour] == false) {
            outcome = activityTopologicalSortingDFS(neighbour, processed, inProcess, sorted);
            if (outcome == false) {
                return false;
            }
        }
    }
    inProcess[node] = false;
    processed[node] = true;
    sorted.push_back(node);
    return true;
}

std::vector<Activity> DirectedGraph::getFullActivityStatus() {
    std::vector<int> sorted = getActivityTopologicalSorting();

    int index;
    int maxTime, minTime;
    int maxEarliestEndTime = -1;
    for (int i = 1; i < numberOfVertices - 1; ++i) {
        index = sorted[i];
        maxTime = -1;
        for (const int &neighbour: inboundEdges[index]) {
            maxTime = std::max(maxTime, activities[neighbour].getEarliestEndTime());
        }
        activities[index].setEarliestStartTime(maxTime);
        activities[index].setEarliestEndTime(maxTime + activities[index].getDuration());
        maxEarliestEndTime = std::max(maxEarliestEndTime, activities[index].getEarliestEndTime());
    }

    activities[numberOfVertices - 1].setEarliestEndTime(maxEarliestEndTime);
    activities[numberOfVertices - 1].setEarliestStartTime(maxEarliestEndTime);
    activities[numberOfVertices - 1].setLatestStartTime(maxEarliestEndTime);
    activities[numberOfVertices - 1].setLatestEndTime(maxEarliestEndTime);
    for (int i = numberOfVertices - 2; i >= 1; --i) {
        index = sorted[i];
        minTime = 2e9;
        for (const int &neighbour: outboundEdges[index]) {
            minTime = std::min(minTime, activities[neighbour].getLatestStartTime());
        }
        activities[index].setLatestEndTime(minTime);
        activities[index].setLatestStartTime(minTime - activities[index].getDuration());
    }

    std::vector<Activity> sortedActivities;
    for (int i = 1; i < numberOfVertices - 1; ++i) {
        sortedActivities.push_back(activities[sorted[i]]);
    }
    return sortedActivities;
}

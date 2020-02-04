//
// Created by razvan on 11.05.2019.
//

#include <iostream>
#include "DAGUserInterface.h"
#include <algorithm>

DAGUserInterface::DAGUserInterface(const std::string &fileName): activityGraph{DirectedGraph()} {
    activityGraph.loadActivityGraphFromFile(fileName);
}

void DAGUserInterface::printActivityGraphDetails() {
    std::vector<Activity> activityStatus = activityGraph.getFullActivityStatus();
    int totalTime = -1;

    for (const Activity& activity: activityStatus) {
        std::cout << "Activity #" << activity.getNodeIndex() << "\n"
                  << "\tEarliest start: " << activity.getEarliestStartTime() << '\n'
                  << "\tEarliest end: " << activity.getEarliestEndTime() << '\n'
                  << "\tLatest start: " << activity.getLatestStartTime() << '\n'
                  << "\tLatest end: " << activity.getLatestEndTime() << '\n';
        totalTime = std::max(totalTime, activity.getEarliestEndTime());
    }
    std::cout << "Critical activities: ";
    for (const Activity& activity: activityStatus) {
        if (activity.isCritical()) {
            std::cout << activity.getNodeIndex() << " ";
        }
    }
    std::cout << "\nTOTAL TIME: " << totalTime << '\n';
}

void DAGUserInterface::runApplication() {
    std::cout << "1. Print activity status\n"
              << "2. Get the number of distinct paths between 2 vertices\n"
              << "3. Get number of distinct lowest cost paths between 2 vertices\n";
    int choice;
    std::cout << "Choice: ";
    std::cin >> choice;
    std::cout << '\n';
    try {
        if (choice == 1)
            printActivityGraphDetails();
        else {
            activityGraph = DirectedGraph{};
            activityGraph.loadGraphFromFile("randomDirected.txt");
            std::vector<int> sorted = activityGraph.getActivityTopologicalSorting();
            std::cout << "Topological sorting: ";
            for (const int &t: sorted)
                std::cout << t << ' ';
            std::cout << '\n';
            int vertex1, vertex2;
            std::cout << "Give the vertices: ";
            std::cin >> vertex1 >> vertex2;
            if (choice == 2) {
                std::cout << "Distinct paths: " << activityGraph.getNumberOfDistinctWalksDAG(vertex1, vertex2);
            } else {
                std::cout << "Distinct lowest cost paths: "
                          << activityGraph.getNumberOfDistinctWalksOfMinimumCost(vertex1, vertex2);
            }
        }
    }
    catch (std::exception &ex) {
        std::cerr << ex.what() << '\n';
    }
}

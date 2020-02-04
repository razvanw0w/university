//
// Created by razvan on 11.05.2019.
//

#ifndef GRAPH_C___ACTIVITY_H
#define GRAPH_C___ACTIVITY_H


class Activity {
private:
    int nodeIndex;
    int duration;
    int earliestStartTime;
    int earliestEndTime;
    int latestStartTime;
    int latestEndTime;

public:
    Activity() = default;
    Activity(int nodeIndex, int duration);
    bool isCritical() const;
    void setEarliestStartTime(int earliestStartTime);
    void setEarliestEndTime(int earliestEndTime);
    void setLatestStartTime(int latestStartTime);
    void setLatestEndTime(int latestEndTime);
    int getDuration() const;
    int getEarliestStartTime() const;
    int getEarliestEndTime() const;
    int getLatestStartTime() const;
    int getLatestEndTime() const;
    int getNodeIndex() const;
};


#endif //GRAPH_C___ACTIVITY_H

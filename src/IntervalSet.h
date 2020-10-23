#ifndef WINDOWS_INTERVAL_TIMER_INTERVALSET_H
#define WINDOWS_INTERVAL_TIMER_INTERVALSET_H

#include "Interval.h"

using std::string;

class IntervalSet {
public:
    explicit IntervalSet(string &setName);

    IntervalSet();

    bool empty();

    std::queue<std::queue<Interval>> &getQueues();

    string getName() const;

    void addQueue(const std::queue<Interval> &queue);

    void setQueues(std::queue<std::queue<Interval>> newQueues);

    string getCurrTime() const;

    string getCurrName() const;

    static void runQueue(std::queue<Interval>* queue);

    static void popFromQueue(std::queue<Interval>* queue);

    void runAll();

private:
    std::queue<std::queue<Interval>> queues;
    string name;
};


#endif //WINDOWS_INTERVAL_TIMER_INTERVALSET_H
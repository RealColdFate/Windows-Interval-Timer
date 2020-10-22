#include "IntervalSet.h"


IntervalSet::IntervalSet(string &setName) {
    name = setName;
}

string IntervalSet::getName() const {
    return name;
}

std::queue<std::queue<Interval>> &IntervalSet::getQueues() {
    return reinterpret_cast<std::queue<std::queue<Interval>> &>(queues);
}

void IntervalSet::addQueue(const std::queue<Interval> &queue) {
    queues.push(queue);
}

void IntervalSet::runQueue(std::queue<Interval> *queue) {
    while (!queue->empty()) {
        IntervalSet::popFromQueue(queue);
    }
}

DWORD WINAPI threadRunAll(LPVOID lpParameter) {
    auto *queues = static_cast<std::queue<std::queue<Interval>> *>(lpParameter);
    while (!queues->empty()) {
        IntervalSet::runQueue(&queues->front());
        queues->pop();
        std::cout << "qq popped" << std::endl;
    }
    return 0;
}

void IntervalSet::popFromQueue(std::queue<Interval> *queue) {
    queue->front().startCountdown();
    while (queue->front().getTime() != 0);
    queue->pop();
    std::cout << "popped an interval" << std::endl;
}


bool IntervalSet::empty() {
    return queues.empty();
}

string IntervalSet::getCurrTime() const {
    if (!queues.empty())
        return queues.front().front().getMinSecDec();
    return "";
}

void IntervalSet::runAll() {
    DWORD tID;
    CreateThread(nullptr, size(queues), threadRunAll, &queues, 0, &tID);

}

string IntervalSet::getCurrName() const {
    if (!queues.empty())
        return queues.front().front().getName();
    return "";
}

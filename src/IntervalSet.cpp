#include "IntervalSet.h"

#include <utility>


IntervalSet::IntervalSet(string &setName) {
    name = setName;
}

IntervalSet::IntervalSet() {
    name = "no Name";
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
    }
    return 0;
}

void IntervalSet::popFromQueue(std::queue<Interval> *queue) {
    queue->front().startCountdown();
    while (queue->front().getTime() != 0);
    queue->pop();
}


bool IntervalSet::empty() {
    return queues.empty();
}

// microseconds
using std::chrono_literals::operator""us;

string IntervalSet::getCurrTime() const {
    std::this_thread::sleep_for(10us);
    if (!(queues.empty()))
        return queues.front().front().getMinSecDec();
    else if (queues.empty())
        return "00:00.000";
    return "";
}

void IntervalSet::runAll() {
    DWORD tID;
    CreateThread(nullptr, size(queues), threadRunAll, &queues, 0, &tID);

}

string IntervalSet::getCurrName() const {
    if (!queues.empty())
        return queues.front().front().getName();
    return "Interval Finished";
}

void IntervalSet::setQueues(std::queue<std::queue<Interval>> newQueues) {
    queues = std::move(newQueues);
}

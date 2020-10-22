#include <iostream>
#include "IntervalSet.h"

using std::cout;
using std::cin;
using std::endl;


Interval makeInterval() {
    cout << "Enter the seconds:";
    long time;
    cin >> time;
    cout << "Enter this interval's name:";
    string name;
    cin >> name;
    cout << time << " " << name << endl;

    return Interval(time, name);
}

IntervalSet createSet() { //todo this only adds one queue
    string setName;
    cout << "What's the name of the set?\n";
    cin >> setName;
    IntervalSet set = IntervalSet(setName);
    std::queue<Interval> q;

    string input;
    while (input != "done") {
        Interval interval = makeInterval();
        cout << interval.getName() << endl;
        q.push(interval);
        cout << q.front().getName();
        cout << "Would you like to repeat this interval? ('yes' / 'no')\n";
        cin >> input;
        if (input == "yes") {
            cout << "How many times shall the interval be repeated?\n";
            int repeatTimes;
            cin >> repeatTimes;
            for (int i = 0; i < repeatTimes - 1; ++i) {
                q.push(interval);
            }
        }
        cout << "add another Interval? ('yes' / 'done')\n";
        cin >> input;
        if (input != "yes") {
            input = "done";
        }
    }
    set.addQueue(q);

    return set;
}

using std::chrono_literals::operator""s;
int main() {

    IntervalSet set = createSet();
    auto start = std::chrono::system_clock::now();
    set.runAll();
    cout << "main has moved on" << endl;
    while (!set.empty())
        cout << "name: " << set.getCurrName() << " Time Remaining: " << set.getCurrTime() << endl;
    auto end = std::chrono::system_clock::now();

    cout << "done" << endl;
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "total time: " << elapsed_seconds.count();
}
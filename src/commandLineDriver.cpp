#include <iostream>
#include "InitWriter.h"
#include "InitReader.h"

using std::cout;
using std::cin;
using std::endl;


Interval makeInterval() {
    cout << "Enter this interval's name:\n";
    string name;
    cin >> name;
    cout << "How long is the interval?\n";
    long time;
    cin >> time;
    cout << "Interval Name: " << name << ", Interval Time: " << time << 's' << endl;

    return Interval(time, name);
}

std::queue<Interval> createQueue() {
    string input;
    std::queue<Interval> q;
    while (input != "done") {
        Interval interval = makeInterval();
        q.push(interval);
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
        if (input != "yes")
            input = "done";
    }

    return q;
}

IntervalSet createSet() {
    string setName, input;

    cout << "What's the name of the set?\n";
    cin >> setName;
    IntervalSet set = IntervalSet(setName);
    while (input != "done") {
        std::queue<Interval> q = createQueue();
        set.addQueue(q);
        cout << "Would you like to repeat this queue? ('yes' / 'no')\n";
        cin >> input;
        if (input != "yes")
            input = "done";
        else {
            int repeatTimes;
            cout << "How Many Times?" << endl;
            cin >> repeatTimes;
            for (int i = 0; i < repeatTimes; ++i)
                set.addQueue(q);
        }
        cout << "Would you like to add another queue? ('yes' / 'no')\n";
        cin >> input;
        if (input != "yes")
            input = "done";
    }
    cout << "Set " << set.getName() << " successfully created\n";
    return set;
}

void runSet(IntervalSet &set) {
    auto start = std::chrono::system_clock::now();
    set.runAll();
    while (!set.empty())
        cout << "name: " << set.getCurrName() << " Time Remaining: " << set.getCurrTime() << endl;

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout << "set completed, total time: " << elapsed_seconds.count() << "s\n";
}

void saveSet(IntervalSet *set) {
    string input;
    if (set->empty()) {
        cout << "It appears this set is empty would you like to create a new one? ('yes' / 'no')\n";
        cin >> input;
        if (input == "yes")
            *set = createSet();
    }
    cout << "What will the config file for this set be called?\n";
    cin >> input;
    InitWriter(input, set);
    std::stringstream stream;
    cout << "\nThe file was successfully saved.\n";
}

IntervalSet loadSet() {
    int input;
    InitReader reader = InitReader();
    std::vector<string> options;
    options = InitReader::getFileNames(reader.CONFIG_PATH);
    int i = 0;

    for (const auto &p : options) {
        std::cout << '(' << i << ") -------- " << p << '\n';
        i++;
    }
    cin >> input;
    InitReader r = InitReader(options[input]);
    IntervalSet set = r.getIntervalSet();
    return set;

}

void printMainOptions() {
    cout << "\nPlease choose from the following:\n\n";
    cout << "Create a new set of intervals. ----(1)\n\n";
    cout << "Save current set. -----------------(2)\n\n";
    cout << "Load a preexisting interval set ---(3)\n\n";
    cout << "Run current set. ------------------(4)\n\n";
    cout << "Print the menu options again. -----(5)\n\n";
    cout << "Quit the program. -----------------(0)\n\n";

}

void commandLineUI() {
    int input;
    IntervalSet set = IntervalSet();
    printMainOptions();
    cin >> input;
    while (input != 0) {
        switch (input) {
            case 1:
                set = createSet();
                printMainOptions();
                break;
            case 2:
                saveSet(&set);
                printMainOptions();
                break;
            case 3:
                set = loadSet();
                printMainOptions();
                break;
            case 4:
                runSet(set);
                printMainOptions();
                break;
            case 5:
                printMainOptions();
                break;
            case 0:
                cout << "bye.\n";
                break;
            default :
                cout << "Invalid option  pleas select another option or press 5 to print options.\n";
                break;
        }
        cin >> input;
    }
}

int main() {
//    string fileName = "configC";
//
//    InitReader reader = InitReader(fileName);
//    set = reader.getIntervalSet();
    commandLineUI();


    cout << "done" << endl;
}
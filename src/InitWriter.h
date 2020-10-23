#ifndef WINDOWS_INTERVAL_TIMER_INITWRITER_H
#define WINDOWS_INTERVAL_TIMER_INITWRITER_H

#include <string>
#include <fstream>
#include "IntervalSet.h"
#include <utility>
#include <direct.h>

class InitWriter {
public:
    InitWriter(const string &fileName, IntervalSet *set);

private:
    void writeFile(const string &fileName, IntervalSet *set);

    void writeQueues(std::ostream *file, IntervalSet *set);

    void writeQueue(std::ostream *file, std::queue<Interval> *queue);

    void writeInterval(std::ostream *file, Interval *interval);

    const char *CONFIG_PATH = R"(Config\)";
    const char *INTERVAL_NAME = "INTERVAL_NAME";
    const char *INTERVAL_TIME = "INTERVAL_TIME";
    const char *SET_NAME = "SET_NAME";
    const char *INTERVAL_DELIM = "INTERVAL_START";
    const char *Q_DELIM = "Q_START";
    const char LINE_DELIM = '\n';
    const char KEY_VAL_DELIM = ':';
};


#endif //WINDOWS_INTERVAL_TIMER_INITWRITER_H

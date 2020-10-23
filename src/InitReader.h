#ifndef WINDOWS_INTERVAL_TIMER_INITREADER_H
#define WINDOWS_INTERVAL_TIMER_INITREADER_H

#include "IntervalSet.h"
#include "InitWriter.h"
#include <filesystem>
#include <sstream>


class InitReader {
public:
    explicit InitReader(string &fileName);

    InitReader();

    // returns a new IntervalSet
    IntervalSet getIntervalSet();

    // returns a vector of strings split at the delimiter given
    static std::vector<string> splitStringByDelim(const string &str, char delim);

    static std::vector<string> getFileNames(const string &path);

    const char *CONFIG_PATH = R"(Config\)";



private:
    string setSetName();

    std::queue<std::queue<Interval>> getQueues();

    std::queue<Interval> getQueue();

    Interval getInterval();

    string takeKey(const string &str) const;

    string takeValue(const string &str) const;

    void readFile(const string &fileName);

    std::vector<string> fileVect;
    int vectorIndex = 0;
    IntervalSet intervalSet = IntervalSet();

    const char *INTERVAL_NAME = "INTERVAL_NAME";
    const char *INTERVAL_TIME = "INTERVAL_TIME";
    const char *SET_NAME = "SET_NAME";
    const char *Q_DELIM = "Q_START";
    const char *INTERVAL_DELIM = "INTERVAL_START";
    const char KEY_VAL_DELIM = ':';


};


#endif //WINDOWS_INTERVAL_TIMER_INITREADER_H

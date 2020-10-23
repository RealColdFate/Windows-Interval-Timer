#include "InitWriter.h"

InitWriter::InitWriter(const string &fileName, IntervalSet *set) {
    writeFile(fileName, set);
}

void InitWriter::writeFile(const string &fileName, IntervalSet *set) {
    std::cout << _mkdir(CONFIG_PATH);

    std::ofstream file{CONFIG_PATH + fileName + ".ini"};
    if (!file)
        std::cerr << "failed to open File" << std::endl;

    writeQueues(&file, set);
    file << Q_DELIM;
    file.close();
}

void InitWriter::writeQueues(std::ostream *file, IntervalSet *set) {
    *file << SET_NAME << KEY_VAL_DELIM << set->getName() << LINE_DELIM;
    while (!set->getQueues().empty()) {
        *file << Q_DELIM << LINE_DELIM;
        writeQueue(file, &set->getQueues().front());
        set->getQueues().pop();
    }
}

void InitWriter::writeQueue(std::ostream *file, std::queue<Interval> *queue) {
    while (!queue->empty()) {
        *file << INTERVAL_DELIM << LINE_DELIM;
        writeInterval(file, &queue->front());
        queue->pop();
    }
}

void InitWriter::writeInterval(std::ostream *file, Interval *interval) {
    *file << INTERVAL_NAME << KEY_VAL_DELIM << interval->getName() << LINE_DELIM;
    *file << INTERVAL_TIME << KEY_VAL_DELIM << interval->getTime() << LINE_DELIM;
}

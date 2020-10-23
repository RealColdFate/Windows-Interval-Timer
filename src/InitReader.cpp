#include "InitReader.h"

InitReader::InitReader(string &inFileName) {
    readFile(inFileName);
    string setName = setSetName();
    intervalSet = IntervalSet(setName);
    intervalSet.setQueues(getQueues());

}

void InitReader::readFile(const string &inFileName) {
    std::ifstream file{CONFIG_PATH + inFileName + ".ini"};
    while (file) {
        string line;
        std::getline(file, line);
        fileVect.push_back(line);
    }
    file.close();
}

std::queue<std::queue<Interval>> InitReader::getQueues() {
    std::queue<std::queue<Interval>> queues;
    while (vectorIndex < fileVect.size() - 2) {
        if (fileVect[vectorIndex] == Q_DELIM) {
            vectorIndex++;
            queues.push(getQueue());
        }
    }
    return queues;
}

std::queue<Interval> InitReader::getQueue() {
    std::queue<Interval> queue;
    while (fileVect[vectorIndex] != Q_DELIM) {
        if (fileVect[vectorIndex] == INTERVAL_DELIM) {
            vectorIndex++;
            queue.push(getInterval());
        }
    }
    return queue;
}

Interval InitReader::getInterval() {
    // get the values of the next two lines
    string name = takeValue(fileVect[vectorIndex]);
    uint64_t time = static_cast<uint64_t>(stoi(takeValue(fileVect[++vectorIndex])));
    vectorIndex++;
    return Interval(time / 1000, name);
}

string InitReader::setSetName() {
    // take the value from the first line of the file
    return takeValue(fileVect[vectorIndex++]);
}


std::vector<string> InitReader::splitStringByDelim(const string &str, char delim) {
    std::vector<string> vect;
    string vectElement;
    for (char c : str) {
        if (c == delim) {
            vect.push_back(vectElement);
            vectElement = "";
            continue;
        }
        vectElement += c;
    }
    vect.push_back(vectElement);
    return vect;
}


string InitReader::takeKey(const string &str) const {
    return splitStringByDelim(str, KEY_VAL_DELIM)[0];
}

string InitReader::takeValue(const string &str) const {
    return splitStringByDelim(str, KEY_VAL_DELIM)[1];
}

IntervalSet InitReader::getIntervalSet() {
    return intervalSet;
}

InitReader::InitReader() = default;


// pulls the file names out of the dir where the files are stored
std::vector<string> InitReader::getFileNames(const string &path) {
    std::stringstream stream;
    std::vector<string> paths;
    std::string str;
    std::vector<string> files;
    std::vector<string> fileNames;

    for (const auto &entry : std::experimental::filesystem::directory_iterator(path))
        stream << entry.path() << '\n';
    while (stream >> str)
        paths.push_back(str);
    for (const auto &p : paths) {
        auto f = splitStringByDelim(p, '\\');
        files.push_back(f.back());
    }
    for (const auto &f: files) {
        auto fn = splitStringByDelim(f, '.');
        fileNames.push_back(fn.front());
    }

    return fileNames;
}
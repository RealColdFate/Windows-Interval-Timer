#include "Interval.h"


Interval::Interval(uint64_t intervalTimeSeconds, string &intervalName) {
    name = intervalName;
    time = intervalTimeSeconds * TIME_MODIFIER;
}

DWORD WINAPI threadRunCountdown(LPVOID lpParameter) {
    uint64_t &timeLeft = *((uint64_t *) lpParameter);
    uint64_t duration = timeLeft;
    auto time = std::chrono::system_clock::now(); // get the current time
    auto since_epoch = time.time_since_epoch(); // get the duration since epoch
    auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
    uint64_t startTime = millis.count(); // time in millis when thread started

    uint64_t endTime = startTime + timeLeft;
    uint64_t currTime;
    do {
        time = std::chrono::system_clock::now();
        since_epoch = time.time_since_epoch();
        millis = std::chrono::duration_cast<std::chrono::milliseconds>(since_epoch);
        currTime = millis.count();
        timeLeft = endTime - currTime;
        if (timeLeft > duration) timeLeft = 0;

    } while (timeLeft != 0);


    return 0;
}

void Interval::startCountdown() {
    DWORD tID;
    CreateThread(nullptr, sizeof(unsigned long), threadRunCountdown, &time, 0, &tID);
}

string Interval::getMinutesLeft(uint64_t currTime) const {
    string strMinutes;
    uint64_t minutes = (currTime / TIME_MODIFIER) / SECONDS_IN_MINUTE;
    if (minutes < 10)
        strMinutes = "0";
    return strMinutes + std::to_string(minutes);
}

string Interval::getSecondsLeft(uint64_t currTime) const {
    string strSeconds;
    uint64_t seconds = (currTime / TIME_MODIFIER) % SECONDS_IN_MINUTE;
    if (seconds < 10)
        strSeconds = "0";
    return strSeconds + std::to_string(seconds);
}

string Interval::getDecimalLeft(uint64_t currTime) const {
    uint64_t decimal = currTime % TIME_MODIFIER;
    string zeros;
    string strDecimal = std::to_string(decimal);
    for (int i = DIGITS_OF_PRECISION; i > strDecimal.size(); --i) {
        zeros += "0";
    }

    return zeros + strDecimal;
}

string Interval::getMinSecDec() const {
    uint64_t currTime = time;
    return getMinutesLeft(currTime) + ":" + getSecondsLeft(currTime) + "." + getDecimalLeft(currTime);
}

string Interval::getMinSec() const {
    uint64_t currTime = time;
    return getMinutesLeft(currTime) + ":" + getSecondsLeft(currTime);
}

const string &Interval::getName() const {
    return name;
}

uint64_t Interval::getTime() const {
    return time;
}

bool Interval::isOver() const {
    return time == 0;
}

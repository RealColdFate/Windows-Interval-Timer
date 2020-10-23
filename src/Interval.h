#ifndef WINDOWS_INTERVAL_TIMER_INTERVAL_H
#define WINDOWS_INTERVAL_TIMER_INTERVAL_H

#include <queue>
#include <string>
#include <thread>
#include <chrono>
#include <utility>
#include <iostream>
#include <Windows.h>

using std::string;

class Interval {
public:
    // public constructor takes in the name of the interval and the time it will take in seconds
    Interval(uint64_t intervalTimeSeconds, string &intervalName);

    // boolean to represent if the interval is over
    bool isOver() const;

    // returns the name of the interval
    const string &getName() const;

    // starts a countdown that will decrement the intervals time until it hits zero
    void startCountdown();


    // returns a string with the time left in the form 00:00.000
    string getMinSecDec() const;

    //returns a string with the time left in the form 00:00
    string getMinSec() const;

    // returns the string of the minutes left in the form 00
    string getMinutesLeft(uint64_t time) const;

    // returns the string of the seconds left in the form 00
    string getSecondsLeft(uint64_t time) const;

    // returns the string of the decimal portion of seconds left in the form 000
    string getDecimalLeft(uint64_t time) const;

    // returns the time left in milliseconds
    uint64_t getTime() const;


private:
    // the time modifier Interval uses time in millis so this is to offset to seconds
    const int TIME_MODIFIER = 1000;
    const int DIGITS_OF_PRECISION = 3;
    const int SECONDS_IN_MINUTE = 60;
    // time in millis
    uint64_t time;
    string name;


};


#endif //WINDOWS_INTERVAL_TIMER_INTERVAL_H

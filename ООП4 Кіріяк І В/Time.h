#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <Windows.h>

class Time {
private:
    int hours;
    int minutes;
    int seconds;

public:
    Time() : hours(0), minutes(0), seconds(0) {}

    Time(int h, int m, int s) : hours(h), minutes(m), seconds(s) {}

    Time(const std::string& timeStr) {
        std::stringstream ss(timeStr);
        char delimiter;
        ss >> hours >> delimiter >> minutes >> delimiter >> seconds;
    }

    Time(int totalSeconds) {
        hours = totalSeconds / 3600;
        totalSeconds %= 3600;
        minutes = totalSeconds / 60;
        seconds = totalSeconds % 60;
    }

    int differenceInSeconds(const Time& other) const {
        int thisSeconds = hours * 3600 + minutes * 60 + seconds;
        int otherSeconds = other.hours * 3600 + other.minutes * 60 + other.seconds;
        return thisSeconds - otherSeconds;
    }

    void addSeconds(int secs) {
        int totalSeconds = hours * 3600 + minutes * 60 + seconds + secs;
        hours = totalSeconds / 3600;
        totalSeconds %= 3600;
        minutes = totalSeconds / 60;
        seconds = totalSeconds % 60;
    }

    void subtractSeconds(int secs) {
        int totalSeconds = hours * 3600 + minutes * 60 + seconds - secs;
        if (totalSeconds < 0) {
            totalSeconds += 86400; // 86400 секунд у добі
        }
        hours = totalSeconds / 3600;
        totalSeconds %= 3600;
        minutes = totalSeconds / 60;
        seconds = totalSeconds % 60;
    }

    bool operator<(const Time& other) const {
        if (hours < other.hours)
            return true;
        if (hours > other.hours)
            return false;
        if (minutes < other.minutes)
            return true;
        if (minutes > other.minutes)
            return false;
        return seconds < other.seconds;
    }

    bool operator>(const Time& other) const {
        if (hours > other.hours)
            return true;
        if (hours < other.hours)
            return false;
        if (minutes > other.minutes)
            return true;
        if (minutes < other.minutes)
            return false;
        return seconds > other.seconds;
    }

    bool operator<=(const Time& other) const {
        return !(*this > other);
    }

    bool operator>=(const Time& other) const {
        return !(*this < other);
    }

    int toSeconds() const {
        return hours * 3600 + minutes * 60 + seconds;
    }

    int toMinutes() const {
        return (hours * 60 + minutes + (seconds >= 30 ? 1 : 0));
    }

    void Display() const {
        std::cout << toString() << std::endl;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << std::setfill('0') << std::setw(2) << hours << ":"
            << std::setfill('0') << std::setw(2) << minutes << ":"
            << std::setfill('0') << std::setw(2) << seconds;
        return ss.str();
    }

    Time operator+(const Time& other) const {
        int totalSeconds = toSeconds() + other.toSeconds();
        return Time(totalSeconds);
    }

    Time operator-(const Time& other) const {
        int totalSeconds = toSeconds() - other.toSeconds();
        return Time(totalSeconds);
    }

    Time operator-(int secs) const {
        int totalSeconds = toSeconds() - secs;
        return Time(totalSeconds);
    }

    void operator+=(int secs) {
        addSeconds(secs);
    }

    bool operator==(const Time& other) const {
        return (hours == other.hours && minutes == other.minutes && seconds == other.seconds);
    }
};

#include <iostream>
#include <ctime>

using namespace std;

class MovieShow {
    string movieName;
    int year, month, day, hour, minute;

public:
    MovieShow(string name, int y, int m, int d, int h, int min) {
        movieName = name;
        year = y;
        month = m;
        day = d;
        hour = h;
        minute = min;
    }

    bool isUpcomingShow() {
        tm currentTime = getCurrentTime();
        tm showTime = {};
        showTime.tm_year = year - 1900;
        showTime.tm_mon = month - 1;
        showTime.tm_mday = day;
        showTime.tm_hour = hour;
        showTime.tm_min = minute;
        showTime.tm_sec = 0;

        time_t currentTimestamp = mktime(&currentTime);
        time_t showTimestamp = mktime(&showTime);

        return showTimestamp > currentTimestamp;
    }

    void displayShow() {
        cout << " " << movieName << " - " 
             << day << "/" << month << "/" << year 
             << " at " << hour << ":00\n";
    }

    static tm getCurrentTime() {
        time_t now = time(0);
        tm *ltm = localtime(&now);
        return *ltm;
    }

    // Function to get a valid date, considering month-end and leap years
    static tm getValidDate(int year, int month, int day) {
        tm date = {};
        date.tm_year = year - 1900;
        date.tm_mon = month - 1;
        date.tm_mday = day;
        date.tm_hour = 0;
        date.tm_min = 0;
        date.tm_sec = 0;

        // Normalize date using mktime
        time_t temp = mktime(&date);
        return *localtime(&temp);
    }
};

int main() {
    const int totalDays = 3;
    const int moviesPerDay = 3;
    MovieShow* shows[totalDays * moviesPerDay];

    tm currentTime = MovieShow::getCurrentTime();
    int currentYear = 1900 + currentTime.tm_year;
    int currentMonth = 1 + currentTime.tm_mon;
    int currentDay = currentTime.tm_mday;

    string movieName = "Avengers"; // Single movie name
    int showTimes[moviesPerDay] = {10, 14, 18}; // 10:00 AM, 2:00 PM, 6:00 PM

    int index = 0;
    for (int day = 0; day < totalDays; day++) {
        tm validDate = MovieShow::getValidDate(currentYear, currentMonth, currentDay + day);
        for (int i = 0; i < moviesPerDay; i++) {
            shows[index] = new MovieShow(movieName,1900 + validDate.tm_year,1 + validDate.tm_mon,validDate.tm_mday,showTimes[i], 0);
            index++;
        }
    }

    cout << "\nUpcoming Movie Shows:\n";
    for (int i = 0; i < totalDays * moviesPerDay; i++) {
        if (shows[i]->isUpcomingShow()) {
            shows[i]->displayShow();
        }
    }

    // Free dynamically allocated memory
    for (int i = 0; i < totalDays * moviesPerDay; i++) {
        delete shows[i];
    }

    return 0;
}

#include <iostream>
#include <ctime>

using namespace std;

struct MovieShow {
    string movieName;
    int year, month, day, hour, minute;
};

tm getCurrentTime() {
    time_t now = time(0);
    tm *ltm = localtime(&now);
    return *ltm;
}

bool isUpcomingShow(MovieShow show) {
    tm currentTime = getCurrentTime();
    tm showTime = {};
    showTime.tm_year = show.year - 1900;
    showTime.tm_mon = show.month - 1;
    showTime.tm_mday = show.day;
    showTime.tm_hour = show.hour;
    showTime.tm_min = show.minute;
    showTime.tm_sec = 0;

    time_t currentTimestamp = mktime(&currentTime);
    time_t showTimestamp = mktime(&showTime);

    return showTimestamp > currentTimestamp;
}

int main() {
    const int totalDays = 5;
    const int moviesPerDay = 3;
    const int totalShows = totalDays * moviesPerDay;
    MovieShow shows[totalShows];

    tm currentTime = getCurrentTime();
    int currentYear = 1900 + currentTime.tm_year;
    int currentMonth = 1 + currentTime.tm_mon;
    int currentDay = currentTime.tm_mday;

    string movieNames[] = {"Movie A", "Movie B", "Movie C"};
    int showTimes[moviesPerDay] = {8, 14, 18};

    int index = 0;
    for (int day = 0; day < totalDays; day++) {
        for (int i = 0; i < moviesPerDay; i++) {
            shows[index].movieName = movieNames[i % 3];
            shows[index].year = currentYear;
            shows[index].month = currentMonth;
            shows[index].day = currentDay + day;
            shows[index].hour = showTimes[i];
            shows[index].minute = 0;
            index++;
        }
    }

    cout << "\nUpcoming Movie Shows:\n";
    for (int i = 0; i < totalShows; i++) {
        if (isUpcomingShow(shows[i])) {
            cout << shows[i].movieName << " - " << shows[i].day << "/" << shows[i].month << "/" << shows[i].year
                 << " at " << shows[i].hour << ":00" << endl;
        }
    }

    return 0;
}
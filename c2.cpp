#include <iostream>
#include <ctime>

using namespace std;

class MovieShow {
    string showName;
    int hour, minute;

public:
    MovieShow(string name, int h, int m) {
        showName = name;
        hour = h;
        minute = m;
    }

    void displayShow(bool isTomorrow) {
        cout << showName << " - ";
        if (isTomorrow) {
            cout << "Tomorrow at ";
        } else {
            cout << "Today at ";
        }
        cout << hour << ":" << (minute < 10 ? "0" : "") << minute << endl;
    }

    bool isTomorrow(int currentHour, int currentMinute) {
        if (currentHour > hour || (currentHour == hour && currentMinute > minute)) {
            return true; // If current time has passed the show time, set it for tomorrow
        }
        return false;
    }
};

int main() {
    // Get current time
    time_t now = time(0);
    tm *ltm = localtime(&now);

    int currentHour = ltm->tm_hour;
    int currentMinute = ltm->tm_min;

    cout << "\nCurrent time: " << currentHour << ":" 
         << (currentMinute < 10 ? "0" : "") << currentMinute << endl;

    // Create show objects
    MovieShow morningShow("Morning Show", 10, 0);
    MovieShow eveningShow("Evening Show", 18, 0);  // 6:00 PM
    MovieShow nightShow("Night Show", 21, 0);      // 9:00 PM

    cout << "\nAvailable Shows:\n";

    // Determine if shows should be set for tomorrow or today
    morningShow.displayShow(morningShow.isTomorrow(currentHour, currentMinute));
    eveningShow.displayShow(eveningShow.isTomorrow(currentHour, currentMinute));
    nightShow.displayShow(nightShow.isTomorrow(currentHour, currentMinute));

    return 0;
}

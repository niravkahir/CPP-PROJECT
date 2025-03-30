#include <iostream>
#include <fstream>
#include <string>
#include <conio.h>
#include<stdlib.h>


using namespace std;

class User {
private:
    string username;
    string password;
    string city;
    
    string cities[5] = {"Ahmedabad", "Surat", "Nadiad", "Vadodara", "Rajkot"};

    bool userExists(const string& user) {
        ifstream file("users.txt");
        if (!file) return false; 

        string storedUser, storedPass, storedCity;
        while (file >> storedUser >> storedPass) {
            file.ignore();
            getline(file, storedCity);
            if (storedUser == user) {
                return true;
            }
        }
        return false;
    }

    string getPassword() {
        string pass;
        char ch;
        cout << "Enter password: ";
        while (true) {
            ch = _getch();
            if (ch == '\r') break;  
            if (ch == '\b' && !pass.empty()) {  
                pass.pop_back();
                cout << "\b \b";  
            } else if (ch != '\b') {
                pass.push_back(ch);
                cout << '*';
            }
        }
        cout << endl;
        return pass;
    }

public:
    void displayCities() {
        cout << "Select your city:\n";
        for (int i = 0; i < 5; i++) {
            cout << i + 1 << ". " << cities[i] << endl;
        }
    }

    void signUp() {
        static int x;
        x=0;
        if(x)system("CLS");
        cout << "Enter a new username: ";
        cin >> username;

        if (userExists(username)) 
        {
            x++;
            cout << "Username already exists! Try another one.\n";
            signUp();
           
        }

        password = getPassword();

        displayCities();
        int choice;
        cout << "Enter your choice (1-5): ";
        
        while (!(cin >> choice) && choice < 1 && choice > 5) {  
            cout << "Invalid input! Please enter a number between 1 and 5: ";
            cin.clear();
            cin.ignore(1000, '\n');
        }

        city = cities[choice - 1];

        ofstream file("users.txt", ios::app);
        if (!file) {
            cout << "Error opening file!\n";
            return;
        }

        file << username << " " << password << " " << city << endl;
        file.close();

        cout << "Sign-up successful! You can now log in.\n";

    }

    void login() {
        system("CLS");
        cout << "Enter your username: ";
        cin >> username;
        password = getPassword();

        ifstream file("users.txt");
        if (!file) {
            cout << "No users found! Please sign up first.\n";
            return;
        }

        string storedUser, storedPass, storedCity;
        bool loginSuccess = false;

        while (file >> storedUser >> storedPass) {
            file.ignore();
            getline(file, storedCity);
            if (storedUser == username && storedPass == password) {
                loginSuccess = true;
                break;
            }
        }
        file.close();

        if (loginSuccess) {
            system("CLS");
            cout << "Login successful! Welcome, " << username << ".\n";
            cout << "Your registered city is: " << city << ".\n";
        } else {
            cout << "Incorrect username or password. Try again.\n";
        }
    }
};

int main() {
    User user;
    int choice;

    while (1) {
        cout << "\n\n|| If you are a new user, please sign up first! ||"; 
        cout << "\n*\n";
        cout << "1. Sign Up\n2. Login\n3. Exit\n";
        cout << "*\n";
        cout << "Enter your choice: ";
        

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter a number.\n";
            continue;
        }

        switch (choice) {
            case 1: user.signUp(); break;
            case 2: user.login(); break;
            case 3: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
        
    }
    return 0;
}
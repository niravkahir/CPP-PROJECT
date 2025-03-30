#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class User {
    string username;
    string password;

    // Function to check if username already exists
    bool userExists(const string& user) {
        ifstream file("users.txt");
        string storedUser, storedPass;

        while (file >> storedUser >> storedPass) {
            if (storedUser == user) {
                return true;
            }
        }
        return false;
    }

public:

    void signUp() {
        cout << "Enter a new username: ";
        cin >> username;

        if (userExists(username)) {
            cout << "Username already exists! Try another one.\n";
            return;
        }

        cout << "Enter a new password: ";
        cin >> password;

        ofstream file("users.txt", ios::app);
        file << username << " " << password << endl;
        file.close();

        cout << "Sign up successful! You can now log in.\n";
    }

    void login() {
        cout << "Enter your username: ";
        cin >> username;
        cout << "Enter your password: ";
        cin >> password;

        ifstream file("users.txt");
        string storedUser, storedPass;
        bool loginSuccess = false;

        while (file >> storedUser >> storedPass) {
            if (storedUser == username && storedPass == password) {
                loginSuccess = true;
                break;
            }
        }
        file.close();

        if (loginSuccess) {
            cout << "Login successful! Welcome, " << username << ".\n";
        } else {
            cout << "Incorrect username or password. Try again.\n";
        }
    }
};

// Main menu
int main() {
    User user;
    int choice;

    while (true) {
        cout << "*****************\n";
        cout << "1. Sign Up\n2. Login\n3. Exit\n";
        cout << "*****************\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: user.signUp(); break;
            case 2: user.login(); break;
            case 3: cout << "Exiting program...\n"; return 0;
            default: cout << "Invalid choice! Try again.\n";
        }
    }
}

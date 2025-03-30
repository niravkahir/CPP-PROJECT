#include <iostream>
using namespace std;

class Booking {
    
};

void storecity(string tstr[5]) {
    tstr[0] = "ahemdabad";
    tstr[1] = "surat";
    tstr[2] = "nadiad";
    tstr[3] = "vadodara";
    tstr[4] = "rajkot";
}


string readcity(string tstr[], int tn) {
    if (tn >= 1 && tn <= 5) {
        return tstr[tn - 1]; 
    }
    return "Invalid choice";
}

int main() {
    cout << "Enter city name:\n";
    
    string str[5]; 
    storecity(str);
    
    cout << "Enter: \n1 for Ahemdabad\n2 for Surat\n3 for Nadiad\n4 for Vadodara\n5 for Rajkot\n"; 
    int n;
    cin >> n;

    cout << "Your city: ";
    string ycity = readcity(str, n);
    cout << ycity << endl;

    return 0;
}

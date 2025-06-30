#include <iostream>
#include <fstream>
#include <conio.h>
#include <string.h>
using namespace std;

class TourBus {
    int bid;
    char destination[200];
    char time[50];
    int max_seats;
    int booked;

public:
    TourBus() {
        bid = 0;
        max_seats = 50;
        booked = 0;
        strcpy(time, "9:30am");
        strcpy(destination, "");
    }

    void input();
    void show();
    void display();
    int getid() {
        return bid;
    }
};

void TourBus::input() {
    cout << "Enter bus ID: ";
    cin >> bid;
    cout << "Enter destination: ";
    cin >> destination;
    cout << "Enter departure time: ";
    cin >> time;
}

void TourBus::display() {
    cout << "Bus ID: " << bid << "\tDestination: " << destination << "\tTime: " << time
        << "\tBooked: " << booked << "\tMax Seats: " << max_seats << endl;
}

void TourBus::show() {
    cout << "\n===== Tour Bus Info =====" << endl;
    cout << "Bus ID       : " << bid << endl;
    cout << "Destination  : " << destination << endl;
    cout << "Departure    : " << time << endl;
    cout << "Booked Seats : " << booked << "/" << max_seats << endl;
    cout << "==========================\n" << endl;
}

int main() {
    int ch, search_id;
    fstream F;
    TourBus bus;

    do {
        cout << "\n=== Tour Bus Management ===\n";
        cout << "1. Add New Tour Bus\n";
        cout << "2. Show All Buses\n";
        cout << "3. Search by Bus ID\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> ch;

        switch (ch) {
        case 1:
            bus.input();
            F.open("buses.dat", ios::binary | ios::app);
            F.write((char*)&bus, sizeof(bus));
            F.close();
            cout << "✅ Bus added successfully.\n";
            break;

        case 2:
            F.open("buses.dat", ios::binary | ios::in);
            if (!F) {
                cout << "❌ File not found.\n";
                break;
            }
            while (F.read((char*)&bus, sizeof(bus))) {
                bus.display();
            }
            F.close();
            break;

        case 3:
            cout << "Enter Bus ID to search: ";
            cin >> search_id;
            F.open("buses.dat", ios::binary | ios::in);
            if (!F) {
                cout << "❌ File not found.\n";
                break;
            }
            {
                bool found = false;
                while (F.read((char*)&bus, sizeof(bus))) {
                    if (bus.getid() == search_id) {
                        bus.show();
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    cout << "⚠️ Bus ID not found.\n";
                }
            }
            F.close();
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice! Try again.\n";
        }
    } while (ch != 4);

    return 0;
}

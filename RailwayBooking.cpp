
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Train {
public:
    int trainNo;
    string trainName;
    string source;
    string destination;
    int totalSeats;
    int fare;

    Train(int no, string name, string src, string dest,
          int seats, int price) {
        trainNo = no;
        trainName = name;
        source = src;
        destination = dest;
        totalSeats = seats;
        fare = price;
    }
};

class Ticket {
public:
    int pnr;
    string passengerName;
    int age;
    int trainNo;
    int seats;
    int totalFare;
    bool active;
};

class RailwayBooking {
private:
    vector<Train> trains;
    vector<Ticket> bookings;
    int nextPNR;

public:
    RailwayBooking() {
        nextPNR = 1001;

        trains.push_back(Train(101, "Vande Bharat",
            "Vijayawada", "Hyderabad", 100, 800));

        trains.push_back(Train(102, "Godavari Express",
            "Vijayawada", "Visakhapatnam", 120, 500));

        trains.push_back(Train(103, "Duronto Express",
            "Hyderabad", "Chennai", 90, 900));

        trains.push_back(Train(104, "Janmabhoomi Express",
            "Visakhapatnam", "Vijayawada", 110, 450));

        trains.push_back(Train(105, "Charminar Express",
            "Hyderabad", "Vijayawada", 100, 600));
    }

    int getAvailableSeats(int index) {
        int booked = 0;

        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].trainNo == trains[index].trainNo &&
                bookings[i].active) {
                booked += bookings[i].seats;
            }
        }

        return trains[index].totalSeats - booked;
    }

    void displayTrains() {
        cout << "\n========== AVAILABLE TRAINS ==========\n";

        cout << left << setw(10) << "Train No"
             << setw(23) << "Train Name"
             << setw(18) << "Source"
             << setw(18) << "Destination"
             << setw(10) << "Seats"
             << "Fare\n";

        cout << "---------------------------------------------------------------\n";

        for (int i = 0; i < trains.size(); i++) {
            cout << left << setw(10) << trains[i].trainNo
                 << setw(23) << trains[i].trainName
                 << setw(18) << trains[i].source
                 << setw(18) << trains[i].destination
                 << setw(10) << getAvailableSeats(i)
                 << trains[i].fare << endl;
        }
    }

    void bookTicket() {
        displayTrains();

        int number;
        cout << "\nEnter Train Number: ";
        cin >> number;

        int index = -1;

        for (int i = 0; i < trains.size(); i++) {
            if (trains[i].trainNo == number) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "\nInvalid Train Number!\n";
            return;
        }

        string name;
        int age, seats;

        cin.ignore();

        cout << "Enter Passenger Name: ";
        getline(cin, name);

        cout << "Enter Age: ";
        cin >> age;

        cout << "Enter Number of Seats: ";
        cin >> seats;

        if (name.empty() || age <= 0 || age > 120 || seats <= 0) {
            cout << "\nInvalid Passenger Details!\n";
            return;
        }

        if (seats > getAvailableSeats(index)) {
            cout << "\nSorry! Not enough seats available.\n";
            return;
        }

        Ticket t;

        t.pnr = nextPNR++;
        t.passengerName = name;
        t.age = age;
        t.trainNo = number;
        t.seats = seats;
        t.totalFare = seats * trains[index].fare;
        t.active = true;

        bookings.push_back(t);

        cout << "\n========== BOOKING SUCCESSFUL ==========\n";
        cout << "PNR Number       : " << t.pnr << endl;
        cout << "Passenger Name   : " << t.passengerName << endl;
        cout << "Train Name       : " << trains[index].trainName << endl;
        cout << "Source           : " << trains[index].source << endl;
        cout << "Destination      : " << trains[index].destination << endl;
        cout << "Number of Seats  : " << t.seats << endl;
        cout << "Total Fare       : Rs." << t.totalFare << endl;
        cout << "========================================\n";
    }

    void viewTickets() {
        cout << "\n========== BOOKED TICKETS ==========\n";

        bool found = false;

        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].active) {
                found = true;

                cout << "\nPNR Number     : " << bookings[i].pnr;
                cout << "\nPassenger Name : " << bookings[i].passengerName;
                cout << "\nAge            : " << bookings[i].age;
                cout << "\nTrain Number   : " << bookings[i].trainNo;
                cout << "\nSeats          : " << bookings[i].seats;
                cout << "\nTotal Fare     : Rs." << bookings[i].totalFare;
                cout << "\nStatus         : Confirmed\n";
                cout << "------------------------------------\n";
            }
        }

        if (!found) {
            cout << "No active bookings found.\n";
        }
    }

    void searchTicket() {
        int pnr;

        cout << "\nEnter PNR Number: ";
        cin >> pnr;

        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].pnr == pnr && bookings[i].active) {
                cout << "\n========== TICKET DETAILS ==========\n";
                cout << "PNR Number     : " << bookings[i].pnr << endl;
                cout << "Passenger Name : " << bookings[i].passengerName << endl;
                cout << "Age            : " << bookings[i].age << endl;
                cout << "Train Number   : " << bookings[i].trainNo << endl;
                cout << "Seats          : " << bookings[i].seats << endl;
                cout << "Total Fare     : Rs." << bookings[i].totalFare << endl;
                cout << "Status         : Confirmed\n";
                return;
            }
        }

        cout << "\nTicket not found or already cancelled!\n";
    }

    void cancelTicket() {
        int pnr;

        cout << "\nEnter PNR Number to Cancel: ";
        cin >> pnr;

        for (int i = 0; i < bookings.size(); i++) {
            if (bookings[i].pnr == pnr && bookings[i].active) {
                bookings[i].active = false;

                cout << "\nTicket Cancelled Successfully!\n";
                cout << "PNR Number: " << pnr << endl;
                cout << "Cancelled Seats: " << bookings[i].seats << endl;
                return;
            }
        }

        cout << "\nInvalid PNR Number or Ticket Already Cancelled!\n";
    }

    void checkSeats() {
        displayTrains();
    }

    void menu() {
        int choice;

        do {
            cout << "\n\n";
            cout << "========================================\n";
            cout << "       RAILWAY TICKET BOOKING SYSTEM    \n";
            cout << "========================================\n";
            cout << "1. Display Available Trains\n";
            cout << "2. Book Ticket\n";
            cout << "3. View All Bookings\n";
            cout << "4. Search Ticket using PNR\n";
            cout << "5. Cancel Ticket\n";
            cout << "6. Check Available Seats\n";
            cout << "7. Exit\n";
            cout << "========================================\n";

            cout << "Enter Your Choice: ";
            cin >> choice;

            switch (choice) {
                case 1:
                    displayTrains();
                    break;

                case 2:
                    bookTicket();
                    break;

                case 3:
                    viewTickets();
                    break;

                case 4:
                    searchTicket();
                    break;

                case 5:
                    cancelTicket();
                    break;

                case 6:
                    checkSeats();
                    break;

                case 7:
                    cout << "\nThank You for Using Railway Booking System!\n";
                    break;

                default:
                    cout << "\nInvalid Choice! Please Try Again.\n";
            }

        } while (choice != 7);
    }
};

int main() {
    RailwayBooking railway;

    railway.menu();

    return 0;
}

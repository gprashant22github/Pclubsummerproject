#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <regex>


using namespace std;

// Structure to represent a booking
struct Booking {
    int rollNumber;
    string facilityType;
    string date;
    string timeslot;
};

// Class to manage sports facilities
class SportsFacilityManager {
private:
    vector<Booking> bookings;
    string fileName = "bookings.txt";

    void loadBookingsFromFile() {
        ifstream file(fileName);
        if (file.is_open()) {
            Booking booking;
            while (file >> booking.rollNumber >> booking.facilityType >> booking.date >> booking.timeslot) {
                bookings.push_back(booking);
            }
            file.close();
        }
    }

    void saveBookingsToFile() {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const Booking& booking : bookings) {
                file << booking.rollNumber << " " << booking.facilityType << " " << booking.date << " " << booking.timeslot << endl;
            }
            file.close();
        }
    }

public:
    SportsFacilityManager() {
        loadBookingsFromFile();
    }

    void bookSlot(int rollNumber, string facilityType, string date, string timeslot) {
        Booking newBooking = {rollNumber, facilityType, date, timeslot};
        bookings.push_back(newBooking);
        saveBookingsToFile();
        cout << "Slot booked successfully!" << endl;
    }

    bool isSlotAvailable(string facilityType, string date, string newTimeslot) {
    int newStart, newEnd;
    sscanf(newTimeslot.c_str(), "%d-%d", &newStart, &newEnd);

    for (const Booking& booking : bookings) {
        if (booking.facilityType == facilityType && booking.date == date) {
            int existingStart, existingEnd;
            sscanf(booking.timeslot.c_str(), "%d-%d", &existingStart, &existingEnd);

            if ((newStart >= existingStart && newStart < existingEnd) ||
                (newEnd > existingStart && newEnd <= existingEnd) ||
                (newStart <= existingStart && newEnd >= existingEnd)) {
                return false;
            }
        }
    }
    return true;
}

    void viewBookingHistory(int rollNumber) {
        cout << setw(15) << left << "Facility Type" << setw(15) << left << "Date" << setw(15) << left << "Timeslot" << endl;
        cout << string(45, '-') << endl;
        for (const Booking& booking : bookings) {
            if (booking.rollNumber == rollNumber) {
                cout << setw(15) << left << booking.facilityType << setw(15) << left << booking.date << setw(15) << left << booking.timeslot << endl;
            }
        }
    }
};

int getIntInput(string prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            cout << "Invalid input. Please enter an integer." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    return value;
}

int main() {
    SportsFacilityManager manager;
    int choice, rollNumber;
    string facilityType, date, timeslot;

    regex datePattern("(0[1-9]|[12][0-9]|3[01])/(0[1-9]|1[012])/([12][0-9]{3})");
    regex timePattern("([01][0-9]|2[0-3]):[0-5][0-9]-([01][0-9]|2[0-3]):[0-5][0-9]");

    do {
        cout << "\nSports Facility Management System\n";
        cout << "1. Book a slot\n";
        cout << "2. Check slot availability\n";
        cout << "3. View booking history\n";
        cout << "4. Exit\n";
        choice = getIntInput("Enter your choice: ");

        switch (choice) {
            case 1:
                rollNumber = getIntInput("Enter roll number: ");
                if (rollNumber < 100000 || rollNumber > 999999) {
                    cout << "Invalid roll number. It should be a 6-digit integer." << endl;
                    continue;
                }
                cout << "Enter facility type (gym/squash/badminton): ";
                cin >> facilityType;
                cout << "Enter date (dd/mm/yyyy): ";
                cin >> date;
                if (!std::regex_match(date, datePattern)) {
                    cout << "Invalid date format. Please enter in dd/mm/yyyy format." << endl;
                    continue;
                }       
                cout << "Enter timeslot (hh:mm-hh:mm): ";
                cin >> timeslot;
                if (!std::regex_match(timeslot, timePattern)) {
                    cout << "Invalid timeslot format. Please enter in hh:mm-hh:mm format." << endl;
                    continue;
                }
                if (manager.isSlotAvailable(facilityType, date, timeslot)) {
                    manager.bookSlot(rollNumber, facilityType, date, timeslot);
                } else {
                    cout << "Slot is already booked. Please try another time." << endl;
                }
                break;
            case 2:
                cout << "Enter facility type (gym/squash/badminton): ";
                cin >> facilityType;
                cout << "Enter date (dd/mm/yyyy): ";
                cin >> date;
                cout << "Enter timeslot (hh:mm-hh:mm): ";
                cin >> timeslot;
                if (manager.isSlotAvailable(facilityType, date, timeslot)) {
                    cout << "The slot is available." << endl;
                } else {
                    cout << "The slot is already booked." << endl;
                }
                break;
            case 3:
                rollNumber = getIntInput("Enter roll number: ");
                manager.viewBookingHistory(rollNumber);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
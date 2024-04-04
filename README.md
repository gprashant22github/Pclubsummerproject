# Pclubsummerproject
Sports Facility Management System
This Sports Facility Management System is a command-line application written in C++. It provides functionalities to manage sports facility bookings including booking slots, checking slot availability, and viewing booking history.

Features
Book Slots: Users can book slots for different sports facilities by providing their roll number, facility type, date, and timeslot.
Check Slot Availability: Users can check the availability of slots for a specific facility, date, and timeslot.
View Booking History: Users can view their booking history by entering their roll number.
Usage
Book a Slot:

Choose option 1 from the main menu.
Enter your roll number (a 6-digit integer).
Enter the facility type (gym/squash/badminton).
Enter the date in dd/mm/yyyy format.
Enter the timeslot in hh:mm-hh:mm format.
If the slot is available, it will be booked successfully; otherwise, you will be notified that the slot is already booked.
Check Slot Availability:

Choose option 2 from the main menu.
Enter the facility type (gym/squash/badminton).
Enter the date in dd/mm/yyyy format.
Enter the timeslot in hh:mm-hh:mm format.
The system will inform you whether the slot is available or already booked.
View Booking History:

Choose option 3 from the main menu.
Enter your roll number (a 6-digit integer).
The system will display your booking history, including facility type, date, and timeslot.



Setup Instructions
Clone the repository: git clone (https://github.com/gprashant22github/Pclubsummerproject.git)


Compile the program: g++ -o main main.cpp
Run the program: ./main

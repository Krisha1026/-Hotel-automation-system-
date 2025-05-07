#include <iostream>
#include <cstring>

#define max 100
using namespace std;

// Class Customer........................................................

class Customer {
public:
    char name[100];
    char address[100];
    char phone[12];
    char from_date[20];
    char to_date[20];
    float payment_advance;
    int booking_id;
};

class Room {
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;

    Customer cust;
    Room addRoom(int);
    void searchRoom(int);
    void displayRoom(Room);
};

// Global Declarations.......................................

Room rooms[max];
int count = 0;

// Add room..................................................

Room Room::addRoom(int rno) {
    Room room;
    room.roomNumber = rno;
    cout << "\nType AC/Non-AC (A/N) : ";
    cin >> room.ac;
    cout << "\nType  room (type A/B.....) : ";
    cin >> room.type;
    cout << "\nType  size (B/S): ";
    cin >> room.stype;
    cout << "\nDaily Rent : ";
    cin >> room.rent;
    status = 0;

    cout << "\n Room Added Successfully!";
    return room;
}

// Search room....................................................

void Room::searchRoom(int rno) {
    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "Room Details\n";
        if (rooms[i].status == 1) {
            cout << "\nRoom is Reserved";
        } else {
            cout << "\nRoom is available";
        }
        displayRoom(rooms[i]);
    } else {
        cout << "\nRoom not found";
    }
}

// Display room.....................................................

void Room::displayRoom(Room tempRoom) {
    cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    cout << "\nType AC/Non-AC (A/N) " << tempRoom.ac;
    cout << "\nType room (type A/B..) " << tempRoom.type;
    cout << "\nType Size (B/S) " << tempRoom.stype;
    cout << "\nRent: " << tempRoom.rent;
}

// Hotel management class........................................................................

class HotelMgnt : protected Room {
public:
    void checkIn();
    void getAvailRoom();
    void searchCustomer(const char *);
    void checkOut(int);
    void guestSummaryReport();
};

//Guest Summary Report.........................................................................

void HotelMgnt::guestSummaryReport() {
    if (count == 0) {
        cout << "\n No Guest in Hotel !!";
    }
    for (int i = 0; i < count; i++) {
        if (rooms[i].status == 1) {
            cout << "\n Customer First Name : " << rooms[i].cust.name;
            cout << "\n Room Number : " << rooms[i].roomNumber;
            cout << "\n Address (only city) : " << rooms[i].cust.address;
            cout << "\n Phone : " << rooms[i].cust.phone;
            cout << "\n---------------------------------------";
        }
    }
}

// Check In.........................................................................................

void HotelMgnt::checkIn() {
    int i, found = 0, rno;
    Room room;
    cout << "\nEnter Room number : ";
    cin >> rno;
    for (i = 0; i < count; i++) {
        if (rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        if (rooms[i].status == 1) {
            cout << "\nRoom is already Booked\n";
            return;
        }

        cout << "\nEnter booking id: ";
        cin >> rooms[i].cust.booking_id;

        cout << "\nEnter Customer Name (First Name): ";
        cin >> rooms[i].cust.name;

        cout << "\nEnter Address (only city): ";
        cin >> rooms[i].cust.address;

        cout << "\nEnter Phone: ";
        cin >> rooms[i].cust.phone;

        cout << "\nEnter From Date: ";
        cin >> rooms[i].cust.from_date;

        cout << "\nEnter to  Date: ";
        cin >> rooms[i].cust.to_date;

        cout << "\nEnter Advance Payment: ";
        cin >> rooms[i].cust.payment_advance;

        rooms[i].status = 1;

        cout << "\n Customer Checked-in Successfully..";
    }
}

// Available Room..............................................................................................

void HotelMgnt::getAvailRoom() {
    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].status == 0) {
            displayRoom(rooms[i]);
            cout << "\n\nPress enter for next room";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nAll rooms are reserved\n";
    }
}

// Search Customer.................................................................................................

void HotelMgnt::searchCustomer(const char *pname) {
    int i, found = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].status == 1 && strcmp(rooms[i].cust.name, pname) == 0) {
            cout << "\nCustomer Name: " << rooms[i].cust.name;
            cout << "\nRoom Number: " << rooms[i].roomNumber;

            cout << "\n\nPress enter for next record\n";
            found = 1;
        }
    }
    if (found == 0) {
        cout << "\nPerson not found.\n";
    }
}

// Check Out.........................................................................................................

void HotelMgnt::checkOut(int roomNum) {
    int i, found = 0, days, rno;
    float billAmount = 0;
    for (i = 0; i < count; i++) {
        if (rooms[i].status == 1 && rooms[i].roomNumber == roomNum) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        cout << "\nEnter Number of Days:\t";
        cin >> days;
        billAmount = days * rooms[i].rent;

        cout << "\n\t######## CheckOut Details ########\n";
        cout << "\nCustomer Name : " << rooms[i].cust.name;
        cout << "\nRoom Number : " << rooms[i].roomNumber;
        cout << "\nAddress : " << rooms[i].cust.address;
        cout << "\nPhone : " << rooms[i].cust.phone;
        cout << "\nTotal Amount Due : " << billAmount << " /";
        cout << "\nAdvance Paid: " << rooms[i].cust.payment_advance << " /";
        cout << "\n*** Total Payable: " << billAmount - rooms[i].cust.payment_advance << "/ only";

        rooms[i].status = 0;
    }
}

// Manage rooms function..........................................................................................

void manageRooms() {
    Room room;
    int opt, rno, i, flag = 0;
    char ch;
    do {
        cout << "\n### Manage Rooms ###";
        cout << "\n1. Add Room";
        cout << "\n2. Search Room";
        cout << "\n3. Back to Main Menu";
        cout << "\n\nEnter Option: ";
        cin >> opt;
        switch (opt) {
            case 1:
                cout << "\nEnter Room Number: ";
                cin >> rno;
                for (i = 0; i < count; i++) {
                    if (rooms[i].roomNumber == rno) {
                        flag = 1;
                        break;
                    }
                }
                if (flag == 1) {
                    cout << "\nRoom Number is Present.\nPlease enter a unique Number";
                    flag = 0;
                } else {
                    rooms[count] = room.addRoom(rno);
                    count++;
                }
                break;
            case 2:
                cout << "\nEnter room number: ";
                cin >> rno;
                room.searchRoom(rno);
                break;
            case 3:
                //nothing to do
                break;
            default:
                cout << "\nPlease Enter correct option";
                break;
        }
    } while (opt != 3);
}

// Login function..........................................................................................

void login() {
    int password;
    cout << "Hello! Enter password: ";
    cin >> password;
    if (password == 123) {
        cout << "Login successful! Have a nice day" << endl;

        // Welcome Home page screen..........................................................................................

        cout << "\n\n";
        cout << "*******************************************************\n";
        cout << "*                                                     *\n";
        cout << "*       ---------------------------------------       *\n";
        cout << "*            WELCOME TO MOON HOTEL - HOME PAGE       *\n";
        cout << "*       ---------------------------------------       *\n";
        cout << "*                                                     *\n";
        cout << "*******************************************************\n\n\n";

        //  Home page Menu......................................................................................

        int opt;
        do {
            cout << "<<<<<<<<<<<<<< 01.Manage ROOMS ---------------------------------PRESS 1\n";
            cout << "<<<<<<<<<<<<<< 02.CHECK-IN ROOMS--------------------------------PRESS 2\n";
            cout << "<<<<<<<<<<<<<< 03.AVAILABLE ROOMS ------------------------------PRESS 3\n";
            cout << "<<<<<<<<<<<<<< 04.SEARCH CUSTOMER-------------------------------PRESS 4\n";
            cout << "<<<<<<<<<<<<<< 05.CHECK-OUT ROOMS-------------------------------PRESS 5\n";
            cout << "<<<<<<<<<<<<<< 06.GUEST SUMMARY REPORT--------------------------PRESS 6\n";
            cout << "<<<<<<<<<<<<<< 07.EXIT -----------------------------------------PRESS 7\n";
            cout << "\n\nEnter Option: ";
            cin >> opt;

            HotelMgnt hm;
            switch (opt) {
                case 1:
                    manageRooms();
                    break;
                case 2:
                    if (count == 0) {
                        cout << "\nRooms data is not available.\nPlease add the rooms first.";
                    } else
                        hm.checkIn();
                    break;
                case 3:
                    if (count == 0) {
                        cout << "\nRooms data is not available.\nPlease add the rooms first.";
                    } else
                        hm.getAvailRoom();
                    break;
                case 4:
                    if (count == 0) {
                        cout << "\nRooms are not available.\nPlease add the rooms first.";
                    } else {
                        cout << "Enter Customer Name: ";
                        char pname[100];
                        cin >> pname;
                        hm.searchCustomer(pname);
                    }
                    break;
                case 5:
                    if (count == 0) {
                        cout << "\nRooms are not available.\nPlease add the rooms first.";
                    } else {
                        cout << "Enter Room Number : ";
                        int rno;
                        cin >> rno;
                        hm.checkOut(rno);
                    }
                    break;
                case 6:
                    hm.guestSummaryReport();
                    break;
                case 7:
                    cout << "\nTHANK YOU FOR BOOKING WITH MOON HOTEL!\n";
                    break;
                default:
                    cout << "\nPlease Enter correct option";
                    break;
            }
        } while (opt != 7);
    } else {
        cout << "Invalid password. Access denied!" << endl;
    }
}

// Hotel details function..................................................................................................

void hotel_details() {
    cout << "Moon Hotel, a renowned establishment in Kandy City, offers a variety of rooms\n\n";
    cout << "---------------------------------------------------------------------------------------------\n";
    cout << "ROOMS   |A-SINGLE ROOM|B-DOUBLE ROOM |C-TWIN ROOM |D-FAMILY ROOM |E- STANDARD ROOM |F- DELUXE ROOM | \n";
    cout << "AC ROOM | 2000        | 2500         |  3000      |  3500        | 4000            |  4500         | \n";
    cout << "NON-AC  | 1000        | 1500         |  2000      |  2500        | 3000            |  3500         | \n";
}

// Main function.........................................................................................................

int main() {
    int choice;
    do {
        cout << "\n\n";
        cout << "*******************************************************\n";
        cout << "*                                                     *\n";
        cout << "*       ---------------------------------------       *\n";
        cout << "*            WELCOME TO MOON HOTEL - KANDY CITY       *\n";
        cout << "*       ---------------------------------------       *\n";
        cout << "*                                                     *\n";
        cout << "*******************************************************\n\n\n";

        //  Main menu....................................................................................

        cout << "<<<<<<<<<<<<<< 01.RECEPTIONIST LOGIN ---------------PRESS 1\n";
        cout << "<<<<<<<<<<<<<< 02.HOTEL ROOM DETAILS ---------------PRESS 2\n";
        cout << "<<<<<<<<<<<<<< 03.EXIT------------------------------PRESS 3\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << std::endl;

        switch (choice) {
            case 1:
                login();
                break;
            case 2:
                hotel_details();
                break;
            case 3:
                exit(0);
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
                break;
        }
    } while (true);

    return 0;
}


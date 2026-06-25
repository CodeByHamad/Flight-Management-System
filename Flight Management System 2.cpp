#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstring>
#include<limits>
using namespace std;
struct Flight{
    int flightNumber;
    char origin[20];
    char destination[20];
    char time[10];
    int economySeats, businessSeats, firstClassSeats;
    int availableEconomy, availableBusiness, availableFirst;
    float priceEconomy, priceBusiness, priceFirst;
};

struct Booking{
    int bookingID;
    int flightNumber;
    char passengerName[20];
    int seatNumber;
    char ticketClass[10];
    float amount;
    
    
};

//==============Function Declarations========================

bool adminLogin();
void adminMenu();

void addFlight();
void viewFlights();
void searchFlight();
void deleteFlight();
void sortFlightsByPrice();

void bookTicket();
void cancelTicket();
void viewReports();
int generateBookingID();

void pause();
void clearScreen();

	int main(){
    int choice;
    do{
        cout<<"\n========Pakistan International Airline========\n"<<endl;
        cout<<"1. Admin Login "<<endl;
        cout<<"2. Exit"<<endl;
        cout<<"Enter Your Choice : ";
        cin>>choice;

        // ?? FIX: prevent infinite loop
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid input! Please enter a number.\n";
            continue;
        }

        switch(choice){
            case 1:
                if(adminLogin()){
                    adminMenu();
                }
                break;
            case 2:
                cout<<"Thank you for using PIA!"<<endl;
                break;
            default:
                cout<<"Invalid choice!"<<endl;
        } 
    } while(choice!=2);

    return 0;
}


bool adminLogin(){
    string password;
    cout << "Enter Admin Password: ";
    cin >> password;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ?? IMPORTANT

    if(password== "PIA123"){
        cout<<"Login Successful! "<<endl;
        return true;
    }
    cout<<"Wrong Password! "<<endl;
    return false;
}

void adminMenu(){
    int choice;
    do{
    	cout<<"=================================================================\n"<<endl;
        cout<<"---------------------------ADMIN MENU----------------------------\n"<<endl;
        cout<<"=================================================================="<<endl;
        cout << "1. Add Flight"<<endl;
        cout << "2. View Flights"<<endl;
        cout << "3. Search Flight"<<endl;
        cout << "4. Book Ticket"<<endl;
        cout << "5. Cancel Ticket"<<endl;
        cout << "6. View Revenue Report"<<endl;
        cout << "7. Sort Flights by Price"<<endl;
        cout << "8. Delete Flight"<<endl;
        cout << "9. Logout"<<endl;
        cout << "Enter choice: ";
        cin >> choice;

        // ?? FIX: prevent infinite loop
        if(cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<<"Invalid input! Please enter a number.\n";
            continue;
        }

        switch(choice){
            case 1:
                addFlight();
                break;
            case 2:
                viewFlights();
                break;
            case 3:
                searchFlight();
                break;
            case 4:
                bookTicket();
                break;
            case 5:
                cancelTicket();
                break;
            case 6:
                viewReports();
                break;
            case 7:
                sortFlightsByPrice();
                break;
            case 8:
                deleteFlight();
                break;
            case 9:
                clearScreen();
                break;
            default:
                cout<<"Invalid choice!"<<endl;
        }
    } while(choice != 9);
}


void addFlight() {
    Flight f;
    ofstream out("flight.dat", ios::binary | ios::app);

    cout << "Flight Number: ";
    cin >> f.flightNumber;

    // ?? FIX: check input failure
    if (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid flight number!\n";
        pause();
        return;
    }

    // ?? FIX: clear full buffer
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout<<"Origin: ";
    cin.getline(f.origin, 20);

    cout<<"Destination: ";
    cin.getline(f.destination, 20);

    cout<<"Departure Time: ";
    cin.getline(f.time, 10);

    cout<<"Number of Economy Seats: ";
    cin>>f.economySeats;
    if (cin.fail()){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout<<"Invalid input!\n";
        pause();
        return;
    }
    f.availableEconomy = f.economySeats;

    cout<<"Economy Price: ";
    cin>>f.priceEconomy;

    cout<<"Number of Business Seats: ";
    cin>>f.businessSeats;
    f.availableBusiness = f.businessSeats;

    cout<<"Business Price: ";
    cin>>f.priceBusiness;

    cout<<"Number of First Class Seats: ";
    cin>>f.firstClassSeats;
    f.availableFirst = f.firstClassSeats;

    cout<<"First Class Price: ";
    cin>>f.priceFirst;

    // ?? FIX: clear leftover ENTER before pause()
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    out.write((char*)&f, sizeof(f));
    out.close();

    cout<<"Flight added successfully!\n";
    pause();
}

void viewFlights() {
    Flight f;
    ifstream in("flight.dat", ios::binary);

    cout<<left<< setw(10) << "Flight";
    cout<<setw(15)<<"From";
    cout<<setw(15)<<"To";
    cout<<setw(10)<<"Time";
    cout<<setw(10)<<"Econ";
    cout<<setw(10)<<"Bus";
    cout<<setw(10)<<"First"<<endl;

    cout<<string(70, '-')<<endl;

    while(in.read((char*)&f, sizeof(f))){
        cout<<left<<setw(10) << f.flightNumber;
        cout<<setw(15)<<f.origin;
        cout<<setw(15)<<f.destination;
        cout<<setw(10)<<f.time;
        cout<<setw(10)<<f.availableEconomy;
        cout<<setw(10)<<f.availableBusiness;
        cout<<setw(10)<<f.availableFirst<<endl;
    }

    in.close();
    pause();
}

void searchFlight(){
    Flight f;
    int num;
    bool found=false;
    cout<<"Enter Flight Number: ";
    cin>>num;
    ifstream in("flight.dat", ios::binary);
    while(in.read((char*)&f, sizeof(f))){
        if (f.flightNumber == num) {
            cout<<"\nFlight Found!"<<endl;
            cout<<"Route: "<<f.origin<<" -> "<<f.destination<<endl;
            cout<<"Time : "<<f.time<<endl;
            cout<<"Seats Available: Economy="<<f.availableEconomy
                <<", Business="<<f.availableBusiness
                << ", First="<<f.availableFirst << endl;
            cout<<"Price: Economy="<<f.priceEconomy
                <<", Business=" <<f.priceBusiness
                <<", First=" << f.priceFirst << endl;
            found = true;
            break;
        }
    }

    if(!found)
        cout<<"Flight not found!\n";

    in.close();
    pause();
}


void deleteFlight(){
    Flight f;
    int num;
    bool found =false;

    cout<<"Enter Flight Number to Delete: ";
    cin>>num;

    ifstream in("flight.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while(in.read((char*)&f, sizeof(f))){
        if(f.flightNumber == num)
            found = true;
        else
            temp.write((char*)&f, sizeof(f));
    }

    in.close();
    temp.close();

    remove("flight.dat");
    rename("temp.dat", "flight.dat");

    if (found)
        cout<<"Flight deleted successfully!\n";
    else
        cout<<"Flight not found!\n";

    pause();
}
//=========Book Tickets=========

void bookTicket() {
    Flight f;
    int flightNo, numPassengers;
    bool found = false;

    fstream file("flight.dat", ios::in | ios::out | ios::binary);
    if (!file) {
        cout<<"No flights available!\n";
        pause();
        return;
    }
	int nextBookingID = generateBookingID();

    cout<<"Enter Flight Number: ";
    cin>>flightNo;

    cout<<"Enter Number of Passengers: ";
    cin>>numPassengers;

    if(numPassengers <= 0){
        cout<<"Invalid number!\n";
        pause();
        return;
    }

    while(file.read((char*)&f, sizeof(f))) {
        if(f.flightNumber == flightNo) {
            found = true;

            char passengerNames[50][20];
            char ticketClasses[50][10];
            int seatNumbers[50];
            float prices[50];
            int bookingIDs[50];

            int bookedCount = 0;

            for(int i = 0; i < numPassengers; i++) {
                cin.ignore();
                cout<<"Enter Name of Passenger " << (i + 1) << ": ";
                cin.getline(passengerNames[i], 20);

                int classChoice;
                cout<<"Select Ticket Class: 1-Economy 2-Business 3-First: ";
                cin>>classChoice;

                int seatNumber = 0;
                float price = 0;

                if(classChoice == 1 && f.availableEconomy > 0) {
                    seatNumber = f.economySeats - f.availableEconomy + 1;
                    f.availableEconomy--;
                    price = f.priceEconomy;
                    strcpy(ticketClasses[i], "Economy");
                }
                else if(classChoice == 2 && f.availableBusiness > 0) {
                    seatNumber = f.businessSeats - f.availableBusiness + 1;
                    f.availableBusiness--;
                    price = f.priceBusiness;
                    strcpy(ticketClasses[i], "Business");
                }
                else if(classChoice == 3 && f.availableFirst > 0) {
                    seatNumber = f.firstClassSeats - f.availableFirst + 1;
                    f.availableFirst--;
                    price = f.priceFirst;
                    strcpy(ticketClasses[i], "First");
                }
                else{
                    cout << "Selected class not available. Try again.\n";
                    i--;
                    continue;
                }

                seatNumbers[i] = seatNumber;
                prices[i] = price;
//                int nextBookingID = generateBookingID();
				bookingIDs[i] = nextBookingID++;
                bookedCount++;
            }

            cout << "\n-------------------- AIRLINE BILL --------------------\n";
            cout << left
                 << setw(12) << "BookingID"
                 << setw(15) << "Name"
                 << setw(8)  << "Seat"
                 << setw(10) << "Class"
                 << setw(10) << "Flight"
                 << setw(15) << "From"
                 << setw(15) << "To"
                 << setw(10) << "Amount" << endl;

            cout << string(95, '-') << endl;

            float totalBill = 0;

            for (int i = 0; i < bookedCount; i++) {
                cout << left
                     << setw(12) << bookingIDs[i]
                     << setw(15) << passengerNames[i]
                     << setw(8)  << seatNumbers[i]
                     << setw(10) << ticketClasses[i]
                     << setw(10) << f.flightNumber
                     << setw(15) << f.origin
                     << setw(15) << f.destination
                     << setw(10) << prices[i] << endl;

                Booking b;
                b.bookingID = bookingIDs[i];
                b.flightNumber = flightNo;
                strcpy(b.passengerName, passengerNames[i]);
                b.seatNumber = seatNumbers[i];
                strcpy(b.ticketClass, ticketClasses[i]);
                b.amount = prices[i];

                ofstream out("booking.dat", ios::binary | ios::app);
                out.write((char*)&b, sizeof(b));
                out.close();

                totalBill += prices[i];
            }

            cout << string(95, '-') << endl;
            cout << right << setw(85) << "Total: Rs " << totalBill << endl;

            int payChoice;
            cout << "\nSelect Payment Method:\n";
            cout << "1. Cash\n";
            cout << "2. Card\n";
            cout << "Enter choice: ";
            cin >> payChoice;

            switch (payChoice) {
                case 1:
                    cout << "Payment paid through cash.\n";
                    break;
                case 2:
                    cout << "Payment paid through card.\n";
                    break;
                default:
                    cout << "Invalid choice! Payment pending.\n";
            }

            cout << "\nBooking Successful!\n";

            file.seekp(-sizeof(f), ios::cur);
            file.write((char*)&f, sizeof(f));
            break;
        }
    }

    if (!found)
        cout << "Flight not found!\n";

    file.close();
    pause();
}



/* ================= CANCEL TICKET ================= */


void cancelTicket() {
    Booking b;
    int id;
    bool found = false;

    cout << "Enter Booking ID to Cancel: ";
    cin >> id;

    ifstream in("booking.dat", ios::binary);
    ofstream temp("temp.dat", ios::binary);

    while (in.read((char*)&b, sizeof(b))) {
        if (b.bookingID == id) {
            found = true;

            // Update flight seats
            Flight f;
            fstream fl("flight.dat", ios::in | ios::out | ios::binary);
            while (fl.read((char*)&f, sizeof(f))) {
                if (f.flightNumber == b.flightNumber) {
                    if (strcmp(b.ticketClass, "Economy") == 0) f.availableEconomy++;
                    else if (strcmp(b.ticketClass, "Business") == 0) f.availableBusiness++;
                    else if (strcmp(b.ticketClass, "First") == 0) f.availableFirst++;
                    fl.seekp(-sizeof(f), ios::cur);
                    fl.write((char*)&f, sizeof(f));
                    break;
                }
            }
            fl.close();

            cout << "Booking Cancelled Successfully!\n";
            cout << "Passenger: " << b.passengerName << endl;
            cout << "Refund Amount: Rs " << b.amount << endl;
        } else {
            temp.write((char*)&b, sizeof(b));
        }
    }

    in.close();
    temp.close();

    remove("booking.dat");
    rename("temp.dat", "booking.dat");

    if (!found)
        cout << "Booking ID not found!\n";

    pause();
}

/* ================= REPORT ================= */

void viewReports() {
    Booking b;
    float revenue = 0;

    ifstream in("booking.dat", ios::binary);
    while (in.read((char*)&b, sizeof(b)))
        revenue += b.amount;

    in.close();
    cout << "Total Revenue: Rs " << revenue << endl;
    pause();
}

/* ================= SORT ================= */

void sortFlightsByPrice() {
    Flight a[50];
    int n = 0;

    ifstream in("flight.dat", ios::binary);
    while (in.read((char*)&a[n], sizeof(Flight))) n++;
    in.close();

    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (a[i].priceEconomy > a[j].priceEconomy)
                swap(a[i], a[j]);

    ofstream out("flight.dat", ios::binary);
    for (int i = 0; i < n; i++)
        out.write((char*)&a[i], sizeof(Flight));
    out.close();

    cout << "Flights sorted by Economy price!\n";
    pause();
}

/* ================= UTILITIES ================= */

int generateBookingID() {
    Booking b;
    int lastID = 1000;

    ifstream in("booking.dat", ios::binary);
    while (in.read((char*)&b, sizeof(b)))
        lastID = b.bookingID;
    in.close();

    return lastID + 1;
}

void clearScreen() {
    system("cls");
}

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    clearScreen();
}

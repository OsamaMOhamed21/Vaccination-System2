#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <ctime>
using namespace std;


class Reservation {
public:
    string clientName;
    string vaccineType;
    string timeSlot;
    double invoiceAmount;

    Reservation(string name, string vaccine, string slot, double amount)
        : clientName(name), vaccineType(vaccine), timeSlot(slot), invoiceAmount(amount) {}

    void displayReservation() {
        cout << "\nClient Name: " << clientName << endl;
        cout << "Vaccine Type: " << vaccineType << endl;
        cout << "Time Slot: " << timeSlot << endl;
        cout << "Invoice Amount: $" << invoiceAmount << endl;
    }


    void saveToFile(ofstream &outFile) {
        outFile << clientName << "," << vaccineType << "," << timeSlot << "," << invoiceAmount << endl;
    }
};


class User {
public:
    string name;
    string password;
    string userType;
    User* next;

    User(string name, string password, string userType) {
        this->name = name;
        this->password = password;
        this->userType = userType;
        this->next = nullptr;
    }


    void saveToFile(ofstream &outFile) {
        outFile << name << "," << password << "," << userType << endl;
    }
};


class VaccinationSystem {
private:
    User* headUser;
    list<Reservation> reservations;
    list<string> vaccineStore;

public:
    VaccinationSystem() : headUser(nullptr) {}


    void addVaccineToStore(string vaccine) {
        vaccineStore.push_back(vaccine);
        ofstream outFile("vaccines.txt", ios::app);
        outFile << vaccine << endl;
        outFile.close();
        cout << "Vaccine " << vaccine << " added to store.\n";
    }


    void generateStoreReport() {
        cout << "\nVaccination Store Report:\n";
        cout << "Available Vaccines:\n";
        for (const string& vaccine : vaccineStore) {
            cout << "- " << vaccine << endl;
        }
        cout << "Total Vaccines Available: " << vaccineStore.size() << endl;
    }


    void loadVaccinesFromFile() {
        ifstream inFile("vaccines.txt");
        string vaccine;
        while (getline(inFile, vaccine)) {
            vaccineStore.push_back(vaccine);
        }
        inFile.close();
    }


    void reserveAppointment(string clientName, string vaccineType, string timeSlot) {
        double amount = 100;  // Default invoice amount
        Reservation newReservation(clientName, vaccineType, timeSlot, amount);
        reservations.push_back(newReservation);

        // Save reservation to file
        ofstream outFile("reservations.txt", ios::app);
        newReservation.saveToFile(outFile);
        outFile.close();

        cout << "\nReservation successful for " << clientName << "!\n";
        cout << "Appointment scheduled for " << timeSlot << " with " << vaccineType << " vaccine.\n";
        newReservation.displayReservation();
    }


    void loadReservationsFromFile() {
        ifstream inFile("reservations.txt");
        string line;
        while (getline(inFile, line)) {
            size_t firstComma = line.find(",");
            size_t secondComma = line.find(",", firstComma + 1);
            size_t thirdComma = line.find(",", secondComma + 1);

            string clientName = line.substr(0, firstComma);
            string vaccineType = line.substr(firstComma + 1, secondComma - firstComma - 1);
            string timeSlot = line.substr(secondComma + 1, thirdComma - secondComma - 1);
            double invoiceAmount = stod(line.substr(thirdComma + 1));

            Reservation newReservation(clientName, vaccineType, timeSlot, invoiceAmount);
            reservations.push_back(newReservation);
        }
        inFile.close();
    }


    void addUser(string username, string password, string userType) {
        User* newUser = new User(username, password, userType);
        if (headUser == nullptr) {
            headUser = newUser;
        } else {
            User* temp = headUser;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newUser;
        }


        ofstream outFile("users.txt", ios::app);
        newUser->saveToFile(outFile);
        outFile.close();

        cout << "User " << username << " added successfully!\n";
    }


    User* searchUser(string username) {
        User* temp = headUser;
        while (temp != nullptr) {
            if (temp->name == username) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }


    bool login(string username, string password) {
        User* user = searchUser(username);
        if (user != nullptr && user->password == password) {
            cout << "Login successful! Welcome, " << user->name << endl;
            return true;
        } else {
            cout << "Invalid username or password!" << endl;
            return false;
        }
    }

    // Logout method for users
    void logout() {
        cout << "You have been logged out successfully.\n";
    }


    void listUsers() {
        User* temp = headUser;
        cout << "\nList of users:\n";
        while (temp != nullptr) {
            cout << "Username: " << temp->name << ", Role: " << temp->userType << endl;
            temp = temp->next;
        }
    }


    void displayMenu() {
        cout << "\n***** Vaccination System Menu *****\n";
        cout << "1. Reserve an appointment\n";
        cout << "2. View store report\n";
        cout << "3. Add user (Admin only)\n";
        cout << "4. List all users (Admin only)\n";
        cout << "5. Login\n";
        cout << "6. Logout\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
    }


    void loadUsersFromFile() {
        ifstream inFile("users.txt");
        string line;
        while (getline(inFile, line)) {
            size_t firstComma = line.find(",");
            size_t secondComma = line.find(",", firstComma + 1);

            string username = line.substr(0, firstComma);
            string password = line.substr(firstComma + 1, secondComma - firstComma - 1);
            string userType = line.substr(secondComma + 1);

            addUser(username, password, userType);
        }
        inFile.close();
    }
};

int main() {
    VaccinationSystem system;
    string username, password, vaccineType, timeSlot, userType;
    int choice;
    bool loggedIn = false;

    while (true) {
        system.displayMenu();
        cin >> choice;

        switch (choice) {
        case 1:
            if (loggedIn) {
                cout << "Enter client name: ";
                cin.ignore();
                getline(cin, username);
                cout << "Enter vaccine type : ";
                getline(cin, vaccineType);
                cout << "Enter desired time slot: ";
                getline(cin, timeSlot);

                system.reserveAppointment(username, vaccineType, timeSlot);
            }
            else {
                cout << "You must be logged in to reserve an appointment!\n";
            }
            break;

        case 2:
            if (loggedIn) {
                system.generateStoreReport();
            }
            else {
                cout << "You must be logged in to view the store report!\n";
            }
            break;

        case 3:
            if (loggedIn) {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;
                cout << "Enter user role (Client, Seller, Admin): ";
                cin >> userType;

                system.addUser(username, password, userType);
            }
            else {
                cout << "You must be logged in to add a user!\n";
            }
            break;

        case 4:
            if (loggedIn) {
                system.listUsers();
            }
            else {
                cout << "You must be logged in to list users!\n";
            }
            break;

        case 5:
            if (!loggedIn) {
                cout << "Enter username: ";
                cin >> username;
                cout << "Enter password: ";
                cin >> password;

                loggedIn = system.login(username, password);
            }
            else {
                cout << "You are already logged in!\n";
            }
            break;

        case 6:
            if (loggedIn) {
                system.logout();
                loggedIn = false;
            }
            else {
                cout << "You are not logged in!\n";
            }
            break;

        case 7:
            cout << "Exiting the system...\n";
            return 0;

        default:
            cout << "Invalid choice, please try again.\n";
        }
    }
}

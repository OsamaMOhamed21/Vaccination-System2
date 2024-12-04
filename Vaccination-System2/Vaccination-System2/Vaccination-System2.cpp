#include<iostream>
#include<string>
#include<list>
#include<ctime>
using namespace std;

class Reservation {
public:
    string clientName;
    string vaccineType;
    string timeSlot;
    double invoiceAmount;

    Reservation(string name, string vaccine, string slot, double amount) {
        clientName = name;
        vaccineType = vaccine;
        timeSlot = slot;
        invoiceAmount = amount;
    }

    void displayReservation() {
        cout << "\nClient Name: " << clientName << endl;
        cout << "Vaccine Type: " << vaccineType << endl;
        cout << "Time Slot: " << timeSlot << endl;
        cout << "Invoice Amount: $" << invoiceAmount << endl;
    }
};

class User {
public:
    string name;
    string password;
    string userType;
    User* next;

    User() {
        next = nullptr;
    }

    User(string name, string password, string userType) {
        this->name = name;
        this->password = password;
        this->userType = userType;
        this->next = nullptr;
    }
};

class VaccinationSystem {
private:
    User* headUser;
    list<Reservation> reservations;
    list<string> vaccineStore;

public:
    VaccinationSystem() {
        headUser = nullptr;
    }

    void reserveAppointment(string clientName, string vaccineType, string timeSlot) {
        double amount = 100;
        Reservation newReservation(clientName, vaccineType, timeSlot, amount);
        reservations.push_back(newReservation);
        cout << "\nReservation successful for " << clientName << "!\n";
        cout << "Appointment scheduled for " << timeSlot << " with " << vaccineType << " vaccine.\n";
        newReservation.displayReservation();
    }

    void sendNotification(string clientName) {
        cout << "\nEmail sent to " << clientName << " requesting feedback on the service.\n";
    }

    void generateStoreReport() {
        cout << "\nVaccination Store Report:\n";
        cout << "Available Vaccines:\n";
        for (const string& vaccine : vaccineStore) {
            cout << " " << vaccine << endl;
        }
        cout << "Total Vaccines Available: " << vaccineStore.size() << endl;
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
        cout << "\nUser added successfully!\n";
    }

    User* searchUser(string username) {
        User* temp = headUser;
        while (temp != nullptr) {
            if (temp->name == username) {  // Correct comparison
                return temp;
            }
            temp = temp->next;
        }
        return nullptr; // Return nullptr if user is not found
    }

    bool login(string username, string password) {
        User* user = searchUser(username);
        if (user != nullptr && user->password == password) {
            cout << "Login successful! Welcome, " << user->name << endl; // Corrected to 'name'
            return true;
        } else {
            cout << "Invalid username or password!" << endl;
            return false;
        }
    }

    void logout() {
        cout << "You have been logged out successfully.\n";
    }

    void listUsers() {
        User* temp = headUser;
        cout << "\nList of users:\n";
        while (temp != nullptr) {
            cout << "Username: " << temp->name << ", Role: " << temp->userType << endl; // Corrected 'username' to 'name'
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

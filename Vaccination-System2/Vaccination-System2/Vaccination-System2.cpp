#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;


class User {
protected:
    string username;
    string password;
    string userType;

public:
    User(string username, string password, string userType): username(username), password(password), userType(userType) 
        {

        }

    string getUsername()
    {
         return username;
     }
    string getUserType()  
    {
         return userType; 
    }
    string getPassword()
    {
        return password ;
    }

    void login() {
        cout << username << " logged in as " << userType << ".\n";
    }

    void logout() {
        cout << username << " logged out.\n";
    }
};


class Client : public User {
private:
    vector<string> appointments;

public:
    Client(string username, string password): User(username, password, "Client")
         {

        }

    void reserveAppointment(const string& timeSlot) 
    {
        appointments.push_back(timeSlot);
        cout << "Appointment reserved at " << timeSlot << ".\n";
    }

    void generateInvoice() 
     {
        if (!appointments.empty())
         {
            cout << "Invoice for appointments:\n";
            for (const auto& slot : appointments)
                cout << "- Appointment at " << slot << endl;
        } else {
            cout << "No appointments to generate invoice for.\n";
        }
    }

    void searchSlot(const string& timeSlot) 
     {
        for (const auto& slot : appointments)
         {
            if (slot == timeSlot) {
                cout << "You have an appointment at " << timeSlot << ".\n";
                return;
            }
        }
        cout << timeSlot << " is available.\n";
    }

    void sendNotification() 
     {
        cout << "Notification email sent to " << username
             << " for service evaluation.\n";
    }
        void saveAppointmentsToFile() 
         {
        ofstream outFile("appointments_" + username + ".txt");
        for (const auto& slot : appointments) {
            outFile << slot << "\n";
        }
    }

    void loadAppointmentsFromFile()
     {
        ifstream inFile("appointments_" + username + ".txt");
        string slot;
        while (getline(inFile, slot)) {
            appointments.push_back(slot);
        }
    }
};


class StoreManagement 
{
private:
    vector<string> vaccines;
    int vaccineCount;

public:
    StoreManagement(int initialCount = 100) : vaccineCount(initialCount) 
    {
        
    }

    void manageStore() {
        cout << "Current vaccine count: " << vaccineCount << endl;
        int used;
        cout << "Enter number of vaccines used: ";
        cin >> used;
        if (used <= vaccineCount) 
        {
            vaccineCount -= used;
            cout << "Vaccine count updated: " << vaccineCount << endl;
        } else {
            cout << "Not enough vaccines in stock.\n";
        }
    }

    void generateReport() 
     {
        cout << "Vaccination store status:\n";
        cout << "- Total vaccines available: " << vaccineCount << endl;
    }
     void saveInventoryToFile() 
      {
        ofstream outFile("inventory.txt");
        outFile << vaccineCount << endl;
    }

    void loadInventoryFromFile()
     {
        ifstream inFile("inventory.txt");
        if (inFile >> vaccineCount) 
        {
            cout << "Inventory loaded successfully.\n";
        } else 
        {
            cout << "Failed to load inventory. Using default value.\n";
        }
    }
};


class UserManagement 
{
private:
    vector<User*> users;

public:
    ~UserManagement() 
    {
        for (auto user : users)
            delete user;
    }

    void addUser(const string& username, const string& password, const string& userType)
     {
        if (userType == "Client") {
            users.push_back(new Client(username, password));
        } else {
            users.push_back(new User(username, password, userType));
        }
        cout << userType << " added successfully with username: " << username << endl;
    }

    void updateUser(const string& username)
     {
        for (auto user : users) {
            if (user->getUsername() == username) {
                cout << "Updating " << username << "'s details.\n";
                string newUsername, newPassword;
                cout << "Enter new username: ";
                cin >> newUsername;
                cout << "Enter new password: ";
                cin >> newPassword;
                user->logout();
                cout << username << " updated successfully to " << newUsername << ".\n";
                return;
            }
        }
        cout << "User not found.\n";
    }

    void deleteUser(const string& username)
     {
        for (auto it = users.begin(); it != users.end(); ++it)
        {
            if ((*it)->getUsername() == username) {
                cout << "User " << username << " deleted successfully.\n";
                delete *it;
                users.erase(it);
                return;
            }
        }
        cout << "User not found.\n";
    }

    void listUsers() 
    {
        if (users.empty()) 
        {
            cout << "No users registered.\n";
        } else {
            cout << "Registered Users:\n";
            for (const auto& user : users) {
                cout << " " << user->getUserType() << ": " << user->getUsername() << endl;
            }
        }
    }
      void saveUsersToFile() 
       {
        ofstream outFile("users.txt");
        for (const auto& user : users) {
            outFile << user->getUserType() << " " << user->getUsername() << " " << user->getPassword() << "\n";
        }
    }

    void loadUsersFromFile() {
        ifstream inFile("users.txt");
        string userType, username, password;
        while (inFile >> userType >> username >> password) {
            addUser(username, password, userType);
        }
    }
};


int main() {
    StoreManagement store(200);
    UserManagement userManagement;

    store.loadInventoryFromFile();
    userManagement.loadUsersFromFile();

    int choice;

    do {
        cout << "\n--- Vaccination System ---\n";
        cout << "1. Client Reservation\n";
        cout << "2. Vaccination Store Management\n";
        cout << "3. User Management\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
         {
            case 1:
             {
                string username, password, timeSlot;
                cout << "\n--- Client Reservation ---\n";
                cout << "Enter Username: ";
                cin >> username;
                cout << "Enter Password: ";
                cin >> password;

               
                Client client(username, password);
                client.login();

                cout << "1. Reserve Appointment\n";
                cout << "2. Generate Invoice\n";
                cout << "3. Search Time Slot\n";
                cout << "4. Send Notification\n";
                int clientChoice;
                cin >> clientChoice;

                switch (clientChoice)
                 {
                    case 1:
                        cout << "Enter preferred time slot: ";
                        cin.ignore();
                        getline(cin, timeSlot);
                        client.reserveAppointment(timeSlot);
                        break;
                    case 2:
                        client.generateInvoice();
                        break;
                    case 3:
                        cout << "Enter time slot to search: ";
                        cin.ignore();
                        getline(cin, timeSlot);
                        client.searchSlot(timeSlot);
                        break;
                    case 4:
                        client.sendNotification();
                        break;
                    default:
                        cout << "Invalid choice.\n";
                }
                client.logout();
                break;
            }

            case 2:
                cout << "\n--- Vaccination Store Management ---\n";
                cout << "1. Manage Store\n";
                cout << "2. Generate Report\n";
                cin >> choice;

                if (choice == 1) 
                {
                    store.manageStore();
                } else if (choice == 2) 
                {
                    store.generateReport();
                } else {
                    cout << "Invalid choice.\n";
                }
                break;

            case 3:
                cout << "\n--- User Management ---\n";
                cout << "1. Add User\n";
                cout << "2. Update User\n";
                cout << "3. Delete User\n";
                cout << "4. List Users\n";
                cin >> choice;

                if (choice == 1)
                 {
                    string username, password, userType;
                    cout << "Enter Username: ";
                    cin >> username;
                    cout << "Enter Password: ";
                    cin >> password;
                    cout << "Enter User Type (Client/Seller/Admin): ";
                    cin >> userType;
                    userManagement.addUser(username, password, userType);
                } else if (choice == 2) 
                {
                    string username;
                    cout << "Enter Username to update: ";
                    cin >> username;
                    userManagement.updateUser(username);
                } else if (choice == 3) 
                {
                    string username;
                    cout << "Enter Username to delete: ";
                    cin >> username;
                    userManagement.deleteUser(username);
                } else if (choice == 4)

                {
                    userManagement.listUsers();
                } else {
                    cout << "Invalid choice.\n";
                }
                break;

            case 4:
                cout << "Exiting the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}

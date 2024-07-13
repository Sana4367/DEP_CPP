#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class Contact {
public:
    std::string name;
    std::string phoneNumber;
    std::string address;
    std::string cnic;

    Contact() = default;
    Contact(std::string n, std::string p, std::string a, std::string c) 
        : name(n), phoneNumber(p), address(a), cnic(c) {}
};

void saveContacts(const std::vector<Contact>& contacts) {
    std::ofstream file("phone_directory.txt");
    for (const auto& contact : contacts) {
        file << contact.name << "," << contact.phoneNumber << "," 
             << contact.address << "," << contact.cnic << "\n";
    }
    file.close();
}

void loadContacts(std::vector<Contact>& contacts) {
    std::ifstream file("phone_directory.txt");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> data;
        while ((pos = line.find(',')) != std::string::npos) {
            token = line.substr(0, pos);
            data.push_back(token);
            line.erase(0, pos + 1);
        }
        data.push_back(line);
        if (data.size() == 4) {
            contacts.push_back(Contact(data[0], data[1], data[2], data[3]));
        }
    }
    file.close();
}

void addContact(std::vector<Contact>& contacts) {
    std::string name, phoneNumber, address, cnic;
    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, phoneNumber);
    std::cout << "Enter address: ";
    std::getline(std::cin, address);
    std::cout << "Enter CNIC: ";
    std::getline(std::cin, cnic);
    contacts.push_back(Contact(name, phoneNumber, address, cnic));
    saveContacts(contacts);
    std::cout << "Contact added successfully.\n";
}

void viewContacts() {
    std::ifstream file("phone_directory.txt");
    std::string line;
    int index = 1;
    std::cout << "Contacts List:\n";
    while (std::getline(file, line)) {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> data;
        while ((pos = line.find(',')) != std::string::npos) {
            token = line.substr(0, pos);
            data.push_back(token);
            line.erase(0, pos + 1);
        }
        data.push_back(line);
        if (data.size() == 4) {
            std::cout << index << ". Name: " << data[0] 
                      << ", Phone Number: " << data[1] 
                      << ", Address: " << data[2] 
                      << ", CNIC: " << data[3] << "\n";
            index++;
        }
    }
    file.close();
}

void deleteContact(std::vector<Contact>& contacts) {
    std::string cnic;
    std::cout << "Enter the CNIC of the contact to delete: ";
    std::cin >> cnic;

    auto it = contacts.begin();
    bool found = false;
    while (it != contacts.end()) {
        if (it->cnic == cnic) {
            it = contacts.erase(it);
            saveContacts(contacts);
            std::cout << "Contact deleted successfully.\n";
            found = true;
            break;
        } else {
            ++it;
        }
    }

    if (!found) {
        std::cout << "No contact found with the provided CNIC.\n";
    }
}

void updateContact(std::vector<Contact>& contacts) {
    std::string cnic;
    std::cout << "Enter the CNIC of the contact to update: ";
    std::cin >> cnic;

    auto it = contacts.begin();
    bool found = false;
    while (it != contacts.end()) {
        if (it->cnic == cnic) {
            it = contacts.erase(it);
            found = true;
            break;
        } else {
            ++it;
        }
    }

    if (found) {
        std::cout << "Enter new details for the contact.\n";
        addContact(contacts);
        std::cout << "Contact updated successfully.\n";
    } else {
        std::cout << "No contact found with the provided CNIC.\n";
    }
}

void displayAdminMenu() {
    std::cout << "Admin Menu\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. View Contacts\n";
    std::cout << "3. Delete Contact\n";
    std::cout << "4. Update Contact\n";
    std::cout << "5. Exit\n";
}

void displayUserMenu() {
    std::cout << "User Menu\n";
    std::cout << "1. View My Contacts\n";
    std::cout << "2. Exit\n";
}

bool authenticateAdmin() {
    std::string username, password;
    std::cout << "Enter admin username: ";
    std::cin >> username;
    std::cout << "Enter admin password: ";
    std::cin >> password;
    return username == "sana" && password == "sana@345";
}

void adminInterface(std::vector<Contact>& contacts) {
    int choice;
    do {
        displayAdminMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                addContact(contacts);
                break;
            case 2:
                viewContacts();
                break;
            case 3:
                deleteContact(contacts);
                break;
            case 4:
                updateContact(contacts);
                break;
            case 5:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);
}

void viewUserContacts() {
    std::string cnic;
    std::cout << "Enter your CNIC: ";
    std::cin >> cnic;
    std::ifstream file("phone_directory.txt");
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        size_t pos = 0;
        std::string token;
        std::vector<std::string> data;
        while ((pos = line.find(',')) != std::string::npos) {
            token = line.substr(0, pos);
            data.push_back(token);
            line.erase(0, pos + 1);
        }
        data.push_back(line);
        if (data.size() == 4 && data[3] == cnic) {
            std::cout << "Name: " << data[0] 
                      << ", Phone Number: " << data[1] 
                      << ", Address: " << data[2] 
                      << ", CNIC: " << data[3] << "\n";
            found = true;
            break;
        }
    }
    file.close();
    if (!found) {
        std::cout << "No contact found with the provided CNIC.\n";
    }
}

void userInterface() {
    int choice;
    do {
        displayUserMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                viewUserContacts();
                break;
            case 2:
                std::cout << "Exiting...\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 2);
}

int main() {
    std::vector<Contact> contacts;
    loadContacts(contacts);
    int role;
    std::cout << "Select role:\n1. Admin\n2. User\nEnter your choice: ";
    std::cin >> role;

    if (role == 1) {
        if (authenticateAdmin()) {
            adminInterface(contacts);
        } else {
            std::cout << "Authentication failed. Exiting...\n";
        }
    } else if (role == 2) {
        userInterface();
    } else {
        std::cout << "Invalid role. Exiting...\n";
    }

    return 0;
}

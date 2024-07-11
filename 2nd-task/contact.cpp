#include <iostream>
#include <vector>
#include <string>

class Contact {
public:
	std::string name;
	std::string phoneNumber;

	Contact(std::string n, std::string p) : name(n), phoneNumber(p) {}
	
};
void addContact(std::vector<Contact>& contacts) {
    std::string name, phoneNumber;
    std::cout << "Enter name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    std::cout << "Enter phone number: ";
    std::getline(std::cin, phoneNumber);
    contacts.push_back(Contact(name, phoneNumber));
    std::cout << "Contact added successfully.\n";
}

void viewContacts(const std::vector<Contact>& contacts) {
    std::cout << "Contacts List:\n";
    for (size_t i = 0; i < contacts.size(); ++i) {
        std::cout << i + 1 << ". Name: " << contacts[i].name << ", Phone Number: " << contacts[i].phoneNumber << "\n";
    }
}

void deleteContact(std::vector<Contact>& contacts) {
    int index;
    std::cout << "Enter the index of the contact to delete: ";
    std::cin >> index;
    if (index > 0 && index <= contacts.size()) {
        contacts.erase(contacts.begin() + index - 1);
        std::cout << "Contact deleted successfully.\n";
    } else {
        std::cout << "Invalid index.\n";
    }
}
void displayMenu() {
    std::cout << "Contact Management System\n";
    std::cout << "1. Add Contact\n";
    std::cout << "2. View Contacts\n";
    std::cout << "3. Delete Contact\n";
    std::cout << "4. Exit\n";
}

int main() {
	std::vector<Contact> contacts;
	int choice;

	do {
		displayMenu();
		std::cout << "Enter your choice: ";
		std::cin >> choice;

		switch (choice) {
			case 1:
				addContact(contacts);
				break;
			case 2:
				viewContacts(contacts);
				break;
			case 3:
				deleteContact(contacts);
				break;
			case 4:
				std::cout << "Exiting...\n";
				break;
			default:
				std::cout << "Invalid choice. Please try again.\n";
		}
	} while (choice != 4);

	return 0;
}

#include "consoleGui.hpp"
#include "contact.hpp"
#include <format>
#include <string>
#include <iostream>

enum class ConsoleMenuOptions : short unsigned int {
	EXIT = 0,
	ADD_CONTACT = 1,
	UPDATE_CONTACT = 2,
	REMOVE_CONTACT = 3,
	SEARCH_CONTACT = 4,
	SHOW_ALL_CONTACTS = 5
};

gui::console::ConsoleGui::ConsoleGui(const core::PhoneBook& phoneBook) : m_phoneBook(phoneBook) {}

void gui::console::ConsoleGui::mainMenu()
{
	while (true) {
		short unsigned int selectedOption{ 0 };
		std::system("cls");
		std::cout << "MAIN MENU\n";
		std::cout << "Please Enter a Number [0-5]: \n\n";
		std::cout << "1. Add a contact\n";
		std::cout << "2. Update a contact\n";
		std::cout << "3. Remove a contact\n";
		std::cout << "4. Search for contact\n";
		std::cout << "5. Show all contacts\n";
		std::cout << "0. Exit\n";

		std::cin >> selectedOption;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		switch (selectedOption) {
		case static_cast<short unsigned int>(ConsoleMenuOptions::EXIT):
			std::cout << "Exiting...\n";
			return;
		case static_cast<short unsigned int>(ConsoleMenuOptions::ADD_CONTACT):
			addContact();
			break;
		case static_cast<short unsigned int>(ConsoleMenuOptions::UPDATE_CONTACT):
			updateContact();
			break;
		case static_cast<short unsigned int>(ConsoleMenuOptions::REMOVE_CONTACT):
			removeContact();
			break;
		case static_cast<short unsigned int>(ConsoleMenuOptions::SEARCH_CONTACT):
			searchContact();
			break;
		case static_cast<short unsigned int>(ConsoleMenuOptions::SHOW_ALL_CONTACTS):
			showAllContacts();
			break;
		}
	}

}

void gui::console::ConsoleGui::addContact()
{
	std::string fullName{};
	std::string phoneNumber{};
	std::system("cls");
	std::cout << colors::TEXT_GREEN << "ADDING NEW CONTACT\n\n" << colors::TEXT_DEFAULT;

	bool isNameValid = false;
	bool isPhoneValid = false;

	std::cout << "Please Enter a Name: \n";
	while (!isNameValid) {
		std::getline(std::cin, fullName);

		if (fullName.size() == 0) {
			std::cout << colors::TEXT_RED << "Name cannot be empty. \n" << colors::TEXT_DEFAULT;
			continue;
		}
		else if (fullName.size() < 2) {
			std::cout << colors::TEXT_RED << "Name must be at lease 2 characters\n" << colors::TEXT_DEFAULT;
			continue;
		}
		else {

			isNameValid = true;
		}
	}

	std::cout << "Please Enter a Phone Number: \n";
	while (!isPhoneValid) {
		std::getline(std::cin, phoneNumber);

		if (phoneNumber.size() == 0) {
			std::cout << colors::TEXT_RED << "Phone Number cannot be empty. \n" << colors::TEXT_DEFAULT;;
			continue;
		}
		else if (phoneNumber.size() < 11 || phoneNumber.size() > 20) {
			std::cout << colors::TEXT_RED << "Invalid Phone Number\n" << colors::TEXT_DEFAULT;
			continue;
		}
		else {
			isPhoneValid = true;
		}
	}

	m_phoneBook.push(fullName, phoneNumber);
	std::cin.get();
}

void gui::console::ConsoleGui::updateContact()
{
	std::string phoneNumber{};
	std::string fullName{};
	bool isContactUpdated= false;
	bool isPhoneValid = false;
	std::system("cls");
	std::cout << colors::TEXT_GREEN << "UPDATE A CONTACT\n" << colors::TEXT_DEFAULT;
	std::cout << "Enter ESC To Return To The Main Menu\n\n";

	std::cout << colors::TEXT_PURPLE << "Contact List:\n";
	m_phoneBook.display();
	std::cout << colors::TEXT_DEFAULT << "\n\n";

	while (!isContactUpdated) {
	std::cout << "Please Enter a Name: \n";
		std::getline(std::cin, fullName);

		if (fullName == "ESC") {
			return;
		}

		std::cout << "Please Enter a Phone Number: \n";
		std::cin.clear();
		std::getline(std::cin, phoneNumber);


		if (phoneNumber.size() == 0) {
			std::cout << "Phone Number cannot be empty. \n";
			continue;
		}
		else if (phoneNumber.size() < 11 || phoneNumber.size() > 20) {
			std::cout << "Invalid Phone Number\n";
			continue;
		}

		if (m_phoneBook.update(fullName, phoneNumber)) {
			isContactUpdated = true;
			continue;
		}
		else {
			std::cout << colors::TEXT_RED << "Contact Not Found\n\n" << colors::TEXT_DEFAULT;
			continue;
		}


	}
	
}

void gui::console::ConsoleGui::removeContact()
{
	std::system("cls");

	std::cout << colors::TEXT_GREEN << "REMOVING A CONTACT\n" << colors::TEXT_DEFAULT;
	std::cout << "Enter ESC To Return To The Main Menu\n\n";

	std::cout << colors::TEXT_PURPLE << "Contact List:\n";
	m_phoneBook.display();
	std::cout << colors::TEXT_DEFAULT << "\n\n";

	std::string fullName{};
	bool isContactRemoved = false;

	while (!isContactRemoved) {
		std::cout << "Please Enter a Name: \n";
		std::getline(std::cin, fullName);

		if (fullName == "ESC") {
			return;
		}
		if (m_phoneBook.remove(fullName)) {
			isContactRemoved = true;
			continue;
		}
		else {
			std::cout << colors::TEXT_RED << "Contact Not Found\n\n" << colors::TEXT_DEFAULT;
			continue;
		}
	}
}

void gui::console::ConsoleGui::searchContact()
{
	std::system("cls");
	std::string fullName{};
	std::system("cls");
	std::cout << colors::TEXT_GREEN << "SEARCHING FOR A CONTACT\n" << colors::TEXT_DEFAULT;
	std::cout << "Enter ESC To Return To The Main Menu\n\n";

	while (true) {
		std::cout << "Please Enter a Name: \n";
		std::getline(std::cin, fullName);

		if (fullName == "ESC") {
			return;
		}
		auto foundCount = m_phoneBook.find(fullName);

		if (foundCount) {
			std::cout << std::format("{}[NAME]: {}, [NO]: {}\n\n{}",colors::TEXT_PURPLE, foundCount->getName(), foundCount->getPhoneNumber(), colors::TEXT_DEFAULT );
			std::cout << "\n\nPress ENTER to continue\n\n";
			std::cin.get();
		}
		else {
			std::cout << colors::TEXT_RED << "Contact Not Found\n\n" << colors::TEXT_DEFAULT ;
		}
	}
	

}

void gui::console::ConsoleGui::showAllContacts()
{
	std::system("cls");
	std::cout << colors::TEXT_GREEN << "ALL CONTACTS\n\n" << colors::TEXT_DEFAULT;

	m_phoneBook.display();

	std::cout << std::endl << "Press ENTER to exis";
	std::cin.get();
}

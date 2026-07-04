#include <iostream>
#include <format>
#include "gui.hpp"
#include "src/phoneBook.hpp"
#include "src/contact.hpp"
#include "src/consoleGui.hpp"

int main(int argc, char* argv[]) {
	try {
		bool consoleGui = false;
		core::PhoneBook phoneBook{};
		if(argc > 1)
		consoleGui = (argv[argc - 2] == std::string("--console") && argv[argc - 1] == std::string("true"));
		if (consoleGui) {
			gui::console::ConsoleGui consoleGui{ phoneBook };
			consoleGui.mainMenu();
		}
		else {
			gui::Gui gui{ "Phone Book", 1280, 720, phoneBook };
			gui.run();
		}


	}
	catch (std::exception& error) {
		std::cout <<error.what() << "\n";
	}
	return 0;
}
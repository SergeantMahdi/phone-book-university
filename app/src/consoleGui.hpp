#pragma once
#include "phoneBook.hpp"
namespace colors{
	using Color_Type = const char*;
	inline constexpr Color_Type TEXT_GREEN = "\033[0;32m";
	inline constexpr Color_Type TEXT_RED = "\033[0;31m";
	inline constexpr Color_Type TEXT_PURPLE = "\033[0;35m";
	inline constexpr Color_Type TEXT_DEFAULT = "\033[m";

}

namespace  gui{
	namespace console {

		class ConsoleGui {
		public:
			ConsoleGui() = default;
			ConsoleGui(const core::PhoneBook& phoneBook);
			~ConsoleGui() = default;
			ConsoleGui(const ConsoleGui&) = delete;
			ConsoleGui(ConsoleGui&&) noexcept = delete;
			ConsoleGui& operator =(const ConsoleGui&) = delete;
			ConsoleGui& operator =(ConsoleGui&&) noexcept = delete;

			void mainMenu();
			void addContact();
			void updateContact();
			void removeContact();
			void searchContact();
			void showAllContacts();

		private:
			core::PhoneBook m_phoneBook;
		};
	}
}
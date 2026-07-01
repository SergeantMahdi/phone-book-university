#pragma once
#include <memory>
#include <string_view>
#include <vector>

namespace core {
	class Contact;

	class PhoneBook {
		using Contact_Shared_Pointer = std::shared_ptr<core::Contact>;

	public:
		PhoneBook();
		PhoneBook(std::initializer_list<Contact> list);
		~PhoneBook() = default;
		bool push(const std::string_view& name, const std::string_view& phoneNumber);
		bool remove(const std::string_view& name);
		Contact_Shared_Pointer find(const std::string_view& name) const;
		void display() const;
		std::vector<Contact_Shared_Pointer> getContactList() const;
		bool update(const std::string_view& name, const std::string_view& phoneNumber);
		size_t size() const;
		bool isEmpty() const;

	private:
		Contact_Shared_Pointer m_shared_root;
		size_t m_size;
	};

}
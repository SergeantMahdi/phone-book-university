#pragma once
#include <string>
#include <string_view>
#include <memory>

/*
-- Mahdi
- Contact class is implemented as Node in our tree.
- Instead of making my variables public, I decided to change the structure and
make my Node class in a way that leaves no way to make mistake other developers.
*/


namespace core {

	class Contact{
	public:
		Contact() = default;
		Contact(const std::string_view& name, const  std::string_view& phoneNumber);
		Contact(const Contact& other);
		Contact(Contact&& other) noexcept;
		~Contact() = default;

		void setRightChild(std::shared_ptr<Contact> child);
		void setLeftChild(std::shared_ptr<Contact> child);
		void setName(const  std::string_view& name);
		void setPhoneNumber(const  std::string_view& phoneNumber);
		std::string getName() const;
		std::string getPhoneNumber() const;
		std::shared_ptr<Contact> getRightChild() const;
		std::shared_ptr<Contact> getLeftChild() const;

	public:
		Contact& operator =(const Contact& other);
		Contact& operator =(Contact&& other) noexcept;

	private:
		std::string m_name;
		std::string m_phoneNumber;
		std::shared_ptr<Contact> m_rightChild;
		std::shared_ptr<Contact> m_leftChild;
	};

}
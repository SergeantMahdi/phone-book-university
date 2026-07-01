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

		using Contact_Shared_Pointer = std::shared_ptr<Contact>;

	public:
		Contact() = default;
		Contact(const std::string_view& name, const  std::string_view& phoneNumber);
		Contact(const Contact& other);
		Contact(Contact&& other) noexcept;
		~Contact() = default;

		void setRightChild(Contact_Shared_Pointer child);
		void setLeftChild(Contact_Shared_Pointer child);
		void setParent(Contact_Shared_Pointer parent);
		void setName(const  std::string_view& name);
		void setPhoneNumber(const  std::string_view& phoneNumber);
		std::string getName() const;
		std::string getPhoneNumber() const;
		Contact_Shared_Pointer getRightChild() const;
		Contact_Shared_Pointer getLeftChild() const;
		Contact_Shared_Pointer getParent() const;
		void swapData(Contact_Shared_Pointer& other);

	public:
		Contact& operator =(const Contact& other);
		Contact& operator =(Contact&& other) noexcept;

	private:
		std::string m_name;
		std::string m_phoneNumber;
		Contact_Shared_Pointer m_rightChild;
		Contact_Shared_Pointer m_leftChild;
		Contact_Shared_Pointer m_parent;
	};

}
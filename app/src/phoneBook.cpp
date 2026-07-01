#include "phoneBook.hpp"
#include "phoneBook.hpp"
#include "phoneBook.hpp"
#include "phoneBook.hpp"
#include "phoneBook.hpp"
#include "phoneBook.hpp"
#include <stack>
#include <iostream>
#include <vector>
#include <format>
#include "contact.hpp"

// Aliases
using Contact_Shared_Pointer = std::shared_ptr<core::Contact>;



// Recursive call increase the space complexity so I use while loop to avoid that
core::PhoneBook::PhoneBook() :m_shared_root(nullptr), m_size(0) {}

core::PhoneBook::PhoneBook(std::initializer_list<Contact> list) : m_size(list.size())
{
	Contact_Shared_Pointer current{ m_shared_root };
	for (size_t i = 0; list.begin() + i != list.end(); i++) {
		Contact_Shared_Pointer newContact = std::make_shared<core::Contact>((list.begin() + i)->getName(), (list.begin() + i)->getPhoneNumber());
		if (!m_shared_root) {
			m_shared_root = newContact;
			current = m_shared_root;
			continue;
		}
		Contact_Shared_Pointer parent;

			if (current->getName() > (list.begin() + i)->getName()) {
				if (!current->getLeftChild()) {
					current->setLeftChild(newContact);
					current->getLeftChild()->setParent(parent);
					continue;
				}
				current = current->getLeftChild();
			}
			else if (current->getName() < (list.begin() + i)->getName()) {
				if (!current->getRightChild()) {
					current->setRightChild(newContact);
					current->getRightChild()->setParent(parent);
					continue;
				}
				current = current->getRightChild();
			}
		}
	
}

bool core::PhoneBook::push(const std::string_view& name, const std::string_view& phoneNumber)
{
	Contact_Shared_Pointer newContact = std::make_shared<core::Contact>(name, phoneNumber);

	if (!m_shared_root){
		m_shared_root = newContact;
		std::cout << "The contact saved as the root\n";
		m_size++;
		return true;
	}
	Contact_Shared_Pointer current{ m_shared_root };
	Contact_Shared_Pointer parent;

	while (current) {
		parent = current;
		if (current->getName() == name) {
			return false;
		}
		else if (current->getName() > name) {
			if (!current->getLeftChild()) {
				current->setLeftChild(newContact);
				current->getLeftChild()->setParent(parent);
				m_size++;
				std::cout << "The contact saved as the left child\n";
				return true;
			}
			current = current->getLeftChild();
		}
		else if (current->getName() < name) {
			if (!current->getRightChild()) {
				current->setRightChild(newContact);
				current->getRightChild()->setParent(parent);
				m_size++;
				std::cout << "The contact saved as the right child\n";
				return true;
			}
			current = current->getRightChild();
		}
	}
	return true;
}

bool core::PhoneBook::remove(const std::string_view& name)							// No Recursion (I don't want to increase the space complexity)
{
	Contact_Shared_Pointer current {nullptr};										// Get the track of current node
	Contact_Shared_Pointer successor {nullptr};										// The successor node is the node that will replace the current node in the tree
	
	current = find(name);

	if (!current)																	// Contact not found
		return false;

	if (current->getRightChild()) {													// [CONDITION 1]: check if the node has the right child		
		successor = current->getRightChild();
		while (successor->getLeftChild()) {											// Check if the node has the left child and keep moving to the very left node	
			successor = successor->getLeftChild();
		}
		current->swapData(successor);
		current = successor;
	}
	else if (current->getLeftChild()) {												// [CONDITION 2]: Check if the node has the left child
		successor = current->getLeftChild();
		while (successor->getLeftChild()) {
			successor = successor->getLeftChild();
		}
		current->swapData(successor);
		current = successor;
	}

	Contact_Shared_Pointer parent = current->getParent();
	if (!parent)																	// [CONDITION 3]: Check if the node is the root
		m_shared_root.reset();
	else if (parent->getRightChild() == current)
		parent->setRightChild(nullptr);
	else if (parent->getLeftChild() == current)
		parent->setLeftChild(nullptr);

	m_size--;
	return true;
}

Contact_Shared_Pointer core::PhoneBook::find(const std::string_view& name) const
{
	Contact_Shared_Pointer current = m_shared_root;

	while (current) {
		if (current->getName() > name) {
			current = current->getLeftChild();
			continue;
		}
		else if (current->getName() < name) {
			current = current->getRightChild();
			continue;
		}
		else if (current->getName() == name) {
			return current;
		}

	}

	return nullptr;
}

void core::PhoneBook::display()	const													// Using Pre-Order Traversal to display the tree
{
	std::stack<Contact_Shared_Pointer> stack;
	Contact_Shared_Pointer current = m_shared_root;

	while (current || !stack.empty()) {
		while (current) {
			stack.push(current);
			current = current->getLeftChild();
		}
		current = stack.top();
		stack.pop();

		std::cout << std::format("[NAME]: {}, [NO]: {}\n", current->getName(), current->getPhoneNumber());
		current = current->getRightChild();
	}


}

std::vector<Contact_Shared_Pointer> core::PhoneBook::getContactList() const
{
	std::stack<Contact_Shared_Pointer> stack;
	Contact_Shared_Pointer current = m_shared_root;
	std::vector<Contact_Shared_Pointer> contactList{};

	while (current || !stack.empty()) {
		while (current) {
			stack.push(current);
			current = current->getLeftChild();
		}
		current = stack.top();
		stack.pop();

		contactList.push_back(current);
		current = current->getRightChild();
	}

	return contactList;
}

bool core::PhoneBook::update(const std::string_view& name, const std::string_view& phoneNumber)
{
	Contact_Shared_Pointer foundContact = find(name);

	if (!foundContact)
		return false;

	foundContact->setPhoneNumber(phoneNumber);
	return true;
}

size_t core::PhoneBook::size() const
{
	return m_size;
}

bool core::PhoneBook::isEmpty() const
{
	return m_size == 0 ? true : false;
}



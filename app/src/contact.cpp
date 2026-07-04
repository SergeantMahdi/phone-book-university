#include "contact.hpp"

// Aliases
using Contact_Shared_Pointer = std::shared_ptr<core::Contact>;

core::Contact::Contact(const std::string_view& name, const std::string_view& phoneNumber) : m_name(name), m_phoneNumber(phoneNumber), m_leftChild(nullptr), m_rightChild(nullptr), m_parent(nullptr) {}

core::Contact::Contact(const core::Contact& other) : m_name(other.m_name), m_phoneNumber(other.m_phoneNumber), m_leftChild(other.m_leftChild), m_rightChild(other.m_rightChild), m_parent(other.m_parent) {}

core::Contact::Contact(core::Contact&& other) noexcept : m_name(std::move(other.m_name)), m_phoneNumber(std::move(other.m_phoneNumber)), m_leftChild(std::move(other.m_leftChild)), m_rightChild(std::move(other.m_rightChild)), m_parent(std::move(other.m_parent)) {}

void core::Contact::setRightChild(Contact_Shared_Pointer child)
{
	m_rightChild = child;
}

void core::Contact::setLeftChild(Contact_Shared_Pointer child)
{
	m_leftChild = child;
}

void core::Contact::setParent(Contact_Shared_Pointer parent)
{
	m_parent = parent;
}

void core::Contact::setName(const std::string_view& name)
{
	m_name = name;
}

void core::Contact::setPhoneNumber(const std::string_view& phoneNumber)
{
	m_phoneNumber = phoneNumber;

}

std::string core::Contact::getName() const
{
	return m_name;
}

std::string core::Contact::getPhoneNumber() const
{
	return m_phoneNumber;
}

Contact_Shared_Pointer core::Contact::getRightChild() const
{
	return m_rightChild;
}

Contact_Shared_Pointer core::Contact::getLeftChild() const
{
	return m_leftChild;
}

Contact_Shared_Pointer core::Contact::getParent() const
{
	return m_parent;
}

void core::Contact::swapData(Contact_Shared_Pointer& other)
{
	std::string name = m_name;
	std::string phoneNumber = m_phoneNumber;
	m_name = other->m_name;
	m_phoneNumber = other->m_phoneNumber;
	other->m_name = name;
	other->m_phoneNumber = phoneNumber;
}

core::Contact& core::Contact::operator=(const core::Contact& other)
{
	if (this == &other)
		return *this;
	m_name = other.m_name;
	m_phoneNumber = other.m_phoneNumber;
	m_leftChild = other.m_leftChild;
	m_rightChild = other.m_rightChild;
	return *this;
}

core::Contact& core::Contact::operator=(core::Contact&& other) noexcept
{
	if (this == &other)
		return *this;
	m_name = std::move(other.m_name);
	m_phoneNumber = std::move(other.m_phoneNumber);
	m_leftChild = std::move(other.m_leftChild);
	m_rightChild = std::move(other.m_rightChild);
	return *this;
}


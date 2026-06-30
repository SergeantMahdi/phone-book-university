#include "contact.hpp"

core::Contact::Contact(const std::string_view& name, const std::string_view& phoneNumber) : m_name(name), m_phoneNumber(phoneNumber), m_leftChild(nullptr), m_rightChild(nullptr) {}

core::Contact::Contact(const core::Contact& other) : m_name(other.m_name), m_phoneNumber(other.m_phoneNumber), m_leftChild(other.m_leftChild), m_rightChild(other.m_rightChild) {}

core::Contact::Contact(core::Contact&& other) noexcept : m_name(std::move(other.m_name)), m_phoneNumber(std::move(other.m_phoneNumber)), m_leftChild(std::move(other.m_leftChild)), m_rightChild(std::move(other.m_rightChild)){}

void core::Contact::setRightChild(std::shared_ptr<Contact> child)
{
	m_rightChild = child;
}

void core::Contact::setLeftChild(std::shared_ptr<Contact> child)
{
	m_leftChild = child;
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

std::shared_ptr<core::Contact> core::Contact::getRightChild() const
{
	return m_rightChild;
}

std::shared_ptr<core::Contact> core::Contact::getLeftChild() const
{
	return m_leftChild;
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


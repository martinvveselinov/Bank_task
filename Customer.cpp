#include <iostream>
#include <string.h>

#include "Customer.h"


Customer::Customer(int i, const char * n, const char * a)
{
	ID = i;
	name = new char[strlen(n) + 1];
	strcpy_s(name, strlen(n) + 1, n);
	adress = new char[strlen(a) + 1];
	strcpy_s(adress, strlen(a) + 1, a);
}

Customer::Customer(const Customer & other )
{
	ID = other.getID();
	name = new char[strlen(other.getName()) + 1];
	strcpy_s(name, strlen(other.getName()) + 1, other.getName());
	adress = new char[strlen(other.getAdress()) + 1];
	strcpy_s(adress, strlen(other.getAdress()) + 1, other.getAdress());
}

Customer & Customer::operator=(const Customer & other)
{
	if (this != &other)
	{	
		delete[] name;
		delete[] adress;
		ID = other.getID();
		name = new char[strlen(other.getName()) + 1];
		strcpy_s(name, strlen(other.getName()) + 1, other.getName());
		adress = new char[strlen(other.getAdress()) + 1];
		strcpy_s(adress, strlen(other.getAdress()) + 1, other.getAdress());
	}
	return *this;
}

Customer::~Customer()
{
	delete[] name;
	delete[] adress;
}

int Customer::getID() const
{
	return ID;
}

char * Customer::getName() const
{
	return name;
}

char * Customer::getAdress() const
{
	return adress;
}

void Customer::display() const
{
	std::cout << ID << " " << name << " " << adress << std::endl;
}

#include <iostream>
#include <string>

#include "Bank.h"

using namespace std;

Bank::Bank(const char* name, const char* adress)
{
	int sizen, sizea;
	sizen = strlen(name) + 1;
	sizea = strlen(adress) + 1;
	this->name = new char[sizen];
	strcpy_s(this->name, sizen, name);
	this->adress = new char[sizea];
	strcpy_s(this->adress, sizea, adress);
}

Bank::Bank(const Bank & other)
{
	int sizea, sizeb;
	sizea = strlen(other.getAdress()) + 1;
	adress = new char[sizea];
	strcpy_s(adress, sizea, other.getAdress());
	sizeb = strlen(other.getName()) + 1;
	name = new char[sizeb];
	strcpy_s(name, sizeb, other.getName());
	accounts = other.accounts;
	customers = other.customers;
}

Bank & Bank::operator=(const Bank & other)
{
	if (this != &other)
	{
		delete[] name;
		delete[] adress;
		for (int i = 0; i < int(customers.size()); ++i)
		{
			delete[] customers[i];
		}
		for (int i = 0; i < int(accounts.size()); ++i)
		{
			delete[] accounts[i];
		}
		int sizea, sizeb;
		sizea = strlen(other.getAdress()) + 1;
		adress = new char[sizea];
		strcpy_s(adress, sizea, other.getAdress());
		sizeb = strlen(other.getName()) + 1;
		name = new char[sizeb];
		strcpy_s(name, sizeb, other.getName());
		accounts = other.accounts;
		customers = other.customers;
	}
	return *this;
}

Bank::~Bank()
{
	delete[] name;
	delete[] adress;
	for (int i = 0; i < int(customers.size()); ++i)
	{
		delete[] customers[i];
	}
	for (int i = 0; i < int(accounts.size()); ++i)
	{
		delete[] accounts[i];
	}
}

char * Bank::getName() const
{
	return name;
}

char * Bank::getAdress() const
{
	return adress;
}

void Bank::addCustomer(int customerid, const char * name, const char * adress)
{
	bool exist = false;
	for (int i = 0; i < int(customers.size()); ++i)
	{
		if (customers[i]->getID() == customerid) exist = true;
	}
	if (exist == false)
	{
		Customer* a = new Customer(customerid, name, adress);
		customers.push_back(a);
	}
	else return;
}

void Bank::listCustomers() const
{
	for (int i = 0; i < int(customers.size()); ++i)
	{
		customers[i]->display();
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Bank::deleteCustomer(int customerid)
{
	for (int i = 0; i < int(customers.size()); ++i)
	{
		if (customers[i]->getID() == customerid)
		{
			for (int j = int(accounts.size()) - 1; j >= 0; --j)
			{
				if (customerid == accounts[j]->getOwner())
					accounts.erase(accounts.begin() + j);
			}
			customers.erase(customers.begin() + i);
			return;
		}
	}
}

void Bank::addAccount(const char * accountType, const char * iban, int ownerid, double amount)
{	
	bool exist = false;
	for (int i = 0; i < int(accounts.size()); ++i)
	{
		if (strcmp(accounts[i]->getIban(), iban) == 0) return;
	}
	for (int i = 0; i < int(customers.size()); ++i)
	{
		if (customers[i]->getID() == ownerid) exist = true;
	}
	if (exist == 0) return;
	else
	{
		if (strcmp(accountType, "Current") == 0) {
			Account* a = new CurrentAccount(iban, ownerid, amount);
			accounts.push_back(a);
		}
		else if (strcmp(accountType, "Privilege") == 0) {
			double over;
			std::cout << "Enter the allowed overdraft: ";
			std::cin >> over;
			Account* a = new PrivilegeAccount(over, iban, ownerid, amount);
			accounts.push_back(a);
		}
		else if (strcmp(accountType, "Savings") == 0) {
			double rate;
			std::cout << "Enter the year rate: ";
			std::cin >> rate;
			Account* a = new SavingsAccount(rate, iban, ownerid, amount);
			accounts.push_back(a);
		}
		else cout << "Wrong account type!";
	}
}

void Bank::deleteAccount(const char* iban)
{
	for (int i = 0; i < int(accounts.size()); ++i)
	{
		if (strcmp(accounts[i]->getIban(),iban) == 0)
		{
			accounts.erase(accounts.begin() + i);
			return;
		}
	}
}

void Bank::listAccounts() const
{
	for (int i = 0; i < int(accounts.size()); ++i)
	{
		accounts[i]->display();
	}
	std::cout << std::endl;
}

void Bank::listCustomerAccount(int customerid) const
{	
	int i = 0;
	for (i; i < int(customers.size()); ++i)
	{
		if (customers[i]->getID() == customerid)
			customers[i]->display();
	}
	for (int j = 0; j < int(accounts.size()); ++j)
	{
		if (accounts[j]->getOwner() == customerid)
			accounts[j]->display();
	}
	std::cout << std::endl;
}

bool Bank::transfer(const char * fromIban, const char * toIban, double amount)
{
	int i = 0;
	for (i; i < int(accounts.size()); ++i)
	{
		if (strcmp(accounts[i]->getIban(), fromIban) == 0)
		{	
			for (int j = 0; j < int(accounts.size()); ++j)
			{
				if (strcmp(accounts[j]->getIban(), toIban) == 0)
				{	
					if (accounts[i]->withdraw(amount) == 1)
					{
						accounts[j]->deposit(amount);
						return true;
					}
				}
			}
		}
	}
	return false;
}

void Bank::display() const
{
	std::cout << std::endl << name << " " << adress << std::endl << std::endl;
	for (int i = 0; i < int(customers.size()); ++i)
	{
		listCustomerAccount(customers[i]->getID());
	}

}

int Bank::getAccSize() const
{
	return int(accounts.size());
}

void Bank::menu()
{
	
	string x;
	
	cout << "1 List customers\n"
		"2 Add new customer\n"
		"3 Delete customer\n"
		"4 List all accounts\n"
		"5 List customer accounts\n"
		"6 Add new account\n"
		"7 Delete account\n"
		"8 Withdraw from account\n"
		"9 Deposit to account\n"
		"10 Transfer\n"
		"11 Display info for the bank\n"
		"12 Quit\n\n";
	do
	{	
		
		cout << "Enter the number of the action you want to complete: ";
		
		cin >> x;
		cout << endl;
		if (x == "1")
		{
			cout << "List of all customers of " << this->name << " bank: \n";
			listCustomers();
			
		}
		else if (x == "2")
		{
			cout << "Adding  new customer: \n";
			int id;
			char name[50];
			char adress[50];
			cout << "Enter the customer ID (only integers): ";
			cin >> id;
			cin.ignore();
			cout << "Enter the customer name: ";
			cin.getline(name, 50);
			cout << "Enter the customer adress: ";
			cin.getline(adress, 50);
			addCustomer(id, name, adress);
			cout << endl;
			
		}
		else if (x == "3")
		{
			cout << "Enter the ID of the customer you want to remove (only integers): ";
			int cid;
			cin >> cid;
			deleteCustomer(cid);
			
		}
		
			
		else if (x == "4")
		{
			cout << "List of all bank accounts in " << this->name << " bank: \n";
			listAccounts();
			
		}
		else if (x == "5")
		{
			int caid;
			cout << "Enter the ID of the customer, whose accounts you want to see (only integers): ";
			cin >> caid;
			listCustomerAccount(caid);
			
		}
		else if (x == "6")
		{
			cout << "Creating new account:\n";
			char accountType[50];
			char iban[50];
			int ownerid;
			double amount;
			cout << "Enter the account type(Current, Savings, or Privilege):";
			cin >> accountType;
			cout << "Enter the IBAN (any symbols): ";
			cin >> iban;
			cout << "Enter the ID of the customer (only integers): ";
			cin >> ownerid;
			cout << "Enter the balance of the account: ";
			cin >> amount;
			addAccount((const char*)accountType, (const char*)iban, ownerid, amount);
			
		}
		else if (x == "7")
		{
			cout << "Enter the IBAN of the account you want to remove (any symbols): ";
			char aiban[50];
			cin >> aiban;
			deleteAccount(aiban);
			
		}
			
		else if (x == "8")
		{
			cout << "Withdraw:\nEnter the IBAN of the account you want to withdraw from: ";
			char wiban[50];
			cin >> wiban;
			for (int i = 0; i < getAccSize(); ++i)
			{
				if (strcmp(accounts[i]->getIban(), wiban) == 0)
				{
					double draw;
					cout << "Enter the amount to withdraw: ";
					cin >> draw;
					accounts[i]->withdraw(draw);
				}
			}
			
		}
			
		else if (x == "9")
		{
			cout << "Deposit:nEnter the IBAN of the account you want to deposit in: ";
			char diban[50];
			cin >> diban;
			for (int i = 0; i < getAccSize(); ++i)
			{
				if (strcmp(accounts[i]->getIban(), diban) == 0)
				{
					double depo;
					cout << "Enter the amount you want to deposit: ";
					cin >> depo;
					accounts[i]->deposit(depo);
				}
			}
			
		}
		else if (x == "10")
		{
			cout << "Transfer:\nEnter the IBAN of the account, from which the withdrawal will be done: ";
			char fromIBAN[50];
			char toIBAN[50];
			double tamount;
			cin >> fromIBAN;
			cout << "Enter the IBAN of the account, which you are depositing in: ";
			cin >> toIBAN;
			cout << "Enter the amount of the transfer: ";
			cin >> tamount;
			transfer(fromIBAN, toIBAN, tamount);
			
		}
		else if (x == "11")
		{
			display();
		}
		else if (x == "12")
			return;
		else
		{
			cout << "Ooops! Wrong input! Try to enter only int digits from 1 to 12!\n\n";
			return menu();
		}
	}
	while (cin);
	//return menu();
}



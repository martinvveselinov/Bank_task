#pragma once
class Customer
{
private:
	int ID;
	char* name;
	char* adress;
public:
	Customer(int, const char* ,const char*);
	Customer(const Customer&);
	Customer& operator=(const Customer&);
	~Customer();

	int getID() const;
	char* getName() const;
	char* getAdress() const;

	void display() const;
};


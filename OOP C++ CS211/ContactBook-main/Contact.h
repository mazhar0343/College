#ifndef CONTACT_H
#define CONTACT_H

#include <string>
#include "Address.h"

class Contact {
private:
	std::string fName;
	std::string lName;
	Address address;
	std::string phoneNumber;
	std::string emailAddress;
public:
	Contact(); // Default Construtor
	Contact(std::string, std::string, Address& , std::string, std::string);
Contact(std::string, std::string, std::string, std::string);
	std::string getFirstName() const;
	std::string getLastName() const;
	std::string getPhoneNumber() const;
	Address& getAddress();
	std::string getEmail() const;
	void setFirstName(std::string);
	void setLastName(std::string);
	void setAddress(Address&);
  void setAddress();
	void setPhoneNumber(std::string);
	void setEmail(std::string);
  	void input();
  	void output() const;
  	
  	// All operator overloading declarations 
  	friend ostream& operator << (ostream&, const Contact&);
    friend istream& operator >> (istream&, Contact&);
  	int operator >(const Contact&)const;
  	int operator >=(const Contact&)const;
  	int operator <(const Contact&)const;
  	int operator <=(const Contact&)const;
  	int operator ==(const Contact&)const;
  	int operator !=(const Contact&)const;
};

#endif
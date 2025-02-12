#ifndef CONTACTBOOK_H
#define CONTACTBOOK_H

#include <string>
#include "Contact.h"

using namespace std;

class ContactBook{
	private:
		int numContacts = 0;
    int capacity = 10;
		string oFName;
		string oLName;
		Contact** cBook;

    void grow();
    int getContactByName() const;
    void sort();

	public:
		ContactBook();
    ContactBook(string fn, string ln);
		void addContact();
    void addContact(Contact*);
    void deleteContact();
    void displayContact();
    void updateContact();
    void displayAll();
    Contact getContact(int);
    friend ostream& operator <<(ostream& out, const ContactBook& cB);
    friend istream& operator >>(istream& in, ContactBook& cB);

    void deleteBook();
    void setFN(string fn);
    void setLN(string ln);
    string getFN();
    string getLN();
    int getCapacity();
    int getNumContacts();
		
		
    // destructor
    ~ContactBook();
    // Copy Construtor
    ContactBook(const ContactBook& other);
    // Assignment operator
    ContactBook& operator = (const ContactBook& other);

};
#endif
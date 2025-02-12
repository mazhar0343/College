#include <iostream>
#include <string>
#include "ContactBook.h"

using namespace std;

// Default Construtor 
ContactBook::ContactBook(){
  cBook = new Contact*[capacity];
}

// Construtor that takes first name and last name
ContactBook::ContactBook(string fn, string ln){
  cBook = new Contact*[capacity];
  oFName = fn;
  oLName = ln;
}

// Destrutor
ContactBook::~ContactBook(){
  for(int i = 0; i < numContacts; i++){
    if(cBook[i] != NULL && cBook != NULL){
      delete cBook[i];
    }
  }
  if(cBook != NULL){
    delete [] cBook;
  }

}

// Copy Construtor
ContactBook::ContactBook(const ContactBook& other){
  cBook = new Contact*[other.capacity];
  for(int i = 0; i < other.capacity; i++){
    cBook[i] = new Contact(*(other.cBook[i]));
  }
  oFName = other.oFName;
  oLName = other.oLName;
}

// Overload of assignment operator
ContactBook& ContactBook::operator = (const ContactBook& other){
  if (this != &other) {
		if (cBook != NULL) {
			delete [] cBook;
			cBook = NULL;
		}
		numContacts = other.numContacts;
		capacity = other.capacity;
    oFName = other.oFName;
      oLName = other.oLName;
		if (capacity > 0)
			cBook = new Contact*[capacity];
		if (other.cBook != NULL) {
			for (int i = 0; i < other.numContacts; i++) {
          cBook[i] = new Contact(*(other.cBook[i]));
      }
		}
	}
	return *this;
}

// Getters and Setters
void ContactBook::setFN(string name){
  oFName = name;
}
void ContactBook::setLN(string name){
  oLName = name;
}

string ContactBook::getFN(){
  return oFName;
};
string ContactBook::getLN(){
  return oLName;
};

int ContactBook::getCapacity(){
  return capacity;
}
int ContactBook::getNumContacts(){
  return numContacts;
}

// Creates a new Contact and adds its to the book
void ContactBook::addContact(){
  if(numContacts >= capacity){
    grow();
  }
  Contact* temp = new Contact();
  temp->input();

  cBook[numContacts] = temp;
  numContacts++;
  sort();
}

// Accepts a Contact as a parameter and adds it to the book
void ContactBook::addContact(Contact* c){
  if(numContacts >= capacity){
    grow();
  }
  cBook[numContacts] = c;
  numContacts++;
  sort();
}

// Deletes a contact in the book
void ContactBook::deleteContact(){
  int input;
  cout << "Enter the contact index: ";
  cin >> input;
  if(input < 1 || input > numContacts){
    cout << "Contact not Found";
    return;
  }
  delete cBook[input];
  for(int i = input - 1 ; i <= numContacts-1; i++){
    cBook[i] = cBook[i + 1];
  }
  numContacts--;
}

// Displays a contact at a given index in array
void ContactBook::displayContact(){
  int index = ContactBook::getContactByName();
  if(index >= 0){
    cBook[index]->output();
  }
}

// Function to update a contact	
void ContactBook::updateContact(){
	int index = ContactBook::getContactByName();
	string input = "";
	
// Finds contact by their name if found then it allows the user to edit the contact information
	if(index >= 0){
		while(input != "EXIT"){
			cout << "Edit: First name, Last name, Address, Phone number, Email, EXIT(fn/ln/a/pn/e/EXIT): "; 
			getline(cin, input);
						
			if(input == "fn"){
				cout << "Enter new first name: "; 
				getline(cin, input);
				cBook[index]->setFirstName(input);
			}else if(input == "ln"){
				cout << "Enter new last name: "; 
				getline(cin, input);
				cBook[index]->setLastName(input);
			}else if(input == "a"){
				cBook[index]->setAddress();
			}else if(input == "pn"){
				cout << "Enter new phone number: "; 
				getline(cin, input);
				cBook[index]->setPhoneNumber(input);
			}else if(input == "e"){
				cout << "Enter new email address: "; 
				getline(cin, input);
				cBook[index]->setEmail(input);
			}	
		}
	}
}

// Displays all contacts in the book
void ContactBook::displayAll(){
  for(int i = 0; i < numContacts; i++){
    cBook[i]->output();
  }
}

// Overload of << operator
ostream& operator <<(ostream& out, const ContactBook& cB){
  for(int i = 0; i < cB.numContacts; i++){
		out << endl << "-----------------------" << endl << "Contact:" << i + 1 << endl <<"-----------------------"<< endl;
		out << *cB.cBook[i];
	}
	
	return out;
}


istream& operator >>(istream& in, ContactBook& cB){
  //TODO: Couldn't figure it out
}

// Increases the size of the book
void ContactBook::grow(){
  capacity += 10;
  Contact** temp = new Contact*[capacity];
  for(int i = 0; i < capacity; i++){
    temp[i] = cBook[i];
  }
  delete [] cBook;
  cBook = temp;
}

// Return the index location of contact
int ContactBook::getContactByName() const{
	string input;
	cout << "Enter Contact Name: " ;
	std::getline(cin >> ws, input);
// For loop goes through the entire Contact Book checking if any names match the name provided by the user and returns its index
	for(int i = 0; i < numContacts; i++){
		string name = cBook[i]->getFirstName() + " " + cBook[i]->getLastName();
		if(name == input){
			return i;
		}
	}
// If the name isnt found it returns a -1 
	cout << "Contact not found" << endl;
	return -1;
}

// Sorts each a contact book
void ContactBook::sort(){
  for(int i = 0; i < numContacts-1; i++){
    for(int j = 0; j < numContacts-1; j++){
      Contact* temp1 = cBook[j];
      Contact* temp2 = cBook[i+1];
  
      if(*temp1 > *temp2){
        cBook[i] = temp2;
        cBook[j+1] = temp1;
      }
  }
  
}
  }

// Returns a contact at a given index location
Contact ContactBook::getContact(int index){
  if(index >= 0 && index < numContacts){
    return *(cBook[index]);
  }
}

void ContactBook::deleteBook(){
  for(int i = 0; i < numContacts; i++){
    delete cBook[i];
  }
}
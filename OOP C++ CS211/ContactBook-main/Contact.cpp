#include <iostream>
#include "Contact.h"

using namespace std;

// Default Constructor 
// Set all values to "N/A"
Contact::Contact() {
	fName = "N/A";
	lName = "N/A";
	phoneNumber = "N/A";
	emailAddress = "N/A";
}

// Constructor accepting parameters
Contact::Contact(string fN, string lN, Address& location, string phone, string email){
//First Name,Last Name and Address are not checked for anything so they are assigned without checking for anything
	fName = fN;
	lName = lN;
	address = location;
//Checks if phone number has 10 numbers by calling a helper function
	setPhoneNumber(phone);
//Checks if email is in correct format by calling a helper function
	setEmail(email);
};

Contact::Contact(string fN, string lN, string phone, string email){
//First Name,Last Name and Address are not checked for anything so they are assigned without checking for anything
	fName = fN;
	lName = lN;
//Checks if phone number has 10 numbers by calling a helper function
	setPhoneNumber(phone);
//Checks if email is in correct format by calling a helper function
	setEmail(email);
};

// Accessors
string Contact::getFirstName() const{
	return fName; // Returns First Name
}
string Contact::getLastName() const{
	return lName; // Returns Last Name
}
Address& Contact::getAddress(){
	return address; // Returns Address
}
string Contact::getPhoneNumber() const{
	return phoneNumber; // Returns Phone Number
}
string Contact::getEmail() const{
	return emailAddress; // Returns Email
}

// Mutators
void Contact::setFirstName(string name) {
	fName = name; // Sets value of first name
}
void Contact::setLastName(string name) {
	lName = name; // Set value of last name
}
void Contact::setAddress(Address& a) {
 	address = a;	
}
void Contact::setAddress() {
 	address.input();
}
void Contact::setPhoneNumber(string number) {
// If phone number has 10 numbers then the value of phoneNumber is assigned
	bool checking = true;
  // checks if the length of phone number is 10 digits then returns true otherwise it stops the program
  	while(checking){
  		if (number.length() == 10) {
			checking = false;
  		}else{
      		cout << "Enter 10 digit contact phone number : ";
	    	getline(cin, number);
    	}
  	}
  	phoneNumber = number;
}
void Contact::setEmail(string email) {
  const int size = 5;
  string domains[size] = {".gov", ".edu", ".org", ".com", ".net"};
  bool checking = true;

  int c1;
  int c2;
  while(checking){
  c1 = email.find("@");
  c2 = email.find(".");
    if(c1 != -1 && c1 > 0){ // checks to see if there is a "@" and that its not the first character 
      if(c2 != -1 && c2 > (c1+1)){ // Once the "@" checks to see if there is "." and it is atleast 2 spaces after the "@"
        string domainCheck = email.substr(email.find("."));
          for(int i = 0; i < size; i++){ // for loops goes through the entire array of domains
            if(domainCheck == domains[i]){ // once a matching domain is found it stops checking
              checking = false;
            }
          }
        
          if(checking){
            cout << "Email missing top level domain or incorrect domain: ";
            getline(cin, email);
          }
        
      }else{
        cout << "Email missing '.' or not at correct postion: ";
        getline(cin, email);
      }
    }else{
      cout << "Email missing '@' or not at correct postion: ";
      getline(cin, email);
    }
  }
  emailAddress = email;
}

// Input Function
// Gets user input and sets values through mutators
void Contact::input() {
	string input = "";
	cout << "Enter contact first name: ";
	getline(cin, input);
	setFirstName(input);
	cout << "Enter contact last name: ";
	getline(cin, input);
  	setLastName(input);
  	setAddress();
  	setPhoneNumber(input);
	cout << "Enter contact email address: ";
	getline(cin, input);
  	setEmail(input);
}

// Output Function
// Using accessors to get variable values from object
void Contact::output() const{
  cout << endl <<"Name: " << getFirstName() << " " << getLastName() << endl;
  cout << "Address: ";
  address.output();
  cout << "Phone Number: " << getPhoneNumber()<<endl;
  cout << "Email: " << getEmail() << endl;
}

// ">" Operator overload
// Compares two contact first and last names and return true if lexicographically correct

int Contact::operator > (const Contact& other) const{
	char n1 = static_cast<char>(tolower(fName[0]));
	char n2 = static_cast<char>(tolower(other.fName[0]));
	
	
	string name1 = lName + n1 + fName.substr(1);
	string name2 = other.lName + n2 + other.fName.substr(1);

	int size = ((name1.length() >= name2.length()) ?  name2.length()  : name1.length());
	  
	for(int i = 0; i < size-1; i++){
		if(static_cast<int>(name1[i]) > static_cast<int>(name2[i])){
			return 1;
		}else if(static_cast<int>(name1[i]) < static_cast<int>(name2[i])){
			return 0;
		}
		
	}
	
	return 0;
}

// "<" Operator overload
// Compares two contact first and last names and return true if lexicographically correct

int Contact::operator < (const Contact& other) const{
	char n1 = static_cast<char>(tolower(fName[0]));
	char n2 = static_cast<char>(tolower(other.fName[0]));

	string name1 = lName + n1 + fName.substr(1);
	string name2 = other.lName + n2 + other.fName.substr(1);
	
	int size = ((name1.length() >= name2.length()) ?  name2.length()  : name1.length());
	
	for(int i = 0; i < size-1; i++){
		if(static_cast<int>(name1[i]) < static_cast<int>(name2[i])){
			return 1;
		}else if(static_cast<int>(name1[i]) > static_cast<int>(name2[i])){
			return 0;
		}
		
	}
	
	return 0;
}

// "==" Operator overload
// Compares two contact first and last names and return true they both match

int Contact::operator == (const Contact& other) const{
	char n1 = static_cast<char>(tolower(fName[0]));
	char n2 = static_cast<char>(tolower(other.fName[0]));

	string name1 = lName + n1 + fName.substr(1);
	string name2 = other.lName + n2 + other.fName.substr(1);
	
	int size = ((name1.length() >= name2.length()) ?  name2.length()  : name1.length());
	
	for(int i = 0; i < size-1; i++){
		if(static_cast<int>(name1[i]) == static_cast<int>(name2[i])){
			return 1;
		}else if(static_cast<int>(name1[i]) != static_cast<int>(name2[i])){
			return 0;
		}
		
	}
	
	return 0;

}

// "!=" Operator overload
// Calls the "==" operator and returns opposite of the return value

int Contact::operator != (const Contact& other) const{
	if(*this == other){
		return 0;
	}else{
		return 1;
	
	}
	return 0;
}

// ">=" Operator overload
// Compares two contact first and last names and return true if lexicographically correct

int Contact::operator >= (const Contact& other) const{
	char n1 = static_cast<char>(tolower(fName[0]));
	char n2 = static_cast<char>(tolower(other.fName[0]));

	string name1 = lName + n1 + fName.substr(1);
	string name2 = other.lName + n2 + other.fName.substr(1);
	
	int size = ((name1.length() >= name2.length()) ?  name2.length()  : name1.length());
	
	for(int i = 0; i < size - 1; i++){
		if(static_cast<int>(name1[i]) >= static_cast<int>(name2[i])){
			return 1;
		}else if(static_cast<int>(name1[i]) <= static_cast<int>(name2[i])){
			return 0;
		}
		
	}
	
	return 0;
}

// "<=" Operator overload
// Compares two contact first and last names and return true if lexicographically correct

int Contact::operator <= (const Contact& other) const{
	char n1 = static_cast<char>(tolower(fName[0]));
	char n2 = static_cast<char>(tolower(other.fName[0]));

	string name1 = lName + n1 + fName.substr(1);
	string name2 = other.lName + n2 + other.fName.substr(1);
	
	int size = ((name1.length() >= name2.length()) ?  name2.length()  : name1.length());
	
	for(int i = 0; i < size - 1; i++){
		if(static_cast<int>(name1[i]) <= static_cast<int>(name2[i])){
			return 1;
		}else if(static_cast<int>(name1[i]) >= static_cast<int>(name2[i])){
			return 0;
		}
		
	}
	
	return 0;
}




// Operator overload of cout
// Takes and Contact as a parameter and displays all the contact info

ostream& operator << (ostream& out, const Contact& c){
	cout << endl <<"Name: " << c.fName << " " << c.lName << endl;
	cout << "Address: ";
  	cout << c.address;
  	cout << "Phone Number: " << c.phoneNumber<<endl;
  	cout << "Email: " << c.emailAddress << endl;
	
	return out;
}

// Operator overload of cin
// Takes and Contact as a parameter and sets Contact values to user input

istream& operator >> (istream& in, Contact& c){
	string userInput;
	
	cout << "Enter contact first name: ";
	getline(in, userInput);
	c.setFirstName(userInput);
	
	cout << "Enter contact last name: ";
	getline(in, userInput);
  	c.setLastName(userInput);
  	
  	c.setAddress();
  	
  	c.setPhoneNumber(userInput);
  	
	cout << "Enter contact email address: ";
	getline(in, userInput);
  	c.setEmail(userInput);

	return in;

}
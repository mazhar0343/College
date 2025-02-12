#include "Address.h"
#include <iostream>

using namespace std;

Address::Address() : home(""),
                     street(""),
                     apt("none"),
                     city(""),
                     state(""),
                     zip("")
{
   // empty
}

Address::Address(string h, string s, string a, string c, string st, string z){
  home = h;
  street = s;
  apt = a;
  city = c;
  state = st;
  zip = z;
}

string Address::getHome() const
{
   return home;
}

string Address::getStreet() const
{
   return street;
}

string Address::getApt() const
{
   return apt;
}

string Address::getCity() const
{
   return city;
}

string Address::getState() const
{
   return state;
}

string Address::getZip() const
{
   return zip;
}


void Address::output() const
{
   cout << home << " " << street;
   if (apt != "none")
      cout << ", Apt# " << apt;
   cout << endl;
   cout << city << ", " << state << " " << zip << endl;
}

void Address::input()
{
   char choice;
   cout << "Apartment or House (a/h):> ";
   cin >> choice;
   cout << endl;

   cin.ignore(10, '\n');
   cout << "Enter home number (EX: 141-92)___: ";
   getline(cin, home);
   cout << "Enter street number (EX: 70th RD): ";
   getline(cin, street);
 
   if (choice == 'a')
   {
      cout << "Enter Apartment Number: (EX: 1A)_: ";
      getline(cin, apt);
   }
   else
      apt = "none";

   cout << "Enter city (Ex: Flushing)________: ";
   getline(cin, city);

   cout << "Enter state (EX: NY)_____________: ";  
   getline(cin, state);

   cout << "Enter zip code (EX: 11367)_______: ";
   getline(cin, zip);
}

// Operator overload of cout
// Takes an address as a parameter and displays the address

ostream& operator << (ostream& out, const Address& a){
	out << a.home << " " << a.street;
	if (a.apt != "none")
		out << ", Apt# " << a.getApt();
	out << endl;
	out << a.city << ", " << a.state << " " << a.zip << endl;
	return out;
}

// Operator overload of cin
// Takes address as parameter and sets each value of that address to user input

istream& operator >> (istream& in, Address& a){
	string userInput;
	char choice;
	
	cout << "Apartment or House (a/h):> ";
	in >> choice;
	
	in.ignore(10, '\n');
	cout << "Enter home number (EX: 141-92)___: ";
    getline(in, a.home);
    cout << "Enter street number (EX: 70th RD): ";
    getline(in, a.street);
	
	if (choice == 'a')
    {
       cout << "Enter Apartment Number: (EX: 1A)_: ";
       getline(in, a.apt);
    }
    else
       a.apt = "none";

	cout << "Enter city (Ex: Flushing)________: ";
   	getline(in, a.city);

   	cout << "Enter state (EX: NY)_____________: ";  
   	getline(in, a.state);

   	cout << "Enter zip code (EX: 11367)_______: ";
   	getline(in, a.zip);
	
	
	return in;
}
/* 
************************************************************
** PLEASE MAKE SURE THERE ARE NO EMPTY LINES IN TEXT FILE **
************************************************************
*/

#include <iostream>
#include <fstream>
#include <string>
#include "ContactBook.h"

using namespace std;

int getContactBookByName(ContactBook*, int);
void EXIT(ContactBook*, int);

int main() {
 
  int numbooks = 0;
  ContactBook cBooks[5];
  ifstream in;
  in.open("contactbooks.txt");
  string data[10];
  string input; 


// Goes through the entire text file and 
  while (!in.eof()){
    getline(in, input);

    string o1 = input.substr(0, input.find("|"));
    string o2 = input.substr(input.find("|")+1);

    cBooks[numbooks].setFN(o1);
    cBooks[numbooks].setLN(o2);
    getline(in, input);

// Goes line by line adding contacts to a contact book until it reaches "endofbook|"
    while(input != "endofbook|"){
      string inputc = input; 
// Since there are a known amount of fields it spilits up the data and stores it in a array
        for (int i = 0; i < 9; i++){
          data[i] = inputc.substr(0, inputc.find_first_of("|"));
          inputc = inputc.substr(inputc.find_first_of("|") + 1);
        }
      
        data[9] = inputc;
// Creates a new contact and adds to the contact book
        Contact* c1 = new Contact (data[0], data[1], data[2], data[3]);
        Address a1 (data[4], data[5], data[6], data[7], data[8], data[9]);

        c1->setAddress(a1);
        cBooks[numbooks].addContact(c1);
        getline(in, input);
    }
    numbooks++;
  }
  in.close();


// Menu to manage Contact books
  while(input != "EXIT"){
    cout << "Create new ContactBook, Delete ContactBook, Display All, Merge, Update ContactBook, EXIT (cc,dc,da,m,uc,EXIT): ";
    getline(cin >> ws, input);
// Creates a new contact book assigns the owners name
    if(input == "cc"){
      if(numbooks >= 5){
        cout << "Can not create more Contact Books" << endl;
      }else{
        string fn, ln;
        cout <<"Enter First Name: ";
        getline(cin, fn);
        cout <<"Enter Last Name: ";
        getline(cin, ln);
        cBooks[numbooks].setFN(fn);
        cBooks[numbooks].setLN(ln);
        numbooks++;
      }
// Deletes a Contact book by owner name
    }else if(input == "dc"){
      int index = getContactBookByName(cBooks, numbooks);
      
      if(index != -1){
  // Goes through Contact book from selected book and overwrites with data from next book and decreases size by 1
        cBooks[index].deleteBook();
        for(int i = index; i <= numbooks-1; i++){
          cBooks[i] = cBooks[i+1];
        }
        numbooks--;
      }else{
        cout << "Contact Book not found" << endl;
      }
    }
// Displays all the contacts in each contact book
    else if(input == "da"){
      for(int i = 0; i < numbooks; i++){
        cout << cBooks[i].getNumContacts() << " : " << cBooks[i].getCapacity() << endl;
        cBooks[i].displayAll();
      }
    }
// Merges two contact books together
// Adds all contact from one book to another
    else if(input == "m"){
      cout << "Contact Book 1: " << endl;
      int index1 = getContactBookByName(cBooks, numbooks);
      cout << "Contact Book 2: "<< endl;
      int index2 = getContactBookByName(cBooks, numbooks);
      
      if(index1 != -1 && index2 != -1){
        for(int i = 0; i < cBooks[index2].getNumContacts(); i++){
          Contact* currentC = new Contact(cBooks[index2].getContact(i));
          cBooks[index1].addContact(currentC);
        }
      }else{
        if(index1 == -1){
          cout << "Contact Book 1 Not Found" << endl;
        }else if(index2 == -1){
          cout << "Contact Book 2 Not Found" << endl;
        }
      }
    }
// Update Contact allows user to edit contacts in a contact book
    else if(input == "uc"){
      int index = getContactBookByName(cBooks, numbooks);
      if(index != -1){
        while(input != "EXIT"){
		      cout << "Add, Delete, Search, Update, Display All, EXIT (a,d,s,u,da,EXIT): ";
      		getline(cin >> ws, input);
      	// Checks user input to determine appropriate function to call 
      		if(input == "a"){
      			cBooks[index].addContact();
      		}else if(input == "d"){
      			cBooks[index].deleteContact();
      		}else if(input == "s"){
      			cBooks[index].displayContact();
      		}else if(input == "u"){
      			cBooks[index].updateContact();
      		}else if(input == "da"){
      			cBooks[index].displayAll();
      		}
	      }
        input = "";
      }else{
        cout << "Contact Book not found";
      }
    }
// Exit rewrites the text file
    else if(input == "EXIT"){
      EXIT(cBooks, numbooks);
  }
}

  }
// Function to return the index of a contact book
int getContactBookByName(ContactBook* cBooks, int numbooks){
  string fn, ln;
  int index = -1;
  cout <<"Enter First Name: ";
  getline(cin, fn);
  cout <<"Enter Last Name: ";
  getline(cin, ln);
  for(int i = 0; i < numbooks; i++){
    if(fn == cBooks[i].getFN() && ln == cBooks[i].getLN()){
      index = i;
    }
  }
  return index;
}

void EXIT(ContactBook* cBooks, int numbooks){
  ofstream out;
  out.open("contactbooks.txt");
  
  for(int i= 0; i < numbooks; i++){
    out << cBooks[i].getFN() << "|" << cBooks[i].getLN() <<  endl;
    for(int j = 0; j < cBooks[i].getNumContacts(); j++){
      Contact currentC = cBooks[i].getContact(j);
          out << currentC.getFirstName() << "|" <<currentC.getLastName() << "|" << currentC.getPhoneNumber() << "|" << currentC.getEmail() << "|" << currentC.getAddress().getHome() << "|" << currentC.getAddress().getStreet() << "|" << currentC.getAddress().getApt() << "|" << currentC.getAddress().getCity() << "|" << currentC.getAddress().getState() << "|" << currentC.getAddress().getZip() << endl; 
        }
        if(i < numbooks-1){
          out << "endofbook|" << endl;
        }else{
          out << "endofbook|";
        }
      }
    }
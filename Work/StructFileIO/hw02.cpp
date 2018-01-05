/*
  Homework #2: A Game of Medieval Times
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

struct warrior {
  string name;
  int strength;
};

void addWarrior( vector<warrior>& Warriors,
		 const string& name,
		 int strength );

void printStatus(const vector<warrior>& Warriors);

void addBattle( vector<warrior>& Warriors,
		const string& firstName,
		const string& secondName );


int main() {

  vector<warrior> Warriors; // Collection of warriors
  
  ifstream someFileStream("warriors.txt");
  if (!someFileStream) {
    cerr << "failed to open\n";
    exit(1);
  }

  string action; // First Word in a line
  while ( someFileStream >> action ) {

    if (action == "Warrior") { // Warrior Case
      string name;
      int strength;
      someFileStream >> name >> strength;
      addWarrior(Warriors, name, strength);
    }

    else if (action == "Status") { // Status Case
      printStatus(Warriors);
    }

    else if (action == "Battle") { // Battle Case
      string firstName, secondName;
      someFileStream >> firstName >> secondName;
      addBattle(Warriors, firstName, secondName);
    }
    
  }

  someFileStream.close();
}



//==========METHODS==========//

// Given name and strength of a warrior, adds him to collection Warriors
void addWarrior( vector<warrior>& Warriors,
		 const string& name, int strength ) {

  bool check = true;
  for ( const warrior& item : Warriors ) { // Prevent double names
    if (item.name == name) {
      cout << "Already have a warrior with name: " << name << endl;
      check = false;
    }
  }
  
  if (check) { // New Warrior must be added
    warrior toAdd;
    toAdd.name = name;
    toAdd.strength = strength;
    Warriors.push_back(toAdd);
  }  
}


//Prints Status of a collection of Warriors
void printStatus(const vector<warrior>& Warriors) {
  cout << "There are: "
       << Warriors.size() << " warriors" << endl;
  
  for (const warrior& item : Warriors) { // print each warriors name and strength
    cout << "Warrior: " << item.name
	 << ", strength: " << item.strength << endl;
  }
}


// Initiate battle between firstName and secondName, strengths are modified
void addBattle( vector<warrior>& Warriors,
		const string& firstName,
		const string& secondName ) {

  size_t first, second;
  int check = 0;

  // Finds the warriors in the collection
  for (size_t index = 0; index < Warriors.size(); ++index) {
    if (Warriors[index].name == firstName) {
      first = index;
      ++check;
    }
    else if (Warriors[index].name == secondName) {
      second = index;
      ++check;
    }
  }

  //Unable to find Warriors
  if ( check != 2 ) {
    cout << "The Desired Warriors Have Not Been Entered" << endl;
  }

  //Warriors found, Battle occurs
  else {
    cout << Warriors[first].name << " battles " << Warriors[second].name << endl;

    //SAME strength cases
    if (Warriors[first].strength == Warriors[second].strength) {
      if (Warriors[first].strength == 0) {
	cout << "Oh, NO! They're both dead! Yuck!" << endl;
      }
      
      else {
	Warriors[first].strength = 0;
	Warriors[second].strength = 0;
	cout << "Mutual Annihilation: "
	     << Warriors[first].name << " and " << Warriors[second].name
	     << " die at each other's hands" << endl;
      }
    }

    //firstName warrior stronger than secondName warrior case
    if (Warriors[first].strength > Warriors[second].strength) {
      if (Warriors[second].strength == 0) {
	cout << "He's Dead, " << Warriors[first].name << endl;
      }

      else {
	Warriors[first].strength -= Warriors[second].strength;
	Warriors[second].strength = 0;
	cout << Warriors[first].name << " defeats " << Warriors[second].name << endl;
      }
    }

    //secondName warrior stronger than firstName warrior case
    if (Warriors[first].strength < Warriors[second].strength) {
      if (Warriors[first].strength == 0) {
	cout << "He's Dead, " << Warriors[second].name << endl;
      }

      else {
	Warriors[second].strength -= Warriors[first].strength;
	Warriors[first].strength = 0;
	cout << Warriors[second].name << " defeats " << Warriors[first].name << endl;
      }
    }
   
  }
  
}






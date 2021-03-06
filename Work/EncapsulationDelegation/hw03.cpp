/*
  Homework #3: A Game of Medieval Times cont.
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

class warrior {

  class weapon {
    
  public:
    //weapon constructor taking name and strength
    weapon (const string& weaponName, int strength) :
      weaponName(weaponName), strength(strength) {}

    //Methods should only be called by warriors
    int getStrength() const { // returns weapon strength
      return strength;
    }
    string getWeapName() const { // returns weapon name
      return weaponName;
    }
    void setStrength(int newStrength) { // changes weapon strength
      strength = newStrength;
    }
    
  private:
    string weaponName;
    int strength;
    
  };

public:
  //warrior constructor taking warrior's name, weapon's name, and weapon's strength
  warrior( const string& name, const string& weaponName, int strength ) :
    name(name), weap(weaponName, strength) {}

  string getName() const { // returns warrior name
    return name;
  }
  int getStrength() const { // returns weapon strength
    return weap.getStrength();
  }
  void setStrength( int newStrength ) { // changes weapon strength
    weap.setStrength(newStrength);
  }
  
  void status() const {
    cout << "Warrior: " << name
	 << ", weapon: " << weap.getWeapName()
	 << ", " << weap.getStrength() << endl;
  }
  
private:
  string name;
  weapon weap;
  
};


void addWarrior( vector<warrior>& Warriors,
		 const string& name,
		 const string& weaponName,
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
      string name, weaponName;
      int strength;
      someFileStream >> name >> weaponName >> strength;
      addWarrior(Warriors, name, weaponName, strength);
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



//==========FUNCTIONS==========//

// Given name and strength of a warrior, adds him to collection Warriors
void addWarrior( vector<warrior>& Warriors, const string& name,
		 const string& weaponName, int strength ) {

  bool check = true;
  for ( const warrior& item : Warriors ) { // Prevent double names
    if (item.getName() == name) {
      cout << "Already have a warrior with name: " << name << endl;
      check = false;
    }
  }

  if (check) { // New Warrior must be added
    warrior toAdd(name, weaponName, strength);
    Warriors.push_back(toAdd);
  }
}


//Prints Status of a collection of Warriors
void printStatus(const vector<warrior>& Warriors) {
  cout << "There are: " << Warriors.size()
       << " warriors" << endl;

  for (const warrior& item : Warriors) {
    // print each warriors name and strength
    item.status();
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
    if (Warriors[index].getName() == firstName) {
      first = index;
      ++check;
    }
    else if (Warriors[index].getName() == secondName) {
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
    cout << Warriors[first].getName() << " battles "
	 << Warriors[second].getName() << endl;


    //SAME strength case
    if (Warriors[first].getStrength() ==
	Warriors[second].getStrength() ) {
      
      if (Warriors[first].getStrength() == 0) {
	cout << "Oh, NO! They're both dead! Yuck!" << endl;
      }

      else {
	Warriors[first].setStrength(0);
	Warriors[second].setStrength(0);
	cout << "Mutual Annihilation: "
	     << Warriors[first].getName() << " and "
	     << Warriors[second].getName()
	     << " die at each other's hands" << endl;
      }
    }

    //firstName warrior stronger than secondName warrior case
    if (Warriors[first].getStrength() >
	Warriors[second].getStrength() ) {
      
      if (Warriors[second].getStrength() == 0) {
	cout << "He's Dead, " << Warriors[first].getName() << endl;
      }

      else {
	Warriors[first].setStrength( Warriors[first].getStrength() -
				     Warriors[second].getStrength() );
	Warriors[second].setStrength(0);
	
	cout << Warriors[first].getName() << " defeats "
	     << Warriors[second].getName() << endl;
      }
    }

    //secondName warrior stronger than firstName warrior case
    if (Warriors[first].getStrength() <
	Warriors[second].getStrength() ) {
      
      if (Warriors[first].getStrength() == 0) {
	cout << "He's Dead, " << Warriors[second].getName() << endl;
      }

      else {
	Warriors[second].setStrength( Warriors[second].getStrength() -
				      Warriors[first].getStrength() );
	Warriors[first].setStrength(0);
	
	cout << Warriors[second].getName() << " defeats "
	     << Warriors[first].getName() << endl;
      }
    }

  }

}



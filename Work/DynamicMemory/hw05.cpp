/*
  Homework #5: A Game of Medieval Times cont. Dynamic Memory
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



// ========================= //
/*
  Warrior Class
    Member Variables:
      const string name
      int strength
      bool hired
    Member Functions:
      string getName() const
      int getStrength() const
      void setStrength()
      void changeHired()
      bool isHired() const
      void display() const
*/
 
class Warrior {

public:
  // Warrior Constructor taking name and strength (starts un-hired)
  Warrior(const string& theName, int theStrength) :
    name(theName), strength(theStrength), hired(false) {}

  // Basic Getters and Setters
  string getName() const {
    return name;
  }
  int getStrength() const {
    return strength;
  }
  void setStrength(int newStrength) {
    strength = newStrength;
  }
  void changeHired() {
    hired = !hired;
  }
  bool isHired() const {
    return hired;
  }

  // Warrior Display (name: strength)
  void display() const {
    cout << name << ": " << strength << endl;
  }

private:
  const string name;
  int strength;
  bool hired;

}; // Class Warrior



// ========================= //
/*
  Noble Class
    Member Variables:
      const string name
      vector<Warrior*> army
      int totalStrength
      bool dead
    Member Functions:
      bool hire( Warrior& toAddWarrior )
      bool fire( Warrior& toRemWarrior )
      void display() const
      bool battle( Noble& opp )
      void deleteAll()
      bool hasWarrior( const string& name ) const
      string getName() const
*/

class Noble {

public:
  // Noble Constructor with name (initially no army, strength=0, and alive)
  Noble(const string& theName) :
    name(theName), army(), totalStrength(0), dead(false) {}

  // Hire takes a toAddWarrior and adds it to the noble's army
  bool hire(Warrior& toAddWarrior) {
    // Only add if Warrior is unhired and noble is alive
    if ( !toAddWarrior.isHired() && !dead ) {
      totalStrength += toAddWarrior.getStrength();
      toAddWarrior.changeHired();
      army.push_back( &toAddWarrior );
      return true;
    }
    cout << "Unable to Hire " << toAddWarrior.getName() << endl;
    return false;
  }

  // Fire takes a toRemWarrior and removes it from the noble's army
  bool fire(Warrior& toRemWarrior) {
    // Nobles can only fire if they're alive
    if ( !dead ) {
      for ( size_t i = 0; i < army.size(); ++i ) {
	if ( army[i] == &toRemWarrior ) { // If Warrior found
	  cout << "You don't work for me anymore " << toRemWarrior.getName()
	       << "! -- " << name << endl;
	  
	  totalStrength -= toRemWarrior.getStrength();

	  // Special Case
	  if ( army.back() == &toRemWarrior ) { 
	    army.pop_back();
	  }
	  else {
	    // Fix army vector
	    for ( size_t j = i+1; j < army.size(); ++j ) { 
	      army[j-1] = army[j];
	      army.pop_back();
	    }
	  }
	  toRemWarrior.changeHired();
	  return true;
	}
      }
    }
    cout << "Unable to Fire " << toRemWarrior.getName() << endl;
    return false;
  }

  // Noble Display shows army count and all Warriors
  void display() const {
    cout << name << " has an army of " << army.size() << endl;
    for ( Warrior* warr : army ) {
      cout << "\t";
      warr->display();
    }
  }

  // Battle takes another Noble opp and both fight to the death!
  void battle(Noble& opp) {
    cout << name << " battles " << opp.name << endl;

    if (dead && opp.dead) { // Both Dead Case
      cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    }
    else if (dead) { // You Are Dead Case
      cout << "He's dead, " << opp.name << endl;
    }
    else if (opp.dead) { // Opp is Dead Case
      cout << "He's dead, " << name << endl;
    }

    // Same Strength Case
    else if (totalStrength == opp.totalStrength) {
      cout << "Mutual Annihilation: " << name << " and "
	   << opp.name << " die at each other's hands" << endl;
      
      totalStrength = 0;
      dead = true;
      opp.totalStrength = 0;
      opp.dead = true;

      for ( size_t i = 0; i < army.size(); ++i ) {
	army[i]->setStrength(0);
      }
      for ( size_t i = 0; i < opp.army.size(); ++i ) {
	opp.army[i]->setStrength(0);
      }
    }

    // You're Stronger than the Opponent
    else if (totalStrength > opp.totalStrength) {
      cout << name << " defeats " << opp.name << endl;
      
      // Opponent's Army Dies
      for ( size_t i = 0; i < opp.army.size(); ++i ) {
	opp.army[i]->setStrength(0);
      }
      opp.dead = true;

      // Modify Strengths of your Army
      int diff = totalStrength - opp.totalStrength;
      for ( size_t i = 0; i < army.size(); ++i ) {
	int newStrength = army[i]->getStrength() * diff / totalStrength;
	army[i]->setStrength(newStrength);
      }

      totalStrength = totalStrength * diff / totalStrength;
      opp.totalStrength = 0;
    }

    // Your Opponent is Stronger than you
    else if (opp.totalStrength > totalStrength) {
      cout << opp.name << " defeats " << name << endl;
      
      // Your Army Dies
      for ( size_t i = 0; i < army.size(); ++i ) {
	army[i]->setStrength(0);
      }
      dead = true;

      // Modify Strengths of your Opponent's Army
      int diff =  opp.totalStrength - totalStrength;
      for ( size_t i = 0; i < opp.army.size(); ++i ) {
	int newStrength = opp.army[i]->getStrength() * diff / opp.totalStrength;
	opp.army[i]->setStrength(newStrength);
      }

      opp.totalStrength = opp.totalStrength * diff / opp.totalStrength;
      totalStrength = 0;
    }

  }

  // Delete all dynamically allocated warriors in army
  void deleteAll() {
    for ( size_t i = 0; i < army.size(); ++i ) {
      delete army[i];
    }
  }

  // Returns true if there is already a warrior in the army with given name
  bool hasWarrior( const string& name ) const {
    for ( Warrior* warrior : army ) {
      if ( warrior->getName() == name ) {
	return true;
      }
    }
    return false;
  }
  
  // Returns name of the Noble
  string getName() const { return name; }

private:
  const string name;
  vector<Warrior*> army;
  int totalStrength;
  bool dead;
  
}; // Class Noble



// ========================= //
/*
  Helper Functions for main
    bool isWarrior( const vector<Warrior*>& Warriors, const string& name )
    Warrior* getWarrior( const vector<Warrior*>& Warriors, const string& name )    
    bool isNoble( const vector<Noble*>& Nobles, const string& name )
    Noble* getNoble( const vector<Noble*>& Nobles, const string& name )
*/

// isWarrior checks if warrior of given name is in collection of unhired warriors
bool isWarrior( const vector<Warrior*>& Warriors, const string& name ) {
  for (size_t i = 0; i < Warriors.size(); ++i) {
    if ( Warriors[i]->getName() == name ) {
      // cout << name << " Warrior already exists: ERROR" << endl;
      return true;
    }
  }
  return false;
}

// getWarrior returns Warrior* of given name in collection of unhired warriors
Warrior* getWarrior( const vector<Warrior*>& Warriors, const string& name ) {
  for (size_t i = 0; i < Warriors.size(); ++i) {
    if ( Warriors[i]->getName() == name ) {
      return Warriors[i];
    }
  }
  return Warriors[0];
  //  return -1;
}

// isNoble checks if noble of given name is in collection of unhired nobles
bool isNoble( const vector<Noble*>& Nobles, const string& name ) {
  for (size_t i = 0; i < Nobles.size(); ++i) {
    if ( Nobles[i]->getName() == name ) {
      // cout << name << " Noble already exists: ERROR" << endl;
      return true;
    }
  }
  return false;
}

// getNoble returns Noble* of given name in collection of unhired nobles
Noble* getNoble( const vector<Noble*>& Nobles, const string& name ) {
  for (size_t i = 0; i < Nobles.size(); ++i) {
    if ( Nobles[i]->getName() == name ) {
      return Nobles[i];
    }
  }
  return Nobles[0];
  //  return -1;
}



// ========================= //
/*
  Main method
    Reads input from nobleWarriors.txt
    Applies appropriate command actions
    
    Commands:
      Noble: Create a Noble on the heap.
      Warrior: Create a Warrior on the heap.
      Hire: Call the Noble's hire method.
      Fire: Call the Noble's fire method.
      Battle: Call the Noble's battle method.
      Status: The status command shows the nobles, together with their armies, 
              in a similar way that the Noble display method did in hw03. In
	      addition, it will show the warriors who do not have an employer,
	      either because they were fired or never hired.
      Clear. Clear out all the nobles and warriors that were created.
*/
int main() {

  vector<Noble*> Nobles; // Collection of nobles
  vector<Warrior*> Warriors; // Collection of out of work (unhired) warriors

  ifstream someFileStream("nobleWarriors.txt");
  if (!someFileStream) {
    cerr << "failed to open\n";
    exit(1);
  }

  string action; // First Word in a line
  while ( someFileStream >> action ) {

    if ( action == "Noble" ) { // Noble Case
      string name;
      someFileStream >> name;

      // Creates a new noble if noble name is unique
      if ( !isNoble(Nobles, name) ) {
	// Noble on the HEAP
	Noble* toAdd = new Noble(name);
	Nobles.push_back(toAdd);
      }
    }

    else if ( action == "Warrior" ) { // Warrior Case
      string name;
      int strength;
      bool cont = true;
      someFileStream >> name >> strength;

      // Check is warrior name is among the unhired
      if ( isWarrior(Warriors, name) ) {
	cont = false;
      }
      else {
	// Check if warrior name is among the hired
	for ( Noble* noble : Nobles ) {
	  if ( noble->hasWarrior( name ) ) {
	    cont = false;
	  }
	}
      }

      // Continue only if warrior name is unique
      if (cont) {
	// Warrior on the HEAP
	Warrior* toAdd = new Warrior(name, strength);
	Warriors.push_back(toAdd);
      }
      else {
	cout << name << " Already Exists!" << endl;
      }
    }

    else if ( action == "Hire" ) { // Hire Case
      string nobleName, warriorName;
      someFileStream >> nobleName >> warriorName;

      // If Noble and Warrior exist, call Noble's hire method
      if ( isNoble(Nobles, nobleName) && isWarrior(Warriors, warriorName) ) {
	Noble* hiring = getNoble(Nobles, nobleName);
	Warrior* hiree = getWarrior(Warriors, warriorName);
	// hire handles if warrior is already hried or noble is dead
	hiring->hire( *hiree );

	// Update out of work Warrior collection
	if ( hiree == Warriors.back() ) {
	  Warriors.pop_back();
	}
	else {
	  for (size_t i = 0; i < Warriors.size(); ++i) {
	    if ( Warriors[i] == hiree ) {
	      for (size_t j = i+1; j < Warriors.size(); ++j) {
		Warriors[j-1] = Warriors[j];
	      }
	      Warriors.pop_back();
	    }
	  }
	}	
      }
      // Problem with noble or warrior
      else {
	if ( !isNoble(Nobles, nobleName) ) {
	  cout << nobleName << " doesn't exist! ";
	}
	if ( !isWarrior(Warriors, warriorName) ) {
	  cout << warriorName << " doesn't exist or is already hired!";
	}
	cout << endl;
      }
    }

    else if (action == "Fire") { // Fire Case
      string nobleName, warriorName;
      someFileStream >> nobleName >> warriorName;

      // If Noble and Warrior exist, call Noble's fire method
      if ( isNoble(Nobles, nobleName) ) {
	Noble* firing = getNoble(Nobles, nobleName);
	Warrior* firee = getWarrior(Warriors, warriorName);
	// fire handles if warrior is not in noble's army or noble is dead
	firing->fire( *firee );
	Warriors.push_back( firee );
      }
      else {
	cout << nobleName << " doesn't exist!" << endl;
      }
      
    }
    
    else if (action == "Status") { // Status Case
      cout << "Status\n=====\nNobles:" << endl;

      // Empty Nobles
      if (Nobles.size() == 0) {
	cout << "NONE" << endl;
      }
      // Call each Noble's display
      for (size_t i = 0; i < Nobles.size(); ++i) {
	Nobles[i]->display();
      }

      // Empty Warriors
      cout << "Unemployed Warriors:" << endl;
      if (Warriors.size() == 0) {
	cout << "NONE" << endl;
      }
      // Call each Warrior's display
      for (size_t i = 0; i < Warriors.size(); ++i) {
	Warriors[i]->display();
      }
    }

    else if (action == "Battle") { // Battle Case
      string firstName, secondName;
      someFileStream >> firstName >> secondName;
      // If firstName and secondName are legal Nobles
      if ( isNoble( Nobles, firstName ) && isNoble( Nobles, secondName ) ) {
	Noble* firstNoble = getNoble( Nobles, firstName );
	Noble* secondNoble = getNoble( Nobles, secondName );
	firstNoble->battle( *secondNoble );
      }
      // Problems with Nobles
      else {

	if ( !isNoble( Nobles, firstName ) && !isNoble( Nobles, secondName ) ) {
	  cout << "No Nobles with names: " << firstName << " and  "
	       << secondName << " were found!" << endl;
	}
	else if ( !isNoble( Nobles, firstName) ) {
	  cout << firstName << " doesn't exist!" << endl;
	}
	else if ( !isNoble( Nobles, secondName) ) {
	  cout << secondName << " doesn't exist!" << endl;
	}
      }
    }

    else if (action == "Clear") { // Clear Case
      // Call deleteAll for each Noble to delete warriors in army
      // Delete each Noble
      for ( Noble* toRem : Nobles ) {
	toRem->deleteAll();
	delete toRem;
      }
      Nobles.clear();

      // Delete all unhired Warriors
      for ( Warrior* toRem : Warriors ) {
	delete toRem;
      }
      Warriors.clear();
    }
  }

  someFileStream.close();
}





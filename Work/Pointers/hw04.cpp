/*
  Homework #4: A Game of Medieval Times cont. Warriors and Nobles
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
};


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
	  cout << toRemWarrior.getName()
	       << ", you're fired! -- " << name << endl;
	  totalStrength -= toRemWarrior.getStrength();
	  if ( army.back() == &toRemWarrior ) { // Special Case
	    army.pop_back();
	  }
	  else {
	    for ( size_t j = i+1; j < army.size(); ++j ) { // Fix army vector
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
    //cout << "Strength: " << totalStrength << " "
    //	 << "\tStatus: " << (dead ? "DEAD" : "ALIVE" ) << endl;
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
      cout << "He's dead " << opp.name << endl;
    }
    else if (opp.dead) { // Opp is Dead Case
      cout << "He's dead " << name << endl;
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
	int newStrength =
	  army[i]->getStrength() * diff / totalStrength;
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
	int newStrength =
	  opp.army[i]->getStrength() * diff / opp.totalStrength;
	opp.army[i]->setStrength(newStrength);
      }
      
      opp.totalStrength = opp.totalStrength * diff / opp.totalStrength;      
      totalStrength = 0;
    }

  }
  
private:
  const string name;
  vector<Warrior*> army;
  int totalStrength;
  bool dead;
};
  


int main() {

  // Sample test Code
  Noble art("King Arthur");
  Noble lance("Lancelot du Lac");
  Noble jim("Jim");
  Noble linus("Linus Torvalds");
  Noble billie("Bill Gates");

  Warrior cheetah("Tarzan", 10);
  Warrior wizard("Merlin", 15);
  Warrior theGovernator("Conan", 12);
  Warrior nimoy("Spock", 15);
  Warrior lawless("Xena", 20);
  Warrior mrGreen("Hulk", 8);
  Warrior dylan("Hercules", 3);

  jim.hire(nimoy);
  lance.hire(theGovernator);
  art.hire(wizard);
  lance.hire(dylan);
  linus.hire(lawless);
  billie.hire(mrGreen);
  art.hire(cheetah);

  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();

  //jim.hire(cheetah);
  art.fire(cheetah);
  //art.fire(cheetah);
  //jim.hire(cheetah);
  art.display();
  //jim.display();

  art.battle(lance);
  jim.battle(lance);
  linus.battle(billie);
  billie.battle(lance);

  // End Result Testing
  /*
  cout << endl;
  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();
  */
}

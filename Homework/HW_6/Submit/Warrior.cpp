/*
  Homework #6: Separate Compilation
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Warrior.h"
#include "Noble.h"

#include <iostream>
#include <string>
using namespace std;

namespace WarriorCraft {
  
  // Warrior Constructor taking name and strength (starts un-hired)
  Warrior::Warrior(const string& theName, int theStrength) :
    name(theName), strength(theStrength), hired(false) {}
  
  // Basic Getters and Setters
  string Warrior::getName() const { return name; }
  int Warrior::getStrength() const { return strength; }
  
  void Warrior::setStrength( int newStrength ) {
    strength = newStrength;
  }
  
  void Warrior::changeHired() { hired = !hired; }
  bool Warrior::isHired() const { return hired; }
  
  // Warrior Display (name: strength)
  void Warrior::display() const {
    cout << name << ": " << strength << endl;
  }
  
  bool Warrior::runaway() {
    if ( boss ) {
      // If you in army
      if ( boss->inArmy( this ) ) {
	cout << name << " flees in terror, abandoning his lord, "
	     << boss->getName() << endl;
	boss->removeWarrior( this );
	this->changeHired();
	return true;
      }
    }
    return false;
  }
  
  void Warrior::changeBoss( Noble* newBoss ) {
    if (!boss) {
      boss = newBoss;
    }
  }

  void Warrior::deleteBoss() { boss = nullptr; }
  
} // Close WarriorCraft

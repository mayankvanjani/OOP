/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Protector.h"
#include "Noble.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {

  Protector::Protector( const string& name, int strength ) :
    name(name), strength(strength), hired(false), boss(nullptr) {}

  void Protector::display() const {
    cout << name << ": " << strength << endl;
  }

  string Protector::getName() const { return name; }
  int Protector::getStrength() const { return strength; }
  string Protector::getBossName() const {
    if (boss) {
      return boss->getName();
    }
    return "none";
  }
  
  void Protector::setStrength( int newStrength ) {
    strength = newStrength;
  }
  
  void Protector::changeHired() { hired = !hired; }
  bool Protector::isHired() const { return hired; }

  void Protector::changeBoss( Lord* newBoss ) {
    if (!boss) { boss = newBoss; }
  }

  bool Protector::runaway() {
    if ( boss ) {
      if ( boss->inArmy( this ) ) {
	cout << name << " flees in terror, abandoning his lord, "
	     << boss->getName() << endl;
	boss->removeProtector( this );
	this->changeHired();
	return true;
      }
    }
    return false;
  }
  
} // Close WarriorCraft

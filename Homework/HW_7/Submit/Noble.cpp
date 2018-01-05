/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Noble.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {
  
  Noble::Noble( const string& name, int strength) :
    name(name), dead(false), strength(strength) {}

  //virtual void Noble::display() const = 0;
  
  string Noble::getName() const {
    return name;
  }
  
  int Noble::getStrength() const {
    return strength;
  }
  
  void Noble::setStrength( int newStrength ) {
    strength = newStrength;
  }

  bool Noble::isDead() const { return dead; }

  void Noble::battle( Noble& opp ) {
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
    
    else if ( strength == opp.strength ) { // Same Strength Case
      warCry();
      opp.warCry();
      cout << "Mutual Annihilation: " << name << " and "
	   << opp.name << " die at each other's hands" << endl;
      update( -1 );
      opp.update( -1 );
      strength = 0;
      dead = true;
      opp.strength = 0;
      opp.dead = true;
    }

    else if ( strength > opp.strength ) { // You're Stronger Case
      warCry();
      opp.warCry();
      cout << name << " defeats " << opp.name << endl;
      update( strength - opp.strength );
      opp.update( -1 );
      strength -= opp.strength;
      opp.dead = true;
      opp.strength = 0;
    }

    else if ( opp.strength > strength ) { // Opp Stronger Case
      warCry();
      opp.warCry();
      cout << opp.name << " defeats " << name << endl;
      opp.update( opp.strength - strength );
      update( -1 );
      opp.strength -= strength;
      dead = true;
      strength = 0;
    }

    else { // Don't Come Here
      cout << "SHOULDNT BE HERE" << endl;
    }
    
  }
  
  void Noble::display() const {
    cout << name << " has ";
  }
  
} // Close WarriorCraft

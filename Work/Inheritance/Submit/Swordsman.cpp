/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Swordsman.h"
#include "Warrior.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {

  Swordsman::Swordsman( const string& name, int strength ) : Warrior( name, strength ) {}
  
  void Swordsman::warCry() const {
    cout << "CLANG! " << getName();
    endStatement();
    cout << getBossName() << endl;
    //cout << "CLANG! " << getName() << " says: Take that in the name of my lord, "
    //	 << getBossName() << endl;
  }
  
} // Close WarriorCraft

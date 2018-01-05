/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Archer.h"
#include "Warrior.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {

  Archer::Archer( const string& name, int strength ) : Warrior( name, strength ) {}

  void Archer::warCry() const {
    cout << "TWANG! " << getName();
    endStatement();
    cout << getBossName() << endl;
    //cout << "TWANG! " << getName() << " says: Take that in the name of my lord, "
    //	 << getBossName() << endl;
  }
  
} // Close WarriorCraft

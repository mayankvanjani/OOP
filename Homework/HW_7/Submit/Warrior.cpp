/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Warrior.h"
#include "Protector.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {
  
  Warrior::Warrior( const string& name, int strength ) : Protector( name, strength ) {}
  
  void Warrior::endStatement() const {
    cout << " says: Take that in the name of my lord, ";
  }
  
} // Close WarriorCraft

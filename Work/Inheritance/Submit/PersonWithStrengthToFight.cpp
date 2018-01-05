/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "PersonWithStrengthToFight.h"
#include "Noble.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {

  PersonWithStrengthToFight::PersonWithStrengthToFight( const string& name, int strength ) :
    Noble(name, strength) {}

  void PersonWithStrengthToFight::display() const {
    Noble::display();
    cout << "strength: " << getStrength() << endl;
  }

  void PersonWithStrengthToFight::warCry() const { }
  void PersonWithStrengthToFight::update( int diff ) { }
  
  
} // Close WarriorCraft

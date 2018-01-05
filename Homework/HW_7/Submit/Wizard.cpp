/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Wizard.h"
#include "Protector.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {

  Wizard::Wizard( const string& name, int strength ) : Protector( name, strength ) {}

  void Wizard::warCry() const {
    cout << "POOF" << endl;
  }

} // Close WarriorCraft

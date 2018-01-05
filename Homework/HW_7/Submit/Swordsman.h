/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _SWORDSMAN_H
#define _SWORDSMAN_H

#include "Warrior.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {

  class Swordsman : public Warrior {
  public:
    Swordsman( const std::string& name, int strength );
  
    void warCry() const;
  
  protected:
  private:
  };

} // Close WarriorCraft

#endif

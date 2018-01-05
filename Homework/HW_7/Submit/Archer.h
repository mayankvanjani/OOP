/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _ARCHER_H
#define _ARCHER_H

#include "Warrior.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {

  class Archer : public Warrior {
  public:
    Archer( const std::string& name, int strength );
    
    void warCry() const;
  
  protected:
  private:
    
  };

} // Close WarriorCraft

#endif

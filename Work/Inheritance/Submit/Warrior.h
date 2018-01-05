/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _WARRIOR_H
#define _WARRIOR_H

#include "Protector.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {

  class Warrior : public Protector {
  public:
    Warrior( const std::string& name, int strength );
  
    void endStatement() const;
  
    virtual void warCry() const = 0;
    
  };

} // Close WarriorCraft

#endif

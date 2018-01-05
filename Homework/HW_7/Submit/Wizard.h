/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _WIZARD_H
#define _WIZARD_H

#include "Protector.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {
  
  class Wizard : public Protector {
  public:
    Wizard( const std::string& name, int strength );

    virtual void warCry() const;
    
  protected:
  private:

  };

} // Close WarriorCraft

#endif

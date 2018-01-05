/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _PERSONWITHSTRENGTHTOFIGHT_H
#define _PERSONWITHSTRENGTHTOFIGHT_H

#include "Noble.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {

  class PersonWithStrengthToFight : public Noble {
  public:
    PersonWithStrengthToFight( const std::string& name, int strength );

    void display() const;

    virtual void warCry() const;
    void update( int diff );
  
  protected:
  private:
  };

} // Close WarriorCraft

#endif

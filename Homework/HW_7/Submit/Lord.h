/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _LORD_H
#define _LORD_H

#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {

  class Protector;
  
  class Lord : public Noble {
  public:
    Lord( const std::string& name );

    void display() const;

    virtual void warCry() const;
  
    bool hires( Protector& toAddProtector );

    bool inArmy( const Protector* check ) const;

    bool removeProtector( Protector* toRemPro );

    int sumStrength() const;

    void update( int diff );

  protected:
  private:
    std::vector<Protector*> army;

  };

} // Close WarriorCraft

#endif

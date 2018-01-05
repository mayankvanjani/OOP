/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _PROTECTOR_H
#define _PROTECTOR_H

#include "Lord.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {

  class Lord;
  
  class Protector {
  public:
    Protector( const std::string& name, int strength );

    void display() const;

    int getStrength() const;
    std::string getBossName() const;
  
    void setStrength( int newStrength );

    void changeHired();
    bool isHired() const;

    void changeBoss( Lord* newBoss );
  
    virtual void warCry() const = 0;

    bool runaway();
    
  protected:
    std::string getName() const;
    
  private:
    std::string name;
    int strength;
    bool hired;
    Lord* boss;
  };

} // Close WarriorCraft

#endif

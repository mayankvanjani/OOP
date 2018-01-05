/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _NOBLE_H
#define _NOBLE_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>

namespace WarriorCraft {

  class Noble {

  public:
    Noble( const std::string& name, int strength = 0 );
    
    virtual void display() const = 0;
    
    std::string getName() const;

    int getStrength() const;

    void setStrength( int newStrength );

    bool isDead() const;

    virtual void warCry() const = 0;
  
    virtual void battle( Noble& opp );

    virtual void update( int diff ) = 0;
      
  protected:
  private:
    std::string name;
    bool dead;
    int strength;
  };

} // Close WarriorCraft

#endif

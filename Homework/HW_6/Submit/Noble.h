/*
  Homework #6: Separate Compilation
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _NOBLE_H
#define _NOBLE_H

#include <string>
#include <vector>
#include <iostream>

namespace WarriorCraft {

  class Warrior;
  
  class Noble {

    friend std::ostream& operator<<( std::ostream& os, const Noble& rhs );

  public:
    // Noble Constructor with name (initially no army, strength=0, and alive)
    Noble(const std::string& theName);
    
    // Hire takes a toAddWarrior and adds it to the noble's army
    bool hire(Warrior& toAddWarrior);
    
    // Fire takes a toRemWarrior and removes it from the noble's army
    bool fire(Warrior& toRemWarrior);
    
    // Noble Display shows army count and all Warriors
    void display() const;
    
    // Battle takes another Noble opp and both fight to the death!
    void battle(Noble& opp);
    
    bool inArmy( const Warrior* checkWarrior ) const;
    
    bool removeWarrior( Warrior* toRemWarrior );
    
    std::string getName() const;

  private:
    const std::string name;
    std::vector<Warrior*> army;
    int totalStrength;
    bool dead;
    
  }; // Close Noble

} // Close WarriorCraft

#endif

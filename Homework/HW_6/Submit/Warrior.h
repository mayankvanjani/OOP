/*
  Homework #6: Separate Compilation
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#ifndef _WARRIOR_H
#define _WARRIOR_H

#include <string>

namespace WarriorCraft {
  
  class Noble;
  
  class Warrior {  
  public:
    // Warrior Constructor taking name and strength (starts un-hired)
    Warrior(const std::string& theName, int theStrength);
    
    // Basic Getters and Setters
    std::string getName() const;
    int getStrength() const;
    
    void setStrength( int newStrength );
    
    void changeHired();
    bool isHired() const;
    
    // Warrior Display (name: strength)
    void display() const;

    void changeBoss( Noble* newBoss );
    void deleteBoss();
    
    bool runaway();
    
  private:
    const std::string name;
    int strength;
    bool hired;
    Noble* boss;
    
  }; // Closes Warrior
  
} // Close WarriorCraft

#endif

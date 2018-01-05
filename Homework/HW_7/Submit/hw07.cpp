/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Noble.h"
#include "PersonWithStrengthToFight.h"
#include "Lord.h"
#include "Protector.h"
#include "Wizard.h"
#include "Warrior.h"
#include "Archer.h"
#include "Swordsman.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;
using namespace WarriorCraft;

int main() {
  Lord sam("Sam");
  Archer samantha("Samantha", 200);
  sam.hires(samantha);
  Lord joe("Joe");
  PersonWithStrengthToFight randy("Randolf the Elder", 250);
  joe.battle(randy);
  joe.battle(sam);
  Lord janet("Janet");
  Swordsman hardy("TuckTuckTheHardy", 100);
  Swordsman stout("TuckTuckTheStout", 80);
  janet.hires(hardy);
  janet.hires(stout);
  PersonWithStrengthToFight barclay("Barclay the Bold", 300);
  //  janet.display();
  janet.battle(barclay);
  //  janet.display();
  //  hardy.runaway();
  //  stout.runaway();
  //  janet.display();
  janet.hires(samantha);
  Archer pethora("Pethora", 50);
  Archer thora("Thorapleth", 60);
  Wizard merlin("Merlin", 150);
  janet.hires(pethora);
  janet.hires(thora);
  sam.hires(merlin);
  janet.battle(barclay);
  sam.battle(barclay);
  joe.battle(barclay);

  /*
  sam.display();
  joe.display();
  randy.display();
  janet.display();
  barclay.display();
  */
  
}



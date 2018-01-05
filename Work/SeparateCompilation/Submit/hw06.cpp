/*
  Homework #6: Separate Compilation
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Warrior.h"
#include "Noble.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;
using namespace WarriorCraft;

int main() {

  // Sample test Code
  Noble art("King Arthur");
  Noble lance("Lancelot du Lac");
  Noble jim("Jim");
  Noble linus("Linus Torvalds");
  Noble billie("Bill Gates");
  
  Warrior cheetah("Tarzan", 10);
  Warrior wizard("Merlin", 15);
  Warrior theGovernator("Conan", 12);
  Warrior nimoy("Spock", 15);
  Warrior lawless("Xena", 20);
  Warrior mrGreen("Hulk", 8);
  Warrior dylan("Hercules", 3);
  
  jim.hire(nimoy);
  lance.hire(theGovernator);
  art.hire(wizard);
  lance.hire(dylan);
  linus.hire(lawless);
  billie.hire(mrGreen);
  art.hire(cheetah);

  cout << jim << endl;
  cout << lance << endl;
  cout << art << endl;
  cout << linus << endl;
  cout << billie << endl;

  /*
  jim.display();
  lance.display();
  art.display();
  linus.display();
  billie.display();
  */
  
  cheetah.runaway();
  cout << art << endl;
  //  art.display();
  
  art.battle(lance);
  jim.battle(lance);
  linus.battle(billie);
  billie.battle(lance);

  // End Testing
  /*
  cout << endl;
  cout << jim << endl;
  cout << lance << endl;
  cout << art << endl;
  cout << linus << endl;
  cout << billie << endl;
  */
  
}

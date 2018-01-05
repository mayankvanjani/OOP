/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include "Lord.h"
#include "Noble.h"
#include "Protector.h"

#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

namespace WarriorCraft {

  Lord::Lord( const string& name ) : Noble(name), army() {}

  void Lord::display() const {
    Noble::display();
    cout << "an army of size " << army.size() << endl;
    for (Protector* pro : army) {
      cout << "\t";
      pro->display();
    }
  }

  void Lord::warCry() const {
    for ( Protector* pro : army ) {
      pro->warCry();
    }    
  }
  
  bool Lord::hires( Protector& toAddProtector ) {
    if ( !toAddProtector.isHired() && !Noble::isDead() ) {
      setStrength( getStrength() + toAddProtector.getStrength() );
      //totalStrength += toAddProtector.getStrength();
      toAddProtector.changeHired();
      army.push_back( &toAddProtector );
      toAddProtector.changeBoss(this);
      return true;
    }
    //cout << "Unable to Hire " << toAddProtector.getName() << endl;
    return false;
  }


  bool Lord::inArmy( const Protector* check ) const {
    for ( const Protector* currPro : army ) {
      if ( check == currPro ) {
	return true;
      }
    }
    return false;
  }

  bool Lord::removeProtector( Protector* toRemPro ) {
    for ( size_t i = 0; i < army.size(); ++i ) {
      if ( army[i] == toRemPro ) {
	if ( army.back() == toRemPro ) {
	  army.pop_back();
	}
	else {
	  for ( size_t j = i+1; j < army.size(); ++j ) {
	    army[j-1] = army[j];
	    army.pop_back();
	  }
	}
	setStrength( getStrength() - toRemPro->getStrength() );
	toRemPro->changeHired();
	return true;
      }
    }
    return false;
  }

  int Lord::sumStrength() const {
    int total = 0;
    for ( size_t i = 0; i < army.size(); ++i ) {
      total += army[i]->getStrength();
    }
    return total;
  }
  
  void Lord::update( int diff ) {
    int total = sumStrength();
    if ( diff == -1 ) {
      for ( size_t i = 0; i < army.size(); ++i ) {
	army[i]-> setStrength( 0 );
      }
    }
    else {
      for ( size_t i = 0; i < army.size(); ++i ) {
	army[i]-> setStrength( army[i]->getStrength() * diff / total );
      }
    }
  }
  
} // Close WarriorCraft

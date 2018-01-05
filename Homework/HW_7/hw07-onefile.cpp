/*
  Homework #7: Inheritance
  Mayank Vanjani mv1506
  CS 2114
  Professor Sterling
  NYU Tandon School of Engineering
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
using namespace std;

class Noble;
class Lord;

class Protector {
public:
  Protector( const string& name, int strength ) :
    name(name), strength(strength), hired(false), boss(nullptr) {}

  void display() const {
    cout << name << ": " << strength << endl;
  }
  
  int getStrength() const { return strength; }
  string getBossName() const;
  
  void setStrength( int newStrength ) {
    strength = newStrength;
  }
  
  void changeHired() { hired = !hired; }
  bool isHired() const { return hired; }

  void changeBoss( Lord* newBoss ) {
    if (!boss) { boss = newBoss; }
  }
  
  virtual void warCry() const = 0;

  bool runaway();
  
protected:
  string getName() const { return name; }
private:
  string name;
  int strength;
  bool hired;
  Lord* boss;
};

class Wizard : public Protector {
public:
  Wizard( const string& name, int strength ) : Protector( name, strength ) {}

  virtual void warCry() const {
    cout << "POOF" << endl;
  }
  
protected:
private:
};

class Warrior : public Protector {
public:
  Warrior( const string& name, int strength ) : Protector( name, strength ) {}
  
  void endStatement() const {
    cout << " says: Take that in the name of my lord, ";
  }
  
  virtual void warCry() const = 0;
    
protected:
private:
};

class Archer : public Warrior {
public:
  Archer( const string& name, int strength ) : Warrior( name, strength ) {}

  void warCry() const {
    cout << "TWANG! " << getName();
    endStatement();
    cout << getBossName() << endl;
    //cout << "TWANG! " << getName() << " says: Take that in the name of my lord, "
    //	 << getBossName() << endl;
  }
  
protected:
private:
};

class Swordsman : public Warrior {
public:
  Swordsman( const string& name, int strength ) : Warrior( name, strength ) {}
  
  void warCry() const {
    cout << "CLANG! " << getName();
    endStatement();
    cout << getBossName() << endl;
    //cout << "CLANG! " << getName() << " says: Take that in the name of my lord, "
    //	 << getBossName() << endl;
  }
  
protected:
private:
};

class Noble {
public:
  Noble( const string& name, int strength = 0 ) :
    name(name), dead(false), strength(strength) {}

  virtual void display() const = 0;

  string getName() const {
    return name;
  }
  int getStrength() const {
    return strength;
  }
  void setStrength( int newStrength ) {
    strength = newStrength;
  }

  bool isDead() const { return dead; }

  virtual void warCry() const = 0;
  
  virtual void battle( Noble& opp ) {
    cout << name << " battles " << opp.name << endl;
    
    if (dead && opp.dead) { // Both Dead Case
      cout << "Oh, NO!  They're both dead!  Yuck!" << endl;
    }
    else if (dead) { // You Are Dead Case
      cout << "He's dead, " << opp.name << endl;
    }
    else if (opp.dead) { // Opp is Dead Case
      cout << "He's dead, " << name << endl;
    }
    
    else if ( strength == opp.strength ) { // Same Strength Case
      warCry();
      opp.warCry();
      cout << "Mutual Annihilation: " << name << " and "
	   << opp.name << " die at each other's hands" << endl;
      update( -1 );
      opp.update( -1 );
      strength = 0;
      dead = true;
      opp.strength = 0;
      opp.dead = true;
    }

    else if ( strength > opp.strength ) { // You're Stronger Case
      warCry();
      opp.warCry();
      cout << name << " defeats " << opp.name << endl;
      update( strength - opp.strength );
      opp.update( -1 );      
      strength -= opp.strength;
      opp.dead = true;
      opp.strength = 0;
    }

    else if ( opp.strength > strength ) { // Opp Stronger Case
      warCry();
      opp.warCry();
      cout << opp.name << " defeats " << name << endl;
      opp.update( opp.strength - strength );
      update( -1 );
      opp.strength -= strength;
      dead = true;
      strength = 0;
    }

    else { // Don't Come Here
      cout << "SHOULDNT BE HERE" << endl;
    }
  }

  virtual void update( int diff ) = 0;

protected:
private:
  string name;
  bool dead;
  int strength;
};

void Noble::display() const {
  cout << name << " has ";
}

class PersonWithStrengthToFight : public Noble {
public:
  PersonWithStrengthToFight( const string& name, int strength ) :
    Noble(name, strength) {}

  void display() const {
    Noble::display();
    cout << "strength: " << getStrength() << endl;
  }

  /*
  void battle( Noble& opp ) {
    int oppStr = opp.getStrength();
    int yourStr = getStrength();

    Noble::battle( opp );
    
    if ( !isDead() ) {
      setStrength( yourStr * (yourStr - oppStr) / yourStr );
    }
  }
  */
  
  // PlaceHolder since PersonWithStrengthToFight doesn't talk
  void warCry() const {}
  void update( int diff ) {};
  
protected:
private:
};

class Lord : public Noble {
public:
  Lord( const string& name ) : Noble(name), army() {}

  void display() const {
    Noble::display();
    cout << "an army of size " << army.size() << endl;
    for (Protector* pro : army) {
      cout << "\t";
      pro->display();
    }
  }

  virtual void warCry() const {
    for ( Protector* pro : army ) {
      pro->warCry();
    }    
  }
  
  bool hires( Protector& toAddProtector ) {
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

  bool inArmy( const Protector* check ) const {
    for ( const Protector* currPro : army ) {
      if ( check == currPro ) {
	return true;
      }
    }
    return false;
  }

  bool removeProtector( Protector* toRemPro ) {
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

  int sumStrength() const {
    int total = 0;
    for ( size_t i = 0; i < army.size(); ++i ) {
      total += army[i]->getStrength();
    }
    return total;
  }

  void update( int diff ) {
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

protected:
private:
  vector<Protector*> army;
};



int main() {
  Lord sam("Sam");
  Archer samantha("Samantha", 200);
  sam.hires(samantha);
  Lord joe("Joe");
  PersonWithStrengthToFight randy("Randolf the Elder", 250);
  joe.battle(randy);
  randy.display();
  joe.battle(sam);
  Lord janet("Janet");
  Swordsman hardy("TuckTuckTheHardy", 150);
  Swordsman stout("TuckTuckTheStout", 50);
  janet.hires(hardy);
  janet.hires(stout);
  PersonWithStrengthToFight barclay("Barclay the Bold", 50);
  janet.battle(barclay);
  janet.display();
  barclay.display();
  hardy.runaway();
  stout.runaway();
  janet.display();
  barclay.display();
  /*
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

  joe.display();
  sam.display();
  janet.display();
  */
}

string Protector::getBossName() const {
  if (boss) {
    return boss->getName();
  }
  return "none";
}

bool Protector::runaway() {
  if ( boss ) {
    if ( boss->inArmy( this ) ) {
      cout << name << " flees in terror, abandoning his lord, "
	   << boss->getName() << endl;
      boss->removeProtector( this );
      this->changeHired();
      return true;
    }
  }
  return false;
}

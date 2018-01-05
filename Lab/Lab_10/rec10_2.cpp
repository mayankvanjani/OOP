/*
  Rec10: More Inheritance
  Mayank Vanjani
  11/10/17
  CS2114
  NYU Tandon School of Engineering
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Instrument {
public:
  virtual void makeSound() const = 0;
  virtual void play() const = 0;
protected:
private:
};

void Instrument::makeSound() const {
  cout << "To make a sound... ";
}

class Brass : public Instrument {
public:
  Brass( int size ) : size(size) {}
  virtual void makeSound() const = 0;
  virtual void play() const = 0;
protected:
private:
  unsigned size;
};

void Brass::makeSound() const {
  Instrument::makeSound();
  cout << "blow on a mouthpiece of size " << size << endl;
}

class Trumpet : public Brass {
public:
  Trumpet( int size ) : Brass( size ) {}
  void makeSound() const {
    Brass::makeSound();
  }
  void play() const {
    cout << "Toot";
  }
protected:
private:
};

class Trombone : public Brass {
public:
  Trombone( int size ) : Brass( size ) {}
  void makeSound() const {
    Brass::makeSound();
  }
  void play() const {
    cout << "Blat";
  }
protected:
private:
};

class String : public Instrument {
public:
  String( int pitch ) : pitch( pitch ) {}
  virtual void makeSound() const = 0;
  virtual void play() const = 0;
protected:
private:
  unsigned pitch;
};

void String::makeSound() const {
  Instrument::makeSound();
  cout << "bow a string with pitch " << pitch << endl;
}

class Violin : public String {
public:
  Violin( int pitch ) : String( pitch ) {}
  void makeSound() const {
    String::makeSound();
  }
  void play() const {
    cout << "Screech";
  }
protected:
private:
};

class Cello : public String {
public:
  Cello( int pitch ) : String( pitch ) {}
  void makeSound() const {
    String::makeSound();
  }
  void play() const {
    cout << "Squawk";
  }
protected:
private:
};

class Percussion : public Instrument {
public:
  Percussion() {}
  virtual void makeSound() const = 0;
  virtual void play() const = 0;
protected:
private:
};

void Percussion::makeSound() const {
  Instrument::makeSound();
  cout << "HIT ME!" << endl;
}

class Drum : public Percussion {
public:
  Drum() {}
  void makeSound() const {
    Percussion::makeSound();
  }
  void play() const {
    cout << "Boom";
  }
protected:
private:
};

class Cymbal : public Percussion {
public:
  Cymbal() {}
  void makeSound() const {
    Percussion::makeSound();
  }
  void play() const {
    cout << "Crash";
  }
protected:
private:
};

class Musician {
public:
  Musician() : instr(nullptr) {}
  void acceptInstr(Instrument& i) { instr = &i; }
  Instrument* giveBackInstr() {
    Instrument* tmp(instr);
    instr = nullptr;
    return tmp;
  }
  void testPlay() const {
    if(instr)
      instr->makeSound();
    else
      cerr << "have no instr\n";
  }
  void play() const {
    if ( instr ) {
      instr->play();
    }
  }
  
private:
  Instrument* instr;
};

class MILL {
public:
  void receiveInstr( Instrument& i ) {
    //i.makeSound();

    for ( size_t index = 0; index < inventory.size(); ++index ) {
      if ( !inventory[index] ) {
	inventory[index] = &i;
	return;
      }
    }

    inventory.push_back( &i );
  }

  void dailyTestPlay() const {
    for ( Instrument* instr : inventory ) {
      if ( instr ) {
	instr->makeSound();
      }
    }
  }

  Instrument* loanOut() {
    for ( size_t i = 0; i < inventory.size(); ++i ) {
      if ( inventory[i] ) {
	Instrument* temp = inventory[i];
	inventory[i] = nullptr;
	return temp;
      }
    }
    return nullptr;
  }

protected:
private:
  vector<Instrument*> inventory;
};

class Orch {
public:
  void addPlayer( Musician& player ) {
    if ( players.size() < 25 ) {
      players.push_back( &player );
    }
    else {
      cout << "Cannot Add Player, Orchestra Full!" << endl;
    }
  }

  void play() const {
    for ( Musician* player : players ) {
      player->play();
    }
    cout << endl;
  }
  
protected:
private:
  vector<Musician*> players;
};





// PART TWO
int main() {
  // The initialization phase
  
  Drum drum;
  Cello cello(673);
  Cymbal cymbal;
  Trombone tbone(4);
  Trumpet trpt(12);
  Violin violin(567);
  
  MILL mill;
  mill.receiveInstr(trpt);
  mill.receiveInstr(violin);
  mill.receiveInstr(tbone);
  mill.receiveInstr(drum);
  mill.receiveInstr(cello);
  mill.receiveInstr(cymbal);
  
  Musician bob;
  Musician sue;
  Musician mary;
  Musician ralph;
  Musician jody;
  Musician morgan;

  Orch orch;
  
  // THE SCENARIO
  
  //Bob joins the orchestra without an instrument.
  orch.addPlayer(bob);

  //The orchestra performs
  cout << "orch performs\n";
  orch.play();

  //Sue gets an instrument from the MIL2 and joins the orchestra.
  sue.acceptInstr(*mill.loanOut());
  orch.addPlayer(sue);

  //Ralph gets an instrument from the MIL2.
  ralph.acceptInstr(*mill.loanOut());
  
  //Mary gets an instrument from the MIL2 and joins the orchestra.
  mary.acceptInstr(*mill.loanOut());
  orch.addPlayer(mary);
  
  //Ralph returns his instrument to the MIL2.
  mill.receiveInstr(*ralph.giveBackInstr());
  
  //Jody gets an instrument from the MIL2 and joins the orchestra.
  jody.acceptInstr(*mill.loanOut());
  orch.addPlayer(jody);
  
  // morgan gets an instrument from the MIL2
  morgan.acceptInstr(*mill.loanOut());
  
  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  
  //Ralph joins the orchestra.
  orch.addPlayer(ralph);
  
  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  
  // bob gets an instrument from the MIL2
  bob.acceptInstr(*mill.loanOut());
  
  // ralph gets an instrument from the MIL2
  ralph.acceptInstr(*mill.loanOut());
  
  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  
  //Morgan joins the orchestra.
  orch.addPlayer(morgan);

  //The orchestra performs.
  cout << "orch performs\n";
  orch.play();
  

} // main


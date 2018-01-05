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
protected:
private:
};

class Trombone : public Brass {
public:
  Trombone( int size ) : Brass( size ) {}
  void makeSound() const {
    Brass::makeSound();
  }
protected:
private:
};

class String : public Instrument {
public:
  String( int pitch ) : pitch( pitch ) {}
  virtual void makeSound() const = 0;
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
protected:
private:
};

class Cello : public String {
public:
  Cello( int pitch ) : String( pitch ) {}
  void makeSound() const {
    String::makeSound();
  }
protected:
private:
};

class Percussion : public Instrument {
public:
  Percussion() {}
  virtual void makeSound() const = 0;
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
protected:
private:
};

class Cymbal : public Percussion {
public:
  Cymbal() {}
  void makeSound() const {
    Percussion::makeSound();
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
private:
    Instrument* instr;
};

class MILL {
public:
  void receiveInstr( Instrument& i ) {
    i.makeSound();
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
    for ( size_t i = inventory.size() - 1; i > 0; --i ) {
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





// PART ONE
int main() {

  cout << "Define some instruments ----------------------------------------\n";
  Drum drum;
  Cello cello(673);
  Cymbal cymbal;
  Trombone tbone(4);
  Trumpet trpt(12) ;
  Violin violin(567) ;
  
  // use the debugger to look at the mill
  cout << "Define the MILL ------------------------------------------------\n";
  MILL mill;
  
  cout << "Put the instruments into the MILL ------------------------------\n";
  cout << "\ttrpt, violin, tbone, drum, cello, cymbal" << endl;
  mill.receiveInstr(trpt);
  mill.receiveInstr(violin);
  mill.receiveInstr(tbone);
  mill.receiveInstr(drum);
  mill.receiveInstr(cello);
  mill.receiveInstr(cymbal);

  cout << endl;
  cout << "Daily test -----------------------------------------------------\n";
  //cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  cout << endl;
  
  cout << "Define some Musicians-------------------------------------------\n";
  Musician j;
  Musician jj;
  Musician q;

  cout << endl;
  cout << "TESTING: q.acceptInstr(*mill.loanOut());-----------------------\n";
  q.testPlay();	
  //cout << endl;
  q.acceptInstr(*mill.loanOut());
  //cout << endl;
  q.testPlay();
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  
  cout << endl << endl;
  
  q.testPlay();	
  cout << endl;
  cout << "Giving back instrument" << endl;
  mill.receiveInstr(*q.giveBackInstr());
  cout << "Loaning out 2 more instruments" << endl;
  j.acceptInstr(*mill.loanOut());
  q.acceptInstr(*mill.loanOut());
  cout << endl;
  cout << "q: ";
  q.testPlay();
  cout << endl;
  cout << "j: ";
  j.testPlay();
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  
  cout << endl;
  cout << "TESTING: mill.receiveInstr(*q.giveBackInstr()); -------------\n";
  // fifth
  mill.receiveInstr(*q.giveBackInstr());
  cout << "TESTING: mill.receiveInstr(*j.giveBackInstr()); -------------\n";
  mill.receiveInstr(*j.giveBackInstr());

  
  cout << endl;
  cout << "dailyTestPlay()" << endl;
  mill.dailyTestPlay();
  cout << endl;

  // ABSTRACT Classes cannot be Declared
  //Instrument i;
  //Brass b;
  //String s;
  //Percussion p;
  cout << endl;
  
}


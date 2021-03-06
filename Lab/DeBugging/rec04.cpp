/*
  Debugger Lab 4
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  9/29/17
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
using namespace std;

struct Complex {
  double real;
  double img;
};

/*
class PlainOldClass {
public:
  PlainOldClass() : x(-72) {}
  int getX() const { return x; }
  void setX( int val )  { x = val; }
private:
  int x;
};
*/

class PlainOldClass {
public:
  PlainOldClass() : x(-72) {}
  
  int getX() const { return x; }
  /*
  void setX( int x )  { x = x; } // HMMMM???
  // STILL -72 even after you change
  
  int getX( const PlainOldClass* const this = &poc ) const { return x; }
  void setX( PlainOldClass* const this = &poc, int x )  { x = x; } // Still HMMMM???
  */
  void setX( int x )  { this->x = x; } // No confusion!
private:
  int x;
};

class Colour {
public:
  Colour( const string& name, unsigned r, unsigned g, unsigned b )
    : name(name), r(r), g(g), b(b) {}
  void display() const {
    cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
  }
private:
  string   name;    // what we call this colour
  unsigned r, g, b; // red/green/blue values for displaying
};

class SpeakerSystem {
public:
  void vibrateSpeakerCones( unsigned signal ) const {

    cout << "Playing: " << signal << "Hz sound..." << endl;
    cout << "Buzz, buzzy, buzzer, bzap!!!\n";
  }
};

class Amplifier {
public:
  // One way to fix this is to not make spkrs constant
  // But this isn't the best way because you don't want to modify spkrs
  // void attachSpeakers( SpeakerSystem& spkrs )
  void attachSpeakers( const SpeakerSystem& spkrs )
  {
    if( attachedSpeakers )
      cout << "already have speakers attached!\n";
    else
      attachedSpeakers = &spkrs; // Problem because spkrs are const
  }
  void detachSpeakers()
  { attachedSpeakers = nullptr; }
  // should there be an "error" message if not attached?
  void playMusic( ) const {
    if( attachedSpeakers )
      attachedSpeakers -> vibrateSpeakerCones( 440 );
    else
      cout << "No speakers attached\n";
  }
private:
  // SpeakerSystem* attachedSpeakers = nullptr;

  // Another Solution is to make attachedSpeakers constant
  // This is better bc you can change the *attachedSpeakers
  const SpeakerSystem* attachedSpeakers = nullptr;
};

class Person {
public:
  // ALready moved in
  // Get roomate name wo roomate
  Person( const string& name ) : name(name) {}
  void movesInWith( Person& newRoomate ) {
    cout << this->getName() << " tries to move in with " << newRoomate.getName() << endl;
    if (!roomie && !newRoomate.roomie) {
      roomie = &newRoomate;        // now I have a new roomie
      newRoomate.roomie = this;    // and now they do too
    }
    else { // Edited if you already have a roomate
      cout << name << " already has a roomate, "
	   << this->getRoomiesName() << " would get jealous" << endl << endl;
    }
  }

  void moveOut() {
    if (roomie && roomie->roomie) {
      roomie->roomie = nullptr;
      roomie = nullptr;
    }
    else {
      cout << "Already Moved Out" << endl;
    }
  }
  
  string getName() const { return name; }
  // Don't need to use getName() below, just there for you to use in debugging.
  string getRoomiesName() const {
    return ( roomie != nullptr ? roomie->getName() : "No Roomate" );
  }
private:
  Person* roomie;
  string name;
};



int main () {
  /*
  int x;
  x = 10;
  cout << "x = " << x << endl;
  int* p;
  p = &x;
  cout << "p = " << p << endl;
  //p = 0x7fff5fbffb7c; // using the value from my Watch window

  cout << "p points to where " << *p << " is stored\n";
  cout << "*p contains " << *p << endl;

  *p = -2763;
  cout << "p points to where " << *p << " is      stored\n";
  cout << "*p now contains " << *p << endl;
  cout << "x now contains " << x << endl;

  int y(13);
  cout << "y contains " << y << endl;
  p = &y;
  cout << "p now points to where " << *p << " is stored\n";
  cout << "*p now contains " << *p << endl;
  *p = 980;
  cout << "p points to where " << *p << " is stored\n";
  cout << "*p now contains " << *p << endl;
  cout << "y now contains " << y << endl;

  int* q;
  q = p;
  cout << "q points to where " << *q << " is stored\n";
  cout << "*q contains " << *q << endl;

  double d(33.44);
  double* pD(&d);
  *pD = *p;
  *pD = 73.2343;
  *p  = *pD;
  *q  = *p;
  //  pD  = p;
  //p   = pD;

  int joe( 24 );
  const int sal( 19 );
  int*  pI;
  pI = &joe;
  *pI = 234;
  // pI = &sal; //ERROR
  *pI = 7623;
  
  const int* pcI;
  pcI = &joe;
  // *pcI = 234; // ERROR -> changing dereference for const
  pcI = &sal;
  // *pcI = 7623; // ERROR -> changing dereference for const

  //int* const cpI; // ERROR
  int* const cpI(&joe); // Pointer to constant memory
  // int* const cpI(&sal); //ERROR -> only one call
  // cpI = &joe; // ERROR -> can't change const
  *cpI = 234; // CAN change dereference
  // cpI = &sal; // ERROR -> can't change const
  *cpI = 7623; // CAN change dereference

  // const int* const cpcI; // ERROR nullptr
  // const int* const cpcI(&joe); // Warning if Unused
  // const int* const cpcI(&sal); // ERROR -> no redefinition
  // cpcI = &joe; //ERROR -> Can't change const
  // *cpcI = 234; // ERROR -> Can't change const pointer
  // cpcI = &sal;
  // *cpcI = 7623;

  Complex c = {11.23,45.67};
  Complex* pC(&c);
  //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
  cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
  cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

  PlainOldClass poc;
  PlainOldClass* ppoc( &poc );
  cout << ppoc->getX() << endl;
  ppoc->setX( 2837 );
  cout << ppoc->getX() << endl;

  int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
  *pDyn = 17;

  cout << "The " << *pDyn
       << " is stored at address " << pDyn
       << " which is in the heap\n";

  cout << pDyn << endl;
  delete pDyn;
  pDyn = nullptr;
  cout << "DELETED" << endl;
  cout << pDyn << endl;

  cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
  
  // cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

  // double* pDouble( nullptr );

  // cout << "Can we dereference nullptr?  " << *pDyn << endl;
  // cout << "Can we dereference nullptr?  " << *pDouble << endl;


  double* pTest = new double( 12 );
  delete pTest;
  pTest = nullptr;
  delete pTest; // safe

  short* pShrt = new short( 5 );
  delete pShrt;
  // delete pShrt;

  long jumper( 12238743 );
  delete jumper;
  long* ptrTolong( &jumper );
  delete ptrTolong;
  Complex cmplx;
  delete cmplx;

  vector<Complex*> complV; // can hold pointers to Complex objects
  Complex* tmpPCmplx;      // space for a Complex pointer
  for ( size_t ndx = 0 ; ndx < 3 ; ++ndx ) {
    tmpPCmplx = new Complex; // create a new Complex object on the heap
    tmpPCmplx->real = ndx;   // set real and img to be the
    tmpPCmplx->img  = ndx;   // value of the current ndx
    complV.push_back( tmpPCmplx ); // store the ADDRESS of the object in a vector or pointer to Complex
  }
  // display the objects using the pointers stored in the vector
  for ( size_t ndx = 0 ; ndx < 3 ; ++ndx ) {
    cout << complV[ ndx ]->real << endl;
    cout << complV[ ndx ]->img  << endl;
  }
  // release the heap space pointed at by the pointers in the vector
  for ( size_t ndx = 0 ; ndx < 3 ; ++ndx ) {
    delete complV[ ndx ];
  }
  // clear the vector
  complV.clear();    

  vector< Colour* > colours;
  string inputName;
  unsigned inputR, inputG, inputB;

  // fill vector with Colours from the file
  // this could be from an actual file but here we are using the keyboard instead of a file
  // (so we don't have to create an actual file)
  // do you remember the keystroke combination to indicate "end of file" at the keyboard?
  // somehow the while's test has to fail - from keyboard input
  // *** End of File Stroke on Mac = ctrl-d ***
  while ( cin >> inputName >> inputR >> inputG >> inputB ) {
    colours.push_back( new Colour(inputName, inputR, inputG, inputB) );
  }

  // display all the Colours in the vector:
  for ( size_t ndx = 0; ndx < colours.size(); ++ndx ) {
    colours[ndx]->display();
    cout << endl;
  }

  SpeakerSystem speak1;
  Amplifier amp1;
  SpeakerSystem speak2;
  amp1.attachSpeakers(speak1);
  speak1.vibrateSpeakerCones(17);
  amp1.attachSpeakers(speak2);
  speak1.vibrateSpeakerCones(17);
  speak2.vibrateSpeakerCones(27);
  amp1.playMusic();

  amp1.detachSpeakers();
  amp1.playMusic();
  amp1.attachSpeakers(speak2);
  speak1.vibrateSpeakerCones(17);
  speak2.vibrateSpeakerCones(27);
  */

  // write code to model two people in this world
  Person joeBob("Joe Bob"), billyJane("Billy Jane"), badPerson("Bad Person");
  // joeBob.movesInWith( nullptr );
  // now model these two becoming roommates
  cout << "Trying to get Joe Bob's Roomate: " << joeBob.getRoomiesName() << endl << endl;
  joeBob.movesInWith( billyJane );
  // did this work out?
  cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
  cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl << endl;

  joeBob.movesInWith( badPerson );

  joeBob.moveOut();
  cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
  cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;
  
}

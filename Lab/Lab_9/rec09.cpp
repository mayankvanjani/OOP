#include <iostream>
#include <string>
#include <vector>
using namespace std;

class PrintedMaterial {
public:
  PrintedMaterial( int numOfPages ) : numOfPages( numOfPages ) {}

  /*
  virtual void displayNumPages() const {
    cout << numOfPages << endl;
  }
  */
  
  virtual void displayNumPages() const = 0;
  
private:
  unsigned numOfPages;
};

void PrintedMaterial::displayNumPages() const {
  cout << numOfPages << endl;
}



class Magazine : public PrintedMaterial {
public:
  Magazine( int numOfPages ) : PrintedMaterial( numOfPages ) {}

  void displayNumPages() const {
    cout << "Inside Magazine Class" << endl;
    PrintedMaterial::displayNumPages();
  }
  
private:

};

class Book : public PrintedMaterial {
public:
  Book( int numOfPages ) : PrintedMaterial( numOfPages ) {}

private:

};

class TextBook : public Book {
public:
  TextBook( int numOfPages, int numOfIndexPages ) :
    Book( numOfPages ), numOfIndexPages( numOfIndexPages ) {}

  /*
  void displayNumPages() const {
    //    cout << numOfIndexPages << endl;
    //    cout << PrintedMaterial::displayNumPages() << endl;
    cout << "Textbook displayNumPages: ";
    PrintedMaterial::displayNumPages();
    cout  << "Textbook numOfIndexPages: " << numOfIndexPages << endl;
  }
  */

  void displayNumPages() const {
    cout << "Inside TextBook Class" << endl;
    cout << "Textbook displayNumPages: ";
    PrintedMaterial::displayNumPages();
    cout  << "Textbook numOfIndexPages: " << numOfIndexPages << endl;
  }

private:
  int numOfIndexPages;

};

class Novel : public Book {
public:
  Novel( int numOfPages ) : Book( numOfPages ) {}

  void displayNumPages() const {
    cout << "Inside Novel Class" << endl;
    PrintedMaterial::displayNumPages();
  }
  
private:

};

/*
void displayNumberOfPages( const PrintedMaterial pm ) {
  pm.displayNumPages();
}
*/

int main()
{

  TextBook t( 1, 10 );
  Novel n( 2 );
  Magazine m( 3 );

  /*
  cout << endl << "TextBook display:" << endl;
  t.displayNumPages();
  cout << endl << "Novel display:" << endl;
  n.displayNumPages();
  cout << endl << "Magazine display:" << endl;
  m.displayNumPages();
  cout << endl;

  // Slicing
  PrintedMaterial pm = t;
  cout << "PrintedMaterial pm = t;\n\tpm: ";
  pm.displayNumPages();
  cout << endl;

  // Pointers
  cout << "PrintedMaterial* pmPtr = &t;\npmPtr: ";
  PrintedMaterial* pmPtr = &t;
  pmPtr->displayNumPages();
  cout << endl;
  
  // When you dereference a pointer to an base class in an inheritance hierarchy 
  // which holds the address of an object of a type that was publicly derived 
  // from the base class, you get the BASE part of the derived class!

  //  Works when virtual is added to displayNumPages


  
  // displayNumPages outside PrintedMaterial
  cout << "t: ";
  displayNumberOfPages( t );
  cout << "n: ";
  displayNumberOfPages( n );
  cout << "m: ";
  displayNumberOfPages( m );
  */

  cout << endl << "TextBook display:" << endl;
  t.displayNumPages();
  cout << endl << "Novel display:" << endl;
  n.displayNumPages();
  cout << endl << "Magazine display:" << endl;
  m.displayNumPages();
  cout << endl;

  cout << "PrintedMaterial* pmPtr = &t;\npmPtr: ";
  PrintedMaterial* pmPtr = &t;
  pmPtr->displayNumPages();
  cout << endl;

  vector<PrintedMaterial*> allPrintedMaterials;
  allPrintedMaterials.push_back( &t );
  allPrintedMaterials.push_back( &n );
  allPrintedMaterials.push_back( &m );
  cout << "Looping" << endl;
  
  for( size_t index = 0; index < allPrintedMaterials.size(); ++index ) {
      allPrintedMaterials[index]->displayNumPages();
      cout << endl;
  }
  
  cout << endl;
}

/*
  Rec 6: Dynamic Arrays and Copy Control
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  10/13/17
*/

#include <string>
#include <iostream>
using namespace std;

class Position {
public:
  Position(const string& aTitle, double aSalary)
    : title(aTitle), salary(aSalary) {}
  
  const string& getTitle() const { return title; }
  double getSalary() const { return salary; }
  void changeSalaryTo(double d) { salary = d; }
  void display(ostream& os = cout) const {
    os << '[' << title << ',' << salary << ']';
  }
  
private:
  string title;
  double salary;
}; // class Position

class Entry {
public:
  Entry(const string& aName, unsigned aRoom, unsigned aPhone,
	Position& aPosition) 
    : name(aName), room(aRoom), phone(aPhone), pos(&aPosition) {}
  
  void display(ostream& os = cout) const {
    os << name << ' ' << room << ' ' << phone << ", ";
    pos->display(os);
  }
  
  const string& getName() const { return name; }
  const unsigned& getPhone() const { return phone; }
  
private:
  string name;
  unsigned room;
  unsigned phone;
  Position* pos;
}; // class Entry

class Directory {
public:

  // Default Constructor
  //  Directory d3;
  Directory() {}

  // Destructor
  // doNothing(d2);
  ~Directory() {
    cout << "Destructor..." << endl;
    for (size_t i = 0; i < size; ++i) {
      delete entries[i];
    }
    delete [] entries;
  }

  // Copy Constructor
  // Directory d2 = d;
  Directory( const Directory& rhs ) {
    size = rhs.size;
    capacity = rhs.capacity;

    entries = new Entry*[capacity];
    for (size_t i = 0; i < size; ++i) {
      Entry* tempEntry = new Entry( *(rhs.entries[i]) );
      entries[i] = tempEntry;
    }
  }

  // Assignment Operator
  // d3 = d2;
  Directory& operator=( const Directory& rhs ) {
    if (this != &rhs) {
      // Free up the old (destructor)
      for (size_t i = 0; i < size; ++i) {
	delete entries[i];
      }
      delete [] entries;
      // Allocate new
      entries = new Entry*[rhs.capacity];
      // Copy all the stuff
      size = rhs.size;
      capacity = rhs.capacity;
      for (size_t i = 0; i < size; ++i) {
	Entry* tempEntry = new Entry( *(rhs.entries[i]) );
	entries[i] = tempEntry;
      }
    }
    // Return ourselves
    return *this;
  }

  // getItem operator []
  // cout << d2["Carmack"] << endl;
  unsigned operator[]( const string& name ) const {
    for (size_t i = 0; i < size; ++i) {
      if ( entries[i]->getName() == name ) {
	return entries[i]->getPhone();
      }
    }
    return entries[0]->getPhone();
  }
  
  /*
  unsigned& operator[]( const string& name ) {
    for (size_t i = 0; i < size; ++i) {
      if ( entries[i]->getName() == name ) {
	return entries[i]->getPhone();
      }
    }
    return -1;
  }
  */
  
  void add(const string& name, unsigned room, unsigned ph, Position& pos) {
    if (size == capacity)	{
      // something is missing!!!  Add it!
      if ( entries == nullptr ) {
	entries = new Entry*[1];
	capacity = 1;
      }
      else {
	Entry** oldEntries = entries;
	entries = new Entry*[2*capacity];
	for (size_t i = 0; i < size; ++i) {
	  entries[i] = oldEntries[i];
	}
	delete [] oldEntries;
	capacity *= 2;
      }
      
    } // if
    
    entries[size] = new Entry(name, room, ph, pos);
    ++size;
  } // add
  
  void display(ostream& os = cout) const {
    for (size_t i = 0; i < size; ++i) {
      entries[i]->display(os);
      os << endl;
    }
    os << endl;
  }
  
private:	
  Entry** entries = nullptr;
  size_t size = 0;
  size_t capacity = 0;
}; // class Directory

void doNothing(Directory dir) { dir.display(); }

int main() {
  
  // Note that the Postion objects are NOT on the heap.
  Position boss("Boss", 3141.59);
  Position pointyHair("Pointy Hair", 271.83);
  Position techie("Techie", 14142.13);
  Position peon("Peonissimo", 34.79);
  
  // Create a Directory
  Directory d;
  d.add("Marilyn", 123, 4567, boss);
  //cout << "Before" << endl;
  cout << "Displaying d" << endl;
  d.display();
  //cout << "After" << endl;
  
  Directory d2 = d;	// What function is being used??
  d2.add("Gallagher", 111, 2222, techie);
  d2.add("Carmack", 314, 1592, techie);
  cout << "Displaying d2" << endl;
  d2.display();
  
  cout << "Calling doNothing\n";
  doNothing(d2);
  cout << "Back from doNothing\n";
  
  Directory d3;
  d3 = d2;
  //  cout << "Displaying d3 (same display as d2)" << endl;
  //  d3.display();
  
  // Should display 1592
  cout << d2["Carmack"] << endl;
  
} // main

/*
  Rec07: Seperate Compilation
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering

*/

#include <vector>
#include <string>
#include <iostream>

#include "Course.h"
#include "Student.h"
using namespace std;

namespace BrooklynPoly {

  Course::Course(const string& name) : name(name) {}

  string Course::getName() const { return name; }

  void Course::display() const {
    if ( students.size() != 0 ) {
      for ( Student* currStudent : students ) {
	cout << "\t" << currStudent->getName() << " " << endl;
      }
    }
    else { cout << "No Students" << endl; } 
  }

  void Course::cancelCourse() {
    for (size_t i = 0; i < students.size(); i++) {
      students[i]->cancelCourse( this );
    }
    students.clear();
  }

  void Course::addStudent( Student* newStudent ) {
    students.push_back( newStudent );
  }

}

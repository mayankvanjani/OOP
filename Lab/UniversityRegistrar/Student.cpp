/*
  Rec07: Seperate Compilation
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering

*/

#include <string>
#include <vector>
#include <iostream>

#include "Student.h"
#include "Course.h"
using namespace std;

namespace BrooklynPoly {

  Student::Student( const string& name ) : name(name) {}

  string Student::getName() const { return name; }

  void Student::addCourse( Course* newCourse ) {
    courses.push_back( newCourse );
  }
  
  void Student::cancelCourse( Course* remCourse ) {
    for (size_t i = 0; i < courses.size(); i++) {
      if (courses[i] == remCourse) {
	  courses[courses.size()-1] = remCourse;
	  courses.pop_back();
	}
      }
    }
  
  bool Student::noCourses() const { return courses.size() == 0; }

  void Student::changeName( const string& newName ) { name = newName; }

}

  

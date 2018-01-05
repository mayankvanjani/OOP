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
#include "Registrar.h"
using namespace std;

namespace BrooklynPoly {

  Registrar::Registrar() {}
  
  void Registrar::printReport() const {
    cout << "Students Without Courses:" << endl;
    for (size_t i = 0; i < students.size(); ++i) {
      if ( students[i]->noCourses() ) {
	//if ( students[i]->numCourses() == 0 ) {
	cout << students[i]->getName() << "\tCourses: None" << endl;
      }
    }
    
    cout << "Courses and Enrolled Students:" << endl;
    for ( Course* currCourse : courses ) {
      cout << currCourse->getName() << endl;
      currCourse->display();
    }

    if ( students.size() == 0 && courses.size() == 0 ) {
      cout << "No Students or Corses" << endl;
    }
    else if (students.size() == 0) {
      cout << "No Students" << endl;
    }
    else if (courses.size() == 0) {
      cout << "No Courses" << endl;
    }

    cout << endl;
  }

  void Registrar::addCourse( const string& name ) {
    courses.push_back( new Course(name) );
  }
  void Registrar::addStudent( const string& name ) {
    students.push_back( new Student(name) );
  }

  size_t Registrar::findCourse( const string& courseName ) const {
    for (size_t i = 0; i < courses.size(); ++i) {
      if (courses[i]->getName() == courseName) {
	return i;
      }
    }
    return courses.size();
  }

  size_t Registrar::findStudent( const string& studentName ) const {
    for (size_t i = 0; i < students.size(); ++i) {
      if (students[i]->getName() == studentName) {
	return i;
      }
    }
    return students.size();
  }
  
  void Registrar::enrollStudentInCourse( const string& studentName,
					 const string& courseName ) {
    
    size_t courseIndex = findCourse( courseName );
    size_t studentIndex = findStudent( studentName );
    if ( courseIndex != courses.size() && studentIndex != students.size() ) {
      courses[courseIndex]->addStudent( students[studentIndex] );
      students[studentIndex]->addCourse( courses[courseIndex] );
    }
    
    if ( courseIndex == courses.size() ) {
      cout << courseName << " Was Not Found\t";
    }

    if ( studentIndex == students.size() ) {
      cout << studentName << " Was Not Found";
    }
    cout << endl;
  }

  void Registrar::cancelCourse( const string& name ) {
    size_t index = findCourse( name );
    courses[index]->cancelCourse();
    courses[courses.size()-1] = courses[index];
    courses.pop_back();
  }

  void Registrar::purge() {
    if (courses.size() > 0) {
      for (size_t i = 0; i < courses.size(); i++) {
	delete courses[i];
	courses.pop_back();
      }
    }
    
    if (students.size() > 0) {
      for (size_t i = 0; i < students.size(); i++) {
	delete students[i];
	students.pop_back();
      }
    }
    
  }

  void Registrar::changeStudentName( const string& name, const string& newName ) {
    size_t index = findStudent( name );
    students[index]->changeName( newName );
  }

}


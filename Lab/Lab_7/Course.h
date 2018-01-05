/*
  Rec07: Seperate Compilation
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering

*/

#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include "Student.h"

namespace BrooklynPoly {

  class Student;
  
  class Course {

  public:
    Course( const std::string& name );
    std::string getName() const;
    void addStudent( Student* newStudent );
    void display() const;
    void cancelCourse();    

  private:
    std::string name;
    std::vector<Student*> students;

  };
  
}

#endif /* COURSE_H */

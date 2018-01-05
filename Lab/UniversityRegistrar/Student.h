/*
  Rec07: Seperate Compilation
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering

*/

#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include "Course.h"

namespace BrooklynPoly {

  class Course;
  
  class Student {

  public:
    Student( const std::string& name );
    std::string getName() const;
    void addCourse( Course* newCourse );
    void cancelCourse( Course* remCourse );
    bool noCourses() const;
    void changeName ( const std::string& newName );
    
  private:
    std::string name;
    std::vector<Course*> courses;

  };
  
}

#endif /* STUDENT_H */

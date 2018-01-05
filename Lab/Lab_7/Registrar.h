/*
  Rec07: Seperate Compilation
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering

*/

#ifndef REGISTRAR_H
#define REGISTRAR_H

#include <iostream>
#include <vector>
#include <string>

namespace BrooklynPoly {

  class Student;
  class Course;
  
  class Registrar {

  public:
    Registrar();
    void printReport() const;
    void addCourse( const std::string& name );
    void addStudent( const std::string& name );
    void enrollStudentInCourse( const std::string& studentName, const std::string& courseName );
    void cancelCourse( const std::string& name );
    size_t findCourse( const std::string& courseName ) const;
    size_t findStudent( const std::string& StudentName ) const;
    void purge();
    
    void changeStudentName( const std::string& name, const std::string& newName );
    /*
    void dropStudentFromCourse();
    void removeStudent();
    */


  private:
    std::vector<Student*>students;
    std::vector<Course*>courses;
    
  };

  
}

#endif /* REGISTRAR_H */

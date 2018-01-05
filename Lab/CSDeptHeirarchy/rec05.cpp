/*
  Rec 5: Tandon CS Lab Administration
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  10/6/17
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

class Section {

  class StudentLabRecord {
  public:
    // StudentLabRecord Constructor
    StudentLabRecord( const string& studentName ) : studentName(studentName) {
      for (int i = 0; i < 14; ++i) {
	grades.push_back(-1);
      }
    }
    /*
    StudentLabRecord( const StudentLabRecord& lab ) :
      studentName(lab.studentName), grades(lab.grades) {}
    */
    // Getters, Setters, and Display
    string getName() const {
      return studentName;
    }
    vector<int> getAllGrades() const {
      return grades;
    }
    void setAllGrades( vector<int> newGrades ) {
      grades = newGrades;
    }
    void changeGrade (int grade, int week) {
      grades[week-1] = grade;
    }
    void display() const {
      cout << "Name: " << studentName << ", Grades:\t";
      for (int grade : grades) { cout << grade << " "; }
      cout << endl;
    }

  private:
    const string studentName;
    vector<int> grades;
  };
  
  class TimeSlot {
  public:
    // TimeSlot Constructor
    TimeSlot ( const string& day, int hour ) : day(day), hour(hour) {}
    // TimeSlot Copy Constructor
    TimeSlot ( const TimeSlot& slot ) : day(slot.day), hour(slot.hour) {}
    string getDay() const { return day; }
    unsigned getHour() const { return hour; }

  private:
    const string day;
    const unsigned hour;

  };

public:
  // Section Constructor
  Section (const string& secNum, const string& day, int hour) :
    sectionNum(secNum), time(day, hour) {}

  // Section Destructor
  ~Section() {
    cout << "Section " << sectionNum << " is being deleted" << endl;
    for ( size_t i = 0; i < group.size(); ++i ) {
      cout << "Deleting: " << group[i]->getName() << endl;
      delete group[i];
    }
    group.clear();
  }

  // Section Copy Constructor
  Section (const Section& rhs) : sectionNum(rhs.sectionNum), time(rhs.time) {
    for (size_t i = 0; i < rhs.group.size(); ++i) {
      //group[i]->setAllGrades( rhs.group[i]->getAllGrades() );
      StudentLabRecord* newLab = new StudentLabRecord( *(rhs.group[i]) );
      newLab->setAllGrades( rhs.group[i]->getAllGrades() );
      group.push_back( newLab );
      // group.push_back( new StudentLabRecord( *(rhs.group[i]) ) );
    }
  }

  // Section Display
  void display() const {
    cout << "Section: " << sectionNum << ", Time Slot: [Day: " <<
      time.getDay() << ", Start Time: ";
    if (time.getHour() < 12) { cout << time.getHour() << "am"; }
    else { cout << (time.getHour() % 12) << "pm"; }
    cout << "] Students: ";
    if ( group.size() == 0) {
      cout << "None" << endl;
    }
    else {
      cout << endl;
      for ( StudentLabRecord* student : group ) {
	(*student).display();
      }
    }
  }

  // Section's Add Student (modify group)
  void addStudent( const string& studentName ) {
    StudentLabRecord* tempStudent = new StudentLabRecord(studentName);
    group.push_back( tempStudent );    
  }

  // Changes Grades by asking StudentLabRecord
  void addGrade( const string& name, int grade, int week ) {
    for (size_t i = 0; i < group.size(); ++i ) {
      if ( group[i]->getName() == name ) {
	group[i]->changeGrade(grade, week);
      }
    }
  }
  
private:
  const string sectionNum;
  const TimeSlot time;
  vector<StudentLabRecord*> group;
};


class LabWorker {
public:
  // LabWorker Constructor
  LabWorker (const string& name) : name(name), haveSec(false), sec(nullptr) {}

  // If you don't have a section, assign
  bool addSection(  Section& section ) {
    if (!haveSec) {
      haveSec = true;
      sec = &section;
      return true;
    }
    return false;
  }

  // Use section's changeGrade
  void addGrade( const string& name, int grade, int week ) {
    sec->addGrade(name, grade, week);
  }

  // LabWorker's Display
  void display() const {
    if (!haveSec) {
      cout << name << " does not have a section" << endl;
    }
    else {
      cout << name << " has ";
      sec->display();
    }
  }

private:
  string name;
  bool haveSec;
  Section* sec;

};





// Test code
void doNothing(Section sec) { sec.display(); }

int main() {

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    secA2.display();

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    secA2.display();

    /*
    cout << "TESTING" << endl;
    Section secA2copy(secA2);
    cout << "First" << endl;
    secA2.display();
    cout << "Second" << endl;
    secA2copy.display();
    */

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    moe.display();

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    moe.display();

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    jane.display();

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);  
    moe.addGrade("Paul", 19, 1);  
    moe.addGrade("George", 16, 1);  
    moe.addGrade("Ringo", 7, 1);  
    moe.display();

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);  
    moe.addGrade("Paul", 20, 3);  
    moe.addGrade("Ringo", 0, 3);  
    moe.addGrade("George", 16, 3);  
    moe.display();

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, then make sure the following call works\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";

} // main

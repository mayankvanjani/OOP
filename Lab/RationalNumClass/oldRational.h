/*
  Rec 8: Rational Number Operator Overloading
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  10/27/17
*/

#ifndef _RATIONAL_H
#define _RATIONAL_H

#include <string>

namespace CS2124 {

  class Rational {
  public:
    friend ostream& operator<<( ostream& os, const Rational& rhs );
    friend ostream& operator>>( const Rational& rhs, ostream& os );

    Rational& oeprator+=( const Rational& rhs );

    bool operator==( const Ratinal& rhs );

    Rational& operator++();
    Rational operator++(int);

    explicit operator bool();

    /*
    friend ostream& operator<<(ostream& os, const Rational& rhs);
  Rational(const string& name, int height) : name(name), height(height);
    */
  private:
    int numerator, denominator;
    
  }; // Close Rational

  
} // Close CS2124

#endif

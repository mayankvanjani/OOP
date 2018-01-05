/*
  Rec 8: Rational Number Operator Overloading
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  10/27/17
*/

#include <iostream>

#ifndef _RATIONAL_H
#define _RATIONAL_H

namespace CS2124 {

  class Rational {
    
    // Friends
    friend void normalize( Rational& rhs );
    
    friend std::ostream& operator<<( std::ostream& os, const Rational& rhs );
    
    friend std::istream& operator>>( std::istream& is, Rational& rhs );
    
    friend bool operator==( const Rational& lhs, const Rational& rhs );
    
    
  public:
    Rational();
    Rational( int val );
    
    //Members
    Rational& operator+=( const Rational& rhs );
    
    Rational& operator++();
    
    Rational operator++(int);
    
    explicit operator bool() const;
    
    
  private:
    int numerator, denominator;  
    
  }; // Close Rational
  
  // Non-Member Non Friends
  Rational operator+(const Rational& lhs, const Rational& rhs);
  
  bool operator!=( const Rational& lhs, const Rational& rhs );
  
  Rational& operator--( Rational& rhs );

  Rational operator--( Rational& rhs, int );

} // Close CS2124

#endif

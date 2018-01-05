/*
  Rec 8: Rational Number Operator Overloading
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  10/27/17
*/

#include "Rational.h"

#include <iostream>
#include <string>
using namespace std;

namespace CS2124 {

  // Friends
  void normalize( Rational& rhs ) {
    int x = rhs.numerator;
    int y = rhs.denominator;
    while (y != 0) {
      int temp = x % y;
      x = y;
      y = temp;
    }
    int divisor = x;
    //    cout << divisor;
    rhs.numerator /= divisor;
    rhs.denominator /= divisor;
    if ( rhs.denominator < 0 ) {
      rhs.numerator *= -1;
      rhs.denominator *= -1;
    }
    
  }
    
  ostream& operator<<( ostream& os, const Rational& rhs ) {
    if ( rhs.denominator == 1 ) {
      os << rhs.numerator;
    }
    else {
      os << rhs.numerator << "/" << rhs.denominator;
    }
    return os;
  }
  
  istream& operator>>( istream& is, Rational& rhs ) {
    is >> rhs.numerator >> rhs.denominator;
    if ( rhs.denominator == 0 ) {
      cout << "Cannot Have 0 in the Denominator!" << endl;
      while ( rhs.denominator == 0 ) {
	cout << "Try Again: ";
	is >> rhs.denominator;
      }
    }
    normalize( rhs );
    return is;
  }
  
  bool operator==( const Rational& lhs, const Rational& rhs ) {
    return (lhs.numerator == rhs.numerator &&
	    lhs.denominator == rhs.denominator);
  }
  
  Rational::Rational() : numerator(0), denominator(0) {}
  Rational::Rational( int val ) : numerator(val), denominator(1) {}
    
  //Members
  Rational& Rational::operator+=( const Rational& rhs ) {
    if ( denominator == rhs.denominator ) {
      numerator += rhs.numerator;
    }
    else {
      int multFirst = rhs.denominator;
      int multSecond = denominator;
      denominator *= rhs.denominator;
      numerator = (numerator*multFirst) + (rhs.numerator*multSecond);
    }
    normalize( *this );
    return *this;
  }
  
  Rational& Rational::operator++() {
    numerator += denominator;
    normalize( *this );
    return *this;
  }
  
  Rational Rational::operator++(int) {
    Rational original (*this);
    numerator += denominator;
    normalize( *this );
    return original;
  }
    
  Rational::operator bool() const {
    return numerator != 0;
  }
    
  // Non-Member Non Friends
  Rational operator+(const Rational& lhs, const Rational& rhs) {
    Rational result(lhs);
    result += rhs;
    normalize( result );
    return result;
  }
  
  bool operator!=( const Rational& lhs, const Rational& rhs ) {
    return !( lhs == rhs );
  }
  
  Rational& operator--( Rational& rhs ) {
    Rational change(-1);
    rhs += change;
    normalize( rhs );
    return rhs;
  }
  
  Rational operator--( Rational& rhs, int ) {
    Rational original(rhs);
    Rational change(-1);
    rhs += change;
    normalize( rhs );
    return original;
  }
  
} // Close CS2124

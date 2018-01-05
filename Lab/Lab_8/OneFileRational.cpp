/*
  Rec 8: Rational Number Operator Overloading
  Mayank Vanjani
  CS2114
  NYU Tandon School of Engineering
  10/27/17
*/

#include <iostream>
#include <string>
using namespace std;

class Rational {

  // Friends
  friend void normalize( Rational& rhs ) {
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
  
  friend ostream& operator<<( ostream& os, const Rational& rhs ) {
    os << rhs.numerator << "/" << rhs.denominator;
    return os;
  }
  
  friend istream& operator>>( istream& is, Rational& rhs ) {
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
  
  friend bool operator==( const Rational& lhs, const Rational& rhs ) {
    return (lhs.numerator == rhs.numerator &&
	    lhs.denominator == rhs.denominator);
  }
  
public:
  Rational() : numerator(0), denominator(0) {}
  Rational( int val ) : numerator(val), denominator(1) {}

  //Members
  Rational& operator+=( const Rational& rhs ) {
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
  
  Rational& operator++() {
    numerator += denominator;
    normalize( *this );
    return *this;
  }

  Rational operator++(int) {
    Rational original (*this);
    numerator += denominator;
    normalize( *this );
    return original;
  }
  
  explicit operator bool() const {
    return numerator != 0;
  }
  
private:
  int numerator, denominator;  

}; // Close Rational

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





int main() {
  Rational a, b;

  cout << "Input two rational numbers.\n";  
  cout << "a: " << endl;
  cin >> a;
  cout << "b: " << endl;
  cin >> b;
  cout << endl;
  
  Rational one(1);
  cout << "a = " << a << endl;
  cout << "b = " << b << endl;
  cout << "one = " << one << endl;
  cout << "a += b: " << (a += b) << endl;// Implement as member
  cout << "a = " << a << endl;
  cout << endl;
  
  // Implement as non-member, but not a friend
  cout << "a + one: " << (a + one) << endl;
  cout << "a == one: " << boolalpha << (a == one) << endl;
  
  // How does this manage to work?
  // It does NOT require writing another == operator.
  cout << "1 == one: " << boolalpha << (1 == one) << endl;
  
  // Do not implement as friend.
  cout << "a != one: " << boolalpha << (a != one) << endl;
  cout << endl;
  
  cout << "a = " << a << endl;
  cout << "++a = " << (++a) << endl;
  cout << "a = " << a << endl;
  cout << "a++ = " << (a++) << endl;
  cout << "a = " << a << endl;
  cout << endl;
  
  cout << "--a = " << (--a) << endl;
  cout << "a = " << a << endl;
  cout << "a-- = " << (a--) << endl;
  cout << "a = " << a << endl;
  cout << endl;
  
  cout << "++ ++a = " << (++ ++a) << endl;
  cout << "a = " << a << endl;
  cout << "-- --a = " << (-- --a) << endl;
  cout << "a = " << a << endl;
  cout << endl;
  
  cout << "a++ ++ = " << (a++ ++) << endl;
  cout << "a = " << a << endl;
  cout << endl;
  
  // Even though the above example, (a++ ++), compiled, the
  // following shouldn't.
  // But some compiler vendors might let it...  Is your compiler
  // doing the right thing?
  // cout << "a-- -- = " << (a-- --) << endl;
  // cout << "a = " << a << endl;
  // DOESNT ALLOW COMPILATION

  if (Rational(1)) {
    cout << "1 is true" << endl;
  } else {
    cout << "1 is false" << endl;
  }
  if (Rational(0)) {
    cout << "0 is true" << endl;
  } else {
    cout << "0 is false" << endl;
  }
  cout << endl;

}




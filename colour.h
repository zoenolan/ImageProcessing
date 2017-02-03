#ifndef colour_h
#define colour_h

/******************************************************************************
 Colour class

 NAME:colour.h
 DATE:10/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include <iostream.h>

class TColour
{
 private:
   // Colour stored as bytes to save space in large pixmaps
   unsigned char _Red   ;
   unsigned char _Green ;
   unsigned char _Blue  ;

   // read and write functions
   istream &Read (istream &In) ;
   ostream &Write (ostream &Out) const ;

 public:
   // Constructors
   TColour () ;
   TColour (double Red,double Green,double Blue) ;
   TColour (unsigned char Red, unsigned char Green, unsigned char Blue) ;
   TColour (int Red, int Green, int Blue) ;

   // Selectors
   double Red() const ;
   double Green() const;
   double Blue() const;

   // Modifiers
   SetRed(double Red) ;
   SetGreen (double Green) ;
   SetBlue (double Blue) ;

   // scale colours
   TColour operator* (const double Scalar) const ;

   // add colours
   TColour operator+ (const TColour Colour) const ;

   // streaming operators
   friend istream &operator>>(istream &In, TColour &Colour);
   friend ostream &operator<<(ostream &Out,const TColour &Colour) ;
} ;
#endif

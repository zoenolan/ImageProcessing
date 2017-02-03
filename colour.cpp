/*****************************************************************************
 Colour Class

 NAME:colour.cpp
 DATE:10/11/1996
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include "colour.h"

// Constructor
TColour::TColour ()
{
 _Red=0 ;
 _Green=0 ;
 _Blue=0 ;
}

// Constructor
TColour::TColour(unsigned char Red,unsigned char Green,unsigned char Blue)
{
 _Red=Red ;
 _Green=Green ;
 _Blue=Blue ;
}

// Constructor
TColour::TColour(int Red,int Green,int Blue)
{
 _Red=Red ;
 _Green=Green ;
 _Blue=Blue ;
}
// Constructor
TColour::TColour(double Red,double Green,double Blue)
{
 // limit the value to 1.0
 if (Red>1.0)
   {
    _Red=255 ;
   }
 else
   {
    _Red=(unsigned char)(Red*255) ;
   }

 // Limit value to one
 if (Green>1.0)
   {
    _Green=255 ;
   }
 else
   {
    _Green=(unsigned char)(Green*255) ;
   }

 // Limit value to one
 if (Blue>1.0)
   {
    _Blue=255 ;
   }
 else
   {
    _Blue=(unsigned char)(Blue*255) ;
   }
}

// return the red part of the colour
double TColour::Red() const
{
 return (_Red/255.0) ;
}

// return the green part of the colour
double TColour::Green() const
{
 return (_Green/255.0) ;
}

// return the blue part of the colour
double TColour::Blue() const
{
 return (_Blue/255.0) ;
}

// set the red part of the colour
TColour::SetRed(double Red)
{
 if (Red>1.0)
   {
    _Red=255 ;
   }
 else
   {
    _Red=(unsigned char)(Red*255) ;
   }
}

// set the green part of the colour
TColour::SetGreen(double Green)
{
 if (Green>1.0)
   {
    _Green=255 ;
   }
 else
   {
    _Green=(unsigned char)(Green*255) ;
   }
}

// set the blue part of the colour
TColour::SetBlue(double Blue)
{
 if (Blue>1.0)
   {
    _Blue=255 ;
   }
 else
   {
    _Blue=(unsigned char)(Blue*255) ;
   }
}

// * a colour by some amount
TColour TColour::operator* (const double Scalar) const
{
 TColour NewColour((*this).Red()*Scalar,
                   (*this).Green()*Scalar,
                   (*this).Blue()*Scalar) ;

 return (NewColour) ;

}


//  add colours together
TColour TColour::operator+ (const TColour Colour) const
{
 TColour NewColour ;

 NewColour.SetRed((*this).Red()+Colour.Red()) ;
 NewColour.SetGreen((*this).Green()+Colour.Green());
 NewColour.SetBlue((*this).Blue()+Colour.Blue()) ;

 return (NewColour) ;

}

// function to input a colour
istream &TColour::Read (istream &In)
{
 char Comma ; // delimter for the vector items
 double Red,Green,Blue ;

 // read in the colour
 In>>Red>>Comma>>Green>>Comma>>Blue ;

 (*this)=TColour(Red,Green,Blue) ;

 // return the stream
 return In ;
}

// function to output a colour
ostream &TColour::Write (ostream &Out) const
{
 // write out the colour
 Out<<(*this).Red()<<','<<(*this).Green()<<','<<(*this).Blue() ;

 // return the stream
 return Out ;
}

// function to read in a vector
istream &operator>>(istream &In,TColour &Colour)
{
 // input a colour
 return Colour.Read(In) ;
}

ostream &operator<<(ostream &Out,const TColour &Colour)
{
 // output the colour
 return Colour.Write(Out) ;

}

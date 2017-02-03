/*****************************************************************************
 Pixmap Class

 NAME:pixmap.cpp
 DATE:10/11/1196
 AUTHOR: Z.A. Nolan

******************************************************************************/

// include the header
#include "pixmap.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "aux.h"

// Constructor
TPixmap::TPixmap()
{
 _Width=-1 ;
 _Height=-1 ;
 _Pixmap=NULL ;
}

// Constructor
TPixmap::TPixmap(int Width,int Height)
{
 _Width=Width ;
 _Height=Height ;
 _Pixmap=new TColour[_Height*_Width] ;
 (*this).Clear() ;
}

// Destructor
TPixmap::~TPixmap()
{
 // delete the pixmap
 delete _Pixmap ;
}

// return the colour at pixel X,Y
TColour TPixmap::operator() (int Width,int Height) const
{
 return (_Pixmap[Width+(_Width*(_Height-Height-1))]) ;
}

// set the colour at pixel X,Y
TColour &TPixmap::operator() (int Width,int Height)
{
 return (_Pixmap[Width+(_Width*(_Height-Height-1))]) ;
}

// clear the screen to black
TPixmap::Clear()
{
 int I,J ; // loop counters
 TColour Black(0.0,0.0,0.0) ; // Black for the clear loop

 // clear the screen
 for (I=0;I<_Height;I++)
   {
    for (J=0;J<_Width;J++)
      {
       _Pixmap[J+I*_Width]=Black ;
      }
   }
}

// clear the screen to the colour given
TPixmap::Clear(TColour Colour)
{
 int I,J ; // loop counters

 // clear the screen
 for (I=0;I<_Height;I++)
   {
    for (J=0;J<_Width;J++)
      {
       _Pixmap[J+I*_Width]=Colour ;
      }
   }
}

// output a ppm file
ostream &TPixmap::StreamPPMOut (ostream &Out)
{
 int X,Y ; // loop counters

 //write header
 Out<<"P3\n"<<_Width<<' '<<_Height<<' '<<255<<'\n' ;
 // save image
 for ( Y = 0 ; Y < _Height ; Y++ )
   {
    for ( X = 0; X < _Width; X++ )
       {
        Out<<(*this)(X,Y).Red()*255<<' '
           <<(*this)(X,Y).Green()*255<<' '
           <<(*this)(X,Y).Blue()*255<<'\n' ;
       }
   }

 // return the stream
 return Out ;
}

TPixmap::SetSize(int X,int Y)
{
 delete _Pixmap ;
 _Height=Y ;
 _Width=X ;
 _Pixmap=new TColour[_Height*_Width] ;
}

TPixmap::Display()
{
 glDrawPixels(_Width,_Height,GL_RGB,GL_UNSIGNED_BYTE,_Pixmap) ;
}

int TPixmap::Width()
{
 return _Width ;
}

int TPixmap::Height()
{
 return _Height ;
}

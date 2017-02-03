#ifndef pixmap_h
#define pixmap_h

/******************************************************************************
 Pixmap Class

 NAME:pixmap.h
 DATE:10/11/1196
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include <iostream.h>
#include "colour.h"
#include "mask.h"

class TPixmap
{
 private:
   int _Width ;
   int _Height ;
   TColour *_Pixmap ;
   int _MapType ;

 public:
   // constructors
   TPixmap () ;
   TPixmap (int Width,int Height) ;

   // Destructor
   ~TPixmap () ;

   // Selectors
   TColour operator() (int Width,int Height) const;

   // Modifiers
   TColour &operator() (int Width,int Height) ;
   Clear () ;
   Clear (TColour Colour) ;
   int Width() ;
   int Height() ;

   // display function
   Display() ;

   // Input/output
   Load(const char *FileName) ;
   Save(const char *FileName) ;

   // operations
   Greyscale() ;
   Threshold(double Level) ;

   // greyscale operations
   Invert();
   Median(int XSize,int YSize);
   Convolute(TMask &Mask);

   // Binary operations
   Erode(int CentreX,int CentreY) ;
   Dilate(int CentreX,int CentreY) ;

} ;

#endif

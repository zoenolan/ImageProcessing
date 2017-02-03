#ifndef mask_h
#define mask_h

/******************************************************************************
 Mask Class

 NAME:mask.h
 DATE:10/4/1197
 AUTHOR: Z.A. Nolan

******************************************************************************/

#include <iostream.h>

class TMask
{
 private:
   int _Width ;
   int _Height ;
   int _CentreX ;
   int _CentreY ;
   double *_Mask ;

 public:
   // constructors
   TMask () ;

   // Destructor
   ~TMask () ;

   // Selectors
   double operator() (int Width,int Height) const;

   // Modifiers
   double &operator() (int Width,int Height) ;

   int Width() ;
   int Height() ;
   int CentreX() ;
   int CentreY() ;

   // Input/output
   Load(const char *FileName) ;


} ;

#endif

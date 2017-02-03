/*****************************************************************************
 Mask Class

 NAME:mask.cpp
 DATE:10/4/1197
 AUTHOR:I.A. Nolan

******************************************************************************/

// include the header
#include "mask.h"
#include <fstream.h>

// Constructor
TMask::TMask()
{
 _Width=-1 ;
 _Height=-1 ;
 _Mask=NULL ;

}

// Destructor
TMask::~TMask()
{
 // delete the mask
 delete _Mask ;
}


// return the value at position X,Y
double TMask::operator() (int Width,int Height) const
{
 return (_Mask[Width+(_Width*(_Height-Height-1))]) ;
}

// set the value at position X,Y
double &TMask::operator() (int Width,int Height)
{
 return (_Mask[Width+(_Width*(_Height-Height-1))]) ;
}

int TMask::Width()
{
 return _Width ;
}

int TMask::Height()
{
 return _Height ;
}

int TMask::CentreX()
{
 return _CentreX ;
}

int TMask::CentreY()
{
 return _CentreY ;
}

// load from a .mask file
TMask::Load(const char *FileName)
{
 int X,Y ; // loop counters
 char LargeBuffer[4] ;
 double Temp ;

 ifstream In (FileName);

 //read header
 In>>LargeBuffer ;

 // read size
 In>>_Width ;
 In>>_Height;

 // read centre
 In>>_CentreX ;
 In>>_CentreY ;

 delete _Mask ;

 _Mask=new double[_Height*_Width] ;

 // read in the  mask
 for ( Y = 0 ; Y < _Height ; Y++ )
   {
    for ( X = 0; X < _Width; X++ )
       {
        In>>Temp ;
        (*this)(X,Y)=Temp ;
       }
   }
}

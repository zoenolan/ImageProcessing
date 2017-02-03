/*****************************************************************************
 Pixmap Class

 NAME:pixmap.cpp
 DATE:10/11/1196
 AUTHOR: Z.A. Nolan

******************************************************************************/

// include the header
#include "pixmap.h"
#include <fstream.h>

#include <GL/gl.h>
#include <GL/glu.h>
#include "aux.h"

// Constructor
TPixmap::TPixmap()
{
 _Width=-1 ;
 _Height=-1 ;
 _Pixmap=NULL ;

 // set the map to NULL
 _MapType=-1 ;
}

// Constructor
TPixmap::TPixmap(int Width,int Height)
{
 _Width=Width ;
 _Height=Height ;
 _Pixmap=new TColour[_Height*_Width] ;
 (*this).Clear() ;
 // set the map to RGB
 _MapType=0 ;
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

int TPixmap::Width()
{
 return _Width ;
}

int TPixmap::Height()
{
 return _Height ;
}

// save to a PPM file
TPixmap::Save(const char *FileName)
{
 int X,Y ; // loop counters

 ofstream Out (FileName);

 //write header
 Out<<"P3"<<endl<<_Width<<' '<<_Height<<' '<<255<<endl ;
 // save image
 for ( Y = 0 ; Y < _Height ; Y++ )
   {
    for ( X = 0; X < _Width; X++ )
       {
        Out<<(*this)(X,Y).Red()*255<<' '
           <<(*this)(X,Y).Green()*255<<' '
           <<(*this)(X,Y).Blue()*255<<endl ;
       }
   }
}

// load to a PPM file
TPixmap::Load(const char *FileName)
{
 int X,Y ; // loop counters
 char LargeBuffer[3] ;
 char SmallBuffer[2] ;
 char Buffer ;
 int TempR,TempG,TempB ;

 ifstream In (FileName);

 //read header
 In>>SmallBuffer ;

 // read size
 In>>_Width ;
 In>>_Height>>LargeBuffer>>Buffer ;


 delete _Pixmap ;

 _Pixmap=new TColour[_Height*_Width] ;
 (*this).Clear() ;
 _MapType=0 ;

 // readin the  image
 for ( Y = 0 ; Y < _Height ; Y++ )
   {
    for ( X = 0; X < _Width; X++ )
       {
        In>>TempR>>TempG>>TempB ;
        (*this)(X,Y)=TColour(TempR,TempG,TempB) ;
       }
   }
}

TPixmap::Greyscale()
{
 int Y,X ;
 double Temp ;

 for ( Y = 0 ; Y < _Height ; Y++ )
   {
    for ( X = 0; X < _Width; X++ )
      {
       // just take the simple mean
       Temp=((*this)(X,Y).Red()+(*this)(X,Y).Green()+(*this)(X,Y).Blue())/3 ;
       (*this)(X,Y)=TColour(Temp,Temp,Temp) ;

      }
   }

 // set the map to greyscale
 _MapType=1 ;
}

TPixmap::Threshold(double Level)
{
 int Y,X ;

 // check to see if it is a greyscale image
 if (_MapType==1)
   {
    for ( Y = 0 ; Y < _Height ; Y++ )
      {
       for ( X = 0; X < _Width; X++ )
         {
          // just set the pixel black or white depending
	  // if it is greater or less than the threshold
          if ((*this)(X,Y).Red()<Level)
            {
             (*this)(X,Y)=TColour(0.0,0.0,0.0) ;
	    }
          else
            {
             (*this)(X,Y)=TColour(1.0,1.0,1.0) ;
            }
         }
     }
    // set the map to bitmap
    _MapType=2 ;
   }
}

// invert an image

TPixmap::Invert()
{
 double Temp ;
 int X,Y ;

 // check to see if it is a greyscale image
 if (_MapType==1)
   {
    for ( Y = 0 ; Y < _Height ; Y++ )
      {
       for ( X = 0; X < _Width; X++ )
         {
          // just invert the pixel
          Temp=(*this)(X,Y).Red() ;
          Temp=1.0-Temp ;
          (*this)(X,Y)=TColour(Temp,Temp,Temp) ;
	 }
     }

   }
}

// invert an image

TPixmap::Median(int XSize,int YSize)
{
 TColour *TempMap ;
 double *Temp ;
 double Swap,Value ;
 int X,Y ;
 int FilterX,FilterY ;

 TempMap=new TColour [_Height*_Width] ;
 Temp=new double [XSize*YSize];

 // check to see if it is a greyscale image
 if (_MapType==1)
   {
    for ( Y = 0 ; Y < (_Height-YSize+1) ; Y++ )
      {
       for ( X = 0; X < (_Width-XSize+1); X++ )
         {
	  // read in the values
          for ( FilterY = 0 ; FilterY < YSize ; FilterY++ )
            {
             for ( FilterX = 0; FilterX < XSize; FilterX++ )
               {
                Temp[(FilterY*XSize)+FilterX]=
		  ((*this)(X+FilterX,Y+FilterY).Red()) ;
               }
            }

          // now sort the list of values into ascending order
          for ( FilterY = 0 ; FilterY < ((YSize*XSize)-1) ; FilterY++ )
            {
             for ( FilterX = 0 ; FilterX < ((YSize*XSize)-1) ; FilterX++ )
               {
                if (Temp[FilterX]>Temp[FilterX+1])
                  {
                   Swap=Temp[FilterX] ;
                   Temp[FilterX]=Temp[FilterX+1] ;
                   Temp[FilterX+1]=Swap ;
                  }
               }
            }

          // now find the middle value
          Value=Temp[(XSize*YSize)/2] ;

          TempMap[X+(_Width*(_Height-Y-1))]=TColour(Value,Value,Value) ;

	 }
       }

    // the extra bits
    for ( Y = (_Height-YSize+1)  ; Y < _Height ; Y++ )
      {
       for ( X = (_Width-XSize+1) ; X < _Width ; X++ )
         {
          TempMap[X+(_Width*(_Height-Y-1))]=TColour(0.0,0.0,0.0) ;
         }
      }

    // make the right map point to the right place
    delete _Pixmap ;
    _Pixmap=TempMap ;
    TempMap=NULL ;

   }

 delete Temp ;
 delete TempMap ;
}

// Dilation operation with 3 by 3 all 1 element
TPixmap::Dilate(int CentreX,int CentreY)
{
 int X,Y ;
 TColour *Temp ;
 int CounterX,CounterY ;
 int ClearCounter ;

 // make a new copy
 Temp=new TColour[_Height*_Width] ;

 // clear it to black
 for (ClearCounter=0;ClearCounter<(_Height*_Width);ClearCounter++)
   {
    Temp[ClearCounter]=TColour(0.0,0.0,0.0) ;
   }

 // test to see if the image is a bitmap
 if (_MapType==2)
   {
    for ( Y = CentreY  ; Y < (_Height-(CentreY-2)) ; Y++ )
      {
       for ( X = CentreX ; X < (_Width-(CentreX-2)) ; X++ )
         {
	  // see if the centre is on or off
          if ((*this)(X,Y).Red()==1.0)
            {
	     // set all the pixels in the element
             for (CounterY=0;CounterY<3;CounterY++)
               {
                for (CounterX=0;CounterX<3;CounterX++)
                  {
                   Temp[(_Height-(Y-CentreY+CounterY)-1)*_Width+
                        (X-CentreX+CounterX)]=TColour(1.0,1.0,1.0) ;
                  }
               }

            }
         }
      }
    delete _Pixmap ;
    _Pixmap=Temp ;
    Temp=NULL ;
   }

 delete Temp ;
}


// Erodtion operation with 3 by 3 all 1 element
TPixmap::Erode(int CentreX,int CentreY)
{
 int X,Y ;
 TColour *Temp ;
 int CounterX,CounterY ;
 int ClearCounter ;
 int Flag ;

 // make a new copy
 Temp=new TColour[_Height*_Width] ;

 // clear it to black
 for (ClearCounter=0;ClearCounter<(_Height*_Width);ClearCounter++)
   {
    Temp[ClearCounter]=TColour(0.0,0.0,0.0) ;
   }

 // test to see if the image is a bitmap
 if (_MapType==2)
   {
    for ( Y = CentreY  ; Y < (_Height-(CentreY-2)) ; Y++ )
      {
       for ( X = CentreX ; X < (_Width-(CentreX-2)) ; X++ )
         {

	  // set to false
          Flag=0 ;

	  // see if the centre is on or off
          if ((*this)(X,Y).Red()==1.0)
            {
	     // set all the pixels in the element
             for (CounterY=0;CounterY<3;CounterY++)
               {
                for (CounterX=0;CounterX<3;CounterX++)
                  {
                   if ((*this)(X-CentreX+CounterX,Y-CentreY+CounterY).Red()
                        !=1.0)
                     {
                      Flag=1 ;
                     }
                  }
               }
             if (Flag==0)
               {
                Temp[X+(_Width*(_Height-Y-1))]=TColour(1.0,1.0,1.0) ;
               }
             else
               {
                Temp[X+(_Width*(_Height-Y-1))]=TColour(0.0,0.0,0.0) ;
               }
            }
         }
      }
    delete _Pixmap ;
    _Pixmap=Temp ;
    Temp=NULL ;
   }

 delete Temp ;
}

TPixmap::Convolute(TMask &Mask)
{
 TColour *TempMap ;
 double Temp ;
 double Swap,Value ;
 int X,Y ;
 int FilterX,FilterY ;
 int ClearCounter ;

 TempMap=new TColour [_Height*_Width] ;

 // clear the new map
 for (ClearCounter=0;ClearCounter<(_Height*_Width);ClearCounter++)
   {
    TempMap[ClearCounter]=TColour(0.0,0.0,0.0) ;
   }

 // check to see if it is a greyscale image
 if (_MapType==1)
   {
    for ( Y = Mask.CentreY() ;
          Y < (_Height-Mask.Height()+Mask.CentreY()) ;
          Y++ )
      {
       for ( X = Mask.CentreX() ;
             X < (_Width-Mask.Width()+Mask.CentreX());
             X++ )
         {
	  // read in the values
          Value=0 ;

          for ( FilterY = 0 ; FilterY < Mask.Height() ; FilterY++ )
            {
             for ( FilterX = 0; FilterX < Mask.Width() ; FilterX++ )
               {
                Temp=((*this)(X-Mask.CentreX()+FilterX,
                              Y-Mask.CentreY()+FilterY).Red()) ;
                Value=Value+(Temp*(Mask(FilterX,FilterY))) ;
               }
            }

          // set the pixel
          TempMap [X+((_Height-Y-1)*_Width)]=TColour(Value,Value,Value) ;

	 }
       }

    // make the right map point to the right place
    delete _Pixmap ;
    _Pixmap=TempMap ;
    TempMap=NULL ;

   }

 delete TempMap ;
}

TPixmap::Display()
{
 // only show pixmap if it is valid
 if (_MapType!=-1)
   {
    glClear(GL_COLOR_BUFFER_BIT) ;
    glDrawPixels(_Width,_Height,GL_RGB,GL_UNSIGNED_BYTE,_Pixmap) ;
   }
}

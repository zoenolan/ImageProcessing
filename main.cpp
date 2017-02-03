/*                                                                          */
/* Image processing coursework                                              */
/*                                                                          */

/*           */
/* main file */
/*           */

#include "iostream.h"
#include "pixmap.h"
#include "mask.h"

#include <GL/gl.h>
#include <GL/glu.h>
#include "aux.h"

TPixmap Image ;

Menu()
{
 cout<<"1. Load Image"<<endl;
 cout<<"2. Save Image"<<endl;
 cout<<"3. Convert to Greyscale"<<endl;
 cout<<"4. Convert to Binary"<<endl;
 cout<<"5. Convolute Image"<<endl;
 cout<<"6. Median Filter"<<endl;
 cout<<"7. Invert Image"<<endl;
 cout<<"8. Erode"<<endl;
 cout<<"9. Dilate"<<endl;
 cout<<"0. Quit"<<endl;
 cout<<endl<<"Please enter an option: " ;
}

load()
{
 char Name[100] ;
 cout<<"Load"<<endl<<"Enter filename to load:" ;
 cin>>Name;
 cout<<endl ;
 Image.Load(Name) ;
}

save()
{
 char Name[100] ;
 cout<<"Save"<<endl<<"Enter filename to save as:" ;
 cin>>Name;
 cout<<endl ;
 Image.Save(Name) ;
}

binary()
{
 double Threshold ;
 cout<<"Convert to binary"<<endl<<"Enter Threshold value (Between 0 and 1):" ;
 cin>>Threshold;
 cout<<endl ;
 Image.Threshold(Threshold) ;
}

median()
{
 int X,Y ;
 cout<<"Median filter"<<endl<<"Enter X size:" ;
 cin>>X;
 cout<<endl ;
 cout<<"Enter Y size:" ;
 cin>>Y;
 cout<<endl ;
 Image.Median(X,Y) ;
}

convolute()
{
 TMask Mask ;
 char Name[100] ;
 cout<<"Convolute"<<endl<<"Enter filename of mask to load:" ;
 cin>>Name;
 cout<<endl ;
 Mask.Load(Name) ;
 Image.Convolute(Mask) ;
}

dilate()
{
 int X,Y ;
 cout<<"Dilate"<<endl<<"Enter X Focus:" ;
 cin>>X;
 cout<<endl ;
 cout<<"Enter Y Focus:" ;
 cin>>Y;
 cout<<endl ;
 Image.Dilate(X,Y) ;
}

erode()
{
 int X,Y ;
 cout<<"Erode"<<endl<<"Enter X Focus:" ;
 cin>>X;
 cout<<endl ;
 cout<<"Enter Y Focus:" ;
 cin>>Y;
 cout<<endl ;
 Image.Erode(X,Y) ;
}

main()
  {
 int QuitFlag=0 ;
 int Selection ;

 cout<<"Image Processing System"<<endl<<endl ;

 auxInitDisplayMode (AUX_SINGLE|AUX_RGB) ;
 auxInitPosition(0,0,600,600) ;
 auxInitWindow ("Image Processor") ;
 glClearColor (0.0,0.0,0.0,0.0) ;
 glShadeModel (GL_FLAT) ;

 while (QuitFlag!=1)
   {
    // show options
    Menu() ;
    cin>>Selection ;
    cout<<endl ;

    // quit
    if (Selection==0)
      {
       QuitFlag=1 ;
      }

    // load image
    else if (Selection==1)
      {
       load() ;
      }

    // save image
    else if (Selection==2)
      {
       save() ;
      }

    // convert to greyscale
    else if (Selection==3)
      {
       Image.Greyscale() ;
      }

    // convert to binary
    else if (Selection==4)
      {
       binary() ;
      }

    // convolute
    else if (Selection==5)
      {
       convolute() ;
      }

    // median filter
    else if (Selection==6)
      {
       median() ;
      }

    // invert the image
    else if (Selection==7)
      {
       Image.Invert() ;
      }

    // erode
    else if (Selection==8)
      {
       erode() ;
      }

    // dilate
    else if (Selection==9)
      {
       dilate() ;
      }

    // show the image
    Image.Display() ;
   }

}

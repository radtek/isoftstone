#ifndef CUSTOMWIDGETSDEF_H
#define CUSTOMWIDGETSDEF_H

#define SCHEME2
#ifdef SCHEME1
#define START_COLOR QColor(50,50,50)
#define END_COLOR   QColor(220,220,220)
#endif

#ifdef SCHEME2
#define START_COLOR QColor(219,219,219)
#define END_COLOR   QColor(157,157,157)
#endif

#ifdef WIN32
#ifdef  COMMON_WIDGET
#define EXPORT_WIDGET _declspec(dllexport)
#else 
#define EXPORT_WIDGET _declspec(dllimport)  
#endif
#else
#define EXPORT_WIDGET
#endif 


#include <QtGui>

#endif // CUSTOMWIDGETSDEF_H


#ifndef EXTITEM_H
#define EXTITEM_H

#ifdef WIN32
#ifdef  EXTITEM
#define EXPORT_EXTITEM _declspec(dllexport)
#else 
#define EXPORT_EXTITEM _declspec(dllimport)  
#endif
#else
#define EXPORT_EXTITEM
#endif 

#include <QtGui>

#endif
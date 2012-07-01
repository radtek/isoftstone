
#ifndef COMMON_H
#define COMMON_H

#include <QtGui>

#ifdef Q_WS_WIN
#ifdef COMMONLIB
#define EXPORT_COMMON _declspec(dllexport)
#else 
#define EXPORT_COMMON _declspec(dllimport)  
#endif
#else
#define EXPORT_COMMON
#endif 



#endif
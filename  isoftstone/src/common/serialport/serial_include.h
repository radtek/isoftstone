
#ifndef SERIAL_INCLUDE_H
#define SERIAL_INCLUDE_H

#ifdef Q_WS_WIN
#ifdef  STATIC_LIB
#define SERIAL_EXPORT _declspec(dllexport)
#else 
#define SERIAL_EXPORT _declspec(dllimport)  
#endif
#else
#define FRAME_EXPORT
#endif 


#endif
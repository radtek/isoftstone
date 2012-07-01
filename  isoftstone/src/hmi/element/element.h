
#ifndef ELEMENT_INCLUDE
#define ELEMENT_INCLUDE

#ifdef WIN32
#ifdef ELEMENTLIB 
#define EXPORT_ELEMENT _declspec(dllexport)
#else 
#define EXPORT_ELEMENT _declspec(dllimport)  
#endif
#else
#define EXPORT_ELEMENT
#endif 

#endif
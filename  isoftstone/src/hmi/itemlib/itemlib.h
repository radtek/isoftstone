
#ifndef ITEMLIB_H
#define ITEMLIB_H

#ifdef Q_WS_WIN
	#ifdef ITEMLIB 
		#define EXPORT_ITEMLIB _declspec(dllexport)
		#else 
		#define EXPORT_ITEMLIB _declspec(dllimport)  
	#endif
#else
	#define EXPORT_ITEMLIB
#endif 

#endif
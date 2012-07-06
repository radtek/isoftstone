
#ifndef MACRO_H
#define MACRO_H

#define COS(X) (cos((float)X*3.1415926/180))
#define SIN(X) (sin(1*(float)X*3.1415926/180))

#define PROJECT_HOME "STONEDIR"
#define DATA_HOME	"VISDATAPATH"

#ifdef WIN32
	#ifdef  EXPORT_STATIC
		#define EXPORT_LIB _declspec(dllexport)
	#else 
		#define EXPORT_LIB _declspec(dllimport)  
	#endif
#else
	#define EXPORT_LIB
#endif 

#ifdef Q_WS_WIN
	#define EXPORT_DLL _declspec(dllexport)
#else 
	#define EXPORT_DLL
#endif


#endif // END IFDEF

#ifndef CREATPRO_H
#define CREATPRO_H
/*
function:1. qmake_vc.bat文件的创建
			2. .pro文件的创建
			3. .h和.cpp文件的读取
			4. qtnmake.bat文件的创建
date:2012-1-11
*/


#include <iostream>
#include <QTextStream>
#include <QDir>
#include <QFileInfo>
#include <QFile>

class CCreatPro
{
public:
    CCreatPro();
    void execute(QString dir);

private:

};

#endif // CREATPRO_H

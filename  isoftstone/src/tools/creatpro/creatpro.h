#ifndef CREATPRO_H
#define CREATPRO_H
/*
function:1. qmake_vc.bat�ļ��Ĵ���
			2. .pro�ļ��Ĵ���
			3. .h��.cpp�ļ��Ķ�ȡ
			4. qtnmake.bat�ļ��Ĵ���
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


#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QString>
#include <QXmlStreamReader>
#include <QTextStream>

bool transformNode(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QTextStream& writer);
bool transformNode(const QVector<QPair<QString,QMap<QString,QString> > >& vecMap,QTextStream& writer);
bool transformNode(const QString& name,const QMap<QString,QString>& attrMap,QTextStream& writer,int nID);
bool transformG2QML(const QString& gFile,QString& svgFile);
int  transformGDir(const QString& dirHome);


void initFuncPointer();

#endif

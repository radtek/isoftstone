
#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <QString>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

bool transformNode(QXmlStreamReader& reader,QXmlStreamWriter& writer,int nID);
bool transformNode(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QXmlStreamWriter& writer);
void writeSvgRoot(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QXmlStreamWriter& writer) ;
void writeHeaderLayer(const QMap<QString,QVector<QMap<QString,QString> > >& layerMap,QXmlStreamWriter& writer);
bool transformNode(const QString& name,const QMap<QString,QString>& attrMap,QXmlStreamWriter& writer,int nID);
bool transformG2SVG(const QString& gFile,QString& svgFile);
int  transformGDir(const QString& dirHome);
bool transformSVG2G(const QString& svgFile,QString& gFile);


void initFuncPointer();

#endif

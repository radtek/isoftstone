
#ifndef SYMBOL_H
#define SYMBOL_H

#include <QMap>
#include <QString>
#include <QXmlStreamWriter>
#include <QTextStream>

QString createSvgSymbol(const QString& fileName,QString& strSymbol);
void writeSymbols(QTextStream& out,QString strID,const QString& strSymbol);
void writeSymbols(QTextStream& out,const QMap<QString,QString>& symbolMap);
void writeSymbols(const QString& dirName,const QString& symbolFile);
void readSymbols(const QString& fileName,QMap<QString,QString>& symbolMap);


#endif
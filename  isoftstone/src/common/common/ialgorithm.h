
#ifndef I_ALGORITHM_H
#define I_ALGORITHM_H

#include <QTreeWidgetItem>
#include <QTreeWidget>
#include <QTreeWidgetItemIterator>
#include <QVector>
#include <QPair>
#include <QList>
#include <QGraphicsItem>

#include <QDebug>

#include "common.h"
#include "enum.h"

class EXPORT_COMMON CAlgorithm
{
public:

	static QTreeWidgetItem* findItemExtend(QTreeWidget* treeWidget,const QVector<QString>& vecFilter,int nColumn);
	static QTreeWidgetItem* findItemExtend(QTreeWidgetItem* rootItem,const QString& filter,int nColumn);
	static void createMenuByMap(QMenu* menu, QMap<QString, QStringList> mapName);
	static QPair<QAction*,bool> getParentMenu(const QStringList& lstMenu,const QList<QAction*>& lstAction );
	static void filteMetaType(QList<QGraphicsItem*> lstItems,QGraphicsItem*& pItem,EItemType& eItemType);
};

EXPORT_COMMON float calcDiff(float* pValues,int beginPos,int endPos);
EXPORT_COMMON void  calcRatio(float* pValues,float* pRatio,int len,int nMethod);
EXPORT_COMMON float colorMapped(char nColor,float v,bool bSmooth);

EXPORT_COMMON QStringList importFiles(const QString& path);
EXPORT_COMMON bool isValidFormat(const QString& str);

EXPORT_COMMON QRgb blendColor(QRgb c1, QRgb c2, int blend);
EXPORT_COMMON QImage* generateReflection(const QImage* slideImage, int w, int h, QRgb bgcolor);

EXPORT_COMMON QStringList getFileRecusive(const QString& dirName,const QStringList& filters);
EXPORT_COMMON bool readElement(const QString& gFile,QMap<QString,QVector<QMap<QString,QString> > >& layerMap,
							QVector<QPair<QString,QMap<QString,QString> > >& vecLayer,QSet<QString>& devSet);


#endif
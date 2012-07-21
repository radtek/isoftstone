
#include <math.h>
#include <QAction>
#include <QMenu>

#include <QXmlStreamReader>

#include "ialgorithm.h"

QTreeWidgetItem* CAlgorithm::findItemExtend(QTreeWidget* treeWidget,const QVector<QString>& vecFilter,int nColumn)
{
	int nTopLevel = treeWidget->topLevelItemCount();
	if (vecFilter.count() == 0 || nTopLevel < 1 || nColumn > treeWidget->columnCount())
	{
		return NULL;
	}
	QTreeWidgetItem* pItem = treeWidget->invisibleRootItem();

	for (int i = 0 ; i < vecFilter.count() ; i++ )
	{
		QString filter = vecFilter[i];
		//qDebug() << filter << "\n";
		pItem = findItemExtend(pItem,filter,nColumn);
		if (!pItem)
		{
			return NULL;
		}
	}
	return pItem;
}

QTreeWidgetItem* CAlgorithm::findItemExtend(QTreeWidgetItem* rootItem,const QString& filter,int nColumn)
{
	if (!rootItem )
	{
		return NULL;
	}
	//qDebug() << filter << "\n";
	QList<QTreeWidgetItem*> itemDeque;
	itemDeque.push_back(rootItem);
	while (!itemDeque.empty())
	{
		QTreeWidgetItem* pItem = itemDeque.front();
		itemDeque.pop_front();
		//qDebug() << pItem->text(nColumn) << "\n";
		if (pItem->text(nColumn) == filter)
		{
			return pItem;
		}
		for (int i = 0 ; i < pItem->childCount() ;i++)
		{
			itemDeque.push_back(pItem->child(i));
		}
	}
	return NULL;
}

void CAlgorithm::createMenuByMap(QMenu* menu, QMap<QString, QStringList> mapName)
{
	QMapIterator<QString, QStringList> iter(mapName);
	while(iter.hasNext())
	{
		iter.next();		
		QString strName = iter.key();
		QStringList	lstName	= iter.value();

		// 只有一层菜单
		if(lstName.size() == 1)
		{
			QAction* action = new QAction(lstName.first(), menu);
			menu->addAction(action);			
		}
		else
		{
			QMenu* subMenu = new QMenu(strName, menu);
			menu->addMenu(subMenu);
			foreach(const QString& str, lstName)
			{
				QAction* action = new QAction(str, menu);
				subMenu->addAction(action);				
			}			
		}
	}	
}

QPair<QAction*,bool> CAlgorithm::getParentMenu(const QStringList& lstMenu,const QList<QAction*>& lstAction )
{
	QAction* defaultAct = NULL;
	QAction* parentAct = NULL;


	QString strHelp = "Renderer";
	QString strParentMenu = lstMenu.first();
	QString strSubMenu = "";

	foreach(QAction* act, lstAction)
	{
		QMenu* menu  = act->menu();
		if(menu != NULL)
		{			
			QString name = menu->objectName();
			if(name == strHelp)
			{
				defaultAct = act;
			}
			if(name == strParentMenu)
			{
				parentAct = act;
				if (lstMenu.count() > 1)
				{
					strSubMenu = lstMenu[1];
					foreach(QAction* subAct,menu->actions())
					{
						QMenu* subMenu = subAct->menu();
						if (subMenu)
						{
							name = subMenu->objectName();
							if (name == strSubMenu)
							{
								parentAct = subAct;
								return QPair<QAction*,bool>(parentAct,true);
							}
						}
					}
				}
				return QPair<QAction*,bool>(parentAct,true);
			}
		}
	}
	// false 代表没有找到对应的父菜单，只能放到help前面
	return QPair<QAction*,bool>(defaultAct,false);
}

void CAlgorithm::filteMetaType(QList<QGraphicsItem*> lstItems,QGraphicsItem*& pItem,EItemType& eItemType)
{
	QList<EItemType> filterType;  
	filterType << CIMGBusDis << CIMGCircle << CIMGLine << CIMGTriangle
		<< CIMGPolyLine << CIMGRoundRect << CIMGPolygon <<CIMGImage
		<< CIMGDiamond << CIMGEllipse << CIMGFeedLine << CIMGLoadDisPloy
		<< CIMGCube << CIMGHandgon << CIMGLogconductorDis << CIMGRect 
		<< CIMGCirclearc << CIMGHandLine << CIMGEllipsearc <<CIMGParallelrect
		<< CIMGConnectLine << CIMGText;

	foreach (QGraphicsItem* item,lstItems)
	{
		EItemType eType = (EItemType)item->type();
		if (eType <= QGraphicsItem::UserType)
		{
			continue;
		}
		if (!filterType.contains(eType))
		{
			pItem = item;
			eItemType = eType;
			return;
		}
	}
	pItem = NULL;
	eItemType = CIMGCommon;
}

float colorMapped(char nColor,float v,bool bSmooth)
{
	float ret = 0.0f;
	if (bSmooth)  // 平滑过渡
	{
		switch(nColor)
		{
		case 'R':
			{
				if (v < 3.0f/8)
				{
					ret = 0.0f;
				}
				else if (v >= 3.0f/8 && v < 5.0f/8)
				{
					ret = 4*(v-3.0f/8);
				}
				else if (v >= 5.0f/8 && v < 7.0f/8 )
				{
					ret = 1;
				}
				else if (v >= 7.0f/8 && v < 1)
				{
					ret = 4*(9.0f/8 - v);
				}
				else
				{
					ret = 1.0f/2;
				}
			}
			break;
		case 'G':
			{
				if (v < 1.0f/8)
				{
					ret = 0.0f;
				}
				else if (v >= 1.0f/8 && v < 3.0f/8)
				{
					ret = 4*(v-1.0f/8);
				}
				else if (v >= 3.0f/8 && v < 5.0f/8 )
				{
					ret = 1;
				}
				else if (v >= 5.0f/8 && v < 7.0f/8)
				{
					ret = 4*(7.0f/8 - v);
				}
				else
				{
					ret = 0;
				}
			}
			break;
		case 'B':
			{
				if (v < 0)
				{
					ret = 1.0f/2;
				}
				else if (v >= 0 && v < 1.0f/8)
				{
					ret = 4*(v + 1.0f/8);
				}
				else if (v >= 1.0f/8 && v < 3.0f/8 )
				{
					ret = 1;
				}
				else if (v >= 3.0f/8 && v < 5.0f/8)
				{
					ret = 4*(5.0f/8 - v);
				}
				else
				{
					ret = 0;
				}
			}
			break;
		default:
			break;
		}
	}
	else // 突变过渡
	{
		switch(nColor)
		{
		case 'R':
			{
				if (v < 1.0f/3)
				{
					ret = 0.0f;
				}
				else if (v >= 1.0f/3 && v < 2.0f/3)
				{
					ret = 3*(v-1.0f/3);
				}
				else if (v >= 2.0f/3  && v < 1)
				{
					ret = 1;
				}
				else
				{
					ret = 1.0f/2;
				}
			}
			break;
		case 'G':
			{
				if (v < 0)
				{
					ret = 0.0f;
				}
				else if (v >= 0 && v < 1.0f/3)
				{
					ret = 3*v;
				}
				else if (v >= 1.0f/3 && v < 2.0f/3)
				{
					ret = 1;
				}
				else if (v >= 2.0f/3 && v < 1)
				{
					ret = 3*(1 - v);
				}
				else
				{
					ret = 0;
				}
			}
			break;
		case 'B':
			{
				if (v < 0)
				{
					ret = 0.5f;
				}
				else if (v >= 0 && v < 1.0f/3)
				{
					ret = 1;
				}
				else if (v >= 1.0f/3  && v < 2.0f/3)
				{
					ret = 3*(2.0f/3 - v);
				}
				else
				{
					ret = 0.0f;
				}
			}
			break;
		default:
			break;
		}
	}

	return ret;
}


float calcDiff(float* pValues,int beginPos,int endPos)
{
	float fDiff = 0.0f;
	float fSum = 0.0f;
	int j = 0;
	for (int i = beginPos ; i < endPos; i++)
	{
		j = i + 1;
		fSum += pow(pValues[j] - pValues[i],2);
	}
	fDiff = sqrt(fSum / (endPos - beginPos));
	return fDiff;
}

void calcRatio(float* pValues,float* pRatio,int len,int nMethod)
{
	qDebug() << "calcRatio " << nMethod << "\n";

	float fAvg = 0.0f;
	switch (nMethod)
	{
	case 2:  // 最大值
		{
			float fMax = 0.0f;
			for (int i = 0 ; i < len ; i++)
			{
				if (fMax < pValues[i])
				{
					fMax = pValues[i];
				}
			}
			for (int i = 0 ; i < len ; i++)
			{
				pRatio[i] = pValues[i] / fMax;

				qDebug() << pRatio[i] << "\n";
			}
		}
		break;
	case 1:  // 平方均分发
		{
			for (int i = 0 ; i < len ; i++)
			{
				fAvg += pow(pValues[i],2)/len;
			}
			for (int i = 0 ; i < len ; i++)
			{
				pRatio[i] = sqrt(pow(pValues[i],2) / fAvg);

				qDebug() << pRatio[i] << "\n";
			}
		}
		break;
	case 0:  // 平均值发
	default:
		{
			for (int i = 0 ; i < len ; i++)
			{
				fAvg += pValues[i]/len;
			}
			for (int i = 0 ; i < len ; i++)
			{
				pRatio[i] = pValues[i] / fAvg;

				qDebug() << pRatio[i] << "\n";
			}
		}
		break;
	}

}



QStringList getFileRecusive(const QString& dirName,const QStringList& filters)
{
	QStringList lstRet;
	QDir dir(dirName);
	QFileInfoList lstDir = dir.entryInfoList();
	foreach(QFileInfo info ,lstDir)
	{
		QString baseName = info.fileName();
		if (info.isDir() &&  baseName != ".." && baseName != "." && baseName != ".svn")
		{
			QString path = info.absoluteFilePath();
			lstRet = lstRet + getFileRecusive(path,filters);
		}
		else if(info.isFile())
		{
			const QString& ext = info.suffix();
			if (filters.contains(ext))
			{
				lstRet.append(info.absoluteFilePath());
			}
		}
	}
	return lstRet;
}


bool readElement(const QString& gFile,QMap<QString,QVector<QMap<QString,QString> > >& layerMap,
				 QVector<QPair<QString,QMap<QString,QString> > >& vecLayer,QSet<QString>& devSet)
{
	QFile file(gFile);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	QXmlStreamReader reader(&file);

	bool bRet = reader.readNextStartElement(); // sgd
	if (bRet)
	{
		while (!reader.atEnd())
		{
			bRet = reader.readNextStartElement(); //layer
			QString name = reader.name().toString();
			if (bRet && name == "Layer")
			{
				QMap<QString,QString> attrMap1;
				const QXmlStreamAttributes& gAttrs1 = reader.attributes ();
				for (int i = 0 ; i < gAttrs1.count();i++)
				{
					attrMap1[gAttrs1[i].name().toString()] = gAttrs1[i].value().toString();
				}
				layerMap[reader.name().toString()].append(attrMap1);

				// viewbox
				QString viewbox ;
				viewbox += layerMap["Layer"][0]["x"] + " ";
				viewbox += layerMap["Layer"][0]["y"] + " ";
				viewbox += layerMap["Layer"][0]["w"] + " ";
				viewbox += layerMap["Layer"][0]["h"];

				vecLayer.append(qMakePair(QString("Layer"),layerMap["Layer"][0]));
				if (layerMap["svg"].count() > 0)
				{
					layerMap["svg"][0]["viewBox"] = viewbox;
					vecLayer.append(qMakePair(QString("svg"),layerMap["svg"][0]));
				}

				while(bRet)
				{
					bRet = reader.readNextStartElement(); // cbreaker
					QString name = reader.name().toString();
					if (name == "Layer")
					{
						bRet = true;
						continue;
					}
					if (bRet)
					{
						QMap<QString,QString> attrMap;
						const QXmlStreamAttributes& gAttrs = reader.attributes ();
						for (int i = 0 ; i < gAttrs.count();i++)
						{
							QString attrName = gAttrs[i].name().toString();
							attrMap[attrName] = gAttrs[i].value().toString();
						}
						if (attrMap.contains("devref") == true )
						{
							QString devRef = attrMap["devref"];
							if (devSet.contains(devRef) == false)
							{
								devSet.insert(devRef);
							}
						}
						reader.skipCurrentElement ();
						layerMap[name].append(attrMap);
						vecLayer.append(qMakePair(name,attrMap));
					}
				}
			}
			else
			{
				QMap<QString,QString> svgMap;
				const QXmlStreamAttributes& gAttrs2 = reader.attributes ();
				for (int i = 0 ; i < gAttrs2.count();i++)
				{
					svgMap[gAttrs2[i].name().toString()] = gAttrs2[i].value().toString();
				}
				svgMap["name"] = name;
				layerMap["svg"].append(svgMap);
			}
		}
	}
	file.close();
	return true;
}

QStringList importFiles(const QString& path = QString())
{
	QStringList files;

	QDir dir = QDir::current();
	if(!path.isEmpty())
		dir = QDir(path);

	dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
#if QT_VERSION >= 0x040000
	QFileInfoList list = dir.entryInfoList();
	for (int i = 0; i < list.size(); ++i)
	{
		QFileInfo fileInfo = list.at(i);
		files.append(dir.absoluteFilePath(fileInfo.fileName()));
	}
#else
	const QFileInfoList* list = dir.entryInfoList(QStringList() << "*.png" << "*.gif" << "*.bmp" << "*.jpg",QDir::Files);
	if(list)
	{
		QFileInfoListIterator it( *list );
		QFileInfo * fi;
		while( (fi=it.current()) != 0 )
		{
			++it;
			files.append(dir.absFilePath(fi->fileName()));
		}
	}
#endif

	return files;
}

bool isValidFormat(const QString &str)
{
	static QList<QByteArray> supportedFormat = QImageReader::supportedImageFormats();
	QFileInfo fInfo(str);
	int formatCnt = supportedFormat.count();
	for(int formatIndex = 0 ;formatIndex < formatCnt;formatIndex++)
	{
#ifdef _DEBUG
		qDebug() << __FUNCTION__ << supportedFormat.at(formatIndex).toUpper();
		qDebug() << __FUNCTION__ << fInfo.completeSuffix().toUpper();
#endif
		if(QString(supportedFormat.at(formatIndex)).toUpper() == fInfo.completeSuffix().toUpper())
		{
			return true;
		}
	}

	return false;
}


QRgb blendColor(QRgb c1, QRgb c2, int blend)
{
	int r = qRed(c1) * blend/256 + qRed(c2)*(256-blend)/256;
	int g = qGreen(c1) * blend/256 + qGreen(c2)*(256-blend)/256;
	int b = qBlue(c1) * blend/256 + qBlue(c2)*(256-blend)/256;
	return qRgb(r, g, b);
}

QImage* generateReflection(const QImage* slideImage, int w, int h, QRgb bgcolor)
{
	Qt::TransformationMode mode = Qt::SmoothTransformation;
	QImage img = slideImage->scaled(w, h, Qt::IgnoreAspectRatio, mode);

	int hofs = h / 3;

	int hs = h + h/3;

	QImage* result = new QImage(hs, w, QImage::Format_RGB32);

	QPixmap *pixmap=new QPixmap(hs,w);
	QLinearGradient pixmapGradient(QPoint(0,0),QPoint(0,pixmap->height()));
	pixmapGradient.setColorAt(0.0,QColor(255,255,255,10));
	pixmapGradient.setColorAt(0.8,QColor(255,255,255,10));
	pixmapGradient.setColorAt(1.0,QColor(170,170,170,10));
	QPainter pixmapPainter(pixmap);
	pixmapPainter.setBrush(pixmapGradient);
	pixmapPainter.drawRect(pixmap->rect());
	pixmapPainter.end();
	result = &pixmap->toImage();

	int startY = 0;
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < h; y++)
		{
			result->setPixel(startY + y, x, img.pixel(x, y));
		}
	}

	int ht =  h/3;
	hofs = 0;
	int hte = ht;
	for(int x = 0; x < w; x++)
	{
		for(int y = 0; y < ht; y++)
		{
			QRgb color = img.pixel(x, img.height()-y-1);
			result->setPixel(h+hofs+y, x, blendColor(color,bgcolor,128*(hte-y)/hte));
		}
	}

	return result;
}

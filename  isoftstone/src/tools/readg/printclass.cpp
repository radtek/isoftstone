
#include "func.h"


extern QMap<QString,QString> attrTypeMap;
extern QMap<QString,QString> valueMap;

// 搜索文件，将每种结构放入各自的类文件中
void printClass(const QString& file,int nOp)
{
	QMap<QString,QStringList> classMap;

	QFile sourcefile(file);
	if (!sourcefile.open(QIODevice::ReadOnly))
	{
		return;
	}

	QTextStream in(&sourcefile);

	QString className = "";
	while(!in.atEnd())
	{
		QString line = in.readLine();

		// 获得类名
		if (line.contains("class",Qt::CaseInsensitive))
		{
			className = "";
			QStringList lst = line.split(' ');
			if (lst.count() > 1)
			{
				className = lst[1].remove("_Struct");
			}
		}

		bool bBegin = line.contains("{",Qt::CaseInsensitive);
		if (bBegin)
		{
			bool bEnd = line.contains("}",Qt::CaseInsensitive);
			QStringList lstAttr;
			while (bEnd != true)
			{
				line = in.readLine();
				bEnd = line.contains("}",Qt::CaseInsensitive);
				if (bEnd)
				{
					break;
				}
				QStringList lst = line.split(' ');
				if (lst.count() > 1)
				{
					lstAttr.append(line);
				}

			}
			classMap.insert(className,lstAttr);
		}
	}

	if (nOp == 1)
	{
		// 生成枚举
		printEnum("info.h",getAutoHome() + "GEnum.h"); //  生成枚举信息
	}
	else if (nOp == 2)
	{
		// 生成串行化信息
		printClass(classMap);
	}
	else if (nOp == 3)
	{
		// 生成派生实现类
		printImplHClass(classMap);
		printImplCPPClass(classMap);
	}
	else if (nOp == 4)
	{
		// 生成工厂
		printClassFactory_H(classMap);
		printClassFactory_CPP(classMap);
	}

}


void printClass(QMap<QString,QStringList> classMap)
{
	QMapIterator<QString,QStringList> iter(classMap);
	while(iter.hasNext())
	{
		iter.next();

		QString className = iter.key();
		const QStringList& lstAttr = iter.value();

		QString dest = getAutoHome() + className + "_Auto.h";
		QFile destfile(dest);
		if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			return;
		}
		QTextStream out(&destfile);
		out << "#ifndef CLASS_" << className.toUpper() <<"_AUTO_H\n";
		out << "#define CLASS_" << className.toUpper() <<"_AUTO_H\n\n";

		out << "#include <QGraphicsItem>\n";
		out << "#include <QDataStream>\n";
		out << "#include <QString>\n";
		out << "#include <QObject>\n";
		out << "#include <QFontMetrics>\n";
		out << "#include <QFont>\n";
		out << "#include <QRect>\n";
		out << "#include <QRectF>\n";
		out << "#include <QPen>\n";
		out << "#include <QBrush>\n";
		out << "#include <QPainter>\n";
		out << "#include <QPixmap>\n";
		out << "#include <QVariant>\n\n";

		out << "#include <math.h>\n";

		out << "\n";
		out << "#include \"rapidxml.hpp\"\n";
		out << "#include \"interface.h\"\n";
		out << "#include \"GEnum.h\"\n";
		out << "#include \"itembase.h\"\n";
		out << "\n\n";

		out << "using namespace rapidxml;\n\n\n";

		out << "struct " << className << "_Struct" << "\n";
		out <<"{\n";
		//out << "public:\n";
		foreach(QString attr,lstAttr)
		{
			out << attr << "\n";
		}

		out << "\n";
		out << "\t" <<  className << "_Struct& operator=(const "<< className << "_Struct& cp)\n";
		out << "\t{\n";
		foreach(QString attr,lstAttr)
		{
			QString attrName = attr.simplified().split(' ')[1].remove(";");
			out << "\t\tthis->" << attrName << " = \t\tcp." << attrName << ";\n";
		}
		out <<"\t\treturn *this;\n";
		out << "\t}\n";

		out << "};\n\n";

		out << "class " << "C" << className << "_Auto : public ISerialize,public GSerialize,public CGraphicsItemBase " << "\n";
		out << "{\n";

		out << "public:\n";

		/***************  图元类型开始  *********************/

// 		out <<"\t" << "virtual int type()" << "\n";
// 		out << "\t{\n";
// 		out << "\t\treturn E" << className << ";\n";
// 		out <<"\t}\n\n";

		/***************  图元类型结束  *********************/

		/***************  图元名称开始  *********************/

		if (0)
		{
			out <<"\t" << "virtual char* name()" << "\n";
			out << "\t{\n";
			out << "\t\treturn \"C" << className << "\";\n";
			out <<"\t}\n\n";

			out <<"\t" << "virtual quint64 keyID()" << "\n";
			out << "\t{\n";
			bool bFindKey = false;
			foreach(QString attr,lstAttr)
			{
				attr = attr.simplified().split(' ')[1].simplified().remove(";");
				if (attr == "keyid")
				{
					bFindKey = true;
					break;
				}
			}
			if (bFindKey)
			{
				out << "\t\treturn m_Info.keyid" << ";\n";
			}
			else
			{
				out <<"\t\t return 0;\n";
			}

			out <<"\t}\n\n";

			//out <<"\t" << "virtual QPixmap pixmap() = 0;" << "\n";

			//out <<"\t" << "virtual void setValue(const QVariant& varValue) = 0;" << "\n";
		}

		/***************  图元名称结束  *********************/

		/***************  二进制 开始  *********************/

		out << "\t" << "virtual void serialize(QDataStream& out) const" << "\n";
		out << "\t" << "{\n";
		foreach(QString attr,lstAttr)
		{
			out << "\t\t" << "out << m_Info." << attr.simplified().split(' ')[1] << "\n";
		}
		out << "\t" << "}\n\n";

		out << "\t" << "virtual void deserialize( QDataStream& out)" << "\n";
		out << "\t" << "{\n";
		foreach(QString attr,lstAttr)
		{
			out << "\t\t" << "out >> m_Info." << attr.simplified().split(' ')[1] << "\n";
		}
		out << "\t" << "}\n";

		/***************  二进制 结束  *********************/

		/***************  XML 开始  *********************/

		out << "\t" << "virtual void serialize(xml_node<char>* node) const" << "\n";
		out << "\t" << "{\n";
		out << "\t\t" << "xml_attribute<char>* attr = NULL;\n\n";
		foreach(QString attr,lstAttr)
		{
			QString name = attr.simplified().split(' ')[1].remove(";");
			out << "\t\t" << "attr = new xml_attribute<char>();\n";

			out << "\t\t" << "attr->name( \""  << name << "\" );\n";

			QString attrType = "QString";
			if (attrTypeMap.contains(name))
			{
				QString strType = attrTypeMap[name];
				if (strType == "long" || 
					strType == "int"  || 
					strType == "uint" || 
					strType == "bool" || 
					strType == "real" || 
					strType == "qreal" ||
					strType == "double" )
				{
					out << "\t\t" << "attr->value(QString::number(m_Info."  << name << ").toLocal8Bit().data());\n";
				}
				else if (strType == "rect")
				{
					out << "\t\t" << "attr->value(QString(\"%1,%2,%3,%4\").arg(QString::number(m_Info." << name << ".left()),QString::number(m_Info." << name << ".right()),QString::number(m_Info." << name << ".top()),QString::number(m_Info." << name << ".bottom())).toLocal8Bit().data());\n";
				}
				else if (strType == "polygon")
				{
					out << "\t\t" << "QString strPolygon = \"\";\n";
					out << "\t\t" << "for (int i = 0; i < m_Info." << name << ".size(); ++i)\n";
					out << "\t\t" <<"{\n";
					out << "\t\t\t" << "QPointF pos = m_Info." << name << "[i];\n";
					out << "\t\t\t" << "strPolygon += QString::number(pos.x());\n";
					out << "\t\t\t" << "strPolygon += \",\";\n";
					out << "\t\t\t" << "strPolygon += QString::number(pos.y());\n";
					out << "\t\t\t" << "strPolygon += \" \";\n";
					out << "\t\t" <<"}\n";

					out << "\t\t" << "attr->value(strPolygon.toLocal8Bit().data());\n";
				}
				else if (strType == "tfr")
				{
					out << "\t\t" << "QString strTfr = \"rotate(\";\n";
					out << "\t\t" << "strTfr += QString::number(m_Info.tfr.rotate);\n";
					out << "\t\t" << "strTfr += \") scale(\";\n";

					out << "\t\t" << "strTfr += QString::number(m_Info.tfr.scale_x);\n";
					out << "\t\t" << "strTfr += \",\";\n";
					out << "\t\t" << "strTfr += QString::number(m_Info.tfr.scale_y);\n";
					out << "\t\t" << "strTfr += \" \";\n";

					out << "\t\t" << "attr->value(strTfr.toLocal8Bit().data());\n";
				}
				else if (strType == "color")
				{
					out << "\t\t" << "attr->value(QString(\"%1,%2,%3\").arg((int)m_Info." << name << ".red(),(int)m_Info." << name << ".green(),(int)m_Info." << name << ".blue()).toLocal8Bit().data());\n";
				}
				else
				{
					out << "\t\t" << "attr->value( m_Info."  << name << ".toLocal8Bit().data() );\n";
				}
			}
			else
			{
				out << "\t\t" << "attr->value( m_Info."  << name << ".toLocal8Bit().data() );\n";
			}

			out << "\t\t" << "node->append_attribute(attr) ;\n\n" ;
		}
		out << "\t" << "}\n\n";

		out << "\t" << "virtual void deserialize( xml_node<char>* node)" << "\n";
		out << "\t" << "{\n";
		out << "\t\t" << "xml_attribute<char>* attr = NULL;\n\n";
		foreach(QString attr,lstAttr)
		{
			QString name = attr.simplified().split(' ')[1].remove(";");
			out << "\t\t" << "attr = node->first_attribute(\"" << name << "\");\n";
			out << "\t\t" << "if(attr)\n";
			out << "\t\t" << "{\n";
			out << "\t\t\t" << " m_AttrInfo[\"" << name << "\"] = QString(attr->value());\n";

			QString attrType = "QString";
			if (attrTypeMap.contains(name))
			{
				QString strType = attrTypeMap[name];
				if (strType == "rect")
				{
					out << "\t\t\t" << " QStringList lstRect = QString(attr->value()).split(',');"<< "\n";
					out << "\t\t\t" << " m_Info." << name  << ".setLeft(lstRect[0].toInt());"<< "\n";
					out << "\t\t\t" << " m_Info." << name  << ".setRight(lstRect[1].toInt());"<< "\n";
					out << "\t\t\t" << " m_Info." << name  << ".setTop(lstRect[2].toInt());"<< "\n";
					out << "\t\t\t" << " m_Info." << name  << ".setBottom(lstRect[3].toInt());"<< "\n";
				}
				else if (strType == "polygon")
				{
					out << "\t\t\t" << " QStringList lstPoints = QString(attr->value()).split(' ');"<< "\n";
					out << "\t\t\t" << " foreach(QString strPoint,lstPoints)"<< "\n";
					out << "\t\t\t" << " {"<< "\n";
					out << "\t\t\t\t" << "if(strPoint.split(',').count() > 1)\n";
					out << "\t\t\t\t" << "{\n";
					out << "\t\t\t\t\t" << " QPointF pos;"<< "\n";
					out << "\t\t\t\t\t" << " pos.setX(strPoint.split(',')[0].toDouble());"<< "\n";
					out << "\t\t\t\t\t" << " pos.setY(strPoint.split(',')[1].toDouble());"<< "\n";
					out << "\t\t\t\t\t" << " m_Info." << name  << ".append(pos);"<< "\n";
					out << "\t\t\t\t" << " }"<< "\n";
					out << "\t\t\t" << " }"<< "\n";
				}
				else if (strType == "color")
				{
					out << "\t\t\t" << " QStringList lstColor = QString(attr->value()).split(',');"<< "\n";
					out << "\t\t\t" << " if(lstColor.count() > 3)"<< "\n";
					out << "\t\t\t" << " {"<< "\n";
					out << "\t\t\t\t" << " m_Info." << name  << ".setRed(lstColor[0].toInt());"<< "\n";
					out << "\t\t\t\t" << " m_Info." << name  << ".setGreen(lstColor[1].toInt());"<< "\n";
					out << "\t\t\t\t" << " m_Info." << name  << ".setBlue(lstColor[2].toInt());"<< "\n";
					out << "\t\t\t" << " }"<< "\n";
				}
				else if (strType == "tfr")
				{
					out << "\t\t\t" << "QString strValue = QString(attr->value());\n";
					out << "\t\t\t" << "if (strValue.split(' ').count() > 0)\n";
					out << "\t\t\t{\n";
					out << "\t\t\t\t" << "QString strRotate = strValue.split(' ')[0];\n";
					out << "\t\t\t\t" << "strRotate.remove(\"rotate(\");\n";
					out << "\t\t\t\t" << "strRotate.remove(\")\");\n";
					out << "\t\t\t\t" << " m_Info." << name  << ".rotate = strRotate.toDouble();"<< "\n";
					out << "\t\t\t}\n";
					out << "\t\t\t" << "if (strValue.split(' ').count() > 1)\n";
					out << "\t\t\t{\n";
					out << "\t\t\t\t" << "QString strScale = strValue.split(' ')[1];\n";
					out << "\t\t\t\t" << "strScale.remove(\"scale(\");\n";
					out << "\t\t\t\t" << "strScale.remove(\")\");\n";
					out << "\t\t\t\t" << "m_Info." << name  << ".scale_x = strScale.split(',')[0].toDouble();"<< "\n";
					out << "\t\t\t\t" << "m_Info." << name  << ".scale_y = strScale.split(',')[1].toDouble();"<< "\n";
					out << "\t\t\t}\n";
				}
				else if (strType == "long")
				{
					out << "\t\t\t" << " m_Info." << name  << " = QString(attr->value()).toULongLong();"<< "\n";
				}
				else if (strType == "uint")
				{
					out << "\t\t\t" << " m_Info." << name  << " = QString(attr->value()).toUInt();"<< "\n";
				}
				else if (strType == "int")
				{
					out << "\t\t\t" << " m_Info." << name  << " = QString(attr->value()).toInt();"<< "\n";
				}
				else if (strType == "bool")
				{
					out << "\t\t\t" << " m_Info." << name  << " = QString(attr->value()).toInt();"<< "\n";
				}
				else if (strType == "qreal")
				{
					out << "\t\t\t" << " m_Info." << name  << " = QString(attr->value()).toFloat();"<< "\n";
				}
				else
				{
					out << "\t\t\t" << " m_Info." << name  << " = QObject::tr(attr->value());"<< "\n";
				}
			}
			else
			{
				out << "\t\t\t" << " m_Info." << name  << " = QObject::tr(attr->value());"<< "\n";
			}

			out << "\t\t" << "}\n\n";
		}
		out << "\t" << "}\n";

		/***************  XML 结束  *********************/
		
		out << "\t"<<className << "_Struct " << "getInfo()" << "\n";
		out <<"\t{\n";
		out << "\t\treturn m_Info;\n";
		out << "\t}\n";

		out << "protected:\n\n";
		out << "\t" << className + "_Struct " << "m_Info ;" << "\n";

		out << "};\n\n";
		out << "#endif\n";
		out.flush();
		destfile.close();

		std::cout << "Write:" << className.toStdString() << "_Auto.h" << "\n";

	}
}

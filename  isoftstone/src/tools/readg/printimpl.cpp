
#include "func.h"

extern QMap<QString,QString> attrTypeMap;
extern QMap<QString,QString> valueMap;

void printImplHClass(QMap<QString,QStringList> classMap)
{
	QMapIterator<QString,QStringList> iter(classMap);
	while(iter.hasNext())
	{
		iter.next();

		QString className = iter.key();
		//const QStringList& lstAttr = iter.value();

		//////////////       头文件部分开始          ///////////////////////

		QString dest = getAutoHome() + "../itemlib/" + className + ".h";
		QFile destfile(dest);
		if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			return;
		}
		QTextStream out(&destfile);
		out << "#ifndef CLASS_" << className.toUpper() <<"_H\n";
		out << "#define CLASS_" << className.toUpper() <<"_H\n\n";

		/***************  包含头文件开始  *********************/
		out << "#include <QGraphicsItem>\n";
		out << "#include <QDataStream>\n";
		out << "#include <QString>\n";

		out << "\n";
		out << "#include \"interface.h\"\n";
		out << "#include \"macro.h\"\n";
		out << "#include \"" << className << "_Auto.h" << "\"";
		out << "\n\n";

		/***************  包含头文件结束  *********************/

		out << "class EXPORT_LIB " << "C" << className << " : public C" << className << "_Auto" << "\n";
		out << "{\n";

		out << "public:\n\n";

		/***************  公共函数开始  *********************/

		out <<"\t" << "virtual ~C" << className << "();" << "\n\n";

		out <<"\t" << "virtual void init();" << "\n\n";

		out <<"\t" << "virtual QGraphicsItem* clone() ;" << "\n\n";

		out <<"\t" << "virtual QRectF boundingRect() const ;" << "\n\n";

		out <<"\t" << "virtual QPixmap pixmap() ;" << "\n\n";

		out <<"\t" << "virtual void setValue(const QVariant& varValue) ;" << "\n\n";

		/***************  公共函数结束  *********************/

		/***************  保护函数开始  *********************/

		out << "\nprotected:\n\n";

		out <<"\t" << "virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );" << "\n";
		//out << "\t{\n";
		//out <<"\t}\n\n";

		/***************  保护函数结束  *********************/

		/***************  私有成员开始  *********************/

		out << "\nprivate:\n\n";


		/***************  私有成员结束  *********************/

		out << "};\n\n";
		out << "#endif\n";
		out.flush();
		destfile.close();

		std::cout << "Write:" << className.toStdString() << ".h" << "\n";

		//////////////       头文件部分结束          ///////////////////////


	}
}

void printImplCPPClass(QMap<QString,QStringList> classMap)
{
	QMapIterator<QString,QStringList> iter(classMap);
	while(iter.hasNext())
	{
		iter.next();

		QString className = iter.key();
		//const QStringList& lstAttr = iter.value();

		//////////////       CPP文件部分开始          ///////////////////////

		QString dest = getAutoHome() + "../itemlib/" + className + ".cpp";
		QFile destfile(dest);
		if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			return;
		}
		QTextStream out(&destfile);

		/***************  包含头文件开始  *********************/
		//out << "#include <QGraphicsItem>\n";

		out << "\n";
		//out << "#include \"macro.h\"\n";
		out << "#include \"" << className << ".h" << "\"";
		out << "\n\n";

		/***************  包含头文件结束  *********************/


		/***************  函数实现开始  *********************/

		out << "C" << className <<"::~C" << className << "() " << "\n";
		out << "{\n";
		out <<"}\n\n";

		out << "QGraphicsItem* " << "C" << className <<"::" << "clone() " << "\n";
		out << "{\n";
		out << "\t C" << className << "* cl = new C" << className << ";\n";
		out <<"\t cl->m_Info = this->m_Info;\n";
		out <<"\t return cl;\n";
		out <<"}\n\n";

		out << "void " << "C" << className <<"::" << "init() " << "\n";
		out << "{\n";
		out <<"}\n\n";

		out << "QRectF " << "C" << className <<"::" << "boundingRect() const " << "\n";
		out << "{\n";
		out << "\t QRectF boundRect;\n\n";
		out <<"\t return boundRect;\n";
		out <<"}\n\n";

		out << "QPixmap " << "C" << className <<"::" << "pixmap() " << "\n";
		out << "{\n";
		out <<"\t return QPixmap();\n";
		out <<"}\n\n";

		out << "void " << "C" << className <<"::" << "setValue(const QVariant& varValue) " << "\n";
		out << "{\n";
		out <<"\t Q_UNUSED(varValue);\n";
		out <<"}\n\n";

		////

		out << "void " << "C" << className <<"::" << "paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget ) " << "\n";
		out << "{\n";
		out << "\tQ_UNUSED(painter);\n";
		out << "\tQ_UNUSED(option);\n";
		out << "\tQ_UNUSED(widget);\n";
		out << "}\n\n";

		/***************  函数实现结束  *********************/

		out.flush();
		destfile.close();

		std::cout << "Write:" << className.toStdString() << ".cpp" << "\n";

		//////////////       CPP文件部分结束          ///////////////////////


	}
}

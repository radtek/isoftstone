
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

		//////////////       ͷ�ļ����ֿ�ʼ          ///////////////////////

		QString dest = getAutoHome() + "../itemlib/" + className + ".h";
		QFile destfile(dest);
		if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			return;
		}
		QTextStream out(&destfile);
		out << "#ifndef CLASS_" << className.toUpper() <<"_H\n";
		out << "#define CLASS_" << className.toUpper() <<"_H\n\n";

		/***************  ����ͷ�ļ���ʼ  *********************/
		out << "#include <QGraphicsItem>\n";
		out << "#include <QDataStream>\n";
		out << "#include <QString>\n";

		out << "\n";
		out << "#include \"interface.h\"\n";
		out << "#include \"macro.h\"\n";
		out << "#include \"" << className << "_Auto.h" << "\"";
		out << "\n\n";

		/***************  ����ͷ�ļ�����  *********************/

		out << "class EXPORT_LIB " << "C" << className << " : public C" << className << "_Auto" << "\n";
		out << "{\n";

		out << "public:\n\n";

		/***************  ����������ʼ  *********************/

		out <<"\t" << "virtual ~C" << className << "();" << "\n\n";

		out <<"\t" << "virtual void init();" << "\n\n";

		out <<"\t" << "virtual QGraphicsItem* clone() ;" << "\n\n";

		out <<"\t" << "virtual QRectF boundingRect() const ;" << "\n\n";

		out <<"\t" << "virtual QPixmap pixmap() ;" << "\n\n";

		out <<"\t" << "virtual void setValue(const QVariant& varValue) ;" << "\n\n";

		/***************  ������������  *********************/

		/***************  ����������ʼ  *********************/

		out << "\nprotected:\n\n";

		out <<"\t" << "virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );" << "\n";
		//out << "\t{\n";
		//out <<"\t}\n\n";

		/***************  ������������  *********************/

		/***************  ˽�г�Ա��ʼ  *********************/

		out << "\nprivate:\n\n";


		/***************  ˽�г�Ա����  *********************/

		out << "};\n\n";
		out << "#endif\n";
		out.flush();
		destfile.close();

		std::cout << "Write:" << className.toStdString() << ".h" << "\n";

		//////////////       ͷ�ļ����ֽ���          ///////////////////////


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

		//////////////       CPP�ļ����ֿ�ʼ          ///////////////////////

		QString dest = getAutoHome() + "../itemlib/" + className + ".cpp";
		QFile destfile(dest);
		if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			return;
		}
		QTextStream out(&destfile);

		/***************  ����ͷ�ļ���ʼ  *********************/
		//out << "#include <QGraphicsItem>\n";

		out << "\n";
		//out << "#include \"macro.h\"\n";
		out << "#include \"" << className << ".h" << "\"";
		out << "\n\n";

		/***************  ����ͷ�ļ�����  *********************/


		/***************  ����ʵ�ֿ�ʼ  *********************/

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

		/***************  ����ʵ�ֽ���  *********************/

		out.flush();
		destfile.close();

		std::cout << "Write:" << className.toStdString() << ".cpp" << "\n";

		//////////////       CPP�ļ����ֽ���          ///////////////////////


	}
}


#include "func.h"

extern QMap<QString,QString> attrTypeMap;
extern QMap<QString,QString> valueMap;

void printClassFactory_H(QMap<QString,QStringList> classMap)
{
	//////////////       ͷ�ļ����ֿ�ʼ          ///////////////////////

	QString dest = getAutoHome() + "../itemlib/factory" + ".h";
	QFile destfile(dest);
	if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	QTextStream out(&destfile);
	out << "#ifndef CLASS_FACTORY_H" << "\n";
	out << "#define CLASS_FACTORY_H" <<"\n\n";

	/***************  ����ͷ�ļ���ʼ  *********************/
	out << "#include <QGraphicsItem>\n";
	out << "#include <QString>\n\n";
	out << "#include <map>\n\n";

	out << "#include \"macro.h\"\n\n";

	QMapIterator<QString,QStringList> iter(classMap);
	while(iter.hasNext())
	{
		iter.next();

		QString className = iter.key();
		out << "#include \"" << className << ".h" << "\"\n";
	}
	out << "\n\n";
	/***************  ����ͷ�ļ�����  *********************/

	out << "class EXPORT_LIB " << "CItemFactory\n";
	out << "{\n";

	out << "public:\n\n";

	/***************  ����������ʼ  *********************/

	out <<"\t" << "void createBasicItem() ;" << "\n";

	/***************  ������������  *********************/

	/***************  ����������ʼ  *********************/

	out << "\nprotected:\n\n";

	//out <<"\t" << "virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );" << "\n";

	/***************  ������������  *********************/

	/***************  ˽�г�Ա��ʼ  *********************/

	out << "\nprivate:\n\n";

	out << "\tstd::map<QString,QGraphicsItem*> m_ItemMap;\n\n";

	/***************  ˽�г�Ա����  *********************/

	out << "};\n\n";
	out << "#endif\n";
	out.flush();
	destfile.close();

	//////////////       ͷ�ļ����ֽ���          ///////////////////////
}

void printClassFactory_CPP(QMap<QString,QStringList> classMap)
{

	//////////////       CPP�ļ����ֿ�ʼ          ///////////////////////

	QString dest = getAutoHome() + "../itemlib/factory" + ".cpp";
	QFile destfile(dest);
	if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	QTextStream out(&destfile);

	/***************  ����ͷ�ļ���ʼ  *********************/
	//out << "#include <QGraphicsItem>\n";

	out << "\n";
	out << "#include \"factory.h\"\n";
	out << "\n\n";

	/***************  ����ͷ�ļ�����  *********************/


	/***************  ����ʵ�ֿ�ʼ  *********************/

	out << "void " << "CItemFactory" <<"::" << "createBasicItem() " << "\n";
	out << "{\n";

	QMapIterator<QString,QStringList> iter(classMap);
	while(iter.hasNext())
	{
		iter.next();
		QString className = iter.key();

		QString strTable =getTabSpace(className);
		out <<"\t m_ItemMap.insert(std::make_pair(\"" << className << "\"," << strTable << " new C" << className << "));\n";
	}

	out <<"}\n\n";


	/***************  ����ʵ�ֽ���  *********************/

	out.flush();
	destfile.close();

	//////////////       CPP�ļ����ֽ���          ///////////////////////

}

#include "func.h"

extern QMap<QString,QString> attrTypeMap;
extern QMap<QString,QString> valueMap;

void printClassFactory_H(QMap<QString,QStringList> classMap)
{
	//////////////       头文件部分开始          ///////////////////////

	QString dest = getAutoHome() + "../itemlib/factory" + ".h";
	QFile destfile(dest);
	if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	QTextStream out(&destfile);
	out << "#ifndef CLASS_FACTORY_H" << "\n";
	out << "#define CLASS_FACTORY_H" <<"\n\n";

	/***************  包含头文件开始  *********************/
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
	/***************  包含头文件结束  *********************/

	out << "class EXPORT_LIB " << "CItemFactory\n";
	out << "{\n";

	out << "public:\n\n";

	/***************  公共函数开始  *********************/

	out <<"\t" << "void createBasicItem() ;" << "\n";

	/***************  公共函数结束  *********************/

	/***************  保护函数开始  *********************/

	out << "\nprotected:\n\n";

	//out <<"\t" << "virtual void paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );" << "\n";

	/***************  保护函数结束  *********************/

	/***************  私有成员开始  *********************/

	out << "\nprivate:\n\n";

	out << "\tstd::map<QString,QGraphicsItem*> m_ItemMap;\n\n";

	/***************  私有成员结束  *********************/

	out << "};\n\n";
	out << "#endif\n";
	out.flush();
	destfile.close();

	//////////////       头文件部分结束          ///////////////////////
}

void printClassFactory_CPP(QMap<QString,QStringList> classMap)
{

	//////////////       CPP文件部分开始          ///////////////////////

	QString dest = getAutoHome() + "../itemlib/factory" + ".cpp";
	QFile destfile(dest);
	if (!destfile.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}
	QTextStream out(&destfile);

	/***************  包含头文件开始  *********************/
	//out << "#include <QGraphicsItem>\n";

	out << "\n";
	out << "#include \"factory.h\"\n";
	out << "\n\n";

	/***************  包含头文件结束  *********************/


	/***************  函数实现开始  *********************/

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


	/***************  函数实现结束  *********************/

	out.flush();
	destfile.close();

	//////////////       CPP文件部分结束          ///////////////////////

}
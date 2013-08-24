
#pragma once

#include <QString>
#include <QMap>

#include "slnproject.h"

class CCreateSln
{
public:

	CCreateSln();
	~CCreateSln();

	void run();
	void execute(CProjectNode* parent,QString folder);
	void setSlnName(QString folder);
	QString getRelativePath(QString path);
	bool filter(QFileInfo info );
	
private:

	void writeGlobal();

private:

	CProjectNode* m_rootNode;
	QString m_mainFolder;
	QFile* m_file;
	QTextStream* m_stream;
	QMap<QString,QString> m_nodeMap;
};
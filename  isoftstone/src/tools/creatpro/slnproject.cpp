
#include "common.h"
#include "slnproject.h"

CProjectNode::CProjectNode(CProjectNode* parent)
{
	m_parentNode = parent;
	m_folderGuid = "2150E333-8FDC-42A3-9474-1A3956D46DE8";
	m_childList.clear();
	m_itemMap.clear();
}

CProjectNode* CProjectNode::getParent()
{
	return m_parentNode;
}

void CProjectNode::setFolderGuid(QString folderguid)
{
	m_folderGuid = folderguid;
}

void CProjectNode::setItemName(QString itemname)
{
	m_itemName = itemname;
}

QString CProjectNode::getItemName()
{
	return m_itemName;
}

void CProjectNode::setItemGuid(QString itemguid)
{
	m_itemGuid = itemguid; 
}

QString CProjectNode::getItemGuid()
{
	return m_itemGuid;
}

void CProjectNode::addItem(QString key,QString value)
{
	m_itemMap.insert(key,value);
}

void CProjectNode::addChild(CProjectNode* child)
{
	m_childList.append(child);
}

QList<CProjectNode*> CProjectNode::getChildList()
{
	return m_childList;
}

void CProjectNode::write2File(QTextStream& stream)
{
	stream << "Project(\"{" << m_folderGuid << "}\") = \"" << m_itemName << "\", \"" << m_itemName << "\", \"" << m_itemGuid << "\"" << ENDLINE;
	if(m_itemMap.count() > 0)
	{
		stream << "\t" << "ProjectSection(SolutionItems) = preProject" << ENDLINE;
		QMap<QString,QString>::Iterator iter = m_itemMap.begin();
		for (;iter != m_itemMap.end() ; iter++)
		{
			QString key = iter.key();
			QString value = iter.value();
			stream << "\t\t" << key << " = " << value << ENDLINE;
		}
		stream << "\t" << "EndProjectSection" << ENDLINE;
	}
	stream << "EndProject" << ENDLINE;

	for (int i = 0 ; i < m_childList.count() ; i++)
	{
		CProjectNode* child = m_childList.at(i);
		child->write2File(stream);
	}
}
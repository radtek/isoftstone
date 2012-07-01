#ifndef _COMMONCOMMAND_H_
#define _COMMONCOMMAND_H_

#include <occi.h>
#include "sqlcommand.h"


using namespace oracle::occi;

enum ETableAction
{
	eCountTableAction,
	eDropTableAction,
	eTruncateTableAction,
	eUnknownTableAction
};


class CTableActionCommand : public CUpdateCommand
{
public:

	CTableActionCommand(const std::string& actionSQL,const ETableAction& action)
		:CUpdateCommand(actionSQL),m_action(action)
	{
	}

	virtual unsigned int execute()
	{
		unsigned int ret = 1;
		std::string sql = "";
		std::string actionSQL = m_exeSQL;
		switch (m_action)
		{
		case eCountTableAction:
			{
				sql = "select count(*) from ";
				sql += actionSQL;
			}
			break;
		case eDropTableAction:
			{
				sql = "drop table ";
				sql += actionSQL;
			}
			break;
		case eTruncateTableAction:
			{
				sql = "truncate table ";
				sql += actionSQL;
				sql += " drop storage";
			}
			break;
		case eUnknownTableAction:
		default:
			{
				sql += actionSQL;
			}
			break;
		}
		m_state->setSQL(sql);
		CLogger::instance()->info( sql );
		switch (m_action)
		{
		case eCountTableAction:
			{
				ResultSet* dataSet = m_state->executeQuery();
				if (dataSet->next())
				{
					ret = dataSet->getUInt(1);
				}
				m_state->closeResultSet(dataSet);
			}
			break;
		case eUnknownTableAction:
		default:
			{
				ret = m_state->executeUpdate();
			}
			break;
		}
		return ret;
	}
	
	ETableAction m_action;
};

#endif
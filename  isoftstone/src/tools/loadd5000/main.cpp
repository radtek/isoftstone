
#include <stdio.h>
#include <stdlib.h>
#include <QTextCodec>
#include <QtXml>
#include <QString>
#include <QDir>
#include <QFile>
#include <QMap>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QStringList>
#include <QDebug>
#include <QSettings>
#include <QtCore>
#include <QThreadPool>

#include <iostream>

#include "./rtdb_api_sim.h"
#include "./vcimdbdata.h"
#include "Logger.h"

QMap<int,QString> g_tableMap;
QVector<quint64> vecApps;
QVector<int> vecContexts;
QMap<QString,quint64> g_AppMap;

void initAppContext(const QString& dir,const QString& strFileName)
{
	QSettings st(dir + strFileName,QSettings::IniFormat);
	st.beginGroup("ALLAPP");

	QStringList lstApp = st.allKeys();
	foreach(QString app,lstApp)
	{
		quint64 appID = st.value(app).toLongLong();
		g_AppMap.insert(app,appID);

		vecApps.append(appID);
	}
	st.endGroup();

	vecContexts.append((int)AC_REALTIME_NO);
// 	vecContexts.append((int)AC_STUDY_NO);
// 	vecContexts.append((int)AC_RESEARCH_NO);
// 	vecContexts.append((int)AC_PLAN_NO);
// 	vecContexts.append((int)AC_TEST_NO);
// 	vecContexts.append((int)AC_PDR_NO);
// 	vecContexts.append((int)AC_DTS_NO);
// 	vecContexts.append((int)AC_TRAINING_NO);
// 	vecContexts.append((int)AC_SYS_NO);
}

QStringList getDownApp(const QString& strApp)
{
	QFile file(strApp);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
		return QStringList();

	QStringList lstApp;
	QTextStream in(&file);
	while (!in.atEnd()) 
	{
		QString line = in.readLine().simplified();
		if (!line.isEmpty())
		{
			lstApp.append(line);
		}
	}
	file.close();
	return lstApp;
}

QStringList loadApp(const QString& dir,const QString& strApp,QMap<int,QString>& tableMap)
{
	QStringList lstTable;

	QString strFile = dir + "/down_load_" + strApp.toUpper() + ".sys";
	if (QFile::exists(strFile))
	{
		QFile file(strFile);
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
			return lstTable;
		
		LoggerI::instance()->print(strFile);
		QTextStream in(&file);
		while (!in.atEnd()) 
		{
			QString line = in.readLine().simplified();
			QStringList lst = line.split(' ');
			if (lst.count() > 1)
			{
				QString strTable = lst[0];
				int	ntableID = lst[1].toInt();
				
				lstTable.append(strTable);

				LoggerI::instance()->print(strTable);

				if (tableMap.contains(ntableID) == false)
				{
					tableMap.insert(ntableID,strTable);
				}
			}
		}
		file.close();
	}
	return lstTable;
}

QXmlStreamWriter& createTableNode(QXmlStreamWriter& writer,const TABLE_PARA_STRU& param,int nTableID)
{
	writer.writeStartElement(param.table_name_eng);
	writer.writeAttribute("nTableID",QString::number(nTableID));
 	writer.writeAttribute("table_name_chn",QString(param.table_name_chn));
	writer.writeAttribute("record_number",QString::number(param.record_number));
 	writer.writeAttribute("max_valid_rec",QString::number(param.max_valid_rec));
 	writer.writeAttribute("min_valid_rec",QString::number(param.min_valid_rec));
 	writer.writeAttribute("max_idle_rec",QString::number(param.max_idle_rec));
 	writer.writeAttribute("min_idle_rec",QString::number(param.min_idle_rec));
 	writer.writeAttribute("key_len",QString::number(param.key_len));
 	writer.writeAttribute("subkey_num",QString::number(param.subkey_num));
 	writer.writeAttribute("record_size",QString::number(param.record_size));
 	writer.writeAttribute("field_sum",QString::number(param.field_sum));
 	writer.writeAttribute("is_auto_generated",QString::number(param.is_auto_generated));
	writer.writeEndElement();

	return writer;
}

QXmlStreamWriter& createFieldNode(QXmlStreamWriter& writer,const FIELD_PARA_STRU& param)
{
	writer.writeStartElement("Field");
	writer.writeAttribute("column_id",QString::number(param.column_id));
	writer.writeAttribute("field_length",QString::number(param.field_length));
	writer.writeAttribute("column_special",QString::number(param.column_special));
	writer.writeAttribute("field_no",QString::number(param.field_no));
	writer.writeAttribute("offset",QString::number(param.offset));
	writer.writeAttribute("ref_tableno",QString::number(param.ref_tableno));
	writer.writeAttribute("ref_fieldno",QString::number(param.ref_fieldno));
	writer.writeAttribute("subkey_num",QString::number(param.search_attribute));

	writer.writeAttribute("field_name_eng",QString(param.field_name_eng));
	writer.writeAttribute("field_name_chn",QString(param.field_name_chn));
	writer.writeAttribute("menu_name",QString(param.menu_name));
	writer.writeAttribute("default_asciival",QString(param.default_asciival));
	writer.writeAttribute("min_asciival",QString(param.min_asciival));
	writer.writeAttribute("max_asciival",QString(param.max_asciival));

	writer.writeAttribute("data_type",QString::number(param.data_type));
	writer.writeAttribute("is_keyword",QString::number(param.is_keyword));
	writer.writeAttribute("is_index",QString::number(param.is_index));
	writer.writeAttribute("allow_null",QString::number(param.allow_null));
	writer.writeAttribute("sort_order_no",QString::number(param.sort_order_no));
	writer.writeAttribute("display_type",QString::number(param.display_type));
	writer.writeAttribute("reference_flag",QString::number(param.reference_flag));
	writer.writeAttribute("reference_display",QString::number(param.reference_display));
	
	writer.writeEndElement();

	return writer;
}

bool saveTableToXml(QXmlStreamWriter& writer,const QString& strTable)
{
	TABLE_PARA_STRU table_Param;
	QVector<FIELD_PARA_STRU> vecFieldParams;
	
	VCimTable vTable(strTable.toLocal8Bit().data());    

	bool bOpen = false;
	int i = 0 ; 
	while(!bOpen && i < vecApps.count())
	{
		int j = 0 ;
		while (j < vecContexts.count())
		{
			bOpen = vTable.reOpen(vecApps[i],vecContexts[j]);
			// 起初考虑打开表需要对应应用和态都正确，其实只要一种态即可
			//if (bOpen)
			//{
			//	bool bTable = vTable.getTableParam(table_Param);
			//	if (bTable)
			//	{
			//		LoggerI::instance()->print(strTable + " App = " + QString::number(vecApps[i]) + " Context = " +   QString::number(vecContexts[j]) );
			//		break;
			//	}
			//}
			j++;
		}
		i++;
	}
	if (bOpen)
	{
		bool bTable = vTable.getTableParam(table_Param);
		if (bTable)
		{
 			createTableNode(writer,table_Param,vTable.getTableID());

			LoggerI::instance()->print(strTable + " ID = " + QString::number(vTable.getTableID()) + QObject::tr(" 获取到表信息"));

 			bool bFiled = vTable.getFieldsPara(vecFieldParams);
 			if (bFiled)
 			{
				writer.setAutoFormattingIndent( writer.autoFormattingIndent() + 4 );
 				foreach (FIELD_PARA_STRU param,vecFieldParams)
 				{
 					createFieldNode(writer,param);
 				}
				writer.setAutoFormattingIndent( writer.autoFormattingIndent() - 4 );
 			}
			return true;
		}
		else
		{
			LoggerI::instance()->print(strTable + " ID = " + QString::number(vTable.getTableID()) + QObject::tr(" 获取表信息失败") );
			return false;
		}
	}
	else
	{
		LoggerI::instance()->print(strTable + "  "  +  QString::number(vTable.getTableID()) + QObject::tr("  查询表结构失败 " ));
		return false;
	}
}

bool saveTableToXml(QXmlStreamWriter& writer,int nTable)
{
	LoggerI::instance()->print( QObject::tr(" => 表号 :") + QString::number(nTable));
	QString strTable = VCimTable::getTableNameByID(nTable);
	if (strTable.isEmpty())
	{
		LoggerI::instance()->print(strTable +  QObject::tr(" 未找到表名"));
		return false;
	}
	return saveTableToXml(writer,strTable);
}

void saveAllTable()
{
	if (QDir::current().exists("xml") == false)
	{
		QDir::current().mkdir("xml");
	}

	QFile file("./xml/D5000Table.xml");
	if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
	{
		return;
	}

	QXmlStreamWriter writer(&file);
	writer.setAutoFormatting(true);
	writer.setAutoFormattingIndent( 4 );
	writer.writeStartDocument();
	writer.writeStartElement("ROOT");
	
	for (int i = 1 ; i < 12828; i++)
	{
		saveTableToXml(writer,i);
	}

	writer.writeEndElement();// root
	writer.writeEndDocument(); //doc
	file.close();
}

void saveDataToTxt(const QString& dir,const QString& strTable ,const QString& strApp,quint64 appID)
{
	// 首先读取列信息
	std::cout << strApp.toLocal8Bit().data() << "  " << strTable.toLocal8Bit().data() << "\n";

	VCimTable vTable(strTable.toLocal8Bit().data());    
	bool bOpen = vTable.reOpen(appID,vecContexts[0]);
	if (bOpen)
	{
		QString appDir = dir + strApp;
		if (QDir::current().exists(appDir) == false)
		{
			QDir::current().mkdir(appDir);
		}

		QFile file(appDir + "/" + strTable + ".txt");
		if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			return;
		}
		QTextStream out(&file);

		QVector< QVector<QVariant> > vecRows;
		vTable.getTableRecs(vecRows);
		
		QVector<FIELD_PARA_STRU> vecFieldParams;
		bool bFiled = vTable.getFieldsPara(vecFieldParams);
		if (bFiled)
		{
			for (int i = 0 ; i < vecFieldParams.count() ; i++)
			{
				out << QString::fromLocal8Bit(vecFieldParams[i].field_name_chn) << "(" << vecFieldParams[i].field_name_eng << ")\t";
			}
			out << "\n\n";
		}
		for (int i = 0 ; i < vecRows.count() ; i++)
		{
			QString strLine ;
			for (int j = 0 ; j < vecRows[i].count() ; j++)
			{
				QString tmp = vecRows[i][j].toString();
				// 此处对数据进行增加长度效果不是太好，所以暂时屏蔽掉
// 				if (tmp.length() < vecLengths[j])
// 				{
// 					for (int t = 0 ; t < vecLengths[j] - tmp.length() ; t++)
// 					{
// 						tmp += ' ';
// 					}
// 				}
				strLine += tmp + "\t";
			}
			strLine += "\n";

			out << strLine;
		}
		file.close();
	}
}

void saveDataToTxt(const QString& dir,int nTableID ,const QString& strApp,quint64 appID)
{
	LoggerI::instance()->print( QObject::tr(" => 表号 :") + QString::number(nTableID));
	QString strTable = VCimTable::getTableNameByID(nTableID);
	saveDataToTxt(dir,strTable,strApp,appID);
}

void saveDataToTxt(const QStringList& lst)
{
	if (lst.count() == 3)
	{
		saveDataToTxt(lst[0],lst[1],lst[2],g_AppMap[lst[2]]);
	}
}

void getTableParamMap(QMap<int,TABLE_PARA_STRU>& tableParamMap)
{
	// 表信息
	VCimTable vTable(1);    
	bool bOpen = vTable.reOpen(AP_SCADA,AC_REALTIME_NO);

	if (bOpen)
	{
		QVector< QVector<QVariant> > vecRows;
		vTable.getTableRecs(vecRows);

		QVector<FIELD_PARA_STRU> vecFieldParams;
		bool bFiled = vTable.getFieldsPara(vecFieldParams);

		if (bFiled)
		{
			// 表号到表信息的映射

			foreach (QVector<QVariant> vecFiledValue,vecRows)
			{
				if (vecFiledValue.count() == vecFieldParams.count())
				{
					TABLE_PARA_STRU table_param;
					table_param.field_sum = vecFieldParams.count();
					int tableID = 0;
					for (int i = 0 ; i < vecFieldParams.count() ; i++)
					{
						FIELD_PARA_STRU& param = vecFieldParams[i];
						QVariant& varValue = vecFiledValue[i];
						//qDebug() << param.field_name_eng << "\n";
						if (!strcmp(param.field_name_eng,"table_id"))
						{
							tableID = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "table_name_eng"))
						{
							strcpy(table_param.table_name_eng,varValue.toByteArray().data());
						}
						else if (!strcmp(param.field_name_eng , "table_name_chn"))
						{
							strcpy(table_param.table_name_chn,varValue.toByteArray().data());
						}
						else if (!strcmp(param.field_name_eng , "max_record_num"))
						{
							table_param.record_number = varValue.toInt();
						}

						table_param.record_size += param.field_length;
					}

					tableParamMap.insert(tableID,table_param);
				}
			}
		}
	}
}

void getFieldParamMap(QMap<int,QVector<FIELD_PARA_STRU> >& filedParamMap)
{
	// 表信息
	VCimTable vTable(2);    
	bool bOpen = vTable.reOpen(AP_SCADA,AC_REALTIME_NO);

	if (bOpen)
	{
		QVector< QVector<QVariant> > vecRows;
		vTable.getTableRecs(vecRows);

		QVector<FIELD_PARA_STRU> vecFieldParams;
		bool bFiled = vTable.getFieldsPara(vecFieldParams);

		if (bFiled)
		{
			// 表号到表信息的映射

			foreach (QVector<QVariant> vecFiledValue,vecRows)
			{
				if (vecFiledValue.count() == vecFieldParams.count())
				{
					int tableID = 0;
					int offset = 0;
					FIELD_PARA_STRU filed_param;
					for (int i = 0 ; i < vecFieldParams.count() ; i++)
					{
						FIELD_PARA_STRU& param = vecFieldParams[i];
						QVariant& varValue = vecFiledValue[i];

						if (!strcmp(param.field_name_eng , "table_id"))
						{
							tableID = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "column_id"))
						{
							filed_param.column_id = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "field_id"))
						{
							filed_param.field_no = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "column_name_eng"))
						{
							strcpy(filed_param.field_name_eng,varValue.toString().toLocal8Bit().data());
						}
						else if (!strcmp(param.field_name_eng , "column_name_chn"))
						{
							strcpy(filed_param.field_name_chn,varValue.toString().toLocal8Bit().data());
						}
						else if (!strcmp(param.field_name_eng , "data_type"))
						{
							filed_param.data_type = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "data_length"))
						{
							filed_param.field_length = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "column_special"))
						{
							filed_param.column_special = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "is_key"))
						{
							filed_param.is_keyword = varValue.toUInt();
						}
						else if (!strcmp(param.field_name_eng , "allow_null"))
						{
							filed_param.allow_null = varValue.toUInt();
						}
						else if (!strcmp(param.field_name_eng , "reference_table"))
						{
							filed_param.ref_tableno = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "reference_column"))
						{
							filed_param.ref_fieldno = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "sort_order_no"))
						{
							filed_param.sort_order_no = varValue.toUInt();
						}
						else if (!strcmp(param.field_name_eng , "init_value"))
						{
							strcpy(filed_param.default_asciival,varValue.toString().toLocal8Bit().data());
						}
						else if (!strcmp(param.field_name_eng , "min_value"))
						{
							strcpy(filed_param.min_asciival,varValue.toString().toLocal8Bit().data());
						}
						else if (!strcmp(param.field_name_eng , "max_value"))
						{
							strcpy(filed_param.max_asciival,varValue.toString().toLocal8Bit().data());
						}
						else if (!strcmp(param.field_name_eng , "menu_name"))
						{
							strcpy(filed_param.menu_name,varValue.toString().toLocal8Bit().data());
						}
						else if (!strcmp(param.field_name_eng , "search_attribute"))
						{
							filed_param.search_attribute = varValue.toInt();
						}
						else if (!strcmp(param.field_name_eng , "reference_display"))
						{
							filed_param.reference_display = varValue.toUInt();
						}
						else if (!strcmp(param.field_name_eng , "reference_flag"))
						{
							filed_param.reference_flag = varValue.toUInt();
						}
						else if (!strcmp(param.field_name_eng , "display_type"))
						{
							filed_param.display_type = varValue.toUInt();
						}
						filed_param.offset = offset;
						offset += param.field_length;

					}

					filedParamMap[tableID ].append(filed_param);
				}
			}
		}
	}
}


// 保存表模式
void saveStudioToSQLFile(const QString& dir)
{
	QString appDir = dir + "/studio_sql";
	if (QDir::current().exists(appDir) == false)
	{
		QDir::current().mkdir(appDir);
	}

	QMap<int,TABLE_PARA_STRU> tableParamMap;
	QMap<int,QVector<FIELD_PARA_STRU> > filedParamMap;
	getTableParamMap(tableParamMap);
	getFieldParamMap(filedParamMap);
	
	QMapIterator<int,TABLE_PARA_STRU> iter(tableParamMap);
	while(iter.hasNext())
	{
		iter.next();

		int tableID = iter.key();
		const TABLE_PARA_STRU& table_param = iter.value();

		QVector<FIELD_PARA_STRU>& vecFileds = filedParamMap[tableID];
		
		QString strTableID =  QString::number(tableID);
		int oldLength = strTableID.length();
		int nZero = 0;
		while(nZero < (5 - oldLength))
		{
			strTableID.prepend('0');
			nZero++;
		}
		QString strTable = strTableID + "-" + table_param.table_name_eng + "-" + table_param.table_name_chn;
		QFile file(appDir + "/" + strTable + ".sql");
		if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			continue;
		}
		QTextStream out(&file);
		// 增加创建表结构
		out << "create table " << table_param.table_name_eng << "( ";
		int index = 0;
		QString keyWord = "";
		bool bMultiKey = false;
		foreach (FIELD_PARA_STRU field_Param,vecFileds)
		{
			index++;
			out << field_Param.field_name_eng << " ";
			if (field_Param.data_type != C_STRING_TYPE && field_Param.data_type != C_TEXT_TYPE && field_Param.data_type != C_UCHAR_TYPE)
			{
				qreal tmpLength = field_Param.field_length*2.5;
				if (tmpLength > qRound(tmpLength))
				{
					tmpLength = qRound(tmpLength) + 1;
				}
				out << "numeric(" << tmpLength << ")";
			}
			else
			{
				out << "varchar(" << field_Param.field_length << ")";
			}
			if (field_Param.allow_null == 0)
			{
				out << " not null";
			}

			if (index != vecFileds.count())
			{
				out << ",";
			}

			if (field_Param.is_keyword != 0)
			{
				if (bMultiKey)
				{
					keyWord +=",";
				}
				keyWord += field_Param.field_name_eng;
				bMultiKey = true;
			}

		}
		out <<");";
		out <<"\n\n";

		// 添加修改表约束
		out << "alter table " << table_param.table_name_eng << " add constraint " << "pk_"<<table_param.table_name_eng ;
		if (bMultiKey)
		{
			out << " primary key (" << keyWord <<");";
		}
		out <<"\n\n";

		// 添加向表信息表中添加表数据
		out <<"insert into sys_table_info(table_id,table_name_eng,table_name_chn,is_system_table,app_type,max_record_num,key_generate_type,is_record_app,is_record_lock,is_record_resp,is_insert_trigger,is_delete_trigger,is_update_trigger,table_version,db_id,tablespace_name,table_description,table_type,pk_index_method,pk_storage_type,pk_mem_alloc_type,reserved_1,reserved_2,reserved_3,reserved_4,reserved_5) "
			"values("<< tableID <<",'"<< table_param.table_name_eng<<"','"<< QString(table_param.table_name_chn)<<"',1,32769,"<< table_param.record_number<<",0,0,0,0,0,0,0,0,0,'OPEN_DATA','',0,-1,-1,0,0,0,0,0,0);\n";

		// 添加向域信息表中添加域数据
		out <<"\n";

		foreach (FIELD_PARA_STRU field_Param,vecFileds)
		{
			out << "insert into sys_column_info(table_id,field_id,column_id,column_name_eng,column_name_chn,data_type,data_length,is_key,allow_null,app_type,is_app_syn,index_order_no,sort_order_no,is_input,is_display,display_order_no,is_fix,display_length,display_precision,align_type,display_type,menu_name,reference_flag,reference_mode,reference_table,reference_column,reference_display,init_value,min_value,max_value,column_special,auto_meas_type,gen_array_dimension,gen_array_name,column_description,search_attribute,statics_attribute,reserved_1,reserved_2,reserved_3,reserved_4,reserved_5) "
				"values("<< tableID<<","<<field_Param.field_no<<","<<field_Param.column_id<<",'"<< field_Param.field_name_eng << "','" << QString(field_Param.field_name_chn )<<"',"<< field_Param.data_type <<","<< field_Param.field_length <<","<<field_Param.is_keyword<<","<< field_Param.allow_null<<",32769,0,0,0,1,1,1,1,10,0,0,4,'',0,0,0,0,1,'','','',0,0,0,'','desp',1,0,0,0,0,0,0);\n";
		}
		file.close();
	}

}


// 保存表模式
void saveStudioToEFile(const QString& dir)
{
	QString appDir = dir + "/studio_e";
	if (QDir::current().exists(appDir) == false)
	{
		QDir::current().mkdir(appDir);
	}

	QMap<int,TABLE_PARA_STRU> tableParamMap;
	QMap<int,QVector<FIELD_PARA_STRU> > filedParamMap;
	getTableParamMap(tableParamMap);
	getFieldParamMap(filedParamMap);

	QMapIterator<int,TABLE_PARA_STRU> iter(tableParamMap);
	while(iter.hasNext())
	{
		iter.next();

		int tableID = iter.key();
		const TABLE_PARA_STRU& table_param = iter.value();

		QVector<FIELD_PARA_STRU>& vecFileds = filedParamMap[tableID];

		QString strTableID =  QString::number(tableID);
		int oldLength = strTableID.length();
		int nZero = 0;
		while(nZero < (5 - oldLength))
		{
			strTableID.prepend('0');
			nZero++;
		}
		QString strTable = strTableID + "-" + table_param.table_name_eng + "-" + table_param.table_name_chn;
		QFile file(appDir + "/" + strTable + ".txt");
		if (!file.open(QIODevice::WriteOnly|QIODevice::Truncate))
		{
			continue;
		}
		QTextStream out(&file);

		out << "tableID=" << tableID << "\n";
		out << "table_name_eng=" << table_param.table_name_eng << "\n";
		out << "table_name_chn=" << QString(table_param.table_name_chn )<< "\n";
		out << "record_number=" << table_param.record_number << "\n";
		out << "record_size=" << table_param.record_size << "\n";
		out << "field_sum=" << table_param.field_sum << "\n";
		
		out <<"---------------------------------------------------------------------------------------\n";
		out <<"\n\n";

		out << "field_id \t column_id \t column_name_eng \t column_name_chn \t data_type \t data_length \t is_key \t allow_null \t init_value \t min_value \t max_value " << "\n\n";

		foreach (FIELD_PARA_STRU field_Param,vecFileds)
		{
			out <<field_Param.field_no<<"\t"<<field_Param.column_id<<"\t'"<< field_Param.field_name_eng << "' \t '" 
				<< QString(field_Param.field_name_chn )<<"' \t "<< field_Param.data_type <<" \t "<< field_Param.field_length <<" \t "<<field_Param.is_keyword<<" \t "<< field_Param.allow_null 
				<< QString(field_Param.default_asciival) << QString(field_Param.min_asciival) <<QString(field_Param.max_asciival) << "\n";
		}

		file.close();
	}

}

int main(int argc, char *argv[])
{
	Q_UNUSED(argc);
	Q_UNUSED(argv);

	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	QTextCodec* codec = QTextCodec::codecForName("GB2312");
	QTextCodec::setCodecForTr(codec); // tr() 会使用此 codec
	QTextCodec::setCodecForLocale(codec); // QString::fromLocal8Bit() 会使用此 codec
	QTextCodec::setCodecForCStrings(codec); // QString::ascii() 会使用此 codec
#ifdef WIN32
	setlocale(LC_ALL,"");
#endif

	QString appSys = "down_load_app.sys";

#ifdef WIN32
	QString confDir = "D:/Vis/conf-guodiao/";
#else
	QString confDir = "/home/d5000/guodiao/conf/";
#endif

	QThreadPool::globalInstance()->setMaxThreadCount(10);

	int oper = 3;

	if (oper == 1)
	{
		initAppContext(confDir,"mng_app_num_name.ini");

		QStringList lstApp = getDownApp(confDir + appSys);

		QVector<QStringList> vecTrans;

		foreach (QString strApp,lstApp)
		{
			QStringList appTables = loadApp(confDir,strApp,g_tableMap);
			foreach(QString strTable,appTables)
			{
				QStringList lst;
				lst.append("./");
				lst.append(strTable);
				lst.append(strApp);
				vecTrans.append(lst);
				// 直接执行为穿行执行，改用并行执行提高效率
				// 但是由于实时数据库不支持多线程同时读取，所以此处改为单线程读取
				saveDataToTxt("./",strTable,strApp,g_AppMap[strApp]);
			}
		}
	}
	else if (oper == 2)
	{
		// 导出模型信息到xml/D5000Table.xml
		// 此模式是通过应用号，态，打开表，然后读取表中字段信息，有个缺点就是如果表打开失败，则不能进行读取，
		// 为此，需要通过打开表信息表和域信息表，构造基础数据，这样就避免了打开其他表失败问题
		saveAllTable();
	}
	else if(oper == 3)
	{
		// 读取表信息表
		saveStudioToSQLFile("./");
	}
	else if(oper == 4)
	{
		// 读取表信息表
		saveStudioToEFile("./");
	}


    return 0;
}


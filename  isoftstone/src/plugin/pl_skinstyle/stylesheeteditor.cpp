

#include <QtGui>
#include <stdlib.h>

#include "macro.h"
#include "stylesheeteditor.h"

extern "C" EXPORT_DLL IPluginBase*  getPlugin()
{
	return new StyleSheetEditor();
}


SPluginInfo StyleSheetEditor::getPluginInfo() 
{
	SPluginInfo info;
	info.pluginName = "pl_stylesheet";
	info.menuName = QObject::tr("Ƥ��");
	info.description = QObject::tr("���������");
	info.object = this;

	return info;
}

void StyleSheetEditor::init() 
{
	m_qSS_Actions.clear();
	loadStyle();
	loadStyleSheet();
}

void StyleSheetEditor::destroy() 
{

}

StyleSheetEditor::StyleSheetEditor()
{
	m_ActionGroup = new QActionGroup(this);
	setupUi(this);
	init();
}

QPair<QString,QStringList> StyleSheetEditor::getMenuInfo()
{
	QPair<QString,QStringList> actPair;
	actPair.first = QObject::tr("Ƥ��");
	actPair.second.append("menuSkin");
	return actPair;
}

void StyleSheetEditor::on_styleCombo_activated(const QString &styleName)
{
    qApp->setStyle(styleName);
    btn_Apply->setEnabled(false);
}

void StyleSheetEditor::on_styleSheetCombo_activated(const QString &sheetName)
{
    loadStyleSheet(sheetName);
}

void StyleSheetEditor::on_txt_Content_textChanged()
{
    btn_Apply->setEnabled(true);
}

void StyleSheetEditor::on_btn_Apply_clicked()
{
    qApp->setStyleSheet(txt_Content->toPlainText());
    btn_Apply->setEnabled(false);
}

void StyleSheetEditor::on_btn_Modify_clicked()
{
	try
	{
		QString strStyle = styleSheetCombo->currentText();
		QString strName = getQssFilePath(strStyle);
		QFile file(strName);
		file.open(QIODevice::WriteOnly | QIODevice::Truncate);
		QString context = txt_Content->toPlainText();
		file.write(context.toLocal8Bit().data());
		file.flush();
	}
	catch(std::exception e)
	{
		QMessageBox::critical(this,"�쳣��ʾ",e.what());
	}
}

void StyleSheetEditor::on_btn_Delete_clicked()
{
	// �ȴ��б���ɾ����Ȼ����ļ�ɾ��,�����б���ɾ��
	
	try
	{
		QString strName = styleSheetCombo->currentText();
		styleSheetCombo->removeItem(styleSheetCombo->currentIndex());
		QString strFile = getQssFilePath(strName);
		QFile::remove(strFile);

		// ��������˵�����ɾ��
		if (m_ToolMenu)
		{
			m_ActionGroup->removeAction(m_qSS_Actions[strName]);
			m_ToolMenu->removeAction(m_qSS_Actions[strName]);
		}

		m_qSS_Actions.remove(strName);

		QMessageBox::information(this,"��ʾ",strName + " ��ʽɾ���ɹ�");
	}
	catch (std::exception e)
	{
		QMessageBox::critical(this,"�쳣��ʾ",e.what());
	}
}

void StyleSheetEditor::on_btn_Add_clicked()
{
	try
	{
		QString strStyle = le_Name->text().simplified();
		if (m_qSS_Actions.contains(strStyle))
		{
			QMessageBox::information(this,"������ʾ",strStyle + " �Ѿ����ڣ����Ϊ��������");
		}
		else
		{
			QString context = txt_Content->toPlainText();
			if (context.isEmpty())
			{
				QMessageBox::information(this,"������ʾ",strStyle + " �ļ�����Ϊ�� ");
			}
			else
			{
				styleSheetCombo->addItem(strStyle);

				QString strName = getQssFilePath(strStyle);
				QFile file(strName);
				file.open(QIODevice::WriteOnly);
				file.write(context.toLocal8Bit().data());
				file.flush();

				createAction(strStyle);
				if (NULL != m_ToolMenu)
				{
					m_ActionGroup->addAction(m_qSS_Actions[strStyle]);
					m_ToolMenu->addAction(m_qSS_Actions[strStyle]);
				}

				QMessageBox::information(this,"������ʾ",strStyle + " ����ɹ�");
			}
		}
	}
	catch(std::exception e)
	{
		QMessageBox::critical(this,"�쳣��ʾ",e.what());
	}
}

void StyleSheetEditor::showWindow()
{
	this->show();
}

QAction* StyleSheetEditor::createAction(const QString& strName)
{
	QAction* action = m_ToolMenu->addAction(strName);
	m_ActionGroup->addAction(action);
	QObject::connect(action, SIGNAL(triggered(bool)), this, SLOT(onActionExecute(bool)));

	m_qSS_Actions.insert(strName,action);
	return action;
}

void StyleSheetEditor::onActionExecute(bool bChecked)
{
	QObject* send = sender();
	QAction* action = dynamic_cast<QAction*>(send);
	if (NULL != action)
	{
		action->setChecked(bChecked);
		QString strStyle = action->text();
		loadStyleSheet(strStyle);
	}
}

void StyleSheetEditor::loadStyle()
{
	QRegExp regExp(".(.*)\\+?Style");
	QString defaultStyle = QApplication::style()->metaObject()->className();

	if (regExp.exactMatch(defaultStyle))
		defaultStyle = regExp.cap(1);

	styleCombo->addItems(QStyleFactory::keys());
	styleCombo->setCurrentIndex(styleCombo->findText(defaultStyle, Qt::MatchContains));
}

QString StyleSheetEditor::getQssDir()
{
	char* visdir = getenv(PROJECT_HOME);
	QString qssdir = QString(visdir) + "/config/qss";
	return qssdir;
}

QString StyleSheetEditor::getQssFilePath(const QString& strName)
{
	return getQssDir() + "/" + strName + ".qss";
}

void StyleSheetEditor::loadStyleSheet()
{
	// ��������qss�����ļ�
	QDir dir(getQssDir(),"*.qss");
	QStringList filters;
	filters << "*.qss";
	dir.setNameFilters(filters);

	QStringList lst = dir.entryList(filters);
	foreach(QString strName,lst)
	{
		strName = strName.remove(".qss");
		styleSheetCombo->addItem(strName);
		createAction(strName);
	}

	// ���ӽ�����ʾ
	QAction* sep = new QAction(this);
	sep->setSeparator(true);

	QAction* show = new QAction(QObject::tr("�������"),this);
	QObject::connect(show, SIGNAL(triggered()), this, SLOT(showWindow()));
}

void StyleSheetEditor::loadStyleSheet(const QString& strStyle)
{
    QFile file(getQssFilePath(strStyle));
    file.open(QFile::ReadOnly);
	QTextStream stream(&file);
    QString styleSheet = stream.readAll();
	file.close();
	txt_Content->setPlainText(QObject::tr(styleSheet.toLocal8Bit().data()));
    qApp->setStyleSheet(styleSheet);
    btn_Apply->setEnabled(false);
}


/****************************************************************************
** CopyRight(c) 2010,�������ķ��̱��Զ����ɷ����޹�˾
** All rights reserved
**
** �ļ�����: stylesheeteditor.h
** ժҪ: Ƥ�������
**       
**
** ��ǰ�汾: 1.0.0.0
** ����:  ����
** �������: 2011.11.1
**
** ȡ���汾:
** ����:
** ������ڣ�
**
** ��ʷ�޸ļ�¼:��
** ���ߡ��������޸�ʱ�䡡���汾�������޸İ汾
** ����      2011.11.1   V1.0      ����
**
****************************************************************************/

#ifndef STYLESHEETEDITOR_H
#define STYLESHEETEDITOR_H

#include <QtGui>

#include "ui_stylesheet.h"
#include "pluginbase.h"
#include "pluginapp.h"

class StyleSheetEditor : public QWidget ,public Ui::CStyleWidget ,public IPluginApplication
{
    Q_OBJECT

public:

    StyleSheetEditor();

public:

	virtual SPluginInfo getPluginInfo() ;
	virtual QPair<QString,QStringList> getMenuInfo();
	virtual void init() ;
	virtual void destroy() ;
	
private slots:

	void on_btn_Add_clicked();
    void on_styleCombo_activated(const QString &styleName);
    void on_styleSheetCombo_activated(const QString &styleSheetName);
    void on_txt_Content_textChanged();
    void on_btn_Apply_clicked();
	void on_btn_Modify_clicked();
	void on_btn_Delete_clicked();

	void onActionExecute(bool);
	void showWindow();

private:

	QString getQssDir();
	QString getQssFilePath(const QString& strName);
	QAction* createAction(const QString& strName);

	void loadStyle();
	void loadStyleSheet();
    void loadStyleSheet(const QString &sheetName);

private:

	QMap<QString,QAction*> m_qSS_Actions;
	QActionGroup*		   m_ActionGroup;

};

#endif

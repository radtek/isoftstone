
/****************************************************************************
** CopyRight(c) 2010,　北京四方继保自动化股份有限公司
** All rights reserved
**
** 文件名称: stylesheeteditor.h
** 摘要: 皮肤插件类
**       
**
** 当前版本: 1.0.0.0
** 作者:  刘瑞功
** 完成日期: 2011.11.1
**
** 取代版本:
** 作者:
** 完成日期：
**
** 历史修改记录:　
** 作者　　　　修改时间　　版本　　　修改版本
** 刘瑞功      2011.11.1   V1.0      创建
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

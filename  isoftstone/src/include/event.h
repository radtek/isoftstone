
#ifndef EVENT_H
#define EVENT_H

#include <QEvent>
#include <QCustomEvent>
#include <QString>

enum ECustomEventType
{
	eEventUser = QEvent::User,
	eEventSceneFileChange,

};

class CSceneFileChangeEvent : public QEvent
{
public:
	CSceneFileChangeEvent(const QString& fileName):QEvent((QEvent::Type)eEventSceneFileChange)
	{
		m_fileName = fileName;
	}

	QString getFileName()
	{
		return m_fileName;
	}

protected:
	QString m_fileName;
};


#endif
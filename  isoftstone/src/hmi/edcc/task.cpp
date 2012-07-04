
#include <math.h>

#include "task.h"
#include "resource.h"
#include "qextserialbase.h"

CDCTask::CDCTask(QextSerialBase* pSerial):m_serial(pSerial)
{
}

void CDCTask::run()
{
	if (m_serial && m_serial->isOpen())
	{
		m_serial->write("collect data",64);
	}
}

CDealDataTask::CDealDataTask()
{
	srand(100);
}

void CDealDataTask::run()
{
	QList<quint64> lstIDs = CResource::instance()->getResourceIDs();
	foreach (quint64 keyid ,lstIDs )
	{
		int value = rand()%100;
		CResource::instance()->setValue(keyid,value);
	}
}

#include <math.h>

#include "task.h"
#include "resource.h"

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
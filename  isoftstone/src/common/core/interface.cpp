
#include "interface.h"
#include "taskpool.h"

CPostTask* QApplication::patchTask(CLObject* receiver,LCustomEvent* event)
{
	// ������������б�
	return new CPostTask(receiver,event);
}



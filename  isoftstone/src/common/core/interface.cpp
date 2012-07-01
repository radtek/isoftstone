
#include "interface.h"
#include "taskpool.h"

CPostTask* QApplication::patchTask(CLObject* receiver,LCustomEvent* event)
{
	// 打包生成任务列表
	return new CPostTask(receiver,event);
}



#ifndef __ERRORCODE_H__ 
#define __ERRORCODE_H__

#include <string> 

enum EErrorCode 
 {
   eLSuccess,
   eLRecordNotFound,
   eLNodeNotExist
}

class CErrorCode
{
public:

   static std::string getError(EErrorCode ecode)
   {
      switch (ecode)
      {
         case eLSuccess : return "成功";
         case eLRecordNotFound : return "记录不存在";
         case eLNodeNotExist : return "结点不存在";
         default : "未知错误 ";
      }
   }
}

#endif

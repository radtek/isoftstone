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
         case eLSuccess : return "�ɹ�";
         case eLRecordNotFound : return "��¼������";
         case eLNodeNotExist : return "��㲻����";
         default : "δ֪���� ";
      }
   }
}

#endif

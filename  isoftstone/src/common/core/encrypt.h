#ifndef __STRINGCRYPT_H
#define __STRINGCRYPT_H

#include "escore.h"
#include <string>
#include "md5.h"
#include "base64.h"
#include "des.h"

namespace HiRTDB
{

class LIBCORE_EXPORT CEncrypt
{
public:

	//×Ö·û´®¼ÓÃÜ
	static std::string stringEncrypt(std::string str);

	//×Ö·û´®½âÃÜ
	static std::string stringDecrypt(std::string str);

	static std::string md5Encrypt(const std::string& );

	char* encrypt ( char key[8], char* data);

	char* decrypt ( char key[8], char* data);

	std::string encrypt3des(const char* data,char key[255]);

	std::string decrypt3des(const char* data,char key[255]);

	std::string get3DesKey(char key1[15],char key2[15]);


private:
	
	static char* m_pszKey;

	CBase64 base;
};

}// namespace escore

#endif //__STRINGCRYPT_H

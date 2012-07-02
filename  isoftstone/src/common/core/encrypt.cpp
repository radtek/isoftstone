#include "encrypt.h"
#include "stringlist.h"
#include "3des.h"
#include "sbdes.h"

#include <vector>

#define MAX_Len 260

char* HiRTDB::CEncrypt::m_pszKey = "unpzScGeCInX7XcRM2z+svTK+gegRLhz9KXVbYKJl5boSvVCcfym";

std::string HiRTDB::CEncrypt::stringEncrypt(std::string str)
{
	const char* pszPlain = str.c_str();
	char pszEncrypted[MAX_Len];
	int iPlainLength = strlen(pszPlain);
	int iKeyLength = strlen(m_pszKey);
	int iPos = strlen(pszPlain) % iKeyLength;

	pszEncrypted[0] = char('\0');

	for (int iChar = 0; iChar < iPlainLength; iChar++)
	{
		sprintf_s(pszEncrypted, "%s%03d", pszEncrypted, pszPlain[iChar] ^ m_pszKey[(iChar + iPos) % iKeyLength]);
	}

	return std::string(pszEncrypted);
}

std::string HiRTDB::CEncrypt::stringDecrypt(std::string str)
{
	char pszPlain[MAX_Len];
	const char* pszEncrypted = str.c_str();
	int cchPlain = str.length();
	int iKeyLength = strlen(m_pszKey);
	int iEncryptedLength = strlen(pszEncrypted);
	int iPos = (iEncryptedLength/3) % iKeyLength;

	pszPlain[0] = char('\0');

	int iChar = 0;
	for (; iChar < iEncryptedLength / 3 && iChar < (int) (cchPlain - 1); iChar++)
	{
		int iDigit = pszEncrypted[iChar * 3];
		if (iDigit < '0' || iDigit > '9')
		{
			pszPlain[0] = char('\0');
			return std::string(pszPlain);
		}

		int iNumber = (iDigit - '0') * 100;
		iDigit = pszEncrypted[iChar * 3 + 1];
		if (iDigit < '0' || iDigit > '9')
		{
			pszPlain[0] = char('\0');
			return std::string(pszPlain);
		}

		iNumber += (iDigit - '0') * 10;
		iDigit = pszEncrypted[iChar * 3 + 2];
		if (iDigit < '0' || iDigit > '9')
		{
			pszPlain[0] = char('\0');
			return std::string(pszPlain);
		}

		iNumber += iDigit - '0';
		pszPlain[iChar] = char(iNumber ^ m_pszKey[(iChar + iPos) % iKeyLength]);
	}

	pszPlain[iChar] = char('\0');

	return std::string(pszPlain);
}

std::string HiRTDB::CEncrypt::md5Encrypt(const std::string& data)
{
	Slice::MD5 md5(reinterpret_cast<const unsigned char*>(data.c_str()), static_cast<int>(data.size()));
	std::vector<unsigned char> bytes;
	bytes.resize(16);
	md5.getDigest(reinterpret_cast<unsigned char*>(&bytes[0]));

	std::string str;
	for (int i = 0 ;i < (int)bytes.size() ;i++)
	{
		str.push_back(bytes[i]);
	}

	return str;
}

char* HiRTDB::CEncrypt::encrypt (char* data, char key[8])
{
	//将字符指针转化为字符数组
	char* datavv = data;
	data =(char *) calloc(100,1);
	memcpy(data,datavv,strlen(datavv));
	data[strlen(data)] = '\0';
	//DES加密
	CDesCrypt des ;
	des.encrypt(key,data,1);
	//base64编码
	base.Encode(data);
	char* res =(char *) base.EncodedMessage();
	return res;
};
char* HiRTDB::CEncrypt::decrypt ( char* data,char key[8])
{
	//base64解码
	base.Decode(data);
	char* datares=(char *) base.DecodedMessage();
	//将字符指针转化为字符数组
	char* datarea = datares;
	datares = (char *)malloc(256);
	memcpy(datares,datarea,strlen(datarea));
	datares[strlen(datarea)] = '\0';
	//DES解密
	CDesCrypt des ;
	des.decrypt(key,datares,1);
	return datares;
};

std::string HiRTDB::CEncrypt::get3DesKey(char key1[15],char key2[15])
{
	int i; 
	char key[255]; 
	memset(key, 0, sizeof(key)); 
	for (i = 0; i < 8; i ++) 
	{ 
		key[i] = key1[i]; 
		key[i + 8] = key2[i]; 
	} 
	return std::string(key);
}

std::string HiRTDB::CEncrypt::encrypt3des(const char* data,char key[255] )
{
	char buf[255]; 
	memset(buf, 0, sizeof(buf)); 
	strcpy(buf, data); 

	DoDES(buf, buf, sizeof(data), key, sizeof(key), ENCRYPT); 
	cout<<buf<<endl; 
	return std::string(buf);
}

std::string HiRTDB::CEncrypt::decrypt3des(const char* data,char key[255])
{
	char buf[255]; 
	memset(buf, 0, sizeof(buf)); 
	DoDES(buf, buf, sizeof(data), key, sizeof(key), DECRYPT); 
	cout<<buf<<endl; 
	return std::string(buf);
}
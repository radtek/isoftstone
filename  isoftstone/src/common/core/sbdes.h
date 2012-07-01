#ifndef __DES_H_
#define __DES_H_

#include "escore.h"

//��ͳ�ĵ�Des�����㷨
//�����SBDesEncrypt(char* data)

enum Mode
{ 
	SBENCRYPT,
	SBDECRYPT 
}; 

class LIBCORE_EXPORT CDesCrypt 
{ 
public: 
        // Encrypt/decrypt the data in "data", according to the "key". 
        // Caller is responsible for confirming the buffer size of "data" 
        // points to is 8*"blocks" bytes. 
        // The data encrypted/decrypted is stored in data. 
        // The return code is 1:success, other:failed. 

        BOOL encrypt ( char key[8], char* data, size_t blocks = 1 ); 
        BOOL decrypt ( char key[8], char* data, size_t blocks = 1 );  

        // Encrypt/decrypt any size data,according to a special method. 
        // Before calling yencrypt, copy data to a new buffer with size 
        // calculated by extend. 

        BOOL yencrypt ( char key[8], char* data, int size ); 
        BOOL ydecrypt ( char key[8], char* in, int blocks, int* size = 0 );  
        int extend ( int size ) { return (size/8+1)*8; };  

private: 
        void des(unsigned char* in, unsigned char* out, size_t blocks); 
        void des_block(unsigned char* in, unsigned char* out);  

private: 
        unsigned long KnL[32];
        void deskey(unsigned char key[8], Mode md); 
        void usekey(unsigned long *); 
        void cookey(unsigned long *);  

private: 
        void scrunch(unsigned char *, unsigned long *); 
        void unscrun(unsigned long *, unsigned char *); 
        void desfunc(unsigned long *, unsigned long *);  

private: 
	void ConvertToStr(char* pData, size_t dataLen);
        static unsigned char Df_Key[24]; 
        static unsigned short bytebit[8]; 
        static unsigned long bigbyte[24]; 
        static unsigned char pc1[56]; 
        static unsigned char totrot[16]; 
        static unsigned char pc2[48]; 
        static unsigned long SP1[64]; 
        static unsigned long SP2[64]; 
        static unsigned long SP3[64]; 
        static unsigned long SP4[64]; 
        static unsigned long SP5[64]; 
        static unsigned long SP6[64]; 
        static unsigned long SP7[64]; 
        static unsigned long SP8[64];  
}; 

//���ݿ���ܺ���
//data Ҫ���ܵ��ַ�����Ҫ�� data �������ռ����Ϊ 8 �ı��� +1 ���ֽ�
//�����ַ�������Ϊ 9���� 9 ��� 8 �ı���Ϊ 16����������������ڵ��� 17 �ֽ�
//�ر�ע�⣺���ַ�����ҲҪ���������ռ� 9 �ֽ�
//���ܷ��ص����ݷ���ԭ����
//����ֵΪTRUE--���ܳɹ���FALSE---����ʧ��
BOOL LIBCORE_EXPORT SBDesEncrypt(char* data);

BOOL LIBCORE_EXPORT SBDesCrypt(char* data,bool encypt = true);

#endif //__DES_H_2002_1_24_8_30_SUNYONG 

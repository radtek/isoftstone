/*********************************************************************************
 *
 * @file	DES.h
 * @version	1.0
 * @date	2010-7-8
 * @author	������
 *
 * @brief	DES���ܽ���ģ��
 *
 *********************************************************************************/
 // ��Ȩ(C) 2009 - 2010 ��������Ƽ�
 // �Ķ���ʷ
 // ����			����	 �Ķ�����
 // 2010-7-8	������	 �����ļ�
 //================================================================================


#ifndef __HIDaq_DES_H__
#define __HIDaq_DES_H__

#include <string>
#include "escore.h"

class LIBCORE_EXPORT CDES
{
public:
		/** @brief ���캯�� */
         CDES(); 

		 /** @brief �������� */
        ~CDES(); 

        /**
         * @brief ����16��28λ��key
         *
         * @param srcBytes Դ8λ���ַ���(key)
         * @param keyN ���key�����0-1
         *
         * @return ����������private CreateSubKey���������char SubKeys[keyN][16][48]
         */
        void InitializeKey(const char* srcBytes,unsigned int keyN);

    
        /**
         * @brief ����8λ�ַ���
         *
         * @param _srcBytes 8λ�ַ���
         * @param keyN ʹ��Key�����0-1
         *
         * @return ���������ܺ��������private szCiphertext[16]���û�ͨ������Ciphertext�õ�
         */
        void EncryptData(char* _srcBytes,unsigned int keyN);

   
        /**
         * @brief ����16λʮ�������ַ���
         *
         * 
         *
         * @param _srcBytes 16λʮ�������ַ���
         * @param keyN ʹ��Key�����0-1
         *
         * @return ���������ܺ��������private szPlaintext[8]���û�ͨ������Plaintext�õ�
         */
        void DecryptData(char* _srcBytes,unsigned int keyN);

 
        /**
         * @brief �������ⳤ���ַ���
         *
         * @param _srcBytes ���ⳤ���ַ���
         * @param _bytesLength ����
         * @param keyN ʹ��Key�����0-1
         *
         * @return ���������ܺ��������private szFCiphertextAnyLength[8192]���û�ͨ������CiphertextAnyLength�õ�
         */
        void EncryptAnyLength(char* _srcBytes,unsigned int _bytesLength,unsigned int keyN);

    
        /**
         * @brief �������ⳤ��ʮ�������ַ���
         *
         * @param _srcBytes ���ⳤ���ַ���
         * @param _bytesLength ����
         * @param keyN ʹ��Key�����0-1
         *
         * @return ���������ܺ��������private szFPlaintextAnyLength[8192]���û�ͨ������PlaintextAnyLength�õ�
         */
        void DecryptAnyLength(char* _srcBytes,unsigned int _bytesLength, unsigned int keyN);

		//����:Bytes��Bits��ת��,
        //����:���任�ַ���,���������Ż�����ָ��,Bits��������С
		void Bytes2Bits(const char *srcBytes, char* dstBits, unsigned int sizeBits);


		/**
		 * @brief Bits��Bytes��ת��
		 *
		 * @param dstBytes ���任�ַ���
		 * @param srcBits ���������Ż�����ָ��
		 * @param sizeBits 
		 *
		 * @return 
		 */
		void Bits2Bytes(char *dstBytes, char* srcBits, unsigned int sizeBits);


		/**
		 * @brief Int��Bits��ת��
		 *
		 * 
		 *
		 * @param srcByte ���任�ַ���
		 * @param dstBits ���������Ż�����ָ��
		 *
		 * @return 
		 */
		void Int2Bits(unsigned int srcByte, char* dstBits);
		

		/**
		 * @brief Bits��Hex��ת��
		 *
		 * @param dstHex ���任�ַ���
		 * @param srcBits ���������Ż�����ָ��
		 * @param sizeBits Bits��������С
		 *
		 * @return 
		 */
		void Bits2Hex(char *dstHex, char* srcBits, unsigned int sizeBits);
		

		/**
		 * @brief Bits��Hex��ת��
		 *
		 * @param srcHex ���任�ַ���
		 * @param dstBits ���������Ż�����ָ��
		 * @param sizeBits Bits��������С
		 *
		 * @return 
		 */
		void Hex2Bits(char *srcHex, char* dstBits, unsigned int sizeBits);


        /**
         * @brief szCiphertextInBinary��get����
         *
         * @return 
         */
        char* GetCiphertextInBinary();


		/**
		 * @brief szCiphertextInHex��get����
		 *
		 * @return 
		 */
		char* GetCiphertextInHex();

		/**
		 * @brief Ciphertext��get����
		 *
		 * @return 
		 */
		char* GetCiphertextInBytes();


        /**
         * @brief Plaintext��get����
         *
         * @return 
         */
        char* GetPlaintext();


		/**
		 * @brief CiphertextAnyLength��get����
		 *
		 * @return 
		 */
		char* GetCiphertextAnyLength();


        /**
         * @brief PlaintextAnyLength��get����
         *
         * @return 
         */
        char* GetPlaintextAnyLength();

private:
        char szSubKeys[2][16][48];//����2��16��48λ��Կ,��2������3DES
		char szCiphertextRaw[64]; //�������������(64��Bits) int 0,1
		char szPlaintextRaw[64]; //�������������(64��Bits) int 0,1
		char szCiphertextInBytes[8];//����8λ����
        char szPlaintextInBytes[8];//����8λ�����ַ���

		char szCiphertextInBinary[65]; //�������������(64��Bits) char '0','1',���һλ��'\0'
		char szCiphertextInHex[17]; //����ʮ����������,���һλ��'\0'
		char szPlaintext[9];//����8λ�����ַ���,���һλ��'\0'

        char szFCiphertextAnyLength[8192];//���ⳤ������
        char szFPlaintextAnyLength[8192];//���ⳤ�������ַ���

        /**
         * @brief ��������Կ
         *
         * 
         *
         * @param sz_56key ����PC1�任��56λ�������ַ���
         * @param keyN ���ɵ�szSubKeys���0-1
         *
         * @return ��������char szSubKeys[16][48]
         */
        void CreateSubKey(char* sz_56key,unsigned int keyN);


        /**
         * @brief DES�е�F����
         *
         * @param sz_Li ��32λ
         * @param sz_Ri ��32λ
         * @param iKey key���(0-15)
         * @param keyN ʹ�õ�szSubKeys���0-1
         *
         * @return ���ڱ任����32λ
         */
        void FunctionF(char* sz_Li,char* sz_Ri,unsigned int iKey,unsigned int keyN);


        /**
         * @brief IP�任
         *
         * @param _src �������ַ���
         * @param _dst ����������ָ��
         *
         * @return �����ı�ڶ�������������
         */
        void InitialPermuteData(char* _src,char* _dst);


        /**
         * @brief ����32λ������չλ48λ
         *
         * @param _src ԭ32λ�ַ���
         * @param _dst ��չ�������ָ��
         *
         * @return �����ı�ڶ�������������
         */
        void ExpansionR(char* _src,char* _dst);

        /**
         * @brief �����
         *
         * @param szParam1 �����Ĳ����ַ���1
         * @param szParam2 �����Ĳ����ַ���2
         * @param uiParamLength ����������
         * @param szReturnValueBuffer ����������ָ��
         *
         * @return �����ı���ĸ�����������
         */
        void XOR(char* szParam1,char* szParam2, unsigned int uiParamLength, char* szReturnValueBuffer);


        /**
         * @brief S-BOX , ����ѹ��
         *
         * @param _src48 :48λ�������ַ���
         * @param _dst32 ����������ָ��
         *
         * @return 2λ�ַ���
         */
        void CompressFuncS(char* _src48, char* _dst32);


        /**
         * @brief IP��任
         *
         * @param _src ���任�ַ���
         * @param _dst ����������ָ��
         *
         * @return �����ı�ڶ�������������
         */
        void PermutationP(char* _src,char* _dst);

};

#endif  //__HIDaq_DES_H__
 
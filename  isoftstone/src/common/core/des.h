/*********************************************************************************
 *
 * @file	DES.h
 * @version	1.0
 * @date	2010-7-8
 * @author	刘东海
 *
 * @brief	DES加密解密模块
 *
 *********************************************************************************/
 // 版权(C) 2009 - 2010 海信网络科技
 // 改动历史
 // 日期			作者	 改动内容
 // 2010-7-8	刘东海	 创建文件
 //================================================================================


#ifndef __HIDaq_DES_H__
#define __HIDaq_DES_H__

#include <string>
#include "escore.h"

class LIBCORE_EXPORT CDES
{
public:
		/** @brief 构造函数 */
         CDES(); 

		 /** @brief 析构函数 */
        ~CDES(); 

        /**
         * @brief 产生16个28位的key
         *
         * @param srcBytes 源8位的字符串(key)
         * @param keyN 存放key的序号0-1
         *
         * @return 函数将调用private CreateSubKey将结果存于char SubKeys[keyN][16][48]
         */
        void InitializeKey(const char* srcBytes,unsigned int keyN);

    
        /**
         * @brief 加密8位字符串
         *
         * @param _srcBytes 8位字符串
         * @param keyN 使用Key的序号0-1
         *
         * @return 函数将加密后结果存放于private szCiphertext[16]，用户通过属性Ciphertext得到
         */
        void EncryptData(char* _srcBytes,unsigned int keyN);

   
        /**
         * @brief 解密16位十六进制字符串
         *
         * 
         *
         * @param _srcBytes 16位十六进制字符串
         * @param keyN 使用Key的序号0-1
         *
         * @return 函数将解密候结果存放于private szPlaintext[8]，用户通过属性Plaintext得到
         */
        void DecryptData(char* _srcBytes,unsigned int keyN);

 
        /**
         * @brief 加密任意长度字符串
         *
         * @param _srcBytes 任意长度字符串
         * @param _bytesLength 长度
         * @param keyN 使用Key的序号0-1
         *
         * @return 函数将加密后结果存放于private szFCiphertextAnyLength[8192]，用户通过属性CiphertextAnyLength得到
         */
        void EncryptAnyLength(char* _srcBytes,unsigned int _bytesLength,unsigned int keyN);

    
        /**
         * @brief 解密任意长度十六进制字符串
         *
         * @param _srcBytes 任意长度字符串
         * @param _bytesLength 长度
         * @param keyN 使用Key的序号0-1
         *
         * @return 函数将加密后结果存放于private szFPlaintextAnyLength[8192]，用户通过属性PlaintextAnyLength得到
         */
        void DecryptAnyLength(char* _srcBytes,unsigned int _bytesLength, unsigned int keyN);

		//功能:Bytes到Bits的转换,
        //参数:待变换字符串,处理后结果存放缓冲区指针,Bits缓冲区大小
		void Bytes2Bits(const char *srcBytes, char* dstBits, unsigned int sizeBits);


		/**
		 * @brief Bits到Bytes的转换
		 *
		 * @param dstBytes 待变换字符串
		 * @param srcBits 处理后结果存放缓冲区指针
		 * @param sizeBits 
		 *
		 * @return 
		 */
		void Bits2Bytes(char *dstBytes, char* srcBits, unsigned int sizeBits);


		/**
		 * @brief Int到Bits的转换
		 *
		 * 
		 *
		 * @param srcByte 待变换字符串
		 * @param dstBits 处理后结果存放缓冲区指针
		 *
		 * @return 
		 */
		void Int2Bits(unsigned int srcByte, char* dstBits);
		

		/**
		 * @brief Bits到Hex的转换
		 *
		 * @param dstHex 待变换字符串
		 * @param srcBits 处理后结果存放缓冲区指针
		 * @param sizeBits Bits缓冲区大小
		 *
		 * @return 
		 */
		void Bits2Hex(char *dstHex, char* srcBits, unsigned int sizeBits);
		

		/**
		 * @brief Bits到Hex的转换
		 *
		 * @param srcHex 待变换字符串
		 * @param dstBits 处理后结果存放缓冲区指针
		 * @param sizeBits Bits缓冲区大小
		 *
		 * @return 
		 */
		void Hex2Bits(char *srcHex, char* dstBits, unsigned int sizeBits);


        /**
         * @brief szCiphertextInBinary的get函数
         *
         * @return 
         */
        char* GetCiphertextInBinary();


		/**
		 * @brief szCiphertextInHex的get函数
		 *
		 * @return 
		 */
		char* GetCiphertextInHex();

		/**
		 * @brief Ciphertext的get函数
		 *
		 * @return 
		 */
		char* GetCiphertextInBytes();


        /**
         * @brief Plaintext的get函数
         *
         * @return 
         */
        char* GetPlaintext();


		/**
		 * @brief CiphertextAnyLength的get函数
		 *
		 * @return 
		 */
		char* GetCiphertextAnyLength();


        /**
         * @brief PlaintextAnyLength的get函数
         *
         * @return 
         */
        char* GetPlaintextAnyLength();

private:
        char szSubKeys[2][16][48];//储存2个16组48位密钥,第2个用于3DES
		char szCiphertextRaw[64]; //储存二进制密文(64个Bits) int 0,1
		char szPlaintextRaw[64]; //储存二进制密文(64个Bits) int 0,1
		char szCiphertextInBytes[8];//储存8位密文
        char szPlaintextInBytes[8];//储存8位明文字符串

		char szCiphertextInBinary[65]; //储存二进制密文(64个Bits) char '0','1',最后一位存'\0'
		char szCiphertextInHex[17]; //储存十六进制密文,最后一位存'\0'
		char szPlaintext[9];//储存8位明文字符串,最后一位存'\0'

        char szFCiphertextAnyLength[8192];//任意长度密文
        char szFPlaintextAnyLength[8192];//任意长度明文字符串

        /**
         * @brief 生成子密钥
         *
         * 
         *
         * @param sz_56key 经过PC1变换的56位二进制字符串
         * @param keyN 生成的szSubKeys编号0-1
         *
         * @return 将保存于char szSubKeys[16][48]
         */
        void CreateSubKey(char* sz_56key,unsigned int keyN);


        /**
         * @brief DES中的F函数
         *
         * @param sz_Li 左32位
         * @param sz_Ri 右32位
         * @param iKey key序号(0-15)
         * @param keyN 使用的szSubKeys编号0-1
         *
         * @return 均在变换左右32位
         */
        void FunctionF(char* sz_Li,char* sz_Ri,unsigned int iKey,unsigned int keyN);


        /**
         * @brief IP变换
         *
         * @param _src 待处理字符串
         * @param _dst 处理后结果存放指针
         *
         * @return 函数改变第二个参数的内容
         */
        void InitialPermuteData(char* _src,char* _dst);


        /**
         * @brief 将右32位进行扩展位48位
         *
         * @param _src 原32位字符串
         * @param _dst 扩展后结果存放指针
         *
         * @return 函数改变第二个参数的内容
         */
        void ExpansionR(char* _src,char* _dst);

        /**
         * @brief 异或函数
         *
         * @param szParam1 待异或的操作字符串1
         * @param szParam2 待异或的操作字符串2
         * @param uiParamLength 操作数长度
         * @param szReturnValueBuffer 处理后结果存放指针
         *
         * @return 函数改变第四个参数的内容
         */
        void XOR(char* szParam1,char* szParam2, unsigned int uiParamLength, char* szReturnValueBuffer);


        /**
         * @brief S-BOX , 数据压缩
         *
         * @param _src48 :48位二进制字符串
         * @param _dst32 处理后结果存放指针
         *
         * @return 2位字符串
         */
        void CompressFuncS(char* _src48, char* _dst32);


        /**
         * @brief IP逆变换
         *
         * @param _src 待变换字符串
         * @param _dst 处理后结果存放指针
         *
         * @return 函数改变第二个参数的内容
         */
        void PermutationP(char* _src,char* _dst);

};

#endif  //__HIDaq_DES_H__
 
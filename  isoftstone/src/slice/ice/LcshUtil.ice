
#ifndef __LCSH_UTIL_COMMON_ICE__
#define __LCSH_UTIL_COMMON_ICE__


module LCSH
{

	sequence<byte> CByteSeq;


	/**
	*
	* �������Ͷ���
	*
	**/
	enum EDataType
	{
		EnumDataTypeEmpty ,					/**< δ���� */
		EnumDataTypeBool ,					/**< ������ */
		EnumDataTypeByte ,					/**< һ�ֽ����� */
		EnumDataTypeShort ,					/**< ���ֽ����� */
		EnumDataTypeInt ,					/**< ���ֽ����� */
		EnumDataTypeLong ,					/**< ���ֽ����� */
		EnumDataTypeFloat ,					/**< �����ȸ����� */
		EnumDataTypeDouble ,				/**< ˫���ȸ����� */
		EnumDataTypeTime ,					/**< ʱ�� */
		EnumDataTypeString ,				/**< �ַ��� */

		EnumDataTypeBoolSeq,				/** Bool ���Ͷ����� */
		EnumDataTypeByteSeq,				/** Byte ���Ͷ����� */
		EnumDataTypeShortSeq,				/** Short ���Ͷ����� */
		EnumDataTypeIntSeq,				/** Int ���Ͷ����� */
		EnumDataTypeLongSeq,				/** Long ���Ͷ����� */
		EnumDataTypeFloatSeq,				/** Float ���Ͷ����� */
		EnumDataTypeDoubleSeq,				/** Double ���Ͷ����� */

		EnumDataTypeMax	,					/**< ����������Ͷ��� */
	};	
	
	/**
	* �������ʱ��
	*/
	struct Time
	{
		int nSecond;			/** �� */
		short sMillisecond;		/** ���� */
	};
		
	
};

#endif // __LCSH_UTIL_COMMON_ICE__
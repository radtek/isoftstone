
#ifndef __LCSH_UTIL_COMMON_ICE__
#define __LCSH_UTIL_COMMON_ICE__


module LCSH
{

	sequence<byte> CByteSeq;


	/**
	*
	* 数据类型定义
	*
	**/
	enum EDataType
	{
		EnumDataTypeEmpty ,					/**< 未定义 */
		EnumDataTypeBool ,					/**< 开关量 */
		EnumDataTypeByte ,					/**< 一字节整数 */
		EnumDataTypeShort ,					/**< 二字节整数 */
		EnumDataTypeInt ,					/**< 四字节整数 */
		EnumDataTypeLong ,					/**< 八字节整数 */
		EnumDataTypeFloat ,					/**< 单精度浮点数 */
		EnumDataTypeDouble ,				/**< 双精度浮点数 */
		EnumDataTypeTime ,					/**< 时间 */
		EnumDataTypeString ,				/**< 字符串 */

		EnumDataTypeBoolSeq,				/** Bool 类型二进制 */
		EnumDataTypeByteSeq,				/** Byte 类型二进制 */
		EnumDataTypeShortSeq,				/** Short 类型二进制 */
		EnumDataTypeIntSeq,				/** Int 类型二进制 */
		EnumDataTypeLongSeq,				/** Long 类型二进制 */
		EnumDataTypeFloatSeq,				/** Float 类型二进制 */
		EnumDataTypeDoubleSeq,				/** Double 类型二进制 */

		EnumDataTypeMax	,					/**< 最大数据类型定义 */
	};	
	
	/**
	* 带毫秒的时间
	*/
	struct Time
	{
		int nSecond;			/** 秒 */
		short sMillisecond;		/** 毫秒 */
	};
		
	
};

#endif // __LCSH_UTIL_COMMON_ICE__
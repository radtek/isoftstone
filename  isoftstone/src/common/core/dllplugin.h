
#ifndef _DLLMODULE_H_
#define _DLLMODULE_H_

#include "escore.h"
#include <IceUtil/Shared.h>
#include <Ice/DynamicLibrary.h>
#include <string>
#include "llogger.h"

class CDllPlugin : IceUtil::Shared
{
public:

	CDllPlugin()
	{
		m_plugin_Name = "";
	}

	virtual ~CDllPlugin()
	{

	}

	const std::string getsymbolName()
	{
		return m_plugin_Name;
	}

	void setsymbolName(const std::string& symbolName)
	{
		m_plugin_Name = symbolName;
	}

	virtual void load() = 0;

	virtual void unLoad() = 0;

protected:

	std::string m_plugin_Name;
};

typedef IceUtil::Handle < CDllPlugin > CDllPluginPtr;

/*
	常用类型函数指针定义- 根据函数名称定位
*/

typedef CDllPlugin* (*Ptr_getDllPlugin)(const char* plugin);

class LIBCORE_EXPORT  CDllPluginProxy 
{
public:

	static CDllPluginProxy* instance(void);

	void registerdDll( const std::string& dllName )
	{
		IceInternal::DynamicLibraryPtr _dll = new IceInternal::DynamicLibrary();
		if (_dll->load( dllName ))
		{
			m_dllPluginMap.insert(std::make_pair(dllName,_dll));
			HI_LOG4CPLUS_INFO("加载动态库:" << dllName << "成功！！");
		}
		else
		{
			HI_LOG4CPLUS_INFO("加载动态库:" << dllName << "失败！！");
		}
	}

	void addSymbol(const std::string& dllName,const std::string& symbolName)
	{
		if ( getDllPlugin(dllName).get() )
		{
			HI_LOG4CPLUS_INFO("查找动态库:" << dllName << "成功！！");

			IceInternal::DynamicLibraryPtr& _dll = getDllPlugin(dllName) ;
			IceInternal::DynamicLibrary::symbol_type symbol = _dll->getSymbol(symbolName);
			std::string dll_plugin_name = dllName + "_" + symbolName;
			if (symbol)
			{
				m_SymbolMap.insert(std::make_pair(dll_plugin_name,symbol));
				HI_LOG4CPLUS_INFO("加载符号:" << dll_plugin_name << "成功！！");
			}
			else
			{
				HI_LOG4CPLUS_INFO("加载符号:" << dll_plugin_name << "失败！！");
			}
		}
		else
		{
			HI_LOG4CPLUS_INFO("查找动态库:" << dllName << "失败！！");
		}

	}

	IceInternal::DynamicLibraryPtr getDllPlugin(const std::string& dllName)
	{
		if (m_dllPluginMap.find(dllName) == m_dllPluginMap.end())
		{
			registerdDll(dllName);
		}
		return m_dllPluginMap[dllName];
	}

	IceInternal::DynamicLibrary::symbol_type& getSymbol(const std::string& dllName,const std::string& symbolName)
	{
		std::string dll_plugin_name = dllName + "_" + symbolName;
		if (m_SymbolMap.find(dll_plugin_name) == m_SymbolMap.end())
		{
			addSymbol(dllName ,symbolName);
		}
		return m_SymbolMap[dll_plugin_name];
	}

protected:

	std::map<std::string, IceInternal::DynamicLibraryPtr > m_dllPluginMap;
	
	typedef std::map<std::string, IceInternal::DynamicLibraryPtr >::iterator DllIterator;

	//std::vector< CDllPluginPtr > m_Objects;

	//typedef std::vector< CDllPluginPtr >::iterator ObjectIterator;

	std::map<std::string, IceInternal::DynamicLibrary::symbol_type > m_SymbolMap;

	typedef std::map<std::string, IceInternal::DynamicLibrary::symbol_type >::iterator SymbolIterator;

private:

	CDllPluginProxy(){};

	virtual ~CDllPluginProxy(){};

	static CDllPluginProxy* s_dllPlugin;

};

#endif
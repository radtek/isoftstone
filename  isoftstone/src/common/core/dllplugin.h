
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
	�������ͺ���ָ�붨��- ���ݺ������ƶ�λ
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
			HI_LOG4CPLUS_INFO("���ض�̬��:" << dllName << "�ɹ�����");
		}
		else
		{
			HI_LOG4CPLUS_INFO("���ض�̬��:" << dllName << "ʧ�ܣ���");
		}
	}

	void addSymbol(const std::string& dllName,const std::string& symbolName)
	{
		if ( getDllPlugin(dllName).get() )
		{
			HI_LOG4CPLUS_INFO("���Ҷ�̬��:" << dllName << "�ɹ�����");

			IceInternal::DynamicLibraryPtr& _dll = getDllPlugin(dllName) ;
			IceInternal::DynamicLibrary::symbol_type symbol = _dll->getSymbol(symbolName);
			std::string dll_plugin_name = dllName + "_" + symbolName;
			if (symbol)
			{
				m_SymbolMap.insert(std::make_pair(dll_plugin_name,symbol));
				HI_LOG4CPLUS_INFO("���ط���:" << dll_plugin_name << "�ɹ�����");
			}
			else
			{
				HI_LOG4CPLUS_INFO("���ط���:" << dll_plugin_name << "ʧ�ܣ���");
			}
		}
		else
		{
			HI_LOG4CPLUS_INFO("���Ҷ�̬��:" << dllName << "ʧ�ܣ���");
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
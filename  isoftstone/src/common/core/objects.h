
#ifndef __INTERFACE__
#define __INTERFACE__

#include <string>
#include "macro2.h"
#include "escore.h"


class CPostTask;

class LCustomEvent
{
public:

	LCustomEvent(int type )
	{
		m_typeid = type ;
		m_data = NULL;
	}

	// data 必须为外部堆方式分配内存
	LCustomEvent(int type,void * data )
	{
		m_typeid = type ;
		m_data = data;
	}

	virtual ~LCustomEvent()
	{
	}

	int type() const
	{
		return m_typeid;
	}

	void* getData()
	{
		return m_data;
	}

	void setData(void* data)
	{
		m_data = data;
	}

private:

	int m_typeid;

	void * m_data;
};

class CLObject
{

public:

	CLObject()
	{
		m_self_id = 0;
	};

	virtual void customEvent(LCustomEvent* event)
	{
		HI_UNUSEDP(event);
	}
	virtual std::string getObjectName()
	{
		return m_obj_name;
	}

	virtual int getObjectID() 
	{
		return m_self_id;
	}

protected:

	std::string m_obj_name;

	int m_self_id;

};

template <class T>
class CSigleton
{
public:

	static T* instance(void)
	{
		if (s_sigleton == NULL)
		{
			s_sigleton = new T();
		}
		return s_sigleton;
	}

private:

	CSigleton(void)
	{
		m_isDestory = false;
	}

	~CSigleton(void)
	{
		if (!m_isDestory)
		{
			destroy();
		}
	}

	bool m_isDestory;

	static T* s_sigleton;
};

template<class T>
T* CSigleton<T>::s_sigleton = NULL;

#endif
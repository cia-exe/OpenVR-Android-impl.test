#pragma once

#undef  CFLAG_DEBUG
#define CFLAG_DEBUG

#ifdef WIN32
#define __WINDOWS__
#elif WIN64
#define __WINDOWS__
#endif


#ifdef __WINDOWS__
//#define __PRETTY_FUNCTION__ __FUNCTION__
#define __PRETTY_FUNCTION__ __FUNCSIG__
//#include <tchar.h>
#endif

#define __X_FUNCTION__ __FUNCTION__ // for shorter log output

//#include <utils/Trace.h> 
//#undef ATRACE_TAG
//#define ATRACE_TAG ATRACE_TAG_GRAPHICS

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <assert.h>
#include <float.h>
#include <string.h>
#include <limits.h>

//#include <unistd.h> //for usleep() in linux


//#include <exception>
//=================================================================
//void* operator new		( size_t s );
//void* operator new[]	( size_t s );
//void  operator delete	( void *p );
//void  operator delete[] ( void *p );

extern "C" void _TraceFormat( const char *fmt, ... );

//=================================================================

//#ifndef ARRAYSIZE // it works but I don't understand its concept.
//
//// copy from WinNT.h
//template <typename T, size_t N>
//char (*RtlpNumberOf(T (&)[N] ))[N];
//#define RTL_NUMBER_OF_V2(A) (sizeof(*RtlpNumberOf(A)))
//#define ARRAYSIZE(A)    RTL_NUMBER_OF_V2(A)
//
//#endif

//#ifdef ARRAYSIZE
//#undef ARRAYSIZE
//#endif

#define ARRAY_SIZE(A)    (sizeof(A)/sizeof(*A))

// **************************************************************************
void ErrorExit( const char *function ,const char *file, int line);
//void ErrorExit( const char *fmt, ... );

//#define ERROR_EXIT(msg) ErrorExit(__FUNCTION__,msg)
#define ERROR_EXIT() ErrorExit(__PRETTY_FUNCTION__ ,__FILE__,__LINE__)
#define CHECKPOINT() _TraceFormat("****(%p) check %s, line: %d\n",this, __X_FUNCTION__ ,__LINE__)
#define CHECKPOINT_C(id) _TraceFormat("****(%p) check %s, line: %d\n",id, __X_FUNCTION__ ,__LINE__)
#define WARNPOINT() _TraceFormat("!!! **** WARNING %s, line: %d\n",__X_FUNCTION__ ,__LINE__)
#define DEPRECATED() {/*_TraceFormat("**Deprecated %s\n",__PRETTY_FUNCTION__)*/}

#define SAFE_DELETE_PTR(p) {if(p){ /*_TraceFormat("%s:%d del(%p)\n",__X_FUNCTION__ ,__LINE__,p);*/ delete p;} p=0;}
#define SAFE_DELETE_ARR(p) {if(p) delete[] p; p=0;}
#define SAFE_FREE_PTR(p) {if(p) free(p); p=0;}

typedef unsigned long long ntime;
ntime GetCurrentTimeInNanoseconds();

class CheckScope
{
	//char m_strMessage[500]; // consume too many memory.
	const char* m_strFunction;
	int m_iLine;
	const void* m_pObj;
	
public:
	/*CheckScope(const char* message)
	{
		strcpy(m_strMessage,message);		
		ShowEnterMessage();
	}*/

	CheckScope(void* pObj, const char* strFunction, int iLine)
	{		
		m_pObj=pObj;
		m_strFunction=strFunction;
		m_iLine=iLine;
		_TraceFormat("<<(%p) %s:%d\n", m_pObj, m_strFunction,m_iLine);
	}	

	~CheckScope()
	{
		_TraceFormat(">>(%p) %s:%d\n", m_pObj, m_strFunction,m_iLine);		
	}		
};

#define CHECKSCOPE() CheckScope ____checkScope(this, __X_FUNCTION__ ,__LINE__)
#define CHECKSCOPE_C(id) CheckScope ____checkScope((void*)id, __X_FUNCTION__ ,__LINE__)
//#define CHECKSCOPE_MSG(MESSAGE) CheckScope ____checkScope(MESSAGE)

class CheckScopeTime 
{
	//char m_strMessage[500]; // consume too many memory.
	const char* m_strFunction;
	int m_iLine;
	ntime m__time;
	const void* m_pObj;
	
public:

	CheckScopeTime(void* pObj, const char* strFunction, int iLine)
	{		
		m_pObj=pObj;
		m_strFunction=strFunction;
		m_iLine=iLine;		
		//_TraceFormat("<-(%p) %s:%d\n",m_pObj, m_strFunction,m_iLine);
		m__time=GetCurrentTimeInNanoseconds();
	}	

	~CheckScopeTime()
	{
		_TraceFormat("(%p) %s:%d, tm=%6.2f\n", m_pObj, m_strFunction,m_iLine, (GetCurrentTimeInNanoseconds()-m__time)/1000000.0f);
	}		
};

#define CHECKSCOPETIME() CheckScopeTime ____checkScopeTime(this, __X_FUNCTION__ ,__LINE__)
#define CHECKSCOPETIME_C(id) CheckScopeTime ____checkScopeTime(id, __X_FUNCTION__ ,__LINE__)

//#define DEBUG_CHECK_MEM_IDENTICAL
#ifdef DEBUG_CHECK_MEM_IDENTICAL
class CheckMemory
{
protected:

	int* m_p;
	int m_v;

public:
	CheckMemory() : m_p(0){}
	CheckMemory(void* p, size_t sz=0);
	void init(void* p, size_t sz=0);
	void snapshot();
	void checkIdentical(const char* strFunction, int iLine);
};

#define CHECK_MEM_IDENTICAL(m) m.checkIdentical(__PRETTY_FUNCTION__ ,__LINE__)

#else

class CheckMemory
{
public:
	CheckMemory(void* p, size_t sz=0) {};
	void snapshot() {};
};
#define CHECK_MEM_IDENTICAL(m)

#endif


//#define DEBUG_CHECKSCOPEMEM
#ifdef DEBUG_CHECKSCOPEMEM

class CheckScopeMemory
{
	//char m_strMessage[500]; // consume too many memory.
	const char* m_strFunction;
	int m_iLine;	
	const void* m_pObj;

	void* m_pMem;

public:

	CheckScopeMemory(void* pObj, const char* strFunction, int iLine);	

	~CheckScopeMemory();		
};


#define CHECKSCOPEMEM() CheckScopeMemory ____checkScopeMem(this, __X_FUNCTION__ ,__LINE__)
#define CHECKSCOPEMEM_C(id) CheckScopeMemory ____checkScopeMem(id, __X_FUNCTION__ ,__LINE__)

#else

#define CHECKSCOPEMEM()
#define CHECKSCOPEMEM_C(id)

#endif

//extern const TCHAR c_strEmpty[];

class BaseObject
{
private:
	enum _STATE{
		CREATED=0xAA55,
		DESTROYED=0x55AA,
		//UNINITIAL=0xCDCD
	} m_state;

	static unsigned int s_serialNum;
	unsigned int m_serialNum;

	bool m_bLocked;
	const char* m_lockFunctionName;
	int		m_lockLineNo;

public:
	BaseObject(): m_state(CREATED), m_serialNum(s_serialNum++), m_bLocked(false), m_lockFunctionName(""), m_lockLineNo(0) {
		_TraceFormat("obj(%p) sn(%x)\n", this, m_serialNum);
	}

	virtual ~BaseObject(){m_state=DESTROYED;}
	bool IsValid() {return m_state==CREATED;}
	void AssertValid() {
		if(m_state!=CREATED){
			_TraceFormat("!!!!! %s: fail! use an invalid object!!! (s=%X)\n",__PRETTY_FUNCTION__,m_state);
			*((int*) 0xdeaddead) = 0xdeaddead; //suicide and Show CallStack
		}
	}

	unsigned int GetSerialNum() {return m_serialNum;}

	void Lock(const char* _function, int _line)
	{
		//CHECKSCOPE();		
		//_TraceFormat("(%p) %s:%d lock. prev=%s:%d (s=%X)\n",this, _function, _line, m_lockFunctionName, m_lockLineNo, m_state);

		AssertValid();
		if(m_bLocked)
		{
			//CHECKPOINT();			
			_TraceFormat("!!!!!(%p) %s:%d fail to lock. it is locked use by %s:%d (s=%X)\n",this, _function, _line, m_lockFunctionName, m_lockLineNo, m_state);
			*((int*) 0xdeaddead) = 0xdeaddead; //suicide and Show CallStack
		}
		else
		{
			m_bLocked=true;
			m_lockFunctionName=_function;
			m_lockLineNo=_line;
		}

		//usleep(1200); // to easily reproduce race condition.
	}

	void Unlock()
	{
		//CHECKSCOPE();
		AssertValid();
		m_bLocked=false;
	}

	class AutoLock
	{
	private:
		BaseObject* m_pObj;

	public:
		AutoLock(BaseObject* pObj, const char* _function, int _line)
		{			
			pObj->Lock(_function,_line);
			m_pObj=pObj;
		}

		~AutoLock()
		{
			m_pObj->Unlock();
		}
	};

};

#define AUTO_LOCK() AutoLock ____autoLock(this, __X_FUNCTION__ ,__LINE__)


//******************************************************************

#define COMPILER_GCC

//#include "stdafx.h"
#include <openvr.h>
#include <stdint.h> 
#include <android/log.h>


typedef unsigned int uint;
typedef unsigned long ulong;
typedef void* IntPtr;
typedef const char* string;
typedef void(*UnityRenderingEvent)(int eventId);



#define  TAG    "VR"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO,TAG,__VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
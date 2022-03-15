#if defined(WIN32) || defined(WIN64)
#include <windows.h>
#endif

#include "Precomp.h"

#include <stdio.h>
#include <stdarg.h>


#ifdef __ANDROID__
#include <time.h>
#include <android/log.h>

#define  TAG    "VR"

bool g_boDisableOutputDebugString = false;

	// **************************************************************************
	void OutputDebugStringA( const char *pcOutputString )
	{
		if( g_boDisableOutputDebugString )
		{
			static bool boFirstTime = true;
			if( boFirstTime )
			{
				boFirstTime = false;
				__android_log_print( ANDROID_LOG_WARN, TAG, "!!! No debug message will be output!\n" );
			}
			return;
		}

		int priority = ANDROID_LOG_DEBUG;
		if( pcOutputString[0] == '!' )
		{
			if( pcOutputString[1] == '!' && pcOutputString[2] == '!' && pcOutputString[3] == '!' )
				priority = ANDROID_LOG_ERROR;
			else
				priority = ANDROID_LOG_WARN;
		}
		else if( pcOutputString[0] == 'L' && pcOutputString[1] == 'o' && pcOutputString[2] == 'g' )
		{
			switch( pcOutputString[3] )
			{
			case 'e': priority = ANDROID_LOG_ERROR; pcOutputString += 4; break;
			case 'w': priority = ANDROID_LOG_WARN; pcOutputString += 4; break;
			case 'i': priority = ANDROID_LOG_INFO; pcOutputString += 4; break;
			case 'd': priority = ANDROID_LOG_DEBUG; pcOutputString += 4; break;
			case 'v': priority = ANDROID_LOG_VERBOSE; pcOutputString += 4; break;
			}
		}

#ifndef CFLAG_DEBUG
		if(priority!=ANDROID_LOG_WARN && priority!=ANDROID_LOG_ERROR && pcOutputString[0] != '`')
			return;
#endif

		__android_log_write( priority, TAG, pcOutputString );
		//__android_log_print( priority, "HtcCodec", pcOutputString );
		//printf( pcOutputString );
	}
#endif




// **************************************************************************
void _TraceFormat( const char *format, ... )
{
	//CHECKSCOPEMEM_C(0);

	char buf[512];

	va_list ap;
	va_start(ap, format);
	//_vsnprintf_s(buf, _TRUNCATE, format, ap);
	vsnprintf(buf, sizeof(buf), format, ap);
	OutputDebugStringA(buf);
	va_end(ap);
}

//const TCHAR c_strEmpty[]={0,0,0,0,0,0,0,0};

#if(0)

#pragma message("overload operator new")

void* operator new		( size_t s )
{
	//if(rand()%99==0)
	//{
	//	_TraceFormat("**** simulate memory corruption!!! (%d)\n",s);
	//	s-=rand()%32;
	//	if(s<=0) s=1;
	//}
	//_TraceFormat( "::operator new (%d)\n", s );
	return AllocMem( s );
}
void* operator new[]	( size_t s )
{
	//if(rand()%99==0)
	//{
	//	_TraceFormat("**** simulate memory corruption!!! (%d)\n",s);
	//	s-=rand()%32;
	//	if(s<=0) s=1;
	//}

	//_TraceFormat( "::operator new[] (%d)\n", s );
	return AllocMem( s );
}
void  operator delete	( void *p )
{
	//_TraceFormat( "::operator delete (0x%x)\n", (int)p );
	FreeMem(p);
}
void  operator delete[] ( void *p )
{
	//_TraceFormat( "::operator delete[] (0x%x)\n", (int)p );
	FreeMem(p);
}

#endif

// **************************************************************************
void ErrorExit( const char *function ,const char *file, int line)
{
	_TraceFormat("!!!!![Error] %s() in %s:%d\n",function,file,line);	
	*((int*) 0xdeaddead) = 0xdeaddead; //suicide and Show CallStack
	//exit(-444);
}

ntime GetCurrentTimeInNanoseconds()
{
#ifdef __ANDROID__

	timespec t;
	clock_gettime(CLOCK_THREAD_CPUTIME_ID , &t);
	//clock_gettime(CLOCK_REALTIME, &t);
	//CLOCK_MONOTONIC stops when the system is suspended. //CLOCK_BOOTTIME is in ndk-9c
	//Some people felt this was a mistake, and subsequently there have been patches for adding a CLOCK_BOOTTIME clock:

	return (ntime)(t.tv_sec*1000000000ULL) + (ntime)t.tv_nsec;
#else
	return 0;
#endif
}


//======================================================================================
#ifdef DEBUG_CHECK_MEM_IDENTICAL

CheckMemory::CheckMemory( void* p, size_t sz/*=0*/ )
{
	init(p,sz);
}

void CheckMemory::init( void* p, size_t sz/*=0*/ )
{
	char* pByte=(char*)p;
	m_p=(int*) (pByte+sz);
	//m_p=(int*) (pByte+3); //test

	snapshot();
}

void CheckMemory::snapshot()
{
	m_v=*m_p;
}

void CheckMemory::checkIdentical( const char* strFunction, int iLine )
{
	if(*m_p != m_v)
	{
		_TraceFormat("!!!memory is not identical! %s:%d, addr=%p, val=%x --> %x\n", strFunction, iLine, m_p, m_v, *m_p); // even though, It could be normal.
	}
}

#endif



//======================================================================================
#ifdef DEBUG_CHECKSCOPEMEM

CheckScopeMemory::CheckScopeMemory( void* pObj, const char* strFunction, int iLine )
{
	m_pObj=pObj;
	m_strFunction=strFunction;
	m_iLine=iLine;		
	//_TraceFormat("<-(%p) %s:%d\n",m_pObj, m_strFunction,m_iLine);

	m_pMem=malloc((iLine%512)+1);
}

CheckScopeMemory::~CheckScopeMemory()
{
	//_TraceFormat("(%p) %s:%d,\n", m_pObj, m_strFunction,m_iLine);
	free(m_pMem);
	//*((int*) 0xdeaddead) = 0xdeaddead; //suicide and Show CallStack
}
#endif

//======================================================================================
unsigned int BaseObject::s_serialNum=0;

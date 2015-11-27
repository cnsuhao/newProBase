////////////////////////////////////////////////////////////////////////
// Copyright(c) 2011-2014, WuHan GoodGame, All Rights Reserved
// Moudle: GlobalMacro.h
// Author: ≈ÌŒƒ∆Ê(Peng Wenqi)
// Created: 2015-1-9
////////////////////////////////////////////////////////////////////////
#ifndef _JYP_MACRO_H_
#define _JYP_MACRO_H_

#ifndef IN
#define IN
#endif

#ifndef OUT
#define OUT
#endif

#define	CHECK(x)					do{ if(!(x))	{ cocos2d::log("%s(%u): CHECK(%s)",		__FILE__, __LINE__, #x);		return;		} }while(0)
#define	CHECKF(x)					do{ if(!(x))	{ cocos2d::log("%s(%u): CHECKF(%s)",	__FILE__, __LINE__, #x);		return 0;	} }while(0)
#define	CHECKF1(x)					do{ if(!(x))	{ cocos2d::log("%s(%u): CHECKF1(%s)",	__FILE__, __LINE__, #x);		return 1;	} }while(0)
#define	CHECKC(x)					if(!(x))		{ cocos2d::log("%s(%u): CHECKC(%s)",	__FILE__, __LINE__, #x);		continue;	}
#define	CHECKBK(x)					if(!(x))		{ cocos2d::log("%s(%u): CHECKBK(%s)",	__FILE__, __LINE__, #x);		break;		}
#define	CHECKB(x)					if(!(x))		{ cocos2d::log("%s(%u): CHECKB(%s)",	__FILE__, __LINE__, #x);		}

#define	CHECK_NOLOG(x)				do{ if(!(x))	{return;}	}while(0)
#define	CHECKF_NOLOG(x)				do{ if(!(x))	{return 0;} }while(0)
#define	CHECKF1_NOLOG(x)			do{ if(!(x))	{return 1;} }while(0)
#define	CHECKC_NOLOG(x)				if(	!(x))		{continue;}
#define	CHECKBK_NOLOG(x)			if(	!(x))		{break;}
#define	CHECKB_NOLOG(x)				if(	!(x))		{}

#define	DEAD_LOOP_BREAK(x,n)		{ if(++(x) > (n)){ LogSave("DEAD_LOCK_BREAK"); break; } }
#define	IF_NOT(x)					if( !(x) ? ( cocos2d::log("%s(%u): IF_NOT(%s)", __FILE__, __LINE__, #x), 1 ) : 0 )
#define	IF_OK(x)					if( (x) ? 1 : ( cocos2d::log("%s(%u): IF_OK(%s)", __FILE__, __LINE__, #x), 0 ) )

// ±‡“ÎÃ· æ∫Í
#define STRING2(x) #x
#define STRING(x) STRING2(x)
#define PRAGMAMSG(x) __FILE__ "(" STRING(__LINE__) ") : " #x " ##########"


#define LogSave(x, ...)				cocos2d::log("%s(%u): "#x, __FILE__, __LINE__, ##__VA_ARGS__)

#endif // end of _JYP_MACRO_H_

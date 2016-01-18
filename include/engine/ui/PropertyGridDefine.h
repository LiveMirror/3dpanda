//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/29 18:05:49_
// 描述:  
//

#ifndef _PROPERTYGRIDDEFINE_2014529180549_
#define _PROPERTYGRIDDEFINE_2014529180549_

#include "Event.h"
#include "base/Config.h"
#include "base/Vector3D.h"
#include "base/Color.h"

namespace panda
{
	template<typename T, typename P>
	class AttrDelegate
	{
		typedef void(T::*SetFun)(P);
		typedef P(T::*GetFun)(void)const;
	public:
		AttrDelegate(T* pRecver, SetFun pSetFun, GetFun pGetFun)
		{
			_this = pRecver;
			_setfun = pSetFun;
			_getfun = pGetFun;
		}

		void	CallSetFun(P v)
		{
			(_this->*_setfun)(v);
		}

		P		CallGetFun(void)
		{
			return (_this->*_getfun)();
		}
	public:
		T*			_this;
		SetFun		_setfun;
		GetFun		_getfun;
	};

	// 定义属性
	template<typename P>
	class PropertyAttr{};

	template<>
	class PropertyAttr<s32>
	{
	public:
		typedef AttrDelegate<BaseNoUse,s32> FunDelegate;
		~PropertyAttr(void)
		{
			delete mFun;
		}
		template<typename T>
		void	InitAttr(T* pRecever, void(T::*SetFun)(s32), s32(T::*GetFun)(void)const)
		{
			mFun = (FunDelegate*)(new AttrDelegate<T, s32>(pRecever, SetFun, GetFun));
		}

		void	ToString(tstring& outStr)
		{
			s32 v = mFun->CallGetFun();
			StringUtils::S32ToStr(v, outStr);
		}

		void	SetValue(const tstring& valueStr)
		{
			s32 v = StringUtils::StrToS32(valueStr.c_str());
			mFun->CallSetFun(v);
		}

		FunDelegate*	mFun;
	};

	template<>
	class PropertyAttr<f32>
	{
	public:
		typedef AttrDelegate<BaseNoUse,f32> FunDelegate;
		~PropertyAttr(void)
		{
			delete mFun;
		}
		template<typename T>
		void	InitAttr(T* pRecever, void(T::*SetFun)(f32), f32(T::*GetFun)(void)const)
		{
			mFun = (FunDelegate*)(new AttrDelegate<T, f32>(pRecever, SetFun, GetFun));
		}

		void	ToString(tstring& outStr)
		{
			f32 v = mFun->CallGetFun();
			StringUtils::F32ToStr(v, outStr, 2);
		}

		void	SetValue(const tstring& valueStr)
		{
			f32 v = StringUtils::StrToF32(valueStr.c_str());
			mFun->CallSetFun(v);
		}

		FunDelegate*	mFun;
	};

	template<>
	class PropertyAttr<const Vector3Df&>
	{
	public:
		typedef AttrDelegate<BaseNoUse,const Vector3Df&> FunDelegate;
		~PropertyAttr(void)
		{
			delete mFun;
		}
		template<typename T>
		void	InitAttr(T* pRecever, void(T::*SetFun)(const Vector3Df&), const Vector3Df&(T::*GetFun)(void)const)
		{
			mFun = (FunDelegate*)(new AttrDelegate<T, const Vector3Df&>(pRecever, SetFun, GetFun));
		}

		void	ToString(tstring& outStr)
		{
			const Vector3Df& v = mFun->CallGetFun();
			tstring temp;
			StringUtils::F32ToStr(v.x, temp, 2);
			outStr = temp;

			StringUtils::F32ToStr(v.y, temp, 2);
			outStr += _T(", ");
			outStr += temp;

			StringUtils::F32ToStr(v.z, temp, 2);
			outStr += _T(", ");
			outStr += temp;
		}

		void	SetValue(const tstring& valueStr)
		{
			Vector3Df v;
			tstring vStr;
			tstring temp = valueStr;
			s32 index = temp.find(_T(','));
			if(index > 0)
			{
				vStr = temp.substr(0, index);
				v.x = StringUtils::StrToF32(vStr.c_str());
				temp = temp.substr(index + 1);
			}
			index = temp.find(_T(','));
			if(index > 0)
			{
				vStr = temp.substr(0, index);
				v.y = StringUtils::StrToF32(vStr.c_str());
				vStr = temp.substr(index + 1);
				v.z = StringUtils::StrToF32(vStr.c_str());
			}

			mFun->CallSetFun(v);
		}

		FunDelegate*	mFun;
	};

	template<>
	class PropertyAttr<const Colorf&>
	{
	public:
		typedef AttrDelegate<BaseNoUse,const Colorf&> FunDelegate;
		~PropertyAttr(void)
		{
			delete mFun;
		}
		template<typename T>
		void	InitAttr(T* pRecever, void(T::*SetFun)(const Colorf&), const Colorf&(T::*GetFun)(void)const)
		{
			mFun = (FunDelegate*)(new AttrDelegate<T, const Colorf&>(pRecever, SetFun, GetFun));
		}

		void	ToString(tstring& outStr)
		{
			const Colorf& v = mFun->CallGetFun();
			tstring temp;
			StringUtils::F32ToStr(v.r, temp, 2);
			outStr = temp;

			StringUtils::F32ToStr(v.g, temp, 2);
			outStr += _T(", ");
			outStr += temp;

			StringUtils::F32ToStr(v.b, temp, 2);
			outStr += _T(", ");
			outStr += temp;

			StringUtils::F32ToStr(v.a, temp, 2);
			outStr += _T(", ");
			outStr += temp;
		}

		void	SetValue(const tstring& valueStr)
		{
			Colorf v;
			tstring vStr;
			tstring temp = valueStr;
			s32 index = temp.find(_T(','));
			if(index > 0)
			{
				vStr = temp.substr(0, index);
				v.r = StringUtils::StrToF32(vStr.c_str());
				temp = temp.substr(index + 1);
			}
			index = temp.find(_T(','));
			if(index > 0)
			{
				vStr = temp.substr(0, index);
				v.g = StringUtils::StrToF32(vStr.c_str());
				temp = temp.substr(index + 1);
			}
			index = temp.find(_T(','));
			if(index > 0)
			{
				vStr = temp.substr(0, index);
				v.b = StringUtils::StrToF32(vStr.c_str());
				vStr = temp.substr(index + 1);
				v.a = StringUtils::StrToF32(vStr.c_str());
			}

			mFun->CallSetFun(v);
		}

		FunDelegate*	mFun;
	};

	template<>
	class PropertyAttr<bool>
	{
	public:
		typedef AttrDelegate<BaseNoUse,bool> FunDelegate;
		~PropertyAttr(void)
		{
			delete mFun;
		}
		template<typename T>
		void	InitAttr(T* pRecever, void(T::*SetFun)(bool), bool(T::*GetFun)(void)const)
		{
			mFun = (FunDelegate*)(new AttrDelegate<T, bool>(pRecever, SetFun, GetFun));
		}

		void	ToString(tstring& outStr)
		{
			bool v = mFun->CallGetFun();
			if(v)
			{
				outStr = _T("true");
			}
			else
			{
				outStr = _T("false");
			}
		}

		void	SetValue(const tstring& valueStr)
		{
			bool v = false;
			if(valueStr == _T("true"))
			{
				v = true;
			}
			mFun->CallSetFun(v);
		}

		FunDelegate*	mFun;
	};

	template<>
	class PropertyAttr<const tstring&>
	{
	public:
		typedef AttrDelegate<BaseNoUse,const tstring&> FunDelegate;
		~PropertyAttr(void)
		{
			delete mFun;
		}
		template<typename T>
		void	InitAttr(T* pRecever, void(T::*SetFun)(const tstring&), const tstring&(T::*GetFun)(void))
		{
			mFun = (FunDelegate*)(new AttrDelegate<T, const tstring&>(pRecever, SetFun, GetFun));
		}

		void	ToString(tstring& outStr)
		{
			outStr = mFun->CallGetFun();
		}

		void	SetValue(const tstring& valueStr)
		{
			mFun->CallSetFun(valueStr);
		}

		FunDelegate*	mFun;
	};
}

#endif // _PROPERTYGRIDDEFINE_2014529180549_
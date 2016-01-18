////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-16 22:46:48
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014416224648_H_
#define	_Tian_2014416224648_H_

#include "IPanda.h"
#include "ILevel.h"
using namespace panda;

namespace editor
{
	typedef Event<void(ILevel*)>				EventLevel;
	typedef Event<void(Resource)>				EventRes;
	typedef Event<void(const tstring&)>			EventString;
}

#endif _Tian_2014416224648_H_
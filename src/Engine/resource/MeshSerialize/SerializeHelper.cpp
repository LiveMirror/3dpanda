#include "SerializeHelper.h"

namespace panda
{
	void SerializeHelper::ReadString( FileStream& file, tstring& outStr )
	{
		char buf;
		
		char cnChar[2];
		wchar_t wChar[2];
		wChar[1] = 0;
		int index = 0;
		while (file.Read(&buf, 1))
		{
			if(buf == '\0' || buf == '\n')
			{
				return;
			}
			u8 b = buf & 0x80;
			if(b > 0)
			{
				cnChar[index] = buf;
				if(1 == index)
				{
					MultiByteToWideChar(CP_ACP, 0, cnChar, 2, wChar, 2);
					outStr += wChar;
					index = 0;
				}
				else
				{
					index++;
				}
			}
			else
			{
				outStr += buf;
			}
		}
	}

	void SerializeHelper::Narrow2wide( const char* mbstr, s32 cSizeMbs, std::wstring& vcstr )
	{
		// check parameters
		if ( NULL == mbstr || !cSizeMbs )
		{
			return;
		}
		wchar_t* pBuf = new wchar_t[cSizeMbs+1];
		s32 c = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, mbstr, cSizeMbs, pBuf, cSizeMbs + 1);
		pBuf[c] = 0;
		vcstr = pBuf;
		delete[] pBuf;
	}
}
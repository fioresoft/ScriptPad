#pragma once
#include <Windows.h>
#include <string>
inline CStringW utf8_to_wide_char(const char* utf8)
{
	CStringW s;
	int lenW = MultiByteToWideChar(CP_UTF8, 0, utf8, -1, NULL, 0);
	LPWSTR buf = s.GetBufferSetLength(lenW + 1);
	buf[0] = L'\0';
	MultiByteToWideChar(CP_UTF8, 0, utf8, -1, buf, lenW+1);
	s.ReleaseBuffer();
	return s;
}
inline CStringA wide_to_utf8_char(LPCWSTR wide)
{
	int len8 = WideCharToMultiByte(CP_UTF8, 0, wide, -1, 0, 0,NULL,NULL);
	CStringA s;
	LPSTR p = s.GetBufferSetLength(len8 + 1);
	WideCharToMultiByte(CP_UTF8, 0, wide, -1, s.GetBuffer(), len8 + 1, NULL, NULL);
	s.ReleaseBuffer();
	return s;
}
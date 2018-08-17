#ifndef LICSTRUCTH
#define LICSTRUCTH
#include <vcl.h>

struct _SerLic{
	wchar_t ToolName[40];
	wchar_t Version[20];
	bool Lock;
};

struct _Lic{
	wchar_t ToolName[40];
	wchar_t ValidityDate[20];
	wchar_t Version[20];
	int ValidityUseCount;
};
#endif

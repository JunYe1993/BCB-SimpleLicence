#ifndef CHECKERH
#define CHECKERH

#include "LicStruct.h"
class Checker
{
private:
	void __fastcall CheckServerLic(String ToolName, String version£®);
	void __fastcall CheckDataFormat(_Lic *LoadLic);
	void __fastcall CheckDataValid(_Lic *LoadLic);
	void __fastcall LicError(String msg, bool quit);
public:
	void __fastcall Check();
};

#endif

#include "Checker.h"
#include "JunYeClass.h"


void __fastcall Checker::CheckDataFormat(_Lic *LoadLic){
	if(LoadLic->ToolName[0] == NULL){
		LicError("License ToolName Data Error!!!", true);
	}else{
		for(int i = 0; i < 40; i++)
			LoadLic->ToolName[i] = LoadLic->ToolName[i]^0xA;
	}
	try{
		StrToDate(LoadLic->ValidityDate);
	}catch(...){
		LicError("License Date Data Error!!!", true);
	}
	String ver = LoadLic->Version;
	if(ver.ToDouble() < 0 || ver.Length() > 6){
		LicError("License Version Data Error!!!", true);
	}
	if(LoadLic->ValidityUseCount < 0){
		LicError("License ValidityUseCount Data Error!!!", true);
	}
}
void __fastcall Checker::CheckDataValid(_Lic *LoadLic){
	TDateTime date = StrToDate(LoadLic->ValidityDate);
	if(double(date)-double(Now()) < 0){
		LicError("Expired License!!!", true);
	}
	if(LoadLic->ValidityUseCount == 0){
		LicError("Usage Max Count is reached!!!", true);
	}else{
		LoadLic->ValidityUseCount--;
	}
}
void __fastcall Checker::CheckServerLic(String ToolName, String version){
	FILE *file;
	struct _SerLic SerLic;

	String path = "\\\\We1-filesrv\\License\\"+ToolName+".lic";
	if(!FileExists(path)){
		LicError("無法與Server連線確認軟體版本，請注意是否使用最新版本!!!", false);
	}else{
		AnsiString temp = path;
		file = fopen(temp.c_str(),"rb");
		fseek(file,sizeof(SerLic)*0,SEEK_SET);
		fread(&SerLic,sizeof(SerLic),1,file);
		fclose(file);

		String ser_ver = SerLic.Version;
		if(ser_ver != version){
			LicError("當前軟體版本非最新版本!!!", false);
		}
		if(SerLic.Lock){
            LicError("此軟體已被 Server 封鎖!!!", true);
		}
	}
}
void __fastcall Checker::LicError(String msg, bool quit){
	int icon = 48;
	if(quit)icon = 16;
	Application->MessageBox( msg.w_str() ,L"Warning",0+icon);
	if(quit)Application->Terminate();
}
void __fastcall Checker::Check(){
	FILE *file;
	struct _Lic LoadLic;
	memset(LoadLic.ToolName,0,40);
	memset(LoadLic.ValidityDate,0,20);
	memset(LoadLic.Version,0,20);

	String path = ExtractFilePath(Application->ExeName)+"License.lic";
	if(!FileExists(path)){
		LicError("License not found!!!", true);
	}else{
		AnsiString temp = path;
		file = fopen(temp.c_str(),"rb");
		fseek(file,sizeof(LoadLic)*0,SEEK_SET);
		fread(&LoadLic,sizeof(LoadLic),1,file);
		fclose(file);

		CheckDataFormat(&LoadLic);
        //Common *cc;cc->BugReport(LoadLic.ToolName);
		CheckDataValid(&LoadLic);
		String ver = LoadLic.Version;
		CheckServerLic(LoadLic.ToolName, ver);

		file = fopen(temp.c_str(),"wb");
		for(int i = 0; i < 40; i++)LoadLic.ToolName[i] = LoadLic.ToolName[i]^0xA;
		fseek(file,sizeof(LoadLic)*0,SEEK_SET);
		fwrite(&LoadLic,sizeof(LoadLic),1,file);
		fclose(file);
	}
}

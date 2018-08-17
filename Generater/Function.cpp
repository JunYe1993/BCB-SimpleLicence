#include "Main.h"
#include "LicStruct.h"

void __fastcall TMainForm::check_InputValid(){}
void __fastcall TMainForm::generate_LocalLicence(){
    FILE *file;
	String path;
	struct _Lic licence;
	memset(licence.ToolName,0,40);
	memset(licence.ValidityDate,0,20);
	memset(licence.Version,0,20);

	wcscpy(licence.ToolName, ToolName->Text.w_str());
	for(int i = 0; i < 40; i++)licence.ToolName[i] = licence.ToolName[i]^0xA;
	TDateTime date = Now() + StrToInt(ToolValidityDays->Text);
	wcscpy(licence.ValidityDate, DateToStr(date).w_str());
	wcscpy(licence.Version, ToolVersion->Text.w_str());
	licence.ValidityUseCount = StrToInt(ToolUseCount->Text);

	path = ExtractFilePath(Application->ExeName)+"License.lic";
	file = _wfopen(path.w_str(),L"wb");
	fseek(file,sizeof(licence)*0,SEEK_SET);
	fwrite(&licence,sizeof(licence),1,file);
	fclose(file);
}
void __fastcall TMainForm::generate_ServerLicence(){
	FILE *file;
	String path;
	struct _SerLic licence;
	memset(licence.ToolName,0,40);
	memset(licence.Version,0,20);

	wcscpy(licence.ToolName, ToolName->Text.w_str());
	wcscpy(licence.Version, ToolVersion->Text.w_str());
	licence.Lock = !(Block->ItemIndex);

	path = ExtractFilePath(Application->ExeName)+ToolName->Text+".lic";
	file = _wfopen(path.w_str(),L"wb");
	fseek(file,sizeof(licence)*0,SEEK_SET);
	fwrite(&licence,sizeof(licence),1,file);
	fclose(file);
}
